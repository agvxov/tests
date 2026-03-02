/* @BAKE
    gcc -DCSER_SHIM -E player.h | cser -i player.h -o player.cs player_t
    gcc -o $*.out $@ player.cs.c -lraylib -luv -std=c23 -Wall -Wpedantic -O0 -ggdb
   @STOP
*/
#ifdef CSER_SHIM
    #define bool	_Bool
    #define true	1
    #define false	0
#endif

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
/* There is a bug in GNU's pthread.h,
 *  where fails to define pthread_rwlock_t under C23.
 * LibUV depends on pthread_rwlock_t.
 * Bellow is the definition that happens to be correct on my machine at this femtosecond.
 */
typedef union {
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;
#include <uv.h>
#include <raylib.h>

const int W = 600;
const int H = 400;

uv_udp_t peer_socket;
const int port = 5000;

#include "player.cs.h"

player_t player1;
player_t player2;

typedef struct {
  uint8_t *mem;
  uint8_t *end;
  uint8_t *p;
} buf_t;

int cser_raw_write(const uint8_t *bytes, size_t n, void *q) {
    buf_t *b = q;

    if ((b->p + n) >= b->end) { return -1; }
    while (n--) { *b->p++ = *bytes++; }

    return 0;
}

int cser_raw_read(uint8_t *bytes, size_t n, void *q) {
    buf_t *b = q;

    if ((b->p + n) >= b->end) { return -1; }
    while (n--) { *bytes++ = *b->p++; }

    return 0;
}

void control_player(void) {
    const float step = 8.0f;

    if (IsKeyDown(KEY_W)) { player1.y -= step; }
    if (IsKeyDown(KEY_S)) { player1.y += step; }
    if (IsKeyDown(KEY_A)) { player1.x -= step; }
    if (IsKeyDown(KEY_D)) { player1.x += step; }

    /* screen wrap */
    if (player1.x < 0)  { player1.x += W; }
    if (player1.x >= W) { player1.x -= W; }
    if (player1.y < 0)  { player1.y += H; }
    if (player1.y >= H) { player1.y -= H; }
}

void draw_player(void) {
    DrawCircle(player1.x, player1.y, 10, BLUE);
    DrawCircle(player2.x, player2.y, 10, RED);
}

void on_recv(uv_udp_t *req, ssize_t nread, const uv_buf_t *buf,
             const struct sockaddr *addr, unsigned flags) {

    if (nread < 0) {
        TraceLog(LOG_ERROR, "Read error");
        uv_close((uv_handle_t*)req, NULL);
        free(buf->base);
        return;
    }

    if (nread > 0) {
        uint8_t space[256] = { 0 };
        buf_t sbuf = { space, space + sizeof (space), space };
        memcpy(space, buf->base, nread);
        cser_raw_load_player_t(&player2, cser_raw_read, &sbuf);
    }

    free(buf->base);
}

void on_send(uv_udp_send_t* req, int status) {
    if (status < 0) {
        TraceLog(LOG_ERROR, uv_strerror(status));
    }
}

void alloc_cb(uv_handle_t* handle,
              size_t suggested_size,
              uv_buf_t* buf) {
    buf->base = malloc(suggested_size);
    buf->len  = suggested_size;
}

int main(void) {
    InitWindow(W, H, "Raylib - Hello World");
    SetTargetFPS(30);

    uv_udp_init(uv_default_loop(), &peer_socket);

    player1 = (player_t) {
        .x = 100,
        .y = 100,
    };

    player2 = (player_t) {
        .x = -100,
        .y = -100,
    };

    // ---
    int port_offset = 0;
    // Send
    struct sockaddr_in local_addr;
    uv_ip4_addr("0.0.0.0", port + port_offset, &local_addr);
    do {
        int r;
        r = uv_udp_bind(
            &peer_socket,
            (const struct sockaddr*)&local_addr,
            0
        );
        if (r != 0) {
            TraceLog(LOG_ERROR, "uv_udp_bind failed: %s", uv_strerror(r));

            ++port_offset;
            uv_ip4_addr("0.0.0.0", port + port_offset, &local_addr);
            r = uv_udp_bind(
                &peer_socket,
                (const struct sockaddr*)&local_addr,
                0
            );

            if (r != 0) {
                TraceLog(LOG_ERROR, "uv_udp_bind failed: %s", uv_strerror(r));
                return 1;
            } else {
                TraceLog(LOG_INFO, "Secondary bind succeeded.");
            }
        } else {
            TraceLog(LOG_INFO, "Primary bind succeeded.");
        }

        uv_udp_recv_start(&peer_socket, alloc_cb, on_recv);
    } while (0);

    // Recieve
    struct sockaddr_in dest;
    uv_ip4_addr("127.0.0.1", port + 1 - port_offset, &dest);

    uv_udp_send_t send_req;
    // ---

    while (!WindowShouldClose()) {
        control_player();

        do {
            // Send
            uint8_t space[256] = { 0 };
            buf_t sbuf = { space, space + sizeof (space), space };
            cser_raw_store_player_t(&player1, cser_raw_write, &sbuf);

            uv_buf_t buf = uv_buf_init(sbuf.mem, sbuf.p - sbuf.mem);
            uv_udp_send(
                &send_req,
                &peer_socket,
                &buf,
                1,
                (const struct sockaddr*)&dest,
                on_send
            );

            // ---
            uv_run(uv_default_loop(), UV_RUN_NOWAIT);
        } while (0);

      BeginDrawing();
        ClearBackground(RAYWHITE);
        draw_player();
      EndDrawing();
    }

    CloseWindow();
    return 0;
}
