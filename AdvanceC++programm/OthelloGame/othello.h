//***************************************************
//Name: 	Zhiqiang Zhang
//Date:		8/14/2013
//Class:    cs2401sum
//Description: game othello :othello class
//***************************************************
#ifndef OTHELLO_H
#define OTHELLO_H
#include"game.h"
#include"pice.h"
#include "colors.h"
namespace main_savitch_14
{
class othello:public game
{
public:
	othello()
	{
		pi=new pice;
	}
	// Display the status of the current game:
	void display_status( ) const;
	// Have the next player make a specified move:
	void make_move(const std::string& move);
	// Return true if the given move is legal for the next player:
	bool is_legal(const std::string& move) const;
	~othello();
	othello(const othello& other);
	// Return a pointer to a copy of myself:
    game* clone( ) const;
    // Compute all the moves that the next player can make:
    // Evaluate a board position:
	// NOTE: positive values are good for the computer.
	int change(char c)const;
	int change_int(char c)const;
    // Return true if the current game is finished:
    bool is_game_over( ) const;
	void display_message(const std::string& message) const;
	//The fuction is displaying the information and explain how to play this game
	bool right_legal(int a,int b,int c,int d)const;
	//check is legal to right move
	bool up_legal(int a,int b,int c,int d)const;
	//check is legal to up move
	bool down_legal(int a,int b,int c,int d)const;
	//check is legal to down move
	bool left_legal(int a,int b,int c,int d)const;
	//check is legal to left move
	bool right_up_legal(int a,int b,int c,int d)const;
	//check is legal to right_up move
	bool right_down_legal(int a,int b,int c,int d)const;
	//check is legal to right_down move
	bool left_up_legal(int a,int b,int c,int d)const;
	//check is legal to left_up move
	bool left_down_legal(int a,int b,int c,int d)const;
	//check is legal to left_down move
	bool check_all_legal(int a,int b, int c,int d)const;
	//check is legal for all dirction
	void filp_piece(int a, int b, int c,int d);
	//filp the pice
	void restart( );
	//restart the game
	void is_passing(std::string pass);
	//pass the player BUT it is not working, can not find reason
	who winning( ) const;
	//check winner
	bool human_legal()const;
	//check is legal move for human in whole borad
	bool computer_legal()const;
	//check is legal move for computer in whole borad
	bool all_legal()const;
	//check is legal move for both computer and human in whole borad BUT it is not working can not find reason
	void compute_moves(std::queue<std::string>& moves) const;
	
	int evaluate( ) const;
private:
	pice* pi;
};

}

#endif