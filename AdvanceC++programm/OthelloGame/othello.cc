//***************************************************
//Name: 	Zhiqiang Zhang
//Date:		8/14/2013
//Class:    cs2401sum
//Description: game othello :othello class
//***************************************************
#include"othello.h"
#include<iostream>
#include<stdio.h>

namespace main_savitch_14
{

void othello::restart( ){
for(int i = 1;i<9;i++)
		for(int j = 1;j<9;j++){
			pi->flip(i,j,-1);
		}
			pi->flip(4,4,1);
			pi->flip(4,5,2);
			pi->flip(5,4,2);
			pi->flip(5,5,1);
			int i = 0;
	for(int j =0;j<10;j++)
			pi->flip(i,j,0);
			int j =0;
	for(int i = 0;i<10;i++)
			pi->flip(i,j,0);
			 j =9;
	for(int i = 0;i<10;i++)
			pi->flip(i,j,0);
			 i =9;
	for(int j =0;j<10;j++)
			pi->flip(i,j,0);
game::restart();
}


othello::~othello(){
	pice* rm;
	rm = pi;
	delete rm;
}

othello::othello(const othello& other){
	pi = new pice(*other.pi);
}

game* othello::clone() const
{
	 return new othello(*this);
}

void othello::display_status( ) const
{
cout<<endl;
char display = 'A';
int d = 0;
std::cout<<" "<<" "<<"  ";
	for(int i = 0;i<8;i++){
			std::cout<<RED<<"  "<<display<<" ";
			display++;
		}

	for(int j = 0;j<pi->get_h();j++){
		if(d==0)
		 cout<<" ";
		else if(d==9)
		 cout<<"  ";
		else
		std::cout<<RED<<"  "<<d<<RESET;
					d++;
			for(int k = 0;k<pi->get_w();k++){
				if(pi->get_pice(j,k)==2)
					std::cout<<BLACK<<"| @ "<<RESET;
				else if(pi->get_pice(j,k)==1)
					std::cout<<MAGENTA<<"| $ "<<RESET;
				else if(pi->get_pice(j,k)==-1){
					std::cout<<YELLOW<<"|   "<<RESET;
				}
				else if(pi->get_pice(j,k)==0 && k==9)
				{
				    if(j==0 && k==9)
						std::cout<<" ";
					else if(j==9 && k==9)
						std::cout<<" ";
					else
					std::cout<<CYAN<<"|"<<RESET;
				}
				else
				    std::cout<<" ";
			}
		if(j<9){
		
		std::cout<<endl;
		std::cout<<"    +---+---+---+---+---+---+---+---+"<<endl<<RESET;	
		}
		else
		 std::cout<<"   ";
	}
	if(is_game_over( )){
		game::who winner;
		winner=winning();
		if(winner==HUMAN)
			cout<<"HUMAN is win"<<endl;
		else if(winner==COMPUTER)
			cout<<"COMPUTER is win"<<endl;
		else if(winner==NEUTRAL)
			cout<<"This game is draw"<<endl;	
	
	}
}
	
int othello::change(char c)const{
	int d;
	d = int(c-'A');
	d = d+1; 
	return d;
}

int othello::change_int(char c)const{
	int d;
	d = int(c-'0');
	return d;

}

void othello::make_move(const std::string& move){
	int row;
	int col;
	row = change(move[0]);
	col = change_int(move[1]);
		if(next_mover( )==HUMAN)
			filp_piece(col,row,2,1);
		   else
			filp_piece(col,row,1,2);
	
	game::make_move(move);
	is_passing(move);
	}

bool othello::is_game_over( ) const{
int over = 0;
	for(int i = 1; i<9;i++)
		for(int j = 1; j<9;j++){
				if(pi->get_pice(i,j)==-1){
					over++;
			}
		}	
			if(over == 0)
				return true;
			else if(over > 0)
				if(all_legal())
				return true;
}
	
bool othello::is_legal(const std::string& move) const{
	int row;
	int col = 0;
	row = change(move[0]);
	col = change_int(move[1]);
		if(next_mover( )==HUMAN){
		if((row>0&&row<9)&&(col>0&&col<9))
				{
					if(pi->get_pice(col,row)==-1){
							if(check_all_legal(col,row,2,1))
								return true;
								else 
								cout<<"IIgel move, please move again"<<endl;
							}
						
				}
			}
		else{
		if((row>0&&row<9)&&(col>0&&col<9))
				{
					if(pi->get_pice(col,row)==-1){
							if(check_all_legal(col,row,1,2))
								return true;
							}
		}
	}
	
	}
	
bool othello::right_legal(int a,int b,int c,int d)const{
		if(pi->get_pice(a,b+1)==c){
				int i =a;
				for(int j = b+1; pi->get_pice(i,j)!=0&&(pi->get_pice(i,j)!=-1);j++)
					if(pi->get_pice(i,j)==d)
							return true;
		}

		
}
bool othello::left_legal(int a,int b,int c,int d)const{
		if(pi->get_pice(a,b-1)==c){
			int i =a;
			for(int j =b-1;(pi->get_pice(i,j)!=0)&&(pi->get_pice(i,j)!=-1);j--)
					if(pi->get_pice(i,j)==d)
						return true;
		}

}
bool othello::up_legal(int a,int b,int c,int d)const{
		if(pi->get_pice(a-1,b)==c){
			int i = b;
				for(int j = a-1;(pi->get_pice(j,i)!=0)&&(pi->get_pice(j,i)!=-1);j--)
					if(pi->get_pice(j,i)==d)
						return true;
		}

}
bool othello::down_legal(int a,int b,int c,int d)const{
		if(pi->get_pice(a+1,b)==c){
			int i = b;
				for(int j =a+1;(pi->get_pice(j,i)!=0)&&(pi->get_pice(j,i)!=-1);j++)
					if(pi->get_pice(j,i)==d)
						return true;
		
		}

}

bool othello::right_up_legal(int a,int b,int c,int d)const{
		if(pi->get_pice(a-1,b+1)==c){
			int i = a-1;
			int j = b+1;
			for(i = a-1,j=b+1;(pi->get_pice(i,j)!=0)&&(pi->get_pice(i,j)!=-1);i--,j++)
					if(pi->get_pice(i,j)==d)
						return true;
		}

}
bool othello::right_down_legal(int a,int b,int c,int d)const{
		if(pi->get_pice(a+1,b+1)==c){
			int i = a+1;
			int j = b+1;
			for(i=a+1,j=b+1;(pi->get_pice(i,j)!=0)&&(pi->get_pice(i,j)!=-1);i++,j++)
					if(pi->get_pice(i,j)==d)
						return true;
		}

}
bool othello::left_up_legal(int a,int b,int c,int d)const{
		if(pi->get_pice(a-1,b-1)==c){
			int i = a-1;
			int	j = b-1;
				for(i=a-1,j=b-1;(pi->get_pice(i,j)!=0)&&(pi->get_pice(i,j)!=-1);i--,j--)
					if(pi->get_pice(i,j)==d)
						return true;
		}

}
bool othello::left_down_legal(int a,int b,int c,int d)const{
		if(pi->get_pice(a+1,b-1)==c){
			int i = a+1;
			int j = b-1;
			for(i=a+1,j=b-1;(pi->get_pice(i,j)!=0)&&(pi->get_pice(i,j)!=-1);i++,j--)
				if(pi->get_pice(i,j)==d)
					return true;
		}
}



bool othello::check_all_legal(int a,int b, int c,int d)const{
							if(right_legal(a,b,c,d)
							||up_legal(a,b,c,d)
							||down_legal(a,b,c,d)
							||left_legal(a,b,c,d)
							||right_up_legal(a,b,c,d)||
							right_down_legal(a,b,c,d)||
							left_up_legal(a,b,c,d)||
							left_down_legal(a,b,c,d))
								return true;
}




void othello::filp_piece(int a, int b, int c, int d){
	pi->flip(a,b,d);
	if(down_legal(a,b,c,d)){
		for(int i = a+1;pi->get_pice(i,b)!=d;i++)
		pi->flip(i,b,d);
	}
	if(right_legal(a,b,c,d)){
		for(int i = b+1;pi->get_pice(a,i)!=d;i++)
		pi->flip(a,i,d);
	}
	if(up_legal(a,b,c,d)){
		for(int i = a-1;pi->get_pice(i,b)!=d;i--)
		pi->flip(i,b,d);
	}
	if(left_legal(a,b,c,d)){
		for(int i = b-1;pi->get_pice(a,i)!=d;i--)
		pi->flip(a,i,d);
	}
	if(right_up_legal(a,b,c,d)){
		for(int i = a-1,j = b+1;pi->get_pice(i,j)!=d;i--,j++)
		pi->flip(i,j,d);
	}
	if(right_down_legal(a,b,c,d)){
		for(int i = a+1,j=b+1;pi->get_pice(i,j)!=d;i++,j++)
		pi->flip(i,j,d);
	}
	if(left_up_legal(a,b,c,d)){
		for(int i = a-1,j=b-1;pi->get_pice(i,j)!=d;i--,j--)
		pi->flip(i,j,d);
	
	}
	if(left_down_legal(a,b,c,d)){
		for(int i = a+1,j=b-1;pi->get_pice(i,j)!=d;i++,j--)
		pi->flip(i,j,d);
	}
	
	}


void othello::is_passing(std::string pass){
	if(next_mover()==HUMAN){
				if(!human_legal()){
					if(computer_legal()){
					cout<<"HUMAN should pass"<<endl;
					game::make_move(pass);
					}
				}
	}
	else{
				if(!computer_legal()){
					if(human_legal()){
					cout<<"COMPUTER should pass"<<endl;
					game::make_move(pass);
				}
		}
	}
	
}


game::who othello::winning( ) const{
int black = 0;
int white = 0;
			for(int i = 1; i<9;i++)
				for(int j = 1; j<9;j++){
						if(pi->get_pice(i,j)==1)
							black++;
						else if(pi->get_pice(i,j)==2)
							white++;
				}
if(black>white)
	return HUMAN;
else if(black<white)
	return COMPUTER;
else if(black==white)
	return NEUTRAL;

}
bool othello::human_legal()const{
	int legal = 0;
		for(int i = 1; i<9;i++)
			for(int j = 1; j<9;j++){
				if(pi->get_pice(i,j)==-1)
					if(check_all_legal(i,j,2,1))
						legal++;
					}
		if(legal>0)
			return true;
		else
			return false;

}
//human has legal move
bool othello::computer_legal()const{
	int legal = 0;
		for(int i = 1; i<9;i++)
			for(int j = 1; j<9;j++){
				if(pi->get_pice(i,j)==-1)
					if(check_all_legal(i,j,1,2))
						legal++;
					}
		if(legal>0)
			return true;
		else
			return false;

}
//computer has legal move
bool othello::all_legal()const{
	if(!human_legal()&& !computer_legal())
		return true;
}
//both of them have legal moves


void othello::compute_moves(std::queue<std::string>& moves) const{
string cmove="";
char row = 'A';
char col = '1';
	for(col='A';col!='I';col++)
		for(row='1';row!='9';row++)
			{
				cmove="";
				cmove+=col;
				cmove+=row;
			if(is_legal(cmove))
				moves.push(cmove);
			}

}
	
int othello::evaluate( ) const{
	int anwser=0;
//inside location value
	for(int i = 3;i<7;i++)
		for(int j = 3;j<7;j++){
			if(pi->get_pice(i,j)==2)
			anwser+=1;
			else if(pi->get_pice(i,j)==1)
			anwser-=1;
			}
//four conner value
	if(pi->get_pice(1,1)==2)
			anwser+=90;
	if(pi->get_pice(1,8)==2)
			anwser+=90;
	if(pi->get_pice(8,1)==2)
			anwser+=90;
	if(pi->get_pice(8,8)==2)
			anwser+=90;
	if(pi->get_pice(1,1)==1)
			anwser-=90;
	if(pi->get_pice(1,8)==1)
			anwser-=90;
	if(pi->get_pice(8,1)==1)
			anwser-=90;
	if(pi->get_pice(8,8)==1)
			anwser-=90;
//around conner value
	if(pi->get_pice(1,2)==2)
			anwser-=60;
	if(pi->get_pice(2,2)==2)
			anwser-=80;
	if(pi->get_pice(2,1)==2)
			anwser-=60;
	if(pi->get_pice(1,7)==2)
			anwser-=60;
	if(pi->get_pice(2,7)==2)
			anwser-=80;
	if(pi->get_pice(2,8)==2)
			anwser-=60;
	if(pi->get_pice(7,1)==2)
			anwser-=60;
	if(pi->get_pice(7,2)==2)
			anwser-=80;
	if(pi->get_pice(8,2)==2)
			anwser-=60;
	if(pi->get_pice(7,7)==2)
			anwser-=80;
	if(pi->get_pice(7,8)==2)
			anwser-=60;
	if(pi->get_pice(8,7)==2)
			anwser-=60;
	
	
	if(pi->get_pice(2,2)==1)
			anwser+=80;
	if(pi->get_pice(1,2)==1)
			anwser+=60;
	if(pi->get_pice(2,1)==1)
			anwser+=60;
	if(pi->get_pice(1,7)==1)
			anwser+=60;
	if(pi->get_pice(2,7)==1)
			anwser+=80;
	if(pi->get_pice(2,8)==1)
			anwser+=60;
	if(pi->get_pice(7,1)==1)
			anwser+=60;
	if(pi->get_pice(7,2)==1)
			anwser+=80;
	if(pi->get_pice(8,2)==1)
			anwser+=60;
	if(pi->get_pice(7,7)==1)
			anwser+=80;
	if(pi->get_pice(7,8)==1)
			anwser+=60;
	if(pi->get_pice(8,7)==1)
			anwser+=60;
			
//with value
	for(int i = 1,j = 3;j<7;j++)
			if(pi->get_pice(i,j)==2)
			anwser+=10;
			else if(pi->get_pice(i,j)==1)
			anwser-=10;
	for(int j=1,i=3;i<7;i++)
			if(pi->get_pice(i,j)==2)
			anwser+=10;
			else if(pi->get_pice(i,j)==1)
			anwser-=10;
	for(int i = 8,j = 3;j<7;j++)
			if(pi->get_pice(i,j)==2)
			anwser+=10;
			else if(pi->get_pice(i,j)==1)
			anwser-=10;
	for(int i = 3,j = 8;i<7;i++)
			if(pi->get_pice(i,j)==2)
			anwser+=10;
			else if(pi->get_pice(i,j)==1)
			anwser-=10;

//with value
	for(int i = 7,j = 3;j<7;j++)
			if(pi->get_pice(i,j)==2)
			anwser+=5;
			else if(pi->get_pice(i,j)==1)
			anwser-=5;
	
	for(int i = 3,j = 7;i<7;i++)
			if(pi->get_pice(i,j)==2)
			anwser+=5;
			else if(pi->get_pice(i,j)==1)
			anwser-=5;
			
	for(int i = 2,j = 3;j<7;j++)
			if(pi->get_pice(i,j)==2)
			anwser+=5;
			else if(pi->get_pice(i,j)==1)
			anwser-=5;
			
	for(int i = 3,j = 2;i<7;i++)
			if(pi->get_pice(i,j)==2)
			anwser+=5;
			else if(pi->get_pice(i,j)==1)
			anwser-=5;
			
			return anwser;
}


void othello::display_message(const std::string& message) const{
	if(next_mover()==HUMAN){
	cout<<"\nyou are player one, your pice is $"<<endl;
	cout<<"Please enter the pice's location such as \"A3\" "<<endl;
	cout<<"Please enter you move > ";
	}
	/*else{
	cout<<"\nyou are player two, your pice is @"<<endl;
	cout<<"Please enter the pice's location such as \"A3\" "<<endl;
	cout<<"Please enter you move > ";
	
	}*/
}
}

