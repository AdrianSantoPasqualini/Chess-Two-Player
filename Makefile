CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD -Werror=vla -lX11
OBJECTS=board.o square.o piece.o player.o window.o main.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=chess
${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o  ${EXEC} ${CXXFLAGS}
-include ${DEPENDS}

clean:
	rm *.o *.d chess
.PHONY: clean
