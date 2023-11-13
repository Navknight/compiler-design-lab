%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

ONE [0-9]
TWO [0-9][0-9]
THREE [0-9][0-9][0-9]
%%
({ONE},)({THREE},)*({THREE})			{ printf("VALID\n"); }
({TWO},)({THREE},)*({THREE})                    { printf("VALID\n"); }
({THREE},)*({THREE})                    	{ printf("VALID\n"); }
({TWO})						{ printf("VALID\n"); }
({ONE})						{ printf("VALID\n"); }
.*						{ printf("INVALID\n"); }
%%

int main(int argc, char* argv[]){
        if(argc > 1){
                FILE *fp = fopen(argv[1], "r");
                if(!fp)
                        return 1;
                yyin = fp;
                yylex();
                return 0;
        }
}
