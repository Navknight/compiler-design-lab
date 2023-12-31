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
int yylex();
int yyerror(char *);
int eflag=0;
int label_count=0;
int temp_count=0;
char temp_var_g[20];
char label_g[20];
extern FILE * yyin;

typedef struct ASTNode {
    enum { 
        NODETYPE_CONSTANT_INT, 
        NODETYPE_IDENTIFIER, 
        NODETYPE_OPERATOR,
        NODETYPE_IF_ELSE,
        NODETYPE_WHILE
    } token;

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
#line 48 "prob1.y"
typedef union YYSTYPE{
	int intValue;
	char lexeme[20];
	struct ASTNode *node;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 82 "y.tab.c"

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
#define IF 271
#define ELSE 272
#define WHILE 273
#define LT 274
#define GT 275
#define LEQ 276
#define GEQ 277
#define EQ 278
#define NEQ 279
#define AND 280
#define OR 281
#define NOT 282
#define INTEGER 283
#define IDENTIFIER 284
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    1,    1,    1,    2,    2,    3,    4,
    4,    5,    5,    6,    6,    6,    7,    7,    7,    7,
    7,    8,    8,    8,    9,    9,    9,   10,   10,   10,
   10,   10,   10,   11,   11,   11,   12,   12,   12,   16,
   17,   13,   14,   14,   18,   19,   15,
};
static const YYINT yylen[] = {                            2,
    1,    3,    2,    2,    2,    0,    1,    3,    1,    1,
    3,    1,    3,    1,    3,    3,    1,    3,    3,    3,
    3,    1,    3,    3,    1,    3,    3,    1,    2,    2,
    2,    2,    2,    1,    2,    2,    1,    1,    3,    0,
    0,   10,    4,    0,    0,    0,    9,
};
static const YYINT yydefred[] = {                         6,
    0,    0,    5,    0,    0,    0,    0,    0,    0,   45,
    0,   37,   38,    0,    7,    0,    0,    0,    0,    0,
    0,    0,    0,   34,    3,    4,   31,   32,   29,   30,
    0,    0,    0,   33,    2,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   35,   36,
   39,    0,    0,    0,   25,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   26,   27,    8,    0,   46,   40,
    0,    6,    0,    0,    6,    0,    0,    0,   47,    0,
   42,    6,    0,   43,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  286,  287,  256,  257,  258,  261,  262,  264,  271,  273,
  282,  283,  284,  288,  289,  290,  291,  292,  293,  294,
  295,  296,  297,  298,  299,  301,  296,  296,  296,  296,
  288,  264,  304,  296,  270,  281,  280,  278,  279,  274,
  275,  276,  277,  257,  258,  259,  260,  263,  261,  262,
  265,  288,  264,  291,  296,  292,  293,  293,  294,  294,
  294,  294,  295,  295,  296,  296,  288,  265,  288,  266,
  305,  302,  265,  287,  266,  303,  287,  267,  267,  272,
  300,  266,  287,  267,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          1,
    2,   14,   15,   16,   17,   18,   19,   20,   21,   55,
   23,   24,   25,   81,   26,   72,   76,   33,   71,
};
static const YYINT yysindex[] = {                         0,
    0, -171,    0, -229, -229, -229, -229, -229, -247,    0,
 -229,    0,    0, -250,    0, -259, -254, -238, -151, -192,
 -190, -221, -167,    0,    0,    0,    0,    0,    0,    0,
 -205, -229, -184,    0,    0, -229, -229, -229, -229, -229,
 -229, -229, -229, -229, -229, -229, -229, -229,    0,    0,
    0, -191, -229, -254,    0, -238, -151, -151, -192, -192,
 -192, -192, -190, -190,    0,    0,    0, -170,    0,    0,
 -164,    0, -163, -171,    0, -158, -246, -168,    0, -156,
    0,    0, -200,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,  118,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -251, -222, -257, -202,  -26,
  -93, -118, -143,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -115,    0, -231, -173,   80,   12,   29,
   46,   63,  -68,  -43,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -148,    0,    0,    0,    1,    0,    0,
    0,    0,    0,    0,
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
    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
   71,   -1,    0,    0,   85,   91,   50,  127,   54,   -2,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 361
static const YYINT yytable[] = {                         22,
   44,   27,   28,   29,   30,   22,   31,   12,   34,    3,
    4,    5,   12,    9,    6,    7,   32,    8,    9,   35,
   79,   36,   12,   12,    9,   37,   10,    4,    5,   22,
   52,    6,    7,   13,    8,   11,   12,   13,   13,   38,
   39,   48,   10,   65,   66,   22,   67,   10,   13,   13,
   22,   69,   11,   12,   13,    3,    4,    5,   10,   51,
    6,    7,   14,    8,   44,   45,   84,   14,   46,   47,
    9,   22,   10,   68,   22,   14,   14,   14,   14,   53,
   22,   11,   12,   13,    3,    4,    5,   57,   58,    6,
    7,   15,    8,   49,   50,   70,   15,   63,   64,    9,
   73,   10,   75,   80,   15,   15,   15,   15,   78,   82,
   11,   12,   13,   28,   28,   28,   28,    1,   41,   28,
   54,   28,   40,   41,   42,   43,   28,   56,    0,    0,
   28,   28,   28,   28,   28,   28,   28,   28,   25,   25,
   25,   25,   74,    0,    0,   77,   25,    0,    0,   11,
    0,   25,   83,    0,   11,   25,   25,   25,   25,   25,
   25,   25,   25,   22,   22,   11,   59,   60,   61,   62,
    0,   22,    0,    0,    0,    0,   22,    0,    0,    0,
   22,   22,   22,   22,   22,   22,   22,   22,   23,   23,
    0,    0,    0,    0,    0,    0,   23,    0,    0,    0,
    0,   23,    0,    0,    0,   23,   23,   23,   23,   23,
   23,   23,   23,   24,   24,    0,    0,    0,    0,    0,
    0,   24,    0,    0,    0,    0,   24,    0,    0,    0,
   24,   24,   24,   24,   24,   24,   24,   24,   17,    0,
    0,    0,    0,   17,    0,    0,    0,   17,   17,   17,
   17,   17,   17,   17,   17,    0,   44,   44,   44,    0,
    0,   44,   44,    0,   44,    0,    0,   44,    0,    0,
    0,   44,    0,   44,    0,    0,   18,    0,    0,    0,
    0,   18,   44,   44,   44,   18,   18,   18,   18,   18,
   18,   18,   18,   19,    0,    0,    0,    0,   19,    0,
    0,    0,   19,   19,   19,   19,   19,   19,   19,   19,
   20,    0,    0,    0,    0,   20,    0,    0,    0,   20,
   20,   20,   20,   20,   20,   20,   20,   21,    0,    0,
    0,    0,   21,    0,    0,    0,   21,   21,   21,   21,
   21,   21,   21,   21,   16,    0,    0,    0,    0,   16,
    0,    0,    0,    0,    0,    0,    0,   16,   16,   16,
   16,
};
static const YYINT yycheck[] = {                          2,
    0,    4,    5,    6,    7,    8,    8,  265,   11,  256,
  257,  258,  270,  265,  261,  262,  264,  264,  270,  270,
  267,  281,  280,  281,  271,  280,  273,  257,  258,   32,
   32,  261,  262,  265,  264,  282,  283,  284,  270,  278,
  279,  263,  265,   46,   47,   48,   48,  270,  280,  281,
   53,   53,  282,  283,  284,  256,  257,  258,  281,  265,
  261,  262,  265,  264,  257,  258,  267,  270,  259,  260,
  271,   74,  273,  265,   77,  278,  279,  280,  281,  264,
   83,  282,  283,  284,  256,  257,  258,   38,   39,  261,
  262,  265,  264,  261,  262,  266,  270,   44,   45,  271,
  265,  273,  266,  272,  278,  279,  280,  281,  267,  266,
  282,  283,  284,  257,  258,  259,  260,    0,  267,  263,
   36,  265,  274,  275,  276,  277,  270,   37,   -1,   -1,
  274,  275,  276,  277,  278,  279,  280,  281,  257,  258,
  259,  260,   72,   -1,   -1,   75,  265,   -1,   -1,  265,
   -1,  270,   82,   -1,  270,  274,  275,  276,  277,  278,
  279,  280,  281,  257,  258,  281,   40,   41,   42,   43,
   -1,  265,   -1,   -1,   -1,   -1,  270,   -1,   -1,   -1,
  274,  275,  276,  277,  278,  279,  280,  281,  257,  258,
   -1,   -1,   -1,   -1,   -1,   -1,  265,   -1,   -1,   -1,
   -1,  270,   -1,   -1,   -1,  274,  275,  276,  277,  278,
  279,  280,  281,  257,  258,   -1,   -1,   -1,   -1,   -1,
   -1,  265,   -1,   -1,   -1,   -1,  270,   -1,   -1,   -1,
  274,  275,  276,  277,  278,  279,  280,  281,  265,   -1,
   -1,   -1,   -1,  270,   -1,   -1,   -1,  274,  275,  276,
  277,  278,  279,  280,  281,   -1,  256,  257,  258,   -1,
   -1,  261,  262,   -1,  264,   -1,   -1,  267,   -1,   -1,
   -1,  271,   -1,  273,   -1,   -1,  265,   -1,   -1,   -1,
   -1,  270,  282,  283,  284,  274,  275,  276,  277,  278,
  279,  280,  281,  265,   -1,   -1,   -1,   -1,  270,   -1,
   -1,   -1,  274,  275,  276,  277,  278,  279,  280,  281,
  265,   -1,   -1,   -1,   -1,  270,   -1,   -1,   -1,  274,
  275,  276,  277,  278,  279,  280,  281,  265,   -1,   -1,
   -1,   -1,  270,   -1,   -1,   -1,  274,  275,  276,  277,
  278,  279,  280,  281,  265,   -1,   -1,   -1,   -1,  270,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  278,  279,  280,
  281,
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
};
#endif
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 284
#define YYUNDFTOKEN 306
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
"SEMICOLON","IF","ELSE","WHILE","LT","GT","LEQ","GEQ","EQ","NEQ","AND","OR",
"NOT","INTEGER","IDENTIFIER","$accept","program","slist","assignmentExpression",
"conditionalExpression","logicalOrExpression","logicalAndExpression",
"equalityExpression","relationalExpression","additiveExpression",
"multiplicativeExpression","unaryExpression","postfixExpression",
"primaryExpression","selectionStatement","elseSelection","iterationStatement",
"$$1","$$2","$$3","$$4","illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : slist",
"slist : slist assignmentExpression SEMICOLON",
"slist : slist selectionStatement",
"slist : slist iterationStatement",
"slist : slist error",
"slist :",
"assignmentExpression : conditionalExpression",
"assignmentExpression : unaryExpression ASSIGN assignmentExpression",
"conditionalExpression : logicalOrExpression",
"logicalOrExpression : logicalAndExpression",
"logicalOrExpression : logicalOrExpression OR logicalAndExpression",
"logicalAndExpression : equalityExpression",
"logicalAndExpression : logicalAndExpression AND equalityExpression",
"equalityExpression : relationalExpression",
"equalityExpression : equalityExpression EQ relationalExpression",
"equalityExpression : equalityExpression NEQ relationalExpression",
"relationalExpression : additiveExpression",
"relationalExpression : relationalExpression LT additiveExpression",
"relationalExpression : relationalExpression GT additiveExpression",
"relationalExpression : relationalExpression LEQ additiveExpression",
"relationalExpression : relationalExpression GEQ additiveExpression",
"additiveExpression : multiplicativeExpression",
"additiveExpression : additiveExpression ADD multiplicativeExpression",
"additiveExpression : additiveExpression SUB multiplicativeExpression",
"multiplicativeExpression : unaryExpression",
"multiplicativeExpression : multiplicativeExpression MUL unaryExpression",
"multiplicativeExpression : multiplicativeExpression DIV unaryExpression",
"unaryExpression : postfixExpression",
"unaryExpression : INC unaryExpression",
"unaryExpression : DEC unaryExpression",
"unaryExpression : ADD unaryExpression",
"unaryExpression : SUB unaryExpression",
"unaryExpression : NOT unaryExpression",
"postfixExpression : primaryExpression",
"postfixExpression : postfixExpression INC",
"postfixExpression : postfixExpression DEC",
"primaryExpression : INTEGER",
"primaryExpression : IDENTIFIER",
"primaryExpression : LPAREN assignmentExpression RPAREN",
"$$1 :",
"$$2 :",
"selectionStatement : IF LPAREN assignmentExpression RPAREN LBRACE $$1 slist $$2 RBRACE elseSelection",
"elseSelection : ELSE LBRACE slist RBRACE",
"elseSelection :",
"$$3 :",
"$$4 :",
"iterationStatement : WHILE $$3 LPAREN assignmentExpression $$4 RPAREN LBRACE slist RBRACE",

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
#line 486 "prob1.y"

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
#line 586 "y.tab.c"

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
#line 61 "prob1.y"
	{printf("\n\nCompleted\n");}
#line 1259 "y.tab.c"
break;
case 5:
#line 66 "prob1.y"
	{printf("\nRejected");}
#line 1264 "y.tab.c"
break;
case 6:
#line 67 "prob1.y"
	{printf("\n");}
#line 1269 "y.tab.c"
break;
case 7:
#line 69 "prob1.y"
	{ yyval.node = yystack.l_mark[0].node; }
#line 1274 "y.tab.c"
break;
case 8:
#line 70 "prob1.y"
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
							genTemp();
							strcpy(yyval.node->temp_var, temp_var_g);
							yyval.node->intValue = yystack.l_mark[0].node->intValue;
							printf("\n%s = %s", yyval.node->temp_var, yyval.node->info.opInfo.right->temp_var);
						}
#line 1293 "y.tab.c"
break;
case 9:
#line 86 "prob1.y"
	{ yyval.node = yystack.l_mark[0].node; }
#line 1298 "y.tab.c"
break;
case 10:
#line 88 "prob1.y"
	{
							yyval.node = yystack.l_mark[0].node;
						}
#line 1305 "y.tab.c"
break;
case 11:
#line 91 "prob1.y"
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
#line 1324 "y.tab.c"
break;
case 12:
#line 107 "prob1.y"
	{
							yyval.node = yystack.l_mark[0].node;
						}
#line 1331 "y.tab.c"
break;
case 13:
#line 110 "prob1.y"
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
#line 1350 "y.tab.c"
break;
case 14:
#line 126 "prob1.y"
	{
							yyval.node = yystack.l_mark[0].node;
						}
#line 1357 "y.tab.c"
break;
case 15:
#line 129 "prob1.y"
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
#line 1376 "y.tab.c"
break;
case 16:
#line 144 "prob1.y"
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
#line 1395 "y.tab.c"
break;
case 17:
#line 160 "prob1.y"
	{
							yyval.node = yystack.l_mark[0].node;
						}
#line 1402 "y.tab.c"
break;
case 18:
#line 163 "prob1.y"
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
#line 1421 "y.tab.c"
break;
case 19:
#line 178 "prob1.y"
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
#line 1440 "y.tab.c"
break;
case 20:
#line 193 "prob1.y"
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
#line 1459 "y.tab.c"
break;
case 21:
#line 208 "prob1.y"
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
#line 1478 "y.tab.c"
break;
case 22:
#line 224 "prob1.y"
	{
						yyval.node = yystack.l_mark[0].node;
					}
#line 1485 "y.tab.c"
break;
case 23:
#line 227 "prob1.y"
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
#line 1505 "y.tab.c"
break;
case 24:
#line 243 "prob1.y"
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
#line 1524 "y.tab.c"
break;
case 25:
#line 259 "prob1.y"
	{
								yyval.node = yystack.l_mark[0].node;
							}
#line 1531 "y.tab.c"
break;
case 26:
#line 262 "prob1.y"
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
#line 1550 "y.tab.c"
break;
case 27:
#line 277 "prob1.y"
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
#line 1569 "y.tab.c"
break;
case 28:
#line 293 "prob1.y"
	{
						yyval.node = yystack.l_mark[0].node;
					}
#line 1576 "y.tab.c"
break;
case 29:
#line 296 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if(yyval.node == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.right = yystack.l_mark[0].node;
						strcpy(yyval.node->info.opInfo.op, "++");
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						yystack.l_mark[0].node->intValue = yystack.l_mark[0].node->intValue + 1;
						printf("\n%s = %s + 1", yystack.l_mark[0].node->temp_var, yystack.l_mark[0].node->temp_var);
						yyval.node->intValue = yystack.l_mark[0].node->intValue;
						printf("\n%s = %s", yyval.node->temp_var, yyval.node->info.opInfo.right->temp_var);
					}
