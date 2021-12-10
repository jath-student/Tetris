CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -lX11 -I/opt/X11/include
 
OBJECTS = commandhandler.o main.o iBlock.o jBlock.o sBlock.o zBlock.o tBlock.o oBlock.o lBlock.o starBlock.o block.o abslevel.o levelzero.o levelone.o leveltwo.o levelthree.o levelfour.o observer.o subject.o cell.o absboard.o baseboard.o textdisplay.o placedblkinfo.o forcefx.o blindfx.o heavyfx.o boarddecorator.o window.o graphicsdisplay.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = biquadris

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -L/opt/X11/lib -lX11

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

