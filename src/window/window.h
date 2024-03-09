#ifndef JS_WINDOW_H
#define JS_WINDOW_H

#include <X11/Xlib.h>
#include <stdbool.h>

typedef struct JSWindow {
  Window x_window;
  Screen *screen;
  Display *display;
  int screen_id;
  Atom atom_wm_delete_window;
  bool is_running;
} JSWindow;

JSWindow *js_init_window(int width, int height);
void js_end_window(JSWindow *window);
void js_handle_event(JSWindow *window);

#endif