#line 1596 "y.tab.c"
break;
case 30:
#line 312 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if(yyval.node == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.right = yystack.l_mark[0].node;
						strcpy(yyval.node->info.opInfo.op, "--");
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						yystack.l_mark[0].node->intValue = yystack.l_mark[0].node->intValue - 1;
						printf("\n%s = %s - 1", yystack.l_mark[0].node->temp_var, yystack.l_mark[0].node->temp_var);
						yyval.node->intValue = yystack.l_mark[0].node->intValue;
						printf("\n%s = %s", yyval.node->temp_var, yyval.node->info.opInfo.right->temp_var);
					}
#line 1616 "y.tab.c"
break;
case 31:
#line 328 "prob1.y"
	{
						yyval.node = yystack.l_mark[0].node;
					}
#line 1623 "y.tab.c"
break;
case 32:
#line 331 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if(yyval.node == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.right = yystack.l_mark[0].node;
						strcpy(yyval.node->info.opInfo.op, "minus");
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						yyval.node->intValue = -1 * yystack.l_mark[0].node->intValue;
						printf("\n%s = -1 * %s", yyval.node->temp_var, yyval.node->info.opInfo.right->temp_var);
					}
#line 1641 "y.tab.c"
break;
case 33:
#line 345 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if(yyval.node == NULL){
							printf("Out of memory\n");
							exit(0);
						}
						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.right = yystack.l_mark[0].node;
						strcpy(yyval.node->info.opInfo.op, "!");
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						yyval.node->intValue = !yystack.l_mark[0].node->intValue;
						printf("\n%s = !%s", yyval.node->temp_var, yyval.node->info.opInfo.right->temp_var);
					}
