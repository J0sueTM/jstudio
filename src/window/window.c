#include "./window.h"
#include "../common/log.h"

#include <stdlib.h>

JSWindow *js_init_window(int width, int height) {
  JSWindow *window = (JSWindow *)malloc(sizeof(JSWindow));
  if (!window) {
    log_fatal("failed to allocate new window");

    return NULL;
  }

  window->display = XOpenDisplay(NULL);
  if (!window->display) {
    log_fatal("failed to open display");

    return NULL;
  }

  window->screen = DefaultScreenOfDisplay(window->display);
  window->screen_id = DefaultScreen(window->display);
  window->x_window = XCreateSimpleWindow(
    window->display,
    RootWindowOfScreen(window->screen),
    0, 0, width, height, 1,
    BlackPixel(window->display, window->screen_id),
    WhitePixel(window->display, window->screen_id)
  );
  XClearWindow(window->display, window->x_window);
  XMapRaised(window->display, window->x_window);

  window->atom_wm_delete_window = XInternAtom(
    window->display,
    "WM_DELETE_WINDOW",
    False
  );
  XSetWMProtocols(
    window->display,
    window->x_window,
    &window->atom_wm_delete_window,
    1
  );
  window->is_running = true;

  return window;
}

void js_end_window(JSWindow *window) {
  XDestroyWindow(window->display, window->x_window);
  XCloseDisplay(window->display);
}

void js_handle_event(JSWindow *window) {
  XEvent cur_event;
  if (XPending(window->display) > 0) {
    XNextEvent(window->display, &cur_event);
    if (cur_event.type == ClientMessage) {
      if (cur_event.xclient.data.l[0] == window->atom_wm_delete_window) {
        window->is_running = false;
      }
    } else if (cur_event.type == DestroyNotify) {
      window->is_running = false;
    }
  }
}
