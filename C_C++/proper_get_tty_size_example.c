// @BAKE gcc -o $*.out $@
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

int get_tty_size(int * width_out, int * height_out) {
    struct winsize ws;

    int fd = open("/dev/tty", O_WRONLY);
    if (fd == -1) { return 1; }

    ioctl(fd, TIOCGWINSZ, &ws);
    close(fd);

    *width_out  = ws.ws_col;
    *height_out = ws.ws_row;

    return 0;
}

#include <stdio.h>

signed main(void) {
    int width, height;
    get_tty_size(&width, &height);

    printf("Your terminal size is %dx%d\n", width, height);

    return 0;
}
