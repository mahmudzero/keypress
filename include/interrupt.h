#include <stdio.h>
#include <stdbool.h>

struct keypress_handlers {
	void (*w)();
	void (*a)();
	void (*s)();
	void (*d)();
};

void null_keypress_handler ();
void set_keypress_handlers (struct keypress_handlers kh);
struct keypress_handlers get_keypress_handlers ();
int begin_loop ();
