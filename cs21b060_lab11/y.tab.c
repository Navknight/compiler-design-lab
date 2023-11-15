/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20230521

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#undef YYBTYACC
#define YYBTYACC 0
#define YYDEBUGSTR YYPREFIX "debug"
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "prob1.y"
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

/* global stack for switch statements storing temp_var and out label*/
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
		/* Dont mess with the ordering of the enum*/
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
    /* sym->name = strdup(name);*/
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
        /* free(sym->name);*/
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

	/* Dont mess with the ordering of the enum*/

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

#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 136 "prob1.y"
typedef union YYSTYPE{
	int intValue;
	char lexeme[20];
	struct ASTNode *node;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 170 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define ADD 257
#define SUB 258
#define MUL 259
#define DIV 260
#define INC 261
#define DEC 262
#define ASSIGN 263
#define LPAREN 264
#define RPAREN 265
#define LBRACE 266
#define RBRACE 267
#define LBRACKET 268
#define RBRACKET 269
#define SEMICOLON 270
#define COLON 271
#define COMMA 272
#define IF 273
#define ELSE 274
#define WHILE 275
#define SWITCH 276
#define CASE 277
#define BREAK 278
#define CONTINUE 279
#define RETURN 280
#define GOTO 281
#define DEFAULT 282
#define INT_TYPE 283
#define FLOAT_TYPE 284
#define CHAR_TYPE 285
#define LT 286
#define GT 287
#define LEQ 288
#define GEQ 289
#define EQ 290
#define NEQ 291
#define AND 292
#define OR 293
#define NOT 294
#define INTEGER 295
#define IDENTIFIER 296
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
   20,    0,    1,    1,    1,    1,   22,    1,    1,   21,
   23,   23,   23,   19,   19,    2,    2,    2,    3,    3,
    4,    4,    5,    6,    6,    7,    7,    8,    8,    8,
    9,    9,    9,    9,    9,   10,   10,   10,   11,   11,
   11,   12,   12,   12,   12,   12,   12,   13,   13,   13,
   14,   14,   14,   24,   25,   15,   26,   15,   27,   29,
   17,   30,   31,   17,   17,   28,   28,   32,   16,   16,
   33,   34,   18,
};
static const YYINT yylen[] = {                            2,
    0,    2,    3,    3,    2,    2,    0,    3,    0,    2,
    1,    3,    4,    4,    3,    1,    1,    1,    1,    3,
    1,    3,    1,    1,    3,    1,    3,    1,    3,    3,
    1,    3,    3,    3,    3,    1,    3,    3,    1,    3,
    3,    1,    2,    2,    2,    2,    2,    1,    2,    2,
    1,    1,    3,    0,    0,   10,    0,    8,    0,    0,
    8,    0,    0,    6,    0,    2,    0,    0,    5,    0,
    0,    0,    9,
};
static const YYINT yydefred[] = {                         1,
    0,    0,    7,    0,    0,    0,    0,    0,    0,   71,
    0,   16,   17,   18,    0,   51,   52,    2,    0,    0,
   21,    0,    0,    0,    0,    0,    0,    0,    0,   48,
    0,    0,    0,    0,   45,   46,   43,   44,    0,   19,
    0,    0,    0,   47,   11,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   49,   50,    5,    6,    0,    8,   53,    0,    0,    0,
    0,    0,    3,    0,   39,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   40,   41,   22,    4,   20,    0,
   72,    0,    0,   54,    0,   57,    0,    0,    0,    0,
    0,    0,    0,   55,    0,    0,    0,    0,   15,    0,
    0,    0,   59,   62,   58,   14,    0,   73,    0,    0,
    0,   56,    0,   63,   68,    0,    0,    0,    0,   60,
   64,    0,   66,    0,   69,   61,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  298,  318,  256,  257,  258,  261,  262,  264,  273,  275,
  276,  283,  284,  285,  294,  295,  296,  299,  300,  302,
  303,  304,  305,  306,  307,  308,  309,  310,  311,  312,
  313,  316,  319,  320,  310,  310,  310,  310,  301,  302,
  264,  331,  264,  310,  296,  321,  270,  293,  292,  290,
  291,  286,  287,  288,  289,  257,  258,  259,  260,  263,
  261,  262,  299,  299,  270,  299,  265,  272,  302,  264,
  301,  272,  299,  305,  310,  306,  307,  307,  308,  308,
  308,  308,  309,  309,  310,  310,  302,  299,  302,  265,
  302,  265,  296,  266,  332,  266,  268,  317,  322,  265,
  324,  295,  268,  299,  266,  277,  282,  315,  269,  295,
  323,  299,  303,  271,  267,  269,  267,  267,  325,  328,
  274,  314,  271,  299,  266,  299,  329,  330,  278,  326,
  326,  299,  270,  327,  267,  315,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          1,
   18,   19,   39,   20,   21,   22,   23,   24,   25,   26,
   27,   28,   29,   30,   31,  122,  108,   32,   98,    2,
   33,   34,   46,   99,  111,  101,  119,  130,  134,  120,
  127,  128,   42,   95,
};
static const YYINT yysindex[] = {                         0,
    0, -174,    0, -231, -231, -231, -231, -231, -264,    0,
 -252,    0,    0,    0, -231,    0,    0,    0, -273, -229,
    0, -233, -223, -232, -170, -161, -118, -190,  -89,    0,
 -174, -174, -195, -174,    0,    0,    0,    0, -237,    0,
 -231, -185, -231,    0,    0, -191, -174, -231, -231, -231,
 -231, -231, -231, -231, -231, -231, -231, -231, -231, -231,
    0,    0,    0,    0, -174,    0,    0, -231, -180, -231,
 -157, -202,    0, -223,    0, -232, -170, -170, -161, -161,
 -161, -161, -118, -118,    0,    0,    0,    0,    0, -154,
    0, -136, -129,    0, -121,    0, -149, -117, -174, -106,
 -262,  -95, -119,    0, -174, -231,  -82,  -61,    0,  -52,
  -49,  -48,    0,    0,    0,    0,  -54,    0,  -50, -174,
  -44,    0, -174,    0,    0,  -53,  -53, -174,  -46,    0,
    0,  -41,    0, -262,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,  231,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -194, -204, -179, -254,   22,  -88, -125, -134,    0,
   21,   21,    0,   21,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -35,   21,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   21,    0,    0,    0,    0,    0,
    0,    0,    0, -122,    0, -165,  -38,  105,   35,   64,
   72,  101,  -79,  -42,    0,    0,    0,    0,    0,    0,
    0,    0, -238,    0,    0,    0,    0, -228,  -31,    0,
  -30,    0,    0,    0,  -31,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    1,    0,    0, -259,
    0,    0, -253,    0,    0,  -92,  -29,  -31,    0,    0,
    0,    0,    0,  -30,    0,    0,
};
#if YYBTYACC
static const YYINT yycindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
  -25,    0,  196,    2,  134,    0,  193,  194,  130,  142,
  131,   -2,    0,    0,    0,    0,  108,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  129,    0,    0,
    0,    0,    0,    0,
};
#define YYTABLESIZE 398
static const YYINT yytable[] = {                         41,
   70,   35,   36,   37,   38,   63,   64,    9,   66,   40,
   28,   43,   44,    9,  106,   28,   28,   28,    9,  107,
    9,   73,   45,    9,    9,    4,    5,   67,    9,    6,
    7,   12,    8,   12,   68,   28,   28,   28,   28,   88,
   47,   13,   69,   13,   40,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   85,   86,   50,   51,   48,
   24,   87,   15,   16,   17,   24,   24,   24,   49,   89,
   23,   91,   60,  104,   65,   23,   23,   23,   70,  112,
   72,    3,    4,    5,   90,   26,    6,    7,   24,    8,
   26,   26,   26,   93,  124,   56,   57,  126,    9,   27,
   10,   11,  132,   75,   27,   27,   27,   92,   12,   13,
   14,   94,   26,   26,   68,   52,   53,   54,   55,   15,
   16,   17,   42,   42,   42,   42,   27,   27,   42,   96,
   42,   39,   39,   39,   39,   42,   42,   42,   97,   39,
   58,   59,   25,  100,   39,  102,   39,   25,   25,   25,
  103,   42,   42,   42,   42,   42,   42,   42,   42,  105,
   39,   39,   39,   39,   39,   39,   39,   39,   36,   36,
   25,   61,   62,  109,   67,  110,   36,   37,   37,   77,
   78,   36,   36,   36,   67,   37,   83,   84,  114,   67,
   37,   37,   37,   79,   80,   81,   82,   36,   36,   36,
   36,   36,   36,   36,   36,  115,   37,   37,   37,   37,
   37,   37,   37,   37,   38,   38,  116,  117,  118,  121,
  123,  125,   38,  133,  129,  135,   29,   38,   38,   38,
    9,   29,   29,   29,   10,    9,   65,   67,   71,  113,
   74,  136,   76,   38,   38,   38,   38,   38,   38,   38,
   38,   29,   29,   29,   29,  131,   70,   70,   70,    0,
    0,   70,   70,    0,   70,    0,    0,   70,    0,    0,
    0,    0,    0,   70,    0,   70,   70,   70,   70,    0,
    0,    0,   70,   70,   70,   70,   31,    9,    0,    0,
    0,   31,   31,   31,   70,   70,   70,    9,    9,   32,
    0,    0,    9,    0,   32,   32,   32,   31,   31,   31,
   31,   31,   31,   31,   31,    0,    0,    0,    0,    0,
   32,   32,   32,   32,   32,   32,   32,   32,   33,    0,
    0,    0,    0,   33,   33,   33,   34,    0,    0,    0,
    0,   34,   34,   34,    0,    0,    0,    0,    0,   33,
   33,   33,   33,   33,   33,   33,   33,   34,   34,   34,
   34,   34,   34,   34,   34,   35,    0,    0,    0,   30,
   35,   35,   35,    0,   30,   30,   30,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   35,   35,   35,   35,
   35,   35,   35,   35,   30,   30,   30,   30,
};
static const YYINT yycheck[] = {                        264,
    0,    4,    5,    6,    7,   31,   32,  267,   34,    8,
  265,  264,   15,  267,  277,  270,  271,  272,  278,  282,
    0,   47,  296,  277,  278,  257,  258,  265,  282,  261,
  262,  270,  264,  272,  272,  290,  291,  292,  293,   65,
  270,  270,   41,  272,   43,   48,   49,   50,   51,   52,
   53,   54,   55,   56,   57,   58,   59,  290,  291,  293,
  265,   60,  294,  295,  296,  270,  271,  272,  292,   68,
  265,   70,  263,   99,  270,  270,  271,  272,  264,  105,
  272,  256,  257,  258,  265,  265,  261,  262,  293,  264,
  270,  271,  272,  296,  120,  257,  258,  123,  273,  265,
  275,  276,  128,  106,  270,  271,  272,  265,  283,  284,
  285,  266,  292,  293,  272,  286,  287,  288,  289,  294,
  295,  296,  257,  258,  259,  260,  292,  293,  263,  266,
  265,  257,  258,  259,  260,  270,  271,  272,  268,  265,
  259,  260,  265,  265,  270,  295,  272,  270,  271,  272,
  268,  286,  287,  288,  289,  290,  291,  292,  293,  266,
  286,  287,  288,  289,  290,  291,  292,  293,  257,  258,
  293,  261,  262,  269,  267,  295,  265,  257,  258,   50,
   51,  270,  271,  272,  277,  265,   56,   57,  271,  282,
  270,  271,  272,   52,   53,   54,   55,  286,  287,  288,
  289,  290,  291,  292,  293,  267,  286,  287,  288,  289,
  290,  291,  292,  293,  257,  258,  269,  267,  267,  274,
  271,  266,  265,  270,  278,  267,  265,  270,  271,  272,
    0,  270,  271,  272,  270,  267,  267,  267,   43,  106,
   48,  134,   49,  286,  287,  288,  289,  290,  291,  292,
  293,  290,  291,  292,  293,  127,  256,  257,  258,   -1,
   -1,  261,  262,   -1,  264,   -1,   -1,  267,   -1,   -1,
   -1,   -1,   -1,  273,   -1,  275,  276,  277,  278,   -1,
   -1,   -1,  282,  283,  284,  285,  265,  267,   -1,   -1,
   -1,  270,  271,  272,  294,  295,  296,  277,  278,  265,
   -1,   -1,  282,   -1,  270,  271,  272,  286,  287,  288,
  289,  290,  291,  292,  293,   -1,   -1,   -1,   -1,   -1,
  286,  287,  288,  289,  290,  291,  292,  293,  265,   -1,
   -1,   -1,   -1,  270,  271,  272,  265,   -1,   -1,   -1,
   -1,  270,  271,  272,   -1,   -1,   -1,   -1,   -1,  286,
  287,  288,  289,  290,  291,  292,  293,  286,  287,  288,
  289,  290,  291,  292,  293,  265,   -1,   -1,   -1,  265,
  270,  271,  272,   -1,  270,  271,  272,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  286,  287,  288,  289,
  290,  291,  292,  293,  290,  291,  292,  293,
};
#if YYBTYACC
static const YYINT yyctable[] = {                        -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 296
#define YYUNDFTOKEN 333
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"$end",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"error","ADD","SUB","MUL","DIV","INC",
"DEC","ASSIGN","LPAREN","RPAREN","LBRACE","RBRACE","LBRACKET","RBRACKET",
"SEMICOLON","COLON","COMMA","IF","ELSE","WHILE","SWITCH","CASE","BREAK",
"CONTINUE","RETURN","GOTO","DEFAULT","INT_TYPE","FLOAT_TYPE","CHAR_TYPE","LT",
"GT","LEQ","GEQ","EQ","NEQ","AND","OR","NOT","INTEGER","IDENTIFIER","$accept",
"program","slist","typeSpec","expression","assignment","conditional",
"logicalOr","logicalAnd","equality","relop","additive","multiplicative","unary",
"postfix","primary","selectionStmt","elseStmt","labeledStmt","iterationStmt",
"arrayDeclarator","$$1","varDeclare","$$2","idList","$$3","$$4","$$5","$$6",
"breakStmt","$$7","$$8","$$9","$$10","$$11","$$12","illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"$$1 :",
"program : $$1 slist",
"slist : assignment SEMICOLON slist",
"slist : varDeclare SEMICOLON slist",
"slist : selectionStmt slist",
"slist : iterationStmt slist",
"$$2 :",
"slist : error $$2 slist",
"slist :",
"varDeclare : typeSpec idList",
"idList : IDENTIFIER",
"idList : idList COMMA IDENTIFIER",
"idList : idList COMMA IDENTIFIER arrayDeclarator",
"arrayDeclarator : arrayDeclarator LBRACKET INTEGER RBRACKET",
"arrayDeclarator : LBRACKET INTEGER RBRACKET",
"typeSpec : INT_TYPE",
"typeSpec : FLOAT_TYPE",
"typeSpec : CHAR_TYPE",
"expression : assignment",
"expression : expression COMMA assignment",
"assignment : conditional",
"assignment : unary ASSIGN assignment",
"conditional : logicalOr",
"logicalOr : logicalAnd",
"logicalOr : logicalOr OR logicalAnd",
"logicalAnd : equality",
"logicalAnd : logicalAnd AND equality",
"equality : relop",
"equality : equality EQ relop",
"equality : equality NEQ relop",
"relop : additive",
"relop : relop LT additive",
"relop : relop GT additive",
"relop : relop LEQ additive",
"relop : relop GEQ additive",
"additive : multiplicative",
"additive : additive ADD multiplicative",
"additive : additive SUB multiplicative",
"multiplicative : unary",
"multiplicative : multiplicative MUL unary",
"multiplicative : multiplicative DIV unary",
"unary : postfix",
"unary : INC unary",
"unary : DEC unary",
"unary : ADD unary",
"unary : SUB unary",
"unary : NOT unary",
"postfix : primary",
"postfix : postfix INC",
"postfix : postfix DEC",
"primary : INTEGER",
"primary : IDENTIFIER",
"primary : LPAREN expression RPAREN",
"$$3 :",
"$$4 :",
"selectionStmt : IF LPAREN assignment RPAREN LBRACE $$3 slist $$4 RBRACE elseStmt",
"$$5 :",
"selectionStmt : SWITCH LPAREN expression RPAREN LBRACE $$5 labeledStmt RBRACE",
"$$6 :",
"$$7 :",
"labeledStmt : CASE conditional $$6 COLON slist breakStmt $$7 labeledStmt",
"$$8 :",
"$$9 :",
"labeledStmt : DEFAULT COLON $$8 slist $$9 breakStmt",
"labeledStmt :",
"breakStmt : BREAK SEMICOLON",
"breakStmt :",
"$$10 :",
"elseStmt : ELSE LBRACE $$10 slist RBRACE",
"elseStmt :",
"$$11 :",
"$$12 :",
"iterationStmt : WHILE $$11 LPAREN assignment $$12 RPAREN LBRACE slist RBRACE",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
YYLTYPE  yyloc; /* position returned by actions */
YYLTYPE  yylloc; /* position from the lexer */
#endif

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(loc, rhs, n) \
do \
{ \
    if (n == 0) \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 0).last_line; \
        (loc).first_column = YYRHSLOC(rhs, 0).last_column; \
        (loc).last_line    = YYRHSLOC(rhs, 0).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, 0).last_column; \
    } \
    else \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 1).first_line; \
        (loc).first_column = YYRHSLOC(rhs, 1).first_column; \
        (loc).last_line    = YYRHSLOC(rhs, n).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, n).last_column; \
    } \
} while (0)
#endif /* YYLLOC_DEFAULT */
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#if YYBTYACC

