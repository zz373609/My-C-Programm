/*
name: zhiqiang zhang
class: cs4100
date: 3/17/2015
*/
#ifndef PASOR_H__
#define PASOR_H__

#include <string>

using namespace std;


class pasor{

public:
	pasor();
	void set_everything(string input);
	bool go_to_next();
	string get_pasor();
	int get_pasor_size();
	int expr();
	int term();
	int factor();
	//int variable();
	int& variable();
	string constant();
	string digit();

	static const char* NUM;
	string token;
	int x;
	int y;
	int z;

private:
	string pasor_str;
	int pso_;
	int size;

};

#endif

