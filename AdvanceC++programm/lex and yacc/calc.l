/*
 *  calc.l  : Tom Conley
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
    #include <iostream>
    using namespace std;
    #include "calc.tab.hh"
%}

 /*-------- lex options here --------*/ 
%option noyywrap
%option nounput

 /*-------- regex macros here --------*/ 
ws [ \t\n]+

zero        (zero|none|zip|zilch|nada|sweet{ws}fanny)
one         (one|uno|eins|moja|一|(the{ws})?loneliest{ws}number)
two         (two|dos|mbili|swei|二)
three       (three|tre|tatu|drei|三)
fifty       (fiddy|fifty|half{ws}a{ws}buck)


plus        (plus|added({ws}to)?|加)
minus       (minus|take({ws}away)?|减)
sqrt        (the{ws}square{ws}root{ws}of|square{ws}root|sqrt)

operator    ([\*|/\+|\-\(\);])

pp    (\+\+)

what (what{ws}is)?
and  (and)
%%  /*-------- lexer definition begins here --------*/ 

[0-9]+   	{ yylval.ival = atoi(yytext); return NUMBER; }

 /* comment here */
{plus}      { return '+'; }
{minus}     { return '-'; }

{operator}  { return yytext[0]; }

{zero}      { 
                yylval.ival = 0; 
                return(NUMBER); 
            }

{one}       { 
                yylval.ival = 1; 
                return(NUMBER); 
            }
{two}       { 
                yylval.ival = 2; 
                return(NUMBER); 
            }
{three}     { 
                yylval.ival = 3; 
                return(NUMBER); 
            }
{pp}        {
                return (PP);
            }

times		{ yylval.cval = '*'; return '*'; }
{sqrt}      { return SQRT; }
four        {yylval.ival = 4; return(NUMBER);}
five        { yylval.ival = 5; return(NUMBER); }
six         { yylval.ival = 6; return(NUMBER); }
seven       { yylval.ival = 7; return(NUMBER); }
eight       { yylval.ival = 8; return(NUMBER); }
nine        { yylval.ival = 9; return(NUMBER); }
ten         { yylval.ival = 10; return(NUMBER); }
eleven      { yylval.ival = 11; return(NUMBER); }
twelve      { yylval.ival = 12; return(NUMBER); }
thirteen    { yylval.ival = 13; return(NUMBER); }
fourteen    { yylval.ival = 14; return(NUMBER); }
fifteen     { yylval.ival = 15; return(NUMBER); }
sixteen     { yylval.ival = 16; return(NUMBER); }
seventeen   { yylval.ival = 17; return(NUMBER); }
eighteen    { yylval.ival = 18; return(NUMBER); }
nineteen    { yylval.ival = 19; return(NUMBER); }

twenty      { yylval.ival = 20; return NUMBER; }
thirty      { yylval.ival = 30; return NUMBER; }
forty       { yylval.ival = 40; return NUMBER; }
fifty       { yylval.ival = 50; return NUMBER; }
sixty       { yylval.ival = 60; return NUMBER; }
seventy     { yylval.ival = 70; return NUMBER; }
eighty      { yylval.ival = 80; return NUMBER; }
ninety      { yylval.ival = 90; return NUMBER; }
hundred     { yylval.ival = 100; return MULTIPLIER; }
thousand    { yylval.ival = 1000; return MULTIPLIER; }
million     { yylval.ival = 1000000; return MULTIPLIER; }

{what}      {/* ignore */ }
{ws} 		{ /* ignore */ }
{and}       {/* ignore */}

.        	{ cerr << "Unrecognized token!" << endl; }

%%