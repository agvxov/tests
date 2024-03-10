#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>


signed main(){
	/*  struct winsize{
	      unsigned short int ws_row;
	      unsigned short int ws_col;
	      unsigned short int ws_xpixel;
	      unsigned short int ws_ypixel;
	}; */
	struct winsize ws;
	
	int fd = open("/dev/tty", O_WRONLY);
	ioctl(fd, TIOCGWINSZ, &ws);
	close(fd);
	
	printf("%dx%d", ws.ws_col, ws.ws_row);

	return 0;
}
