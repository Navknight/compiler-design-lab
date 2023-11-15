%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int yylex();
int yyerror(char *);
int eflag=0;
int label_count=0;
int temp_count=0;
char temp_var_g[20];
char label_g[20];
extern FILE * yyin;

// global stack for switch statements storing temp_var and out label
typedef struct {
	char temp_var[20];
	char out_label[20];
} switchElement;

switchElement switchStack[100];
int switchStackTop = -1;

typedef struct symbol {
	enum { 
			INT_TYPE, 
			FLOAT_TYPE, 
			CHAR_TYPE 
		} type;
		// Dont mess with the ordering of the enum
	bool is_array;
    char name[20];
    int size;
    int offset;
    struct symbol *next;
} symbol;

symbol *symtab = NULL;

symbol *store_symbol(char name[], int size, int type, bool is_array) {
    symbol *sym = malloc(sizeof(symbol));
	strcpy(sym->name, name);
	sym->type = type;
	sym->is_array = is_array;
    // sym->name = strdup(name);
    sym->size = size;
    sym->offset = symtab ? symtab->offset + symtab->size : 0;
    sym->next = symtab;
    symtab = sym;
    return sym;
}

symbol *lead_symbol(char *name) {
    for (symbol *sym = symtab; sym; sym = sym->next) {
        if (strcmp(sym->name, name) == 0) {
            return sym;
        }
    }
    return NULL;
}

symbol *get_scoped_symbol(char *name) {
	for (symbol *sym = symtab; sym && sym->size != 0; sym = sym->next) {
		if (strcmp(sym->name, name) == 0) {
			return sym;
		}
	}
	return NULL;
}

void create_scope() {
    store_symbol("", 0, 0, false);
}

void remove_scope() {
    symbol *sym = symtab;
	printf("\n\nPrevious Function Scope->-----------------\n");
    printf("//\tLexeme\tSize\tOffset\tType\t//\n");
    while (sym && sym->size != 0) {
		if(sym->is_array)
			printf("//\t%s\t%d\t%#06x\t%s\t//\n", sym->name, sym->size, sym->offset, sym->type == INT_TYPE ? "int-Arr" : sym->type == FLOAT_TYPE ? "fl-Arr" : "ch-Arr");
		else
			printf("//\t%s\t%d\t%#06x\t%s\t//\n", sym->name, sym->size, sym->offset, sym->type == INT_TYPE ? "int" : sym->type == FLOAT_TYPE ? "float" : "char");
        symbol *next = sym->next;
        // free(sym->name);
        free(sym);
        sym = next;
    }
	printf("------------------------------------------\n");
    symtab = sym ? sym->next : NULL;
    if (sym) {
        free(sym);
    }
}

typedef struct ASTNode {
    enum { 
		NODETYPE_INT_TYPE,
		NODETYPE_FLOAT_TYPE,
		NODETYPE_CHAR_TYPE,
        NODETYPE_CONSTANT_INT, 
        NODETYPE_IDENTIFIER, 
        NODETYPE_OPERATOR,
        NODETYPE_IF_ELSE,
		NODETYPE_SWITCH,
        NODETYPE_WHILE
    } token;

	// Dont mess with the ordering of the enum

    int intValue;
    char lexeme[20];
	char temp_var[20];

    union {
        struct {
            char op[20];
            struct ASTNode* left;
            struct ASTNode* right;
        } opInfo;
        struct {
            struct ASTNode* condition;
			char condition_label[20];
            struct ASTNode* trueBranch;
			char true_label[20];
            struct ASTNode* falseBranch;
			char false_label[20];
            struct ASTNode* nextBranch;
			char next_label[20];
        } flowControlInfo;
    } info;

} ASTNode;

%}

%union{
	int intValue;
	char lexeme[20];
	struct ASTNode *node;
}

%token ADD SUB MUL DIV INC DEC ASSIGN LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET SEMICOLON COLON COMMA IF ELSE WHILE SWITCH CASE BREAK CONTINUE RETURN GOTO DEFAULT INT_TYPE FLOAT_TYPE CHAR_TYPE LT GT LEQ GEQ EQ NEQ AND OR NOT
%token <intValue> INTEGER
%token <lexeme> IDENTIFIER
%type <node> slist typeSpec expression assignment conditional logicalOr logicalAnd equality relop additive multiplicative unary postfix primary selectionStmt elseStmt labeledStmt iterationStmt
%type <intValue> arrayDeclarator