#ifndef YYLVQUEUEGROWTH
#define YYLVQUEUEGROWTH 32
#endif
#endif /* YYBTYACC */

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#ifndef YYINITSTACKSIZE
#define YYINITSTACKSIZE 200
#endif

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  *p_base;
    YYLTYPE  *p_mark;
#endif
} YYSTACKDATA;
#if YYBTYACC

struct YYParseState_s
{
    struct YYParseState_s *save;    /* Previously saved parser state */
    YYSTACKDATA            yystack; /* saved parser stack */
    int                    state;   /* saved parser state */
    int                    errflag; /* saved error recovery status */
    int                    lexeme;  /* saved index of the conflict lexeme in the lexical queue */
    YYINT                  ctry;    /* saved index in yyctable[] for this conflict */
};
typedef struct YYParseState_s YYParseState;
#endif /* YYBTYACC */
/* variables for the parser stack */
static YYSTACKDATA yystack;
#if YYBTYACC

/* Current parser state */
static YYParseState *yyps = 0;

/* yypath != NULL: do the full parse, starting at *yypath parser state. */
static YYParseState *yypath = 0;

/* Base of the lexical value queue */
static YYSTYPE *yylvals = 0;

/* Current position at lexical value queue */
static YYSTYPE *yylvp = 0;

