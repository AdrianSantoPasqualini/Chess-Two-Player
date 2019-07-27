CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD -Werror=vla
OBJECTS=board.o square.o piece.o player.o main.o
EPENDS=${OBJECTS:.o=.d}
EXEC=chess
${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}

clean:
	rm *.o *.d chess
.PHONY: clean