%%

program : {create_scope();} slist {remove_scope(); printf("\n\nCompleted\n");};

slist : assignment SEMICOLON slist
		| varDeclare SEMICOLON slist
		| selectionStmt slist
		| iterationStmt slist
		| error {printf("\nRejected");} slist
		| {printf("\n");};

varDeclare : typeSpec idList;

idList : IDENTIFIER {
					if(get_scoped_symbol($1) != NULL){
						printf("\nError : Variable %s already inside symbol table, exiting program\n", $1);
						exit(0);
					}
					store_symbol($1, $<node>0->intValue, $<node>0->token, false);
					printf("\nNew variable %s", $1);
				}
				| idList COMMA IDENTIFIER {
					if(get_scoped_symbol($3) != NULL){
						printf("\nError : Variable %s already inside symbol table, exiting program\n", $3);
						exit(0);
					}
					store_symbol($3, $<node>0->intValue, $<node>0->token, false);
					printf("\nNew variable %s", $3);
				}
				| idList COMMA IDENTIFIER arrayDeclarator {
					if(get_scoped_symbol($3) != NULL){
						printf("\nError : Variable %s already inside symbol table, exiting program\n", $3);
						exit(0);
					}
					store_symbol($3, $<node>0->intValue * $4, $<node>0->token, true);
					printf("\nNew variable %s", $3);
				};

arrayDeclarator : arrayDeclarator LBRACKET INTEGER RBRACKET {
					$$ = $1 * $3;
				}
				| LBRACKET INTEGER RBRACKET {
					$$ = $2;
				};

typeSpec :	INT_TYPE {
					$$ = malloc(sizeof(struct ASTNode));
					if($$ == NULL){
						printf("Out of memory\n");
						exit(0);
					}
					$$->intValue = 4;
					$$->token = NODETYPE_INT_TYPE;
				}
				| FLOAT_TYPE {
					$$ = malloc(sizeof(struct ASTNode));
					if($$ == NULL){
						printf("Out of memory\n");
						exit(0);
					}
					$$->intValue = 4;
					$$->token = NODETYPE_FLOAT_TYPE;
				}
				| CHAR_TYPE {
					$$ = malloc(sizeof(struct ASTNode));
					if($$ == NULL){
						printf("Out of memory\n");
						exit(0);
					}
					$$->intValue = 1;
					$$->token = NODETYPE_CHAR_TYPE;
				};

expression : assignment { $$ = $1;}
			| expression COMMA assignment {
				$$ = malloc(sizeof(struct ASTNode));
				if($$ == NULL){
					printf("Out of memory\n");
					exit(0);
				}
				$$->token = NODETYPE_OPERATOR;
				$$->info.opInfo.left = $1;
				$$->info.opInfo.right = $3;
				strcpy($$->info.opInfo.op, ",");
			};

