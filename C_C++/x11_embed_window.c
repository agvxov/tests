//@BAKE gcc $@ -o $*.out -lX11
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

/* $ xdotool search --name "THING" */

int main(int argc, char * argv[]) {
    if (argc < 2) { return 1; }

    int xid;
    sscanf(argv[1], "%d", &xid);

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

    Window child = xid; 

Atom net_wm_type = XInternAtom(d, "_NET_WM_WINDOW_TYPE", False);
Atom net_wm_normal = XInternAtom(d, "_NET_WM_WINDOW_TYPE_NORMAL", False);
XChangeProperty(d, child, net_wm_type, XA_ATOM, 32,
                PropModeReplace, (unsigned char*)&net_wm_normal, 1);


    XReparentWindow(d, child, parent, 0, 0);
    XMapWindow(d, child);
    XFlush(d);

    while (1) XNextEvent(d, &(XEvent){0});
}
