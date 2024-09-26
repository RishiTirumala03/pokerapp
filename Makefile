all: make

make:
	(cd src/; make; cd ..)
#	cp src/Poker bin/
	cp src/poker_client bin/
#	cp src/poker_client bin/

test:
	(cd src/; make TestServer; ./ServerTest;cd ..)
	(cd src/; make TestClient;./ClientTest; cd ..)
	(cd src/; make TestGui;./GuiTest; cd ..)

test-gui:
	(cd src/; make TestGui;./GuiTest; cd ..)


tar:
	gtar cvzf Poker_Alpha_src.tar.gz README COPYRIGHT INSTALL Makefile bin/ doc/ src/
	gtar cvzf Poker_Alpha.tar.gz README COPYRIGHT INSTALL bin/ doc/Poker_UserManual.pdf
	
clean:
	(cd src/; make clean; cd ..)
	rm *.tar.gz

