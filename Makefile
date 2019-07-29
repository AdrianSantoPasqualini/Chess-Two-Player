CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD -Werror=vla -I/usr/X11/include/
OBJECTS=board.o square.o piece.o player.o window.o main.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=chess
${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@ -L/usr/X11/lib -lX11
-include ${DEPENDS}

clean:
	rm *.o *.d chess
.PHONY: clean
