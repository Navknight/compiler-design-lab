%{
#include <stdio.h>
#include <string.h>
int yylex();
int yyerror(char*);
int eflag = 0;
int label_count = 0;
int temp_count = 0;
char label_g[20];
char temp_g[20];
extern FILE *yyin;

struct I_NODE{
	struct I_NODE *left, *right;
	char token[20];
	char lexeme[20];
	char temp[20];
	char true_label[20];
	char false_label[20];
	char next_label[20];
	int intValue;
};

char *getLabel();
char *getTemp();
%}

%union{
	int intValue;
	char *lexeme;
	struct I_NODE *node;
}

%token PLUS MINUS DIV MUL RPAREN LPAREN LSQ RSQ LBRACE RBRACE SEMI COMMA ASSIGN GT LT GTEQ LTEQ INC DEC FOR EQ NEQ NOT
%token <intValue> INT
%token <lexeme> ID

%type <node> slist assignment var boolean additive multiplicative unary postfix primary constant

%% 
slist:		assignment SEMI {
		$$ = malloc(sizeof(struct I_NODE*));
		if($$ == NULL)
			yyerror("no mem");
		$$ = $1;
	} slist 
	|	FOR LPAREN assignment {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		getLabel();
		strcpy($$->token, "KEYWORD");
		strcpy($$->lexeme, "FOR");
		strcpy($$->next_label, label_g);
		printf("\n%s:\n", $$->next_label);
	} SEMI boolean {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		strcpy($$->token, "KEYWORD");
		strcpy($$->lexeme, "IF ELSE");
		getLabel();
		strcpy($$->true_label, label_g);
		strcpy($6->true_label, label_g);
		getLabel();
		strcpy($$->false_label, label_g);
		strcpy($6->false_label, label_g);
		getLabel();
		strcpy($$->next_label, label_g);
		strcpy($6->next_label, label_g);
		printf("if %s goto %s\n", $6->temp, $$->true_label);
		printf("goto %s\n", $$->false_label);
		printf("\n%s:\n", $$->true_label);
	} SEMI {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		getLabel();
		strcpy($$->next_label, label_g);
		printf("\n%s:\n", $$->next_label);
	} assignment {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		strcpy($$->next_label, $4->next_label);
		printf("\n%s:\n", $$->next_label);
	} RPAREN LBRACE { printf("%s:", $7->true_label); } slist {
		printf("goto %s\n", $9->next_label);
	} RBRACE slist
	|
	| 	error {yyerror("error");};
	;

assignment:	var ASSIGN additive {
	$$ = malloc(sizeof(struct I_NODE));
	if($$ == NULL)
		yyerror("no mem");
	$$->left = $1;
	$$->right = $3;
	$$->intValue = $3->intValue;
	getTemp();
	strcpy($$->temp, temp_g);
	strcpy($$->lexeme,"=");
	strcpy($$->token, "ASSIGN");
	printf("%s = %s\n", $1->temp, $3->temp);
}
    |		var INC {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "++");
		strcpy($$->temp, $1->temp);
		$$->intValue = $1->intValue + 1;
		$$->left = $1;
		$$->right = NULL;
		printf("%s = %s + 1\n", $$->temp, $1->temp);
	}
	|		var DEC {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "--");
		strcpy($$->temp, $1->temp);
		$$->intValue = $1->intValue - 1;
		$$->left = $1;
		$$->right = NULL;
		printf("%s = %s - 1\n", $$->temp, $1->temp);
	}
	|		INC var {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "++");
		strcpy($$->temp, $2->temp);
		$$->intValue = $2->intValue + 1;
		$$->left = NULL;
		$$->right = $2;
		printf("%s = %s + 1\n", $$->temp, $2->temp);
	}
	|		DEC var {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "--");
		strcpy($$->temp, $2->temp);
		$$->intValue = $2->intValue - 1;
		$$->left = NULL;
		$$->right = $2;
		printf("%s = %s - 1\n", $$->temp, $2->temp);
}
;

