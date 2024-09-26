# Makefile: Poker
GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`
INC	= $(GTKINC)
LIBS	= $(GTKLIBS)
OPTS	= -g

# Variable
cc = gcc
DEBUG = -g -DDEBUG
CFLAGS = -Wall -std=c11 -pedantic $(DEBUG) -c
LFLAGS = -Wall -std=c11 -pedantic $(DEBUG) -lm

# Targets
all: poker_server poker_client
#all: Poker
TestServer: ServerTest
TestClient: ClientTest
TestGui: GuiTest



######################### Generate object files #######################


Gui.o: Gui.c Gui.h
	gcc -c Gui.c $(INC) $(OPTS) -o Gui.o

Gui: Gui.o
	gcc Gui.o $(LIBS) $(OPTS) -o Gui

GuiTest.o: GuiTest.c GuiTest.h
	gcc -c GuiTest.c $(INC) $(OPTS) -o GuiTest.o

GuiTest: GuiTest.o
	gcc GuiTest.o $(LIBS) $(OPTS) -o GuiTest

poker_client.o: poker_client.c types.h Gui.h
	gcc -c poker_client.c -std=c99 $(OPTS) $(INC) -o poker_client.o


poker_client: poker_client.o Gui.o
	gcc poker_client.o Gui.o $(OPTS) $(LIBS) -o poker_client


poker_server.o: poker_server.c config.c types.h
	gcc -c -lpthread  poker_server.c $(OPTS) -o poker_server.o

config.o: config.c
	gcc -c config.c $(OPTS) -o config.o


poker_server: poker_server.o config.o
	gcc poker_server.o config.o $(OPTS) -lpthread -o poker_server

#Poker: poker_server.o config.o poker_client.o Gui.o
#	gcc poker_server.o config.o poker_client.o Gui.o $(OPTS) $(LIBS) -o Poker
###############################  cleam  ###############################
# Target for clean-up
clean:
	rm -rf *.o Poker ServerTest ClientTest Gui GuiTest
