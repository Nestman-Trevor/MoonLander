###############################################################
# Program:
#     Project 2, Moon Lander
#     Brother Comeau, CS165
# Author:
#     Trevor Nestman
# Summary:
#     This is Moon Lander! I added the speed of x and y on the right.
#
#     Estimated:  0.0 hrs
#     Actual:     0.0 hrs
#       Please describe briefly what was the most difficult part
###############################################################

LFLAGS = -lglut -lGLU

###############################################################
# Programs:
#    moon:         The moon lander game
###############################################################
a.out: ground.o game.o uiInteract.o uiDraw.o point.o velocity.o lander.o
	g++ -o a.out ground.o game.o uiInteract.o uiDraw.o point.o velocity.o lander.o $(LFLAGS)
	tar -j -cf project2.tar makefile *.h *.cpp

###############################################################
# Individual files
#    ground.o      Displays the ground and platform
#    game.o        The moon game
#    uiInteract.o  Handles input events
#    uiDraw.o      Drawing functions
#    point.o       Point class
###############################################################
ground.o: ground.cpp ground.h
	g++ -c ground.cpp

game.o: game.cpp uiDraw.h uiInteract.h point.h ground.h lander.h velocity.h
	g++ -c game.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

velocity.o: point.cpp velocity.h
	g++ -c velocity.cpp

lander.o: velocity.cpp lander.h uiDraw.h
	g++ -c lander.cpp

###############################################################
# General rules
###############################################################
clean:
	rm a.out project2.tar *.o

all:
	a.out