/* End position of lexical value queue */
static YYSTYPE *yylve = 0;

/* The last allocated position at the lexical value queue */
static YYSTYPE *yylvlim = 0;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
/* Base of the lexical position queue */
static YYLTYPE *yylpsns = 0;

/* Current position at lexical position queue */
static YYLTYPE *yylpp = 0;

/* End position of lexical position queue */
static YYLTYPE *yylpe = 0;

/* The last allocated position at the lexical position queue */
static YYLTYPE *yylplim = 0;
#endif

/* Current position at lexical token queue */
static YYINT  *yylexp = 0;

static YYINT  *yylexemes = 0;
#endif /* YYBTYACC */
#line 711 "prob1.y"

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
#line 758 "y.tab.c"

/* For use in generated program */
#define yydepth (int)(yystack.s_mark - yystack.s_base)
#if YYBTYACC
#define yytrial (yyps->save)
#endif /* YYBTYACC */

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE *newps;
#endif

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    newps = (YYLTYPE *)realloc(data->p_base, newsize * sizeof(*newps));
    if (newps == 0)
        return YYENOMEM;

    data->p_base = newps;
    data->p_mark = newps + i;
#endif

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;

#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%sdebug: stack size increased to %d\n", YYPREFIX, newsize);
#endif
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    free(data->p_base);
#endif
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif /* YYPURE || defined(YY_NO_LEAKS) */
#if YYBTYACC

static YYParseState *
yyNewState(unsigned size)
{
    YYParseState *p = (YYParseState *) malloc(sizeof(YYParseState));
    if (p == NULL) return NULL;

    p->yystack.stacksize = size;
    if (size == 0)
    {
        p->yystack.s_base = NULL;
        p->yystack.l_base = NULL;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        p->yystack.p_base = NULL;
#endif
        return p;
    }
    p->yystack.s_base    = (YYINT *) malloc(size * sizeof(YYINT));
    if (p->yystack.s_base == NULL) return NULL;
    p->yystack.l_base    = (YYSTYPE *) malloc(size * sizeof(YYSTYPE));
    if (p->yystack.l_base == NULL) return NULL;
    memset(p->yystack.l_base, 0, size * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    p->yystack.p_base    = (YYLTYPE *) malloc(size * sizeof(YYLTYPE));
    if (p->yystack.p_base == NULL) return NULL;
    memset(p->yystack.p_base, 0, size * sizeof(YYLTYPE));
#endif

    return p;
}

static void
yyFreeState(YYParseState *p)
{
    yyfreestack(&p->yystack);
    free(p);
}
#endif /* YYBTYACC */

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab
#if YYBTYACC
#define YYVALID        do { if (yyps->save)            goto yyvalid; } while(0)
#define YYVALID_NESTED do { if (yyps->save && \
                                yyps->save->save == 0) goto yyvalid; } while(0)
#endif /* YYBTYACC */

int
YYPARSE_DECL()
{
    int yym, yyn, yystate, yyresult;
#if YYBTYACC
    int yynewerrflag;
    YYParseState *yyerrctx = NULL;
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  yyerror_loc_range[3]; /* position of error start/end (0 unused) */
#endif
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
    if (yydebug)
        fprintf(stderr, "%sdebug[<# of symbols on state stack>]\n", YYPREFIX);
#endif
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    memset(yyerror_loc_range, 0, sizeof(yyerror_loc_range));
#endif

#if YYBTYACC
    yyps = yyNewState(0); if (yyps == 0) goto yyenomem;
    yyps->save = 0;
#endif /* YYBTYACC */
    yym = 0;
    /* yyn is set below */
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base;
#endif
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
#if YYBTYACC
        do {
        if (yylvp < yylve)
        {
            /* we're currently re-reading tokens */
            yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc = *yylpp++;
#endif
            yychar = *yylexp++;
            break;
        }
        if (yyps->save)
        {
            /* in trial mode; save scanner results for future parse attempts */
            if (yylvp == yylvlim)
            {   /* Enlarge lexical value queue */
                size_t p = (size_t) (yylvp - yylvals);
                size_t s = (size_t) (yylvlim - yylvals);

                s += YYLVQUEUEGROWTH;
                if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL) goto yyenomem;
                if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL) goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL) goto yyenomem;
#endif
                yylvp   = yylve = yylvals + p;
                yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp   = yylpe = yylpsns + p;
                yylplim = yylpsns + s;
#endif
                yylexp  = yylexemes + p;
            }
            *yylexp = (YYINT) YYLEX;
            *yylvp++ = yylval;
            yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *yylpp++ = yylloc;
            yylpe++;
#endif
            yychar = *yylexp++;
            break;
        }
        /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
        yychar = YYLEX;
#if YYBTYACC
        } while (0);
#endif /* YYBTYACC */
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, " <%s>", YYSTYPE_TOSTRING(yychar, yylval));
#endif
            fputc('\n', stderr);
        }
