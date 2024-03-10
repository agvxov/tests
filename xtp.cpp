// @COMPILECMD g++ $@ -o $* -lX11 -lXtst -ggdb
#include <X11/Xlib.h>
#include <stdio.h>

int main() {
    // Open the display
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Unable to open display\n");
        return 1;
    }

    // Get the root window
    Window root = DefaultRootWindow(display);

    // Create a window
    Window window = XCreateSimpleWindow(
        display, root, 100, 100, 400, 300, 2, BlackPixel(display, DefaultScreen(display)), WhitePixel(display, DefaultScreen(display))
    );

    // Set the window title
    XStoreName(display, window, "Xlib Window Example");

    // Select events to listen for
    XSelectInput(display, window, ExposureMask | StructureNotifyMask);

    // Map the window to the screen
    XMapWindow(display, window);

    XEvent event;

    while (1) {
        XNextEvent(display, &event);

        switch (event.type) {
            case Expose:
                // Handle expose events
                printf("Expose event received\n");
                break;
            case ConfigureNotify:
                // Handle window resize or other configuration changes
                printf("Window resized or reconfigured\n");

                // Get the absolute window position
                Window root_return, child_return;
                int root_x, root_y, win_x, win_y;
                unsigned int mask_return;

                if (XTranslateCoordinates(display, window, root, 0, 0, &root_x, &root_y, &child_return)) {
                    printf("Window position: (%d, %d)\n", root_x, root_y);
                } else {
                    fprintf(stderr, "Failed to translate coordinates\n");
                }
                break;
            default:
                break;
        }
    }

    // Close the display
    XCloseDisplay(display);
    return 0;
}
