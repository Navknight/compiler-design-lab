%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}


%%
((y|z)|x(y|z)|xx(y|z))*xxx((y|z)|(y|z)x|(y|z)xx)*		{ printf("VALID\n");}
.*								{ printf("INVALID\n"); }
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
