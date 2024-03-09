CC=gcc
X11_LIB=$(pwd)/vendor/x11/include
X11_INC=$(pwd)/vendor/x11/src/.libs

all:
	${CC} -o jstudio src/*.c -lX11 -L${X11_LIB} -I${X11_INC}
