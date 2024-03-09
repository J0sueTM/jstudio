#include <stdio.h>
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

  XEvent evt;
  while (1) {
    XNextEvent(display, &evt);
  }

  XDestroyWindow(display, window);
  XFree(screen);
  XCloseDisplay(display);

  return 0;
}
