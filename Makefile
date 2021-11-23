CC         = clang
AR         = ar

LIB_PROG    = ./interrupt.o
LIB_FILES   = ./src/interrupt.c
LIB_CFLAGS  = -Wall -Wextra -I./include
LIB_LDFLAGS =

PROG    = main.out
FILES   = ./src/example.c ./interrupt.a
CFLAGS  = -Wall -Wextra -I./include
LDFLAGS =

VERBOSITY = -v

all: lib executable
executable:
	$(CC) $(CFLAGS) $(LDFLAGS) $(VERBOSITY) -o $(PROG) $(FILES)
lib:
	$(CC) $(LIB_FILES) $(LIB_CFLAGS) $(VERBOSITY) -o $(LIB_PROG) -c && \
	$(AR) rc ./interrupt.a ./interrupt.o
clean:
	rm -f ${PROG}
