#***************************************************
#Name: 	Zhiqiang Zhang
#Date:		8/9/2013
#Class:    cs2401sum
#Description: makefile
#***************************************************
mypro: game.o othello.o main.o
	g++ game.o othello.o main.o -o mypro
game.o:game.h game.cc
	g++ -c game.cc
othello.o:othello.h othello.cc colors.h pice.h
	g++ -c othello.cc
main.o:main.cc
	g++ -c main.cc

clean:
	rm game.o
	rm othello.o
	rm main.o