var:		ID {
	$$ = malloc(sizeof(struct I_NODE));
	if($$ == NULL)
		yyerror("no mem");
	// printf("from var ID production\n");
	strcpy($$->lexeme, $1);
	strcpy($$->token, "ID");
	$$->left = NULL;
	$$->right = NULL;
	getTemp();
	strcpy($$->temp, temp_g);
	printf("%s = %s\n", $$->temp, $$->lexeme);
}
|		LPAREN var RPAREN {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		$$=$2;
}
;

boolean:	primary {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		// printf("from boolean primary production\n");
		$$=$1;}
    |	primary LT primary {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		$$->left = $1;
		$$->right = $3;
		getTemp();
		strcpy($$->temp, temp_g);
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "<");
		$$->intValue = $1->intValue < $3->intValue;
		printf("%s = %s < %s\n", $$->temp, $1->temp, $3->temp);
	}
	|		primary GT primary {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		$$->left = $1;
		$$->right = $3;
		getTemp();
		strcpy($$->temp, temp_g);
		strcpy($$->token, "OP");
		strcpy($$->lexeme, ">");
		$$->intValue = $1->intValue > $3->intValue;
		printf("%s = %s > %s\n", $$->temp, $1->temp, $3->temp);
	}
	|		primary LTEQ primary {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		$$->left = $1;
		$$->right = $3;
		getTemp();
		strcpy($$->temp, temp_g);
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "<=");
		$$->intValue = $1->intValue <= $3->intValue;
		printf("%s = %s <= %s\n", $$->temp, $1->temp, $3->temp);
	}
	| 		primary GTEQ primary {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		$$->left = $1;
		$$->right = $3;
		getTemp();
		strcpy($$->temp, temp_g);
		strcpy($$->token, "OP");
		strcpy($$->lexeme, ">=");
		$$->intValue = $1->intValue >= $3->intValue;
		printf("%s = %s >= %s\n", $$->temp, $1->temp, $3->temp);
	}
	|		primary EQ primary {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		$$->left = $1;
		$$->right = $3;
		getTemp();
		strcpy($$->temp, temp_g);
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "==");
		$$->intValue = $1->intValue == $3->intValue;
		printf("%s = %s == %s\n", $$->temp, $1->temp, $3->temp);
	}
	|		primary NEQ primary{
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		$$->left = $1;
		$$->right = $3;
		$$->intValue = $1->intValue != $3->intValue;
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "!=");
		getTemp();
		strcpy($$->temp, temp_g);
		printf("%s = %s != %s\n", $$->temp, $1->temp, $3->temp);
	}
	|		NOT primary{
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		$$->left = NULL;
		$$->right = $2;
		$$->intValue = !$2->intValue;
		strcpy($$->lexeme, "!");
		strcpy($$->token, "OP");
		getTemp();
		strcpy($$->temp, temp_g);
		printf("%s = !%s\n", $$->temp, $2->temp);
	}
	;	

additive:	multiplicative {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		// printf("from additive multiplicative production\n");
		$$ = $1;}
	|		additive PLUS multiplicative {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		$$->left = $1;
		$$->right = $3;
		getTemp();
		strcpy($$->temp, temp_g);
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "+");
		$$->intValue = $1->intValue + $3->intValue;
		printf("%s = %s + %s\n", $$->temp, $1->temp, $3->temp);
	}
	|		additive MINUS multiplicative {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		$$->left = $1;
		$$->right = $3;
		getTemp();
		strcpy($$->temp, temp_g);
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "-");
		$$->intValue = $1->intValue - $3->intValue;
		printf("%s = %s - %s\n", $$->temp, $1->temp, $3->temp);
	}
	;

