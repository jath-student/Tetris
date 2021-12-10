CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
OBJECTS = commandhandler.o main.o iBlock.o jBlock.o sBlock.o zBlock.o tBlock.o oBlock.o lBlock.o starBlock.o block.o abslevel.o levelzero.o levelone.o leveltwo.o levelthree.o levelfour.o observer.o subject.o cell.o absboard.o baseboard.o textdisplay.o placedblkinfo.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = main

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

