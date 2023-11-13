%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"                               
%}

%%                                                
"+"					{ return PLUS; }
"-"					{ return MINUS; }
"/"					{ return DIV; }
"*"					{ return MUL; }
"("					{ return LPAREN; }
")"					{ return RPAREN; }
"["					{ return LSQ; }
"]"					{ return RSQ; }
"{"					{ return LBRACE; }
"}"					{ return RBRACE; }
";"					{ return SEMI; }
","					{ return COMMA; }
"="					{ return ASSIGN; }
"=="					{ return EQ; }
"!="                    { return NEQ; }
">"					{ return GT; }
"<"					{ return LT; }
">="					{ return GTEQ; }
"<="					{ return LTEQ; }
"++"					{ return INC; }
"--"					{ return DEC; }
"!"                     { return NOT; }
"for"					{ return FOR; }
[a-zA-Z]+[0-9a-zA-Z]*			{ yylval.lexeme = strdup(yytext); return ID; }
[0-9]+					{ yylval.intValue = atoi(yytext); return INT; }

[ \t\n]					{}
.					{ return yytext[0]; }
<<EOF>>					{ return 0; }
%%                                              

