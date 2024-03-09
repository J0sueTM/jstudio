#include "./window/window.h"

int main(void) {
  JSWindow *window = js_init_window(800, 600);
  while (window->is_running) {
    js_handle_event(window);
  }

  js_end_window(window);

  return 0;
}
