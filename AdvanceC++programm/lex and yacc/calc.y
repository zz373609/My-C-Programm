/*
 *  calc.y  : Tom Conley
 *
 *  File    : Starter file for LEX/YACC assignment
 *  Author  : Tom Conley, Ohio University
 *  Created : March 31 2015
 *  Version : <none>
 *  
 *  Class   : CS 4100/5100 -- Spring 15
 *
 *    Copyright (c) 2015  Ohio University. All rights reserved.
 *    This program is free software; you can redistribute it and/or
 *    modify it under the same terms as lex itself.
 *
 */
%{
	#include "node.h"
	Node node;

	// prototypes et al 
	int yylex(); 
	void yyerror(const char *p) 
	{ 
		std::cerr << "error:" << (p?p:"unknown") << std::endl; 
	}
	#define P printf
%}

%union 
{
  double ival; 
  char cval;
  class Node * pval;
};

%token <ival> NUMBER MULTIPLIER SQRT
%token <cval> PP
%type  <ival> expr value statement error
%type  <pval> program

%left '|'
%left '&'

%left '+' '-'
%left '*' '/' '%'
%left SQRT
%left UMINUS  // precedence for unary minus

%nonassoc LOWER_THAN_NUMBER
%nonassoc NUMBER
%nonassoc LOWER_THAN_MULTIPLIER
%nonassoc MULTIPLIER
%nonassoc HIGHER_THAN_MULTIPLIER

// Grammars Rule!
%%
program: statement program		{ /* do nothing but allow */ }
| 		 statement 				{ /* multiple statements  */ } 
;

statement: expr ';'       		{ cout << $1 << endl; node.whatever($1); }
;

expr: 	value           		{ $$ = $1; }
| 		expr '*' expr			{ $$ = $1 * $3; }
|      	expr '+' expr 			{ $$ = $1 + $3; }
|       expr '-' expr 			{ $$ = $1 - $3; }
|       expr '/' expr 			{ $$ = $3==0 ? Node::INF : $1 / $3; }
|       '-' expr %prec UMINUS 	{ $$ = -$2; } 
|    	'(' expr ')'  			{ $$ = $2; }
|		SQRT expr 				{ $$ = sqrt($2); }
;

// value: 	NUMBER           		{ $$ = $1; }
// ;

// value: 	NUMBER           { $$ = $1;      P("1 $$ = %d\n", $1); }
// |       value value		 { $$ = $1 + $2; P("2 $$ = %d + %d\n", $1, $2);}
// |       value MULTIPLIER { $$ = $1 * $2; P("3 $$ = %d * %d\n", $1, $2);}
// ;

value: 	NUMBER           %prec NUMBER 					{ $$ = $1;      P("1 $$ = %f\n", $1); }
|       value value		 %prec LOWER_THAN_MULTIPLIER	{ $$ = $1 + $2; P("2 $$ = %f + %f\n", $1, $2);}
|       value MULTIPLIER 								{ $$ = $1 * $2; P("3 $$ = %f * %f\n", $1, $2);}
|       MULTIPLIER 	 value								{ $$ = $1 + $2; P("3 $$ = %f + %f\n", $1, $2);}
|		SQRT value 										{ $$ = sqrt($1);}
;


%%












