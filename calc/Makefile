#LLDLIBS = $(MUI) $(GLUT) -lGLU -lGL -lXmu -lXi -lXext -lX11 -lm

CFLAGS += $(shell pkg-config --cflags freeglut)
CFLAGS += $(shell pkg-config --cflags x11)
CFLAGS += $(shell pkg-config --cflags xext)
CFLAGS += $(shell pkg-config --cflags xi)
CFLAGS += $(shell pkg-config --cflags xmu)
LIBS += $(shell pkg-config --libs freeglut)
LIBS += $(shell pkg-config --libs x11)
LIBS += $(shell pkg-config --libs xext)
LIBS += $(shell pkg-config --libs xi)
LIBS += $(shell pkg-config --libs xmu)
LIBS += -lm

all: calc

calc: calc.c calc.h
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)
