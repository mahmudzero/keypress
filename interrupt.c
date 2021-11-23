#include <termios.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

struct termios _base_termios;

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

struct keypress_handlers {
	void (*w)();
	void (*a)();
	void (*s)();
	void (*d)();
};

void null_keypress_handler () {
	printf("Unhandled keypress!\n");
}

int main (int argc, char** argv) {
	struct keypress_handlers kh = {
		null_keypress_handler,
		null_keypress_handler,
		null_keypress_handler,
		null_keypress_handler
	};

	initialize_base_termios();
	termios_no_return();

	while (true) {
		printf("Press any key to continue...\n");
		switch (getchar()) {
			case 'w': kh.w(); break;
			case 'a': kh.a(); break;
			case 's': kh.s(); break;
			case 'd': kh.d(); break;
		}
	}

	reset_termios();
	printf("Try now...\n");
	getchar();

	return 0;
}