#endif
    }
#if YYBTYACC

    /* Do we have a conflict? */
    if (((yyn = yycindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
        yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        YYINT ctry;

        if (yypath)
        {
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: CONFLICT in state %d: following successful trial parse\n",
                                YYDEBUGSTR, yydepth, yystate);
#endif
            /* Switch to the next conflict context */
            save = yypath;
            yypath = save->save;
            save->save = NULL;
            ctry = save->ctry;
            if (save->state != yystate) YYABORT;
            yyFreeState(save);

        }
        else
        {

            /* Unresolved conflict - start/continue trial parse */
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
            {
                fprintf(stderr, "%s[%d]: CONFLICT in state %d. ", YYDEBUGSTR, yydepth, yystate);
                if (yyps->save)
                    fputs("ALREADY in conflict, continuing trial parse.\n", stderr);
                else
                    fputs("Starting trial parse.\n", stderr);
            }
#endif
            save                  = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (save == NULL) goto yyenomem;
            save->save            = yyps->save;
            save->state           = yystate;
            save->errflag         = yyerrflag;
            save->yystack.s_mark  = save->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (save->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            save->yystack.l_mark  = save->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (save->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            save->yystack.p_mark  = save->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (save->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            ctry                  = yytable[yyn];
            if (yyctable[ctry] == -1)
            {
#if YYDEBUG
                if (yydebug && yychar >= YYEOF)
                    fprintf(stderr, "%s[%d]: backtracking 1 token\n", YYDEBUGSTR, yydepth);
#endif
                ctry++;
            }
            save->ctry = ctry;
            if (yyps->save == NULL)
            {
                /* If this is a first conflict in the stack, start saving lexemes */
                if (!yylexemes)
                {
                    yylexemes = (YYINT *) malloc((YYLVQUEUEGROWTH) * sizeof(YYINT));
                    if (yylexemes == NULL) goto yyenomem;
                    yylvals   = (YYSTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYSTYPE));
                    if (yylvals == NULL) goto yyenomem;
                    yylvlim   = yylvals + YYLVQUEUEGROWTH;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpsns   = (YYLTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYLTYPE));
                    if (yylpsns == NULL) goto yyenomem;
                    yylplim   = yylpsns + YYLVQUEUEGROWTH;
#endif
                }
                if (yylvp == yylve)
                {
                    yylvp  = yylve = yylvals;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp  = yylpe = yylpsns;
#endif
                    yylexp = yylexemes;
                    if (yychar >= YYEOF)
                    {
                        *yylve++ = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                        *yylpe++ = yylloc;
#endif
                        *yylexp  = (YYINT) yychar;
                        yychar   = YYEMPTY;
                    }
                }
            }
            if (yychar >= YYEOF)
            {
                yylvp--;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp--;
#endif
                yylexp--;
                yychar = YYEMPTY;
            }
            save->lexeme = (int) (yylvp - yylvals);
            yyps->save   = save;
        }
        if (yytable[yyn] == ctry)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                                YYDEBUGSTR, yydepth, yystate, yyctable[ctry]);
#endif
            if (yychar < 0)
            {
                yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp++;
#endif
                yylexp++;
            }
            if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                goto yyoverflow;
            yystate = yyctable[ctry];
            *++yystack.s_mark = (YYINT) yystate;
            *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *++yystack.p_mark = yylloc;
#endif
            yychar  = YYEMPTY;
            if (yyerrflag > 0) --yyerrflag;
            goto yyloop;
        }
        else
        {
            yyn = yyctable[ctry];
            goto yyreduce;
        }
    } /* End of code dealing with conflicts */
#endif /* YYBTYACC */
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                            YYDEBUGSTR, yydepth, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yylloc;
#endif
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;
#if YYBTYACC

    yynewerrflag = 1;
    goto yyerrhandler;
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */

yyerrlab:
    /* explicit YYERROR from an action -- pop the rhs of the rule reduced
     * before looking for error recovery */
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif

    yynewerrflag = 0;
yyerrhandler:
    while (yyps->save)
    {
        int ctry;
        YYParseState *save = yyps->save;
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: ERROR in state %d, CONFLICT BACKTRACKING to state %d, %d tokens\n",
                            YYDEBUGSTR, yydepth, yystate, yyps->save->state,
                    (int)(yylvp - yylvals - yyps->save->lexeme));
#endif
        /* Memorize most forward-looking error state in case it's really an error. */
        if (yyerrctx == NULL || yyerrctx->lexeme < yylvp - yylvals)
        {
            /* Free old saved error context state */
            if (yyerrctx) yyFreeState(yyerrctx);
            /* Create and fill out new saved error context state */
            yyerrctx                 = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (yyerrctx == NULL) goto yyenomem;
            yyerrctx->save           = yyps->save;
            yyerrctx->state          = yystate;
            yyerrctx->errflag        = yyerrflag;
            yyerrctx->yystack.s_mark = yyerrctx->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (yyerrctx->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yyerrctx->yystack.l_mark = yyerrctx->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (yyerrctx->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yyerrctx->yystack.p_mark = yyerrctx->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (yyerrctx->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yyerrctx->lexeme         = (int) (yylvp - yylvals);
        }
        yylvp          = yylvals   + save->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yylpp          = yylpsns   + save->lexeme;
#endif
        yylexp         = yylexemes + save->lexeme;
        yychar         = YYEMPTY;
        yystack.s_mark = yystack.s_base + (save->yystack.s_mark - save->yystack.s_base);
        memcpy (yystack.s_base, save->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
        yystack.l_mark = yystack.l_base + (save->yystack.l_mark - save->yystack.l_base);
        memcpy (yystack.l_base, save->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yystack.p_mark = yystack.p_base + (save->yystack.p_mark - save->yystack.p_base);
        memcpy (yystack.p_base, save->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
        ctry           = ++save->ctry;
        yystate        = save->state;
        /* We tried shift, try reduce now */
        if ((yyn = yyctable[ctry]) >= 0) goto yyreduce;
        yyps->save     = save->save;
        save->save     = NULL;
        yyFreeState(save);

        /* Nothing left on the stack -- error */
        if (!yyps->save)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%sdebug[%d,trial]: trial parse FAILED, entering ERROR mode\n",
                                YYPREFIX, yydepth);
#endif
            /* Restore state as it was in the most forward-advanced error */
            yylvp          = yylvals   + yyerrctx->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylpp          = yylpsns   + yyerrctx->lexeme;
#endif
            yylexp         = yylexemes + yyerrctx->lexeme;
            yychar         = yylexp[-1];
            yylval         = yylvp[-1];
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc         = yylpp[-1];
#endif
            yystack.s_mark = yystack.s_base + (yyerrctx->yystack.s_mark - yyerrctx->yystack.s_base);
            memcpy (yystack.s_base, yyerrctx->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yystack.l_mark = yystack.l_base + (yyerrctx->yystack.l_mark - yyerrctx->yystack.l_base);
            memcpy (yystack.l_base, yyerrctx->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yystack.p_mark = yystack.p_base + (yyerrctx->yystack.p_mark - yyerrctx->yystack.p_base);
            memcpy (yystack.p_base, yyerrctx->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yystate        = yyerrctx->state;
            yyFreeState(yyerrctx);
            yyerrctx       = NULL;
        }
        yynewerrflag = 1;
    }
    if (yynewerrflag == 0) goto yyinrecovery;
#endif /* YYBTYACC */

    YYERROR_CALL("syntax error");
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yyerror_loc_range[1] = yylloc; /* lookahead position is error start position */
#endif

#if !YYBTYACC
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
#endif
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: state %d, error recovery shifting to state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* lookahead position is error end position */
                yyerror_loc_range[2] = yylloc;
                YYLLOC_DEFAULT(yyloc, yyerror_loc_range, 2); /* position of error span */
                *++yystack.p_mark = yyloc;
#endif
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: error recovery discarding state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* the current TOS position is the error start position */
                yyerror_loc_range[1] = *yystack.p_mark;
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
                if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark, yystack.p_mark);
#else
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
                --yystack.s_mark;
                --yystack.l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                --yystack.p_mark;
#endif
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, error recovery discarding token %d (%s)\n",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
        }
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval, &yylloc);
#else
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
    yym = yylen[yyn];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: state %d, reducing by rule %d (%s)",
                        YYDEBUGSTR, yydepth, yystate, yyn, yyrule[yyn]);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            if (yym > 0)
            {
                int i;
                fputc('<', stderr);
                for (i = yym; i > 0; i--)
                {
                    if (i != yym) fputs(", ", stderr);
                    fputs(YYSTYPE_TOSTRING(yystos[yystack.s_mark[1-i]],
                                           yystack.l_mark[1-i]), stderr);
                }
                fputc('>', stderr);
            }
#endif
        fputc('\n', stderr);
    }
#endif
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)

    /* Perform position reduction */
    memset(&yyloc, 0, sizeof(yyloc));
