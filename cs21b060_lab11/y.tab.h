#ifndef _yy_defines_h_
#define _yy_defines_h_

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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE{
	int intValue;
	char lexeme[20];
	struct ASTNode *node;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
