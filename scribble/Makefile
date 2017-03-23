CFLAGS += -std=c1x -O2 -Wall
CFLAGS += $(shell pkg-config --cflags gtk+-3.0)
LIBS += $(shell pkg-config --libs gtk+-3.0)

scribble: scribble.c
	gcc $(CFLAGS) $< -o $@ $(LIBS)
