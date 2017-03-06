CFLAGS += -std=c1x -O2 -Wall
CFLAGS += $(shell pkg-config --cflags gtk+-3.0)
LIBS += $(shell pkg-config --libs gtk+-3.0)

rgb: rgb.c
	gcc $(CFLAGS) $< -o $@ $(LIBS)
