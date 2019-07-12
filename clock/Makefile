CFLAGS += -Ofast -march=native -mtune=native
CFLAGS += -std=c1x -Wall -Wextra -Wno-unused-parameter
CFLAGS += $(shell pkg-config --cflags gtk+-3.0)
CFLAGS += $(shell pkg-config --cflags cairo)
LIBS += $(shell pkg-config --libs gtk+-3.0)
LIBS += $(shell pkg-config --libs cairo)

all:
	$(CC) $(CFLAGS) clock.c -o clock $(LIBS)
