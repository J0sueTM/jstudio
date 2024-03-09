#include <stdio.h>
#include <stdbool.h>
#include <X11/Xlib.h>

int main(void) {
  Display *display = XOpenDisplay(NULL);
  if (!display) {
    printf("%s\n", "failed to open display");

    return 1;
  }
  Screen *screen = DefaultScreenOfDisplay(display);
  int dflt_screen_id = DefaultScreen(display);

  Window window = XCreateSimpleWindow(
    display,
    RootWindowOfScreen(screen),
    0, 0, 320, 200, 1,
    BlackPixel(display, dflt_screen_id),
    WhitePixel(display, dflt_screen_id)
  );
  XClearWindow(display, window);
  XMapRaised(display, window);

  Atom atom_wm_delete_window = XInternAtom(
    display,
    "WM_DELETE_WINDOW",
    False
  );
  XSetWMProtocols(display, window, &atom_wm_delete_window, 1);

  XEvent evt;
  bool is_running = true;
  while (is_running) {
    if (XPending(display) > 0) {
      XNextEvent(display, &evt);
      if (evt.type == ClientMessage) {
        if (evt.xclient.data.l[0] == atom_wm_delete_window) {
          is_running = false;
        }
      } else if (evt.type == DestroyNotify) {
        is_running = false;
      }
    }
  }

  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}