#if YYBTYACC
    if (!yytrial)
#endif /* YYBTYACC */
    {
        YYLLOC_DEFAULT(yyloc, &yystack.p_mark[-yym], yym);
        /* just in case YYERROR is invoked within the action, save
           the start of the rhs as the error start position */
        yyerror_loc_range[1] = yystack.p_mark[1-yym];
    }
#endif

    switch (yyn)
    {
case 1:
#line 150 "prob1.y"
	{create_scope();}
#line 1431 "y.tab.c"
break;
case 2:
#line 150 "prob1.y"
	{remove_scope(); printf("\n\nCompleted\n");}
#line 1436 "y.tab.c"
break;
case 7:
#line 156 "prob1.y"
	{printf("\nRejected");}
#line 1441 "y.tab.c"
break;
case 9:
#line 157 "prob1.y"
	{printf("\n");}
#line 1446 "y.tab.c"
break;
case 11:
#line 161 "prob1.y"
	{
					if(get_scoped_symbol(yystack.l_mark[0].lexeme) != NULL){
						printf("\nError : Variable %s already inside symbol table, exiting program\n", yystack.l_mark[0].lexeme);
						exit(0);
					}
					store_symbol(yystack.l_mark[0].lexeme, yystack.l_mark[-1].node->intValue, yystack.l_mark[-1].node->token, false);
					printf("\nNew variable %s", yystack.l_mark[0].lexeme);
				}
#line 1458 "y.tab.c"
break;
case 12:
#line 169 "prob1.y"
	{
					if(get_scoped_symbol(yystack.l_mark[0].lexeme) != NULL){
						printf("\nError : Variable %s already inside symbol table, exiting program\n", yystack.l_mark[0].lexeme);
						exit(0);
					}
					store_symbol(yystack.l_mark[0].lexeme, yystack.l_mark[-3].node->intValue, yystack.l_mark[-3].node->token, false);
					printf("\nNew variable %s", yystack.l_mark[0].lexeme);
				}
#line 1470 "y.tab.c"
break;
case 13:
#line 177 "prob1.y"
	{
					if(get_scoped_symbol(yystack.l_mark[-1].lexeme) != NULL){
						printf("\nError : Variable %s already inside symbol table, exiting program\n", yystack.l_mark[-1].lexeme);
						exit(0);
					}
					store_symbol(yystack.l_mark[-1].lexeme, yystack.l_mark[-4].node->intValue * yystack.l_mark[0].intValue, yystack.l_mark[-4].node->token, true);
					printf("\nNew variable %s", yystack.l_mark[-1].lexeme);
				}
#line 1482 "y.tab.c"
break;
case 14:
#line 186 "prob1.y"
	{
					yyval.intValue = yystack.l_mark[-3].intValue * yystack.l_mark[-1].intValue;
				}
#line 1489 "y.tab.c"
break;
case 15:
#line 189 "prob1.y"
	{
					yyval.intValue = yystack.l_mark[-1].intValue;
				}
#line 1496 "y.tab.c"
break;
case 16:
#line 193 "prob1.y"
	{
					yyval.node = malloc(sizeof(struct ASTNode));
					if(yyval.node == NULL){
						printf("Out of memory\n");
						exit(0);
					}
					yyval.node->intValue = 4;
					yyval.node->token = NODETYPE_INT_TYPE;
				}
#line 1509 "y.tab.c"
break;
case 17:
#line 202 "prob1.y"
	{
					yyval.node = malloc(sizeof(struct ASTNode));
					if(yyval.node == NULL){
						printf("Out of memory\n");
						exit(0);
					}
					yyval.node->intValue = 4;
					yyval.node->token = NODETYPE_FLOAT_TYPE;
				}
#line 1522 "y.tab.c"
break;
case 18:
#line 211 "prob1.y"
	{
					yyval.node = malloc(sizeof(struct ASTNode));
					if(yyval.node == NULL){
						printf("Out of memory\n");
						exit(0);
					}
					yyval.node->intValue = 1;
					yyval.node->token = NODETYPE_CHAR_TYPE;
				}
#line 1535 "y.tab.c"
break;
case 19:
#line 221 "prob1.y"
	{ yyval.node = yystack.l_mark[0].node;}
#line 1540 "y.tab.c"
break;
case 20:
#line 222 "prob1.y"
	{
				yyval.node = malloc(sizeof(struct ASTNode));
				if(yyval.node == NULL){
					printf("Out of memory\n");
					exit(0);
				}
				yyval.node->token = NODETYPE_OPERATOR;
				yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
				yyval.node->info.opInfo.right = yystack.l_mark[0].node;
				strcpy(yyval.node->info.opInfo.op, ",");
			}
#line 1555 "y.tab.c"
break;
case 21:
#line 234 "prob1.y"
	{ yyval.node = yystack.l_mark[0].node; }
#line 1560 "y.tab.c"
break;
case 22:
#line 235 "prob1.y"
	{
							yyval.node = malloc(sizeof(struct ASTNode));
							if(yyval.node == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							yyval.node->token = NODETYPE_OPERATOR;
							yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
							yyval.node->info.opInfo.right = yystack.l_mark[0].node;
							strcpy(yyval.node->info.opInfo.op, "=");
							yystack.l_mark[-2].node->intValue = yystack.l_mark[0].node->intValue;
							printf("\n%s = %s", yystack.l_mark[-2].node->lexeme, yystack.l_mark[0].node->temp_var);
						}
#line 1577 "y.tab.c"
break;
case 23:
#line 249 "prob1.y"
	{ yyval.node = yystack.l_mark[0].node; }
#line 1582 "y.tab.c"
break;
case 24:
#line 251 "prob1.y"
	{
							yyval.node = yystack.l_mark[0].node;
						}
#line 1589 "y.tab.c"
break;
case 25:
#line 254 "prob1.y"
	{
							yyval.node = malloc(sizeof(struct ASTNode));
							if(yyval.node == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							yyval.node->token = NODETYPE_OPERATOR;
							yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
							yyval.node->info.opInfo.right = yystack.l_mark[0].node;
							strcpy(yyval.node->info.opInfo.op, "||");
							genTemp();
							strcpy(yyval.node->temp_var, temp_var_g);
							yyval.node->intValue = yystack.l_mark[-2].node->intValue || yystack.l_mark[0].node->intValue;
							printf("\n%s = %s || %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var, yyval.node->info.opInfo.right->temp_var);
						}
#line 1608 "y.tab.c"
break;
case 26:
#line 270 "prob1.y"
	{
							yyval.node = yystack.l_mark[0].node;
						}
#line 1615 "y.tab.c"
break;
case 27:
#line 273 "prob1.y"
	{
							yyval.node = malloc(sizeof(struct ASTNode));
							if(yyval.node == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							yyval.node->token = NODETYPE_OPERATOR;
							yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
							yyval.node->info.opInfo.right = yystack.l_mark[0].node;
							strcpy(yyval.node->info.opInfo.op, "&&");
							genTemp();
							strcpy(yyval.node->temp_var, temp_var_g);
							yyval.node->intValue = yystack.l_mark[-2].node->intValue && yystack.l_mark[0].node->intValue;
							printf("\n%s = %s && %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var, yyval.node->info.opInfo.right->temp_var);
						}
#line 1634 "y.tab.c"
break;
case 28:
#line 289 "prob1.y"
	{
							yyval.node = yystack.l_mark[0].node;
						}
#line 1641 "y.tab.c"
break;
case 29:
#line 292 "prob1.y"
	{
							yyval.node = malloc(sizeof(struct ASTNode));
							if(yyval.node == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							yyval.node->token = NODETYPE_OPERATOR;
							yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
							yyval.node->info.opInfo.right = yystack.l_mark[0].node;
							strcpy(yyval.node->info.opInfo.op, "==");
							genTemp();
							strcpy(yyval.node->temp_var, temp_var_g);
							yyval.node->intValue = yystack.l_mark[-2].node->intValue == yystack.l_mark[0].node->intValue;
							printf("\n%s = %s == %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var, yyval.node->info.opInfo.right->temp_var);
						}
#line 1660 "y.tab.c"
break;
case 30:
#line 307 "prob1.y"
	{
							yyval.node = malloc(sizeof(struct ASTNode));
							if(yyval.node == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							yyval.node->token = NODETYPE_OPERATOR;
							yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
							yyval.node->info.opInfo.right = yystack.l_mark[0].node;
							strcpy(yyval.node->info.opInfo.op, "!=");
							genTemp();
							strcpy(yyval.node->temp_var, temp_var_g);
							yyval.node->intValue = yystack.l_mark[-2].node->intValue != yystack.l_mark[0].node->intValue;
							printf("\n%s = %s != %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var, yyval.node->info.opInfo.right->temp_var);
						}
#line 1679 "y.tab.c"
break;
case 31:
#line 323 "prob1.y"
	{
							yyval.node = yystack.l_mark[0].node;
						}
#line 1686 "y.tab.c"
break;
case 32:
#line 326 "prob1.y"
	{
							yyval.node = malloc(sizeof(struct ASTNode));
							if(yyval.node == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							yyval.node->token = NODETYPE_OPERATOR;
							yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
							yyval.node->info.opInfo.right = yystack.l_mark[0].node;
							strcpy(yyval.node->info.opInfo.op, "<");
							genTemp();
							strcpy(yyval.node->temp_var, temp_var_g);
							yyval.node->intValue = yystack.l_mark[-2].node->intValue < yystack.l_mark[0].node->intValue;
							printf("\n%s = %s < %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var, yyval.node->info.opInfo.right->temp_var);
						}
#line 1705 "y.tab.c"
break;
case 33:
#line 341 "prob1.y"
	{
							yyval.node = malloc(sizeof(struct ASTNode));
							if(yyval.node == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							yyval.node->token = NODETYPE_OPERATOR;
							yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
							yyval.node->info.opInfo.right = yystack.l_mark[0].node;
							strcpy(yyval.node->info.opInfo.op, ">");
							genTemp();
							strcpy(yyval.node->temp_var, temp_var_g);
							yyval.node->intValue = yystack.l_mark[-2].node->intValue > yystack.l_mark[0].node->intValue;
							printf("\n%s = %s > %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var, yyval.node->info.opInfo.right->temp_var);
						}
#line 1724 "y.tab.c"
break;
case 34:
#line 356 "prob1.y"
	{
							yyval.node = malloc(sizeof(struct ASTNode));
							if(yyval.node == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							yyval.node->token = NODETYPE_OPERATOR;
							yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
							yyval.node->info.opInfo.right = yystack.l_mark[0].node;
							strcpy(yyval.node->info.opInfo.op, "<=");
							genTemp();
							strcpy(yyval.node->temp_var, temp_var_g);
							yyval.node->intValue = yystack.l_mark[-2].node->intValue <= yystack.l_mark[0].node->intValue;
							printf("\n%s = %s <= %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var, yyval.node->info.opInfo.right->temp_var);
						}
#line 1743 "y.tab.c"
break;
case 35:
#line 371 "prob1.y"
	{
							yyval.node = malloc(sizeof(struct ASTNode));
							if(yyval.node == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							yyval.node->token = NODETYPE_OPERATOR;
							yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
							yyval.node->info.opInfo.right = yystack.l_mark[0].node;
							strcpy(yyval.node->info.opInfo.op, ">=");
							genTemp();
							strcpy(yyval.node->temp_var, temp_var_g);
							yyval.node->intValue = yystack.l_mark[-2].node->intValue >= yystack.l_mark[0].node->intValue;
							printf("\n%s = %s >= %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var, yyval.node->info.opInfo.right->temp_var);
						}
#line 1762 "y.tab.c"
break;
case 36:
#line 387 "prob1.y"
	{
						yyval.node = yystack.l_mark[0].node;
					}
#line 1769 "y.tab.c"
break;
case 37:
#line 390 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if(yyval.node == NULL){
							printf("Out of memory\n");
							exit(0);
						}

						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
						yyval.node->info.opInfo.right = yystack.l_mark[0].node;
						strcpy(yyval.node->info.opInfo.op, "+");
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						yyval.node->intValue = yystack.l_mark[-2].node->intValue + yystack.l_mark[0].node->intValue;
						printf("\n%s = %s + %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var, yyval.node->info.opInfo.right->temp_var);
					}
#line 1789 "y.tab.c"
break;
case 38:
#line 406 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if(yyval.node == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
						yyval.node->info.opInfo.right = yystack.l_mark[0].node;
						strcpy(yyval.node->info.opInfo.op, "-");
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						yyval.node->intValue = yystack.l_mark[-2].node->intValue - yystack.l_mark[0].node->intValue;
						printf("\n%s = %s - %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var, yyval.node->info.opInfo.right->temp_var);
					}
#line 1808 "y.tab.c"
break;
case 39:
#line 422 "prob1.y"
	{
								yyval.node = yystack.l_mark[0].node;
							}
#line 1815 "y.tab.c"
break;
case 40:
#line 425 "prob1.y"
	{
								yyval.node = malloc(sizeof(struct ASTNode));
								if(yyval.node == NULL){
									printf("Out of memory\n");
									exit(0);
								}
								yyval.node->token = NODETYPE_OPERATOR;
								yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
								yyval.node->info.opInfo.right = yystack.l_mark[0].node;
								strcpy(yyval.node->info.opInfo.op, "*");
								genTemp();
								strcpy(yyval.node->temp_var, temp_var_g);
								yyval.node->intValue = yystack.l_mark[-2].node->intValue * yystack.l_mark[0].node->intValue;
								printf("\n%s = %s * %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var, yyval.node->info.opInfo.right->temp_var);
							}
#line 1834 "y.tab.c"
break;
case 41:
#line 440 "prob1.y"
	{
								yyval.node = malloc(sizeof(struct ASTNode));
								if(yyval.node == NULL){
									printf("Out of memory\n");
									exit(0);
								}
								yyval.node->token = NODETYPE_OPERATOR;
								yyval.node->info.opInfo.left = yystack.l_mark[-2].node;
								yyval.node->info.opInfo.right = yystack.l_mark[0].node;
								strcpy(yyval.node->info.opInfo.op, "/");
								genTemp();
								strcpy(yyval.node->temp_var, temp_var_g);
								yyval.node->intValue = yystack.l_mark[-2].node->intValue / yystack.l_mark[0].node->intValue;
								printf("\n%s = %s / %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var, yyval.node->info.opInfo.right->temp_var);
							}
#line 1853 "y.tab.c"
break;
case 42:
#line 456 "prob1.y"
	{
						yyval.node = yystack.l_mark[0].node;
					}
#line 1860 "y.tab.c"
break;
case 43:
#line 459 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if(yyval.node == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.right = yystack.l_mark[0].node;
						strcpy(yyval.node->info.opInfo.op, "++");
						strcpy(yyval.node->lexeme, yystack.l_mark[0].node->lexeme);
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						yystack.l_mark[0].node->intValue = yystack.l_mark[0].node->intValue + 1;
						printf("\n%s = %s + 1", yystack.l_mark[0].node->temp_var, yystack.l_mark[0].node->temp_var);
						yyval.node->intValue = yystack.l_mark[0].node->intValue;
						printf("\n%s = %s", yyval.node->temp_var, yyval.node->info.opInfo.right->temp_var);
					}
#line 1881 "y.tab.c"
break;
case 44:
#line 476 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if(yyval.node == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.right = yystack.l_mark[0].node;
						strcpy(yyval.node->info.opInfo.op, "--");
						strcpy(yyval.node->lexeme, yystack.l_mark[0].node->lexeme);
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						yystack.l_mark[0].node->intValue = yystack.l_mark[0].node->intValue - 1;
						printf("\n%s = %s - 1", yystack.l_mark[0].node->temp_var, yystack.l_mark[0].node->temp_var);
						yyval.node->intValue = yystack.l_mark[0].node->intValue;
						printf("\n%s = %s", yyval.node->temp_var, yyval.node->info.opInfo.right->temp_var);
					}
#line 1902 "y.tab.c"
break;
case 45:
#line 493 "prob1.y"
	{
						yyval.node = yystack.l_mark[0].node;
					}
#line 1909 "y.tab.c"
break;
case 46:
#line 496 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if(yyval.node == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.right = yystack.l_mark[0].node;
						strcpy(yyval.node->info.opInfo.op, "minus");
						strcpy(yyval.node->lexeme, yystack.l_mark[0].node->lexeme);
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						yyval.node->intValue = -1 * yystack.l_mark[0].node->intValue;
						printf("\n%s = -1 * %s", yyval.node->temp_var, yyval.node->info.opInfo.right->temp_var);
					}
#line 1928 "y.tab.c"
break;
case 47:
#line 511 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if(yyval.node == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.right = yystack.l_mark[0].node;
						strcpy(yyval.node->info.opInfo.op, "!");
						strcpy(yyval.node->lexeme, yystack.l_mark[0].node->lexeme);
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						yyval.node->intValue = !yystack.l_mark[0].node->intValue;
						printf("\n%s = !%s", yyval.node->temp_var, yyval.node->info.opInfo.right->temp_var);
					}
#line 1947 "y.tab.c"
break;
case 48:
#line 527 "prob1.y"
	{
						yyval.node = yystack.l_mark[0].node;
					}
#line 1954 "y.tab.c"
break;
case 49:
#line 530 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if (yyval.node == NULL) {
							yyerror("no mem");
						}
						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.left = yystack.l_mark[-1].node;
						yyval.node->intValue = yystack.l_mark[-1].node->intValue;
						strcpy(yyval.node->info.opInfo.op, "++");
						strcpy(yyval.node->lexeme, yystack.l_mark[-1].node->lexeme);
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						printf("\n%s = %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var);
						yystack.l_mark[-1].node->intValue = yystack.l_mark[-1].node->intValue + 1;
						printf("\n%s = %s + 1", yystack.l_mark[-1].node->temp_var, yystack.l_mark[-1].node->temp_var);
					}
#line 1974 "y.tab.c"
break;
case 50:
#line 546 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if (yyval.node == NULL) {
							yyerror("no mem");
						}
						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.left = yystack.l_mark[-1].node;
						strcpy(yyval.node->info.opInfo.op, "--");
						strcpy(yyval.node->lexeme, yystack.l_mark[-1].node->lexeme);
						yyval.node->intValue = yystack.l_mark[-1].node->intValue;
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						printf("\n%s = %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var);
						yystack.l_mark[-1].node->intValue = yystack.l_mark[-1].node->intValue - 1;
						printf("\n%s = %s - 1", yystack.l_mark[-1].node->temp_var, yystack.l_mark[-1].node->temp_var);
					}
#line 1994 "y.tab.c"
break;
case 51:
#line 563 "prob1.y"
	{
						yyval.node = malloc(sizeof(ASTNode));
						if(yyval.node == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						yyval.node->token = NODETYPE_CONSTANT_INT;
						yyval.node->intValue = yystack.l_mark[0].intValue;
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						printf("\n%s = %d", yyval.node->temp_var, yyval.node->intValue);
					}
#line 2010 "y.tab.c"
break;
case 52:
#line 575 "prob1.y"
	{
						if(lead_symbol(yystack.l_mark[0].lexeme) == NULL){
							printf("\nError : Variable %s not in symbol table, exiting program\n", yystack.l_mark[0].lexeme);
							exit(0);
						}
						yyval.node = malloc(sizeof(ASTNode));
						if(yyval.node == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						yyval.node->token = NODETYPE_IDENTIFIER;
						strcpy(yyval.node->lexeme, yystack.l_mark[0].lexeme);
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						printf("\n%s = %s", yyval.node->temp_var, yyval.node->lexeme);
					}
#line 2030 "y.tab.c"
break;
case 53:
#line 591 "prob1.y"
	{
						yyval.node = yystack.l_mark[-1].node;
					}
#line 2037 "y.tab.c"
break;
case 54:
#line 595 "prob1.y"
	{
							create_scope();
							yyval.node = malloc(sizeof(struct ASTNode));
							if(yyval.node == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							yyval.node->token = NODETYPE_IF_ELSE;
							yyval.node->info.flowControlInfo.condition = yystack.l_mark[-2].node;
							genLabel();
							strcpy(yyval.node->info.flowControlInfo.true_label, label_g);
							genLabel();
							strcpy(yyval.node->info.flowControlInfo.false_label, label_g);
							genLabel();
							strcpy(yyval.node->info.flowControlInfo.next_label, label_g);
							printf("\nif %s goto %s", yyval.node->info.flowControlInfo.condition->temp_var, yyval.node->info.flowControlInfo.true_label);
							printf("\ngoto %s", yyval.node->info.flowControlInfo.false_label);
							printf("\n\n%s:", yyval.node->info.flowControlInfo.true_label);
						}
#line 2060 "y.tab.c"
break;
case 55:
#line 613 "prob1.y"
	{
							yyval.node = yystack.l_mark[-1].node;
							yyval.node->info.flowControlInfo.trueBranch = yystack.l_mark[0].node;
							printf("\ngoto %s", yyval.node->info.flowControlInfo.next_label);
							printf("\n\n%s:", yyval.node->info.flowControlInfo.false_label);
							remove_scope();
						}
#line 2071 "y.tab.c"
break;
case 56:
#line 619 "prob1.y"
	{
							yyval.node = yystack.l_mark[-2].node;
							ASTNode *temp = yystack.l_mark[0].node;
							if(temp != NULL){
								yyval.node->info.flowControlInfo.falseBranch = temp;
							}
							printf("\n\n%s:", yyval.node->info.flowControlInfo.next_label);
						}
#line 2083 "y.tab.c"
break;
case 57:
#line 627 "prob1.y"
	{
							yyval.node = malloc(sizeof(struct ASTNode));
							if(yyval.node == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							yyval.node->token = NODETYPE_SWITCH;
							genLabel();
							strcpy(yyval.node->info.flowControlInfo.next_label, label_g);
							strcpy(yyval.node->temp_var, yystack.l_mark[-2].node->temp_var);
							if(switchStackTop >= 100){
								printf("Switch Stack overflow\n");
								exit(0);
							}
							switchStackTop++;
							strcpy(switchStack[switchStackTop].temp_var, yyval.node->temp_var);
							strcpy(switchStack[switchStackTop].out_label, yyval.node->info.flowControlInfo.next_label);
						}
#line 2105 "y.tab.c"
break;
case 58:
#line 644 "prob1.y"
	{
							yyval.node = yystack.l_mark[-2].node;
							switchStackTop--;
							printf("\n\n%s:", yyval.node->info.flowControlInfo.next_label);
						}
#line 2114 "y.tab.c"
break;
case 59:
#line 650 "prob1.y"
	{
						create_scope();
						yyval.node = malloc(sizeof(struct ASTNode));
						if(yyval.node == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						genLabel();
						strcpy(yyval.node->info.flowControlInfo.false_label, label_g);
						printf("\nifFalse %s = %s goto %s", switchStack[switchStackTop].temp_var, yystack.l_mark[0].node->temp_var, label_g);
					}
#line 2129 "y.tab.c"
break;
case 60:
#line 660 "prob1.y"
	{
						remove_scope();
						printf("\n\n%s:", yystack.l_mark[-3].node->info.flowControlInfo.false_label);
					}
#line 2137 "y.tab.c"
break;
case 61:
#line 663 "prob1.y"
	{yyval.node = yystack.l_mark[-5].node;}
#line 2142 "y.tab.c"
break;
case 62:
#line 664 "prob1.y"
	{create_scope();}
#line 2147 "y.tab.c"
break;
case 63:
#line 664 "prob1.y"
	{remove_scope();}
#line 2152 "y.tab.c"
break;
case 64:
#line 664 "prob1.y"
	{
						yyval.node = NULL;
					}
#line 2159 "y.tab.c"
break;
case 65:
#line 667 "prob1.y"
	{yyval.node=NULL;printf("\ngoto %s", switchStack[switchStackTop].out_label); }
#line 2164 "y.tab.c"
break;
case 66:
#line 669 "prob1.y"
	{
					printf("\ngoto %s", switchStack[switchStackTop].out_label);
				}
#line 2171 "y.tab.c"
break;
case 67:
#line 672 "prob1.y"
	{}
#line 2176 "y.tab.c"
break;
case 68:
#line 675 "prob1.y"
	{create_scope();}
#line 2181 "y.tab.c"
break;
case 69:
#line 675 "prob1.y"
	{
					remove_scope();
					yyval.node = yystack.l_mark[-1].node;
				}
#line 2189 "y.tab.c"
break;
case 70:
#line 678 "prob1.y"
	{ yyval.node = NULL;}
#line 2194 "y.tab.c"
break;
case 71:
#line 680 "prob1.y"
	{
							yyval.node = malloc(sizeof(struct ASTNode));
							if(yyval.node == NULL){
								printf("Out of memory\n");
								exit(0);
							}
							yyval.node->token = NODETYPE_WHILE;
							genLabel();
							strcpy(yyval.node->info.flowControlInfo.condition_label, label_g);
							genLabel();
							strcpy(yyval.node->info.flowControlInfo.true_label, label_g);
							genLabel();
							strcpy(yyval.node->info.flowControlInfo.false_label, label_g);
							printf("\n\n%s:", yyval.node->info.flowControlInfo.condition_label);
						}
#line 2213 "y.tab.c"
break;
case 72:
#line 694 "prob1.y"
	{
							yyval.node = yystack.l_mark[-2].node;
							yyval.node->info.flowControlInfo.condition = yystack.l_mark[0].node;
							printf("\nif %s goto %s", yyval.node->info.flowControlInfo.condition->temp_var, yyval.node->info.flowControlInfo.true_label);
							printf("\ngoto %s", yyval.node->info.flowControlInfo.false_label);
							printf("\n\n%s:", yyval.node->info.flowControlInfo.true_label);
							create_scope();
						}
#line 2225 "y.tab.c"
break;
case 73:
#line 701 "prob1.y"
	{
							remove_scope();
							yyval.node = yystack.l_mark[-4].node;
							yyval.node->info.flowControlInfo.trueBranch = yystack.l_mark[-1].node;
							printf("\ngoto %s", yyval.node->info.flowControlInfo.condition_label);
							printf("\n\n%s:", yyval.node->info.flowControlInfo.false_label);
						}
#line 2236 "y.tab.c"
break;
#line 2238 "y.tab.c"
    default:
        break;
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
        {
            fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[YYFINAL], yyval));
#endif
            fprintf(stderr, "shifting from state 0 to final state %d\n", YYFINAL);
        }
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yyloc;
#endif
        if (yychar < 0)
        {
#if YYBTYACC
            do {
            if (yylvp < yylve)
            {
                /* we're currently re-reading tokens */
                yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylloc = *yylpp++;
#endif
                yychar = *yylexp++;
                break;
            }
            if (yyps->save)
            {
                /* in trial mode; save scanner results for future parse attempts */
                if (yylvp == yylvlim)
                {   /* Enlarge lexical value queue */
                    size_t p = (size_t) (yylvp - yylvals);
                    size_t s = (size_t) (yylvlim - yylvals);

                    s += YYLVQUEUEGROWTH;
                    if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL)
                        goto yyenomem;
                    if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL)
                        goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL)
                        goto yyenomem;
#endif
                    yylvp   = yylve = yylvals + p;
                    yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp   = yylpe = yylpsns + p;
                    yylplim = yylpsns + s;
#endif
                    yylexp  = yylexemes + p;
                }
                *yylexp = (YYINT) YYLEX;
                *yylvp++ = yylval;
                yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                *yylpp++ = yylloc;
                yylpe++;
#endif
                yychar = *yylexp++;
                break;
            }
            /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
            yychar = YYLEX;
#if YYBTYACC
            } while (0);
#endif /* YYBTYACC */
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)\n",
                                YYDEBUGSTR, yydepth, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[yystate], yyval));
#endif
        fprintf(stderr, "shifting from state %d to state %d\n", *yystack.s_mark, yystate);
    }
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    *++yystack.p_mark = yyloc;
#endif
    goto yyloop;
#if YYBTYACC

    /* Reduction declares that this path is valid. Set yypath and do a full parse */
yyvalid:
    if (yypath) YYABORT;
    while (yyps->save)
    {
        YYParseState *save = yyps->save;
        yyps->save = save->save;
        save->save = yypath;
        yypath = save;
    }
#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%s[%d]: state %d, CONFLICT trial successful, backtracking to state %d, %d tokens\n",
                        YYDEBUGSTR, yydepth, yystate, yypath->state, (int)(yylvp - yylvals - yypath->lexeme));
#endif
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    yylvp          = yylvals + yypath->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yylpp          = yylpsns + yypath->lexeme;
#endif
    yylexp         = yylexemes + yypath->lexeme;
    yychar         = YYEMPTY;
    yystack.s_mark = yystack.s_base + (yypath->yystack.s_mark - yypath->yystack.s_base);
    memcpy (yystack.s_base, yypath->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
    yystack.l_mark = yystack.l_base + (yypath->yystack.l_mark - yypath->yystack.l_base);
    memcpy (yystack.l_base, yypath->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base + (yypath->yystack.p_mark - yypath->yystack.p_base);
    memcpy (yystack.p_base, yypath->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
    yystate        = yypath->state;
    goto yyloop;
#endif /* YYBTYACC */

yyoverflow:
    YYERROR_CALL("yacc stack overflow");
#if YYBTYACC
    goto yyabort_nomem;
yyenomem:
    YYERROR_CALL("memory exhausted");
yyabort_nomem:
#endif /* YYBTYACC */
    yyresult = 2;
    goto yyreturn;

yyabort:
    yyresult = 1;
    goto yyreturn;

yyaccept:
#if YYBTYACC
    if (yyps->save) goto yyvalid;
#endif /* YYBTYACC */
    yyresult = 0;

yyreturn:
#if defined(YYDESTRUCT_CALL)
    if (yychar != YYEOF && yychar != YYEMPTY)
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval, &yylloc);
#else
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */

    {
        YYSTYPE *pv;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYLTYPE *pp;

        for (pv = yystack.l_base, pp = yystack.p_base; pv <= yystack.l_mark; ++pv, ++pp)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv, pp);
#else
        for (pv = yystack.l_base; pv <= yystack.l_mark; ++pv)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
    }
#endif /* defined(YYDESTRUCT_CALL) */

#if YYBTYACC
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    while (yyps)
    {
        YYParseState *save = yyps;
        yyps = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
    while (yypath)
    {
        YYParseState *save = yypath;
        yypath = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
#endif /* YYBTYACC */
    yyfreestack(&yystack);
    return (yyresult);
}
