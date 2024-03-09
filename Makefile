CC=gcc
X11_LIB=./vendor/x11/include
X11_INC=./vendor/x11/src/.libs
SRC=./src/common/*.c ./src/window/*.c ./src/*.c

all:
	${CC} -g -o jstudio ${SRC} -lX11 -L${X11_LIB} -I${X11_INC}