assignment :	conditional { $$ = $1; }
						| unary ASSIGN assignment {
							$$ = malloc(sizeof(struct ASTNode));
							if($$ == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							$$->token = NODETYPE_OPERATOR;
							$$->info.opInfo.left = $1;
							$$->info.opInfo.right = $3;
							strcpy($$->info.opInfo.op, "=");
							$1->intValue = $3->intValue;
							printf("\n%s = %s", $1->lexeme, $3->temp_var);
						};

conditional : logicalOr { $$ = $1; };

logicalOr :	logicalAnd {
							$$ = $1;
						}
						| logicalOr OR logicalAnd {
							$$ = malloc(sizeof(struct ASTNode));
							if($$ == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							$$->token = NODETYPE_OPERATOR;
							$$->info.opInfo.left = $1;
							$$->info.opInfo.right = $3;
							strcpy($$->info.opInfo.op, "||");
							genTemp();
							strcpy($$->temp_var, temp_var_g);
							$$->intValue = $1->intValue || $3->intValue;
							printf("\n%s = %s || %s", $$->temp_var, $$->info.opInfo.left->temp_var, $$->info.opInfo.right->temp_var);
						};

logicalAnd :	equality {
							$$ = $1;
						}
						| logicalAnd AND equality {
							$$ = malloc(sizeof(struct ASTNode));
							if($$ == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							$$->token = NODETYPE_OPERATOR;
							$$->info.opInfo.left = $1;
							$$->info.opInfo.right = $3;
							strcpy($$->info.opInfo.op, "&&");
							genTemp();
							strcpy($$->temp_var, temp_var_g);
							$$->intValue = $1->intValue && $3->intValue;
							printf("\n%s = %s && %s", $$->temp_var, $$->info.opInfo.left->temp_var, $$->info.opInfo.right->temp_var);
						};

equality :	relop {
							$$ = $1;
						}
						| equality EQ relop {
							$$ = malloc(sizeof(struct ASTNode));
							if($$ == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							$$->token = NODETYPE_OPERATOR;
							$$->info.opInfo.left = $1;
							$$->info.opInfo.right = $3;
							strcpy($$->info.opInfo.op, "==");
							genTemp();
							strcpy($$->temp_var, temp_var_g);
							$$->intValue = $1->intValue == $3->intValue;
							printf("\n%s = %s == %s", $$->temp_var, $$->info.opInfo.left->temp_var, $$->info.opInfo.right->temp_var);
						}
						| equality NEQ relop {
							$$ = malloc(sizeof(struct ASTNode));
							if($$ == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							$$->token = NODETYPE_OPERATOR;
							$$->info.opInfo.left = $1;
							$$->info.opInfo.right = $3;
							strcpy($$->info.opInfo.op, "!=");
							genTemp();
							strcpy($$->temp_var, temp_var_g);
							$$->intValue = $1->intValue != $3->intValue;
							printf("\n%s = %s != %s", $$->temp_var, $$->info.opInfo.left->temp_var, $$->info.opInfo.right->temp_var);
						};

relop :	additive {
							$$ = $1;
						}
						| relop LT additive {
							$$ = malloc(sizeof(struct ASTNode));
							if($$ == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							$$->token = NODETYPE_OPERATOR;
							$$->info.opInfo.left = $1;
							$$->info.opInfo.right = $3;
							strcpy($$->info.opInfo.op, "<");
							genTemp();
							strcpy($$->temp_var, temp_var_g);
							$$->intValue = $1->intValue < $3->intValue;
							printf("\n%s = %s < %s", $$->temp_var, $$->info.opInfo.left->temp_var, $$->info.opInfo.right->temp_var);
						}
						| relop GT additive {
							$$ = malloc(sizeof(struct ASTNode));
							if($$ == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							$$->token = NODETYPE_OPERATOR;
							$$->info.opInfo.left = $1;
							$$->info.opInfo.right = $3;
							strcpy($$->info.opInfo.op, ">");
							genTemp();
							strcpy($$->temp_var, temp_var_g);
							$$->intValue = $1->intValue > $3->intValue;
							printf("\n%s = %s > %s", $$->temp_var, $$->info.opInfo.left->temp_var, $$->info.opInfo.right->temp_var);
						}
						| relop LEQ additive {
							$$ = malloc(sizeof(struct ASTNode));
							if($$ == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							$$->token = NODETYPE_OPERATOR;
							$$->info.opInfo.left = $1;
							$$->info.opInfo.right = $3;
							strcpy($$->info.opInfo.op, "<=");
							genTemp();
							strcpy($$->temp_var, temp_var_g);
							$$->intValue = $1->intValue <= $3->intValue;
							printf("\n%s = %s <= %s", $$->temp_var, $$->info.opInfo.left->temp_var, $$->info.opInfo.right->temp_var);
						}
						| relop GEQ additive {
							$$ = malloc(sizeof(struct ASTNode));
							if($$ == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							$$->token = NODETYPE_OPERATOR;
							$$->info.opInfo.left = $1;
							$$->info.opInfo.right = $3;
							strcpy($$->info.opInfo.op, ">=");
							genTemp();
							strcpy($$->temp_var, temp_var_g);
							$$->intValue = $1->intValue >= $3->intValue;
							printf("\n%s = %s >= %s", $$->temp_var, $$->info.opInfo.left->temp_var, $$->info.opInfo.right->temp_var);
						};

additive : multiplicative {
						$$ = $1;
					}
					| additive ADD multiplicative {
						$$ = malloc(sizeof(struct ASTNode));
						if($$ == NULL){
							printf("Out of memory\n");
							exit(0);
						}

						$$->token = NODETYPE_OPERATOR;
						$$->info.opInfo.left = $1;
						$$->info.opInfo.right = $3;
						strcpy($$->info.opInfo.op, "+");
						genTemp();
						strcpy($$->temp_var, temp_var_g);
						$$->intValue = $1->intValue + $3->intValue;
						printf("\n%s = %s + %s", $$->temp_var, $$->info.opInfo.left->temp_var, $$->info.opInfo.right->temp_var);
					}
					| additive SUB multiplicative {
						$$ = malloc(sizeof(struct ASTNode));
						if($$ == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						$$->token = NODETYPE_OPERATOR;
						$$->info.opInfo.left = $1;
						$$->info.opInfo.right = $3;
						strcpy($$->info.opInfo.op, "-");
						genTemp();
						strcpy($$->temp_var, temp_var_g);
						$$->intValue = $1->intValue - $3->intValue;
						printf("\n%s = %s - %s", $$->temp_var, $$->info.opInfo.left->temp_var, $$->info.opInfo.right->temp_var);
					};

multiplicative :	unary {
								$$ = $1;
							}
							| multiplicative MUL unary {
								$$ = malloc(sizeof(struct ASTNode));
								if($$ == NULL){
									printf("Out of memory\n");
									exit(0);
								}
								$$->token = NODETYPE_OPERATOR;
								$$->info.opInfo.left = $1;
								$$->info.opInfo.right = $3;
								strcpy($$->info.opInfo.op, "*");
								genTemp();
								strcpy($$->temp_var, temp_var_g);
								$$->intValue = $1->intValue * $3->intValue;
								printf("\n%s = %s * %s", $$->temp_var, $$->info.opInfo.left->temp_var, $$->info.opInfo.right->temp_var);
							}
							| multiplicative DIV unary {
								$$ = malloc(sizeof(struct ASTNode));
								if($$ == NULL){
									printf("Out of memory\n");
									exit(0);
								}
								$$->token = NODETYPE_OPERATOR;
								$$->info.opInfo.left = $1;
								$$->info.opInfo.right = $3;
								strcpy($$->info.opInfo.op, "/");
								genTemp();
								strcpy($$->temp_var, temp_var_g);
								$$->intValue = $1->intValue / $3->intValue;
								printf("\n%s = %s / %s", $$->temp_var, $$->info.opInfo.left->temp_var, $$->info.opInfo.right->temp_var);
							};

unary :	postfix {
						$$ = $1;
					}
					| INC unary {
						$$ = malloc(sizeof(struct ASTNode));
						if($$ == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						$$->token = NODETYPE_OPERATOR;
						$$->info.opInfo.right = $2;
						strcpy($$->info.opInfo.op, "++");
						strcpy($$->lexeme, $2->lexeme);
						genTemp();
						strcpy($$->temp_var, temp_var_g);
						$2->intValue = $2->intValue + 1;
						printf("\n%s = %s + 1", $2->temp_var, $2->temp_var);
						$$->intValue = $2->intValue;
						printf("\n%s = %s", $$->temp_var, $$->info.opInfo.right->temp_var);
					}
					| DEC unary {
						$$ = malloc(sizeof(struct ASTNode));
						if($$ == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						$$->token = NODETYPE_OPERATOR;
						$$->info.opInfo.right = $2;
						strcpy($$->info.opInfo.op, "--");
						strcpy($$->lexeme, $2->lexeme);
						genTemp();
						strcpy($$->temp_var, temp_var_g);
						$2->intValue = $2->intValue - 1;
						printf("\n%s = %s - 1", $2->temp_var, $2->temp_var);
						$$->intValue = $2->intValue;
						printf("\n%s = %s", $$->temp_var, $$->info.opInfo.right->temp_var);
					}
					| ADD unary {
						$$ = $2;
					}
					| SUB unary {
						$$ = malloc(sizeof(struct ASTNode));
						if($$ == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						$$->token = NODETYPE_OPERATOR;
						$$->info.opInfo.right = $2;
						strcpy($$->info.opInfo.op, "minus");
						strcpy($$->lexeme, $2->lexeme);
						genTemp();
						strcpy($$->temp_var, temp_var_g);
						$$->intValue = -1 * $2->intValue;
						printf("\n%s = -1 * %s", $$->temp_var, $$->info.opInfo.right->temp_var);
					}
					| NOT unary {
						$$ = malloc(sizeof(struct ASTNode));
						if($$ == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						$$->token = NODETYPE_OPERATOR;
						$$->info.opInfo.right = $2;
						strcpy($$->info.opInfo.op, "!");
						strcpy($$->lexeme, $2->lexeme);
						genTemp();
						strcpy($$->temp_var, temp_var_g);
						$$->intValue = !$2->intValue;
						printf("\n%s = !%s", $$->temp_var, $$->info.opInfo.right->temp_var);
					};

postfix : primary {
						$$ = $1;
					}
					| postfix INC {
						$$ = malloc(sizeof(struct ASTNode));
						if ($$ == NULL) {
							yyerror("no mem");
						}
						$$->token = NODETYPE_OPERATOR;
						$$->info.opInfo.left = $1;
						$$->intValue = $1->intValue;
						strcpy($$->info.opInfo.op, "++");
						strcpy($$->lexeme, $1->lexeme);
						genTemp();
						strcpy($$->temp_var, temp_var_g);
						printf("\n%s = %s", $$->temp_var, $$->info.opInfo.left->temp_var);
						$1->intValue = $1->intValue + 1;
						printf("\n%s = %s + 1", $1->temp_var, $1->temp_var);
					}
					| postfix DEC {
						$$ = malloc(sizeof(struct ASTNode));
						if ($$ == NULL) {
							yyerror("no mem");
						}
						$$->token = NODETYPE_OPERATOR;
						$$->info.opInfo.left = $1;
						strcpy($$->info.opInfo.op, "--");
						strcpy($$->lexeme, $1->lexeme);
						$$->intValue = $1->intValue;
						genTemp();
						strcpy($$->temp_var, temp_var_g);
						printf("\n%s = %s", $$->temp_var, $$->info.opInfo.left->temp_var);
						$1->intValue = $1->intValue - 1;
						printf("\n%s = %s - 1", $1->temp_var, $1->temp_var);
					};

primary : INTEGER {
						$$ = malloc(sizeof(ASTNode));
						if($$ == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						$$->token = NODETYPE_CONSTANT_INT;
						$$->intValue = $1;
						genTemp();
						strcpy($$->temp_var, temp_var_g);
						printf("\n%s = %d", $$->temp_var, $$->intValue);
					} 
					| IDENTIFIER {
						if(lead_symbol($1) == NULL){
							printf("\nError : Variable %s not in symbol table, exiting program\n", $1);
							exit(0);
						}
						$$ = malloc(sizeof(ASTNode));
						if($$ == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						$$->token = NODETYPE_IDENTIFIER;
						strcpy($$->lexeme, $1);
						genTemp();
						strcpy($$->temp_var, temp_var_g);
						printf("\n%s = %s", $$->temp_var, $$->lexeme);
					}
					| LPAREN expression RPAREN {
						$$ = $2;
					};

selectionStmt :	IF LPAREN assignment RPAREN LBRACE {
							create_scope();
							$$ = malloc(sizeof(struct ASTNode));
							if($$ == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							$$->token = NODETYPE_IF_ELSE;
							$$->info.flowControlInfo.condition = $3;
							genLabel();
							strcpy($$->info.flowControlInfo.true_label, label_g);
							genLabel();
							strcpy($$->info.flowControlInfo.false_label, label_g);
							genLabel();
							strcpy($$->info.flowControlInfo.next_label, label_g);
							printf("\nif %s goto %s", $$->info.flowControlInfo.condition->temp_var, $$->info.flowControlInfo.true_label);
							printf("\ngoto %s", $$->info.flowControlInfo.false_label);
							printf("\n\n%s:", $$->info.flowControlInfo.true_label);
						} slist {
							$$ = $6;
							$$->info.flowControlInfo.trueBranch = $7;
							printf("\ngoto %s", $$->info.flowControlInfo.next_label);
							printf("\n\n%s:", $$->info.flowControlInfo.false_label);
							remove_scope();
						} RBRACE elseStmt {
							$$ = $8;
							ASTNode *temp = $10;
							if(temp != NULL){
								$$->info.flowControlInfo.falseBranch = temp;
							}
							printf("\n\n%s:", $$->info.flowControlInfo.next_label);
						}
						| SWITCH LPAREN expression RPAREN LBRACE {
							$$ = malloc(sizeof(struct ASTNode));
							if($$ == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							$$->token = NODETYPE_SWITCH;
							genLabel();
							strcpy($$->info.flowControlInfo.next_label, label_g);
							strcpy($$->temp_var, $3->temp_var);
							if(switchStackTop >= 100){
								printf("Switch Stack overflow\n");
								exit(0);
							}
							switchStackTop++;
							strcpy(switchStack[switchStackTop].temp_var, $$->temp_var);
							strcpy(switchStack[switchStackTop].out_label, $$->info.flowControlInfo.next_label);
						} labeledStmt RBRACE {
							$$ = $6;
							switchStackTop--;
							printf("\n\n%s:", $$->info.flowControlInfo.next_label);
						};

labeledStmt :	CASE conditional {
						create_scope();
						$$ = malloc(sizeof(struct ASTNode));
						if($$ == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						genLabel();
						strcpy($$->info.flowControlInfo.false_label, label_g);
						printf("\nifFalse %s = %s goto %s", switchStack[switchStackTop].temp_var, $2->temp_var, label_g);
					} COLON slist breakStmt  {
						remove_scope();
						printf("\n\n%s:", $3->info.flowControlInfo.false_label);
					} labeledStmt {$$ = $3;}
					| DEFAULT COLON {create_scope();} slist {remove_scope();} breakStmt {
						$$ = NULL;
					}
					| {$$=NULL;printf("\ngoto %s", switchStack[switchStackTop].out_label); };

breakStmt : BREAK SEMICOLON {
					printf("\ngoto %s", switchStack[switchStackTop].out_label);
				}
				| {};


elseStmt : ELSE LBRACE {create_scope();} slist RBRACE {
					remove_scope();
					$$ = $4;
				} | { $$ = NULL;};

iterationStmt :	WHILE {
							$$ = malloc(sizeof(struct ASTNode));
							if($$ == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							$$->token = NODETYPE_WHILE;
							genLabel();
							strcpy($$->info.flowControlInfo.condition_label, label_g);
							genLabel();
							strcpy($$->info.flowControlInfo.true_label, label_g);
							genLabel();
							strcpy($$->info.flowControlInfo.false_label, label_g);
							printf("\n\n%s:", $$->info.flowControlInfo.condition_label);
						} LPAREN assignment {
							$$ = $2;
							$$->info.flowControlInfo.condition = $4;
							printf("\nif %s goto %s", $$->info.flowControlInfo.condition->temp_var, $$->info.flowControlInfo.true_label);
							printf("\ngoto %s", $$->info.flowControlInfo.false_label);
							printf("\n\n%s:", $$->info.flowControlInfo.true_label);
							create_scope();
						} RPAREN LBRACE slist RBRACE {
							remove_scope();
							$$ = $5;
							$$->info.flowControlInfo.trueBranch = $8;
							printf("\ngoto %s", $$->info.flowControlInfo.condition_label);
							printf("\n\n%s:", $$->info.flowControlInfo.false_label);
						};


%%

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Usage: ./parser <filename>\n");
		return 1;
	}
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		printf("File not found\n");
		return 1;
	}
	yyin = fp;
	yyparse();
	return 0;
}

char *genTemp()
{
	sprintf(temp_var_g, "t%d", temp_count);
	temp_count++;
}

char *genLabel()
{
	sprintf(label_g, "L%d", label_count);
	label_count++;
}