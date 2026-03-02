// @BAKE gcc -o $*.out $@ -luv -std=c23 -Wall -Wpedantic -ggdb
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

uv_udp_t peer_socket;
const int port = 5000;

void on_recv(
    uv_udp_t *req,
    ssize_t nread,
    const uv_buf_t *buf,
    const struct sockaddr *addr,
    unsigned flags
  ) {

    if (nread < 0) {
        printf("Read error\n");
        uv_close((uv_handle_t*)req, NULL);
        free(buf->base);
        return;
    }

    if (nread > 0) {
        buf->base[nread] = '\0';  // null-terminate
        printf(buf->base);
        puts("");
    }

    free(buf->base);
}

void on_send(uv_udp_send_t* req, int status) {
    if (status < 0) {
        printf(uv_strerror(status));
        puts("");
    }
}

void alloc_cb(uv_handle_t* handle,
              size_t suggested_size,
              uv_buf_t* buf) {
    buf->base = malloc(suggested_size);
    buf->len  = suggested_size;
}

int main(void) {
    uv_udp_init(uv_default_loop(), &peer_socket);

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
            printf("uv_udp_bind failed: %s\n", uv_strerror(r));

            ++port_offset;
            uv_ip4_addr("0.0.0.0", port + port_offset, &local_addr);
            r = uv_udp_bind(
                &peer_socket,
                (const struct sockaddr*)&local_addr,
                0
            );

            if (r != 0) {
                printf("uv_udp_bind failed: %s\n", uv_strerror(r));
                return 1;
            } else {
                printf("Secondary bind succeeded.\n");
            }
        } else {
            printf("Primary bind succeeded.\n");
        }

        uv_udp_recv_start(&peer_socket, alloc_cb, on_recv);
    } while (0);

    // Recieve
    struct sockaddr_in dest;
    uv_ip4_addr("127.0.0.1", port + 1 - port_offset, &dest);

    const char * msg = "hello world";
    uv_buf_t buf = uv_buf_init((char*)msg, strlen(msg));

    uv_udp_send_t send_req;
    // ---

    while (true) {
        // Send
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
    }

    return 0;
}
