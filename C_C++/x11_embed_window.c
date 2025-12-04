//@BAKE gcc $@ -o $*.out -lX11
#include <X11/Xlib.h>

int main() {
    Display *d = XOpenDisplay(0);
    int s = DefaultScreen(d);
    Window parent = XCreateSimpleWindow(
                        d,
                        RootWindow(d, s),
                        100,
                        100,
                        400,
                        300,
                        1,
                        BlackPixel(d, s),
                        WhitePixel(d, s)
    );
    XStoreName(d, parent, "MY CONTAINER");
    XMapWindow(d, parent);
    XFlush(d);

    Window child = 14680066; /* $ xdotool search --name "THING" */
    XReparentWindow(d, child, parent, 0, 0);
    XMapWindow(d, child);
    XFlush(d);

    while (1) XNextEvent(d, &(XEvent){0});
}
