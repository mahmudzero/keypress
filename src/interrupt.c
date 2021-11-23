#include "interrupt.h"
#include <termios.h>

struct termios _base_termios;
struct keypress_handlers _kh = {
	null_keypress_handler,
	null_keypress_handler,
	null_keypress_handler,
	null_keypress_handler
};

void termios_no_return () {
	struct termios info;
	tcgetattr(0, &info);          /* get current terminal attirbutes; 0 is the file descriptor for stdin */
	info.c_lflag &= ~ICANON;      /* disable canonical mode */
	info.c_cc[VMIN] = 1;          /* wait until at least one keystroke available */
	info.c_cc[VTIME] = 0;         /* no timeout */
	tcsetattr(0, TCSANOW, &info); /* set immediately */
}

void reset_termios () {
	tcsetattr(0, TCSANOW, &_base_termios);
}

void initialize_base_termios () {
	tcgetattr(0, &_base_termios);
}

void null_keypress_handler () {
	printf("\nUnhandled keypress!\n");
}

void set_keypress_handlers (struct keypress_handlers kh) {
	_kh = kh;
}

struct keypress_handlers get_keypress_handlers () {
	return _kh;
}

int begin_loop () {
	initialize_base_termios();
	termios_no_return();

	while (true) {
		switch (getchar()) {
			case 'w': _kh.w(); break;
			case 'a': _kh.a(); break;
			case 's': _kh.s(); break;
			case 'd': _kh.d(); break;
			default : null_keypress_handler(); break;
		}
	}

	reset_termios();

	return 0;
}