#line 1659 "y.tab.c"
break;
case 34:
#line 360 "prob1.y"
	{
						yyval.node = yystack.l_mark[0].node;
					}
#line 1666 "y.tab.c"
break;
case 35:
#line 363 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if (yyval.node == NULL) {
							yyerror("no mem");
						}
						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.left = yystack.l_mark[-1].node;
						yyval.node->intValue = yystack.l_mark[-1].node->intValue;
						strcpy(yyval.node->info.opInfo.op, "++");
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						printf("\n%s = %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var);
						yystack.l_mark[-1].node->intValue = yystack.l_mark[-1].node->intValue + 1;
						printf("\n%s = %s + 1", yystack.l_mark[-1].node->temp_var, yystack.l_mark[-1].node->temp_var);
					}
#line 1685 "y.tab.c"
break;
case 36:
#line 378 "prob1.y"
	{
						yyval.node = malloc(sizeof(struct ASTNode));
						if (yyval.node == NULL) {
							yyerror("no mem");
						}
						yyval.node->token = NODETYPE_OPERATOR;
						yyval.node->info.opInfo.left = yystack.l_mark[-1].node;
						strcpy(yyval.node->info.opInfo.op, "--");
						yyval.node->intValue = yystack.l_mark[-1].node->intValue;
						genTemp();
						strcpy(yyval.node->temp_var, temp_var_g);
						printf("\n%s = %s", yyval.node->temp_var, yyval.node->info.opInfo.left->temp_var);
						yystack.l_mark[-1].node->intValue = yystack.l_mark[-1].node->intValue - 1;
						printf("\n%s = %s - 1", yystack.l_mark[-1].node->temp_var, yystack.l_mark[-1].node->temp_var);
					}
