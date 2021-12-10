CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
OBJECTS = commandhandler.o test.o iBlock.o jBlock.o sBlock.o zBlock.o tBlock.o oBlock.o lBlock.o block.o abslevel.o levelzero.o levelone.o leveltwo.o levelthree.o levelfour.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = main

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

