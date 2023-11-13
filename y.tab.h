#ifndef _yy_defines_h_
#define _yy_defines_h_

#define PLUS 257
#define MINUS 258
#define DIV 259
#define MUL 260
#define RPAREN 261
#define LPAREN 262
#define LSQ 263
#define RSQ 264
#define LBRACE 265
#define RBRACE 266
#define SEMI 267
#define COMMA 268
#define ASSIGN 269
#define GT 270
#define LT 271
#define GTEQ 272
#define LTEQ 273
#define INC 274
#define DEC 275
#define FOR 276
#define EQ 277
#define NEQ 278
#define NOT 279
#define INT 280
#define ID 281
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE{
	int intValue;
	char *lexeme;
	struct I_NODE *node;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