multiplicative:	unary {
			$$ = malloc(sizeof(struct I_NODE));
			if($$ == NULL)
				yyerror("no mem");
			// printf("from multiplicative unary production\n");
			$$ = $1;}
	|		multiplicative MUL unary {
			$$ = malloc(sizeof(struct I_NODE));
			if($$ == NULL)
				yyerror("no mem");
			getTemp();
			strcpy($$->temp, temp_g);
			strcpy($$->token, "OP");
			strcpy($$->lexeme, "*");
			$$->intValue = $1->intValue * $3->intValue;
			$$->left = $1;
			$$->right = $3;
			printf("%s = %s * %s\n", $$->temp, $1->temp, $3->temp);
		}
    |		multiplicative DIV unary {
			$$ = malloc(sizeof(struct I_NODE));
			if($$ == NULL)
				yyerror("no mem");
			getTemp();
			strcpy($$->temp, temp_g);
			$$->intValue = $1->intValue / $3->intValue;
			$$->left = $1;
			$$->right = $3;
			strcpy($$->token, "OP");
			strcpy($$->lexeme, "/");
			printf("%s = %s / %s\n", $$->temp, $1->temp, $3->temp);
		
		}
    ;

unary:		postfix {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		// printf("from unary postfix production\n");
		$$ = $1;}
	|	INC unary {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		$$->right = $2;
		$$->left = NULL;
		$$->intValue = $2->intValue + 1;
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "++");
		strcpy($$->temp, $2->temp);
		printf("%s = %s + 1\n", $$->temp, $$->temp);
	}
	|		DEC unary {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "--");
		strcpy($$->temp, $2->temp);
		$$->intValue = $2->intValue - 1;
		$$->right = $2;
		$$->left = NULL;
		printf("%s = %s - 1\n", $$->temp, $2->temp);
	}
	|		PLUS unary {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			printf("no mem\n");
		$$ = $2;
	}
	|		MINUS unary {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		getTemp();
		strcpy($$->temp, temp_g);
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "negative");
		$$->intValue = -1 * ($2->intValue);
		$$->right = $2;
		$$->left = NULL;
		printf("%s = -1 * %s\n", $$->temp, $$->temp);
	}
	;

postfix:	primary {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		// printf("from postfix primary production\n");
		$$ = $1;
		}
    |	postfix INC {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "++");
		strcpy($$->temp, $1->temp);
		$$->intValue = $1->intValue + 1;
		$$->left = $1;
		$$->right = NULL;
		printf("%s = %s + 1\n", $$->temp, $$->temp);
	}
	|		postfix DEC {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		strcpy($$->token, "OP");
		strcpy($$->lexeme, "--");
		strcpy($$->temp, $1->temp);
		$$->left = $1;
		$$->right = NULL;
		$$->intValue = $1->intValue - 1;
		printf("%s = %s - 1\n", $$->temp, $1->temp);
	}
	;

primary:	constant {
			$$ = malloc(sizeof(struct I_NODE));
			if($$ == NULL)
				yyerror("no mem");
			$$ = $1;
			}
    |	ID {
			$$ = malloc(sizeof(struct I_NODE));
			if($$ == NULL)
				yyerror("no mem");
			
			strcpy($$->lexeme, $1);
			strcpy($$->token, "ID");
			$$->right = NULL;
			$$->left = NULL;
			getTemp();
			strcpy($$->temp, temp_g);
			// printf("from primary ID production\n");
			printf("%s = %s\n", $$->temp, $$->lexeme);
		}
	|		LPAREN additive RPAREN {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL){
			yyerror("no mem");
		}
		$$ = $2;
	}
	;

constant:	INT {
		$$ = malloc(sizeof(struct I_NODE));
		if($$ == NULL)
			yyerror("no mem");
		$$->intValue = $1;
		$$->left = NULL;
		$$->right = NULL;
		getTemp();
		strcpy($$->token, "CONST");
		strcpy($$->lexeme, "INT");
		$$->intValue = $1;
		strcpy($$->temp, temp_g);
		printf("%s = %i\n", $$->temp, $$->intValue);
	}
	;
			
%%

int main(int argc, char* argv[]){
	if(argc>1){
		FILE *fp = fopen(argv[1], "r");
		if(!fp)
			return 1;
		yyin = fp;
		yyparse();
		return 0;
	}
}

char* getLabel(){
	sprintf(label_g, "L%d", label_count);
	label_count++;
}

char* getTemp(){
	sprintf(temp_g, "t%d", temp_count);
	temp_count++;
}

int yyerror(char* buffer){}