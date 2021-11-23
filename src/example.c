#include "interrupt.h"

void handle_w () {
	printf("\nHANDLED W\n");
}

int main (int argc, char** argv) {
	struct keypress_handlers _base_kh = get_keypress_handlers();
	struct keypress_handlers kh = get_keypress_handlers();
	kh.w = handle_w;
	set_keypress_handlers(kh);

	begin_loop();
}