#line 1704 "y.tab.c"
break;
case 37:
#line 394 "prob1.y"
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
#line 1720 "y.tab.c"
break;
case 38:
#line 406 "prob1.y"
	{
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
#line 1736 "y.tab.c"
break;
case 39:
#line 418 "prob1.y"
	{
						yyval.node = yystack.l_mark[-1].node;
					}
#line 1743 "y.tab.c"
break;
case 40:
#line 422 "prob1.y"
	{
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
#line 1765 "y.tab.c"
break;
case 41:
#line 439 "prob1.y"
	{
							yyval.node = yystack.l_mark[-1].node;
							yyval.node->info.flowControlInfo.trueBranch = yystack.l_mark[0].node;
							printf("\ngoto %s", yyval.node->info.flowControlInfo.next_label);
							printf("\n\n%s:", yyval.node->info.flowControlInfo.false_label);
						}
#line 1775 "y.tab.c"
break;
case 42:
#line 444 "prob1.y"
	{
							yyval.node = yystack.l_mark[-2].node;
							ASTNode *temp = yystack.l_mark[0].node;
							if(temp != NULL){
								yyval.node->info.flowControlInfo.falseBranch = temp;
							}
							printf("\n\n%s:", yyval.node->info.flowControlInfo.next_label);
						}
#line 1787 "y.tab.c"
break;
case 43:
#line 453 "prob1.y"
	{
					yyval.node = yystack.l_mark[-1].node;
				}
#line 1794 "y.tab.c"
break;
case 44:
#line 455 "prob1.y"
	{ yyval.node = NULL;}
#line 1799 "y.tab.c"
break;
case 45:
#line 457 "prob1.y"
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
#line 1818 "y.tab.c"
break;
case 46:
#line 471 "prob1.y"
	{
							yyval.node = yystack.l_mark[-2].node;
							yyval.node->info.flowControlInfo.condition = yystack.l_mark[0].node;
							printf("\nif %s goto %s", yyval.node->info.flowControlInfo.condition->temp_var, yyval.node->info.flowControlInfo.true_label);
							printf("\ngoto %s", yyval.node->info.flowControlInfo.false_label);
							printf("\n\n%s:", yyval.node->info.flowControlInfo.true_label);
						}
#line 1829 "y.tab.c"
break;
case 47:
#line 477 "prob1.y"
	{
							yyval.node = yystack.l_mark[-4].node;
							yyval.node->info.flowControlInfo.trueBranch = yystack.l_mark[-1].node;
							printf("\ngoto %s", yyval.node->info.flowControlInfo.condition_label);
							printf("\n\n%s:", yyval.node->info.flowControlInfo.false_label);
						}
#line 1839 "y.tab.c"
break;
#line 1841 "y.tab.c"
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
