%option noyywrap yylineno

%{
   #include <string.h>
   #include "semantic.tab.h"
   #include "defs.h"
   extern YYSTYPE yylval; // Dodato u 7. vezbama
%}

%%

[ \t\n]+             { /* skip */ }

"int"                { yylval.i = INT;  return TYPE; }
"unsigned"           { yylval.i = UINT; return TYPE; }
"void"               { yylval.i = VOID; return VOIDTYPE; }
"if"                 { return IF; }
"else"               { return ELSE; }
"return"             { return RETURN; }
"for"				 { return FOR; }
"to"				 { return TO; }
"step"				 { return STEP; }
"switch"			 { return SWITCH; }
"case"				 { return CASETOKEN; }
"->"				 { return ARROW; }
"otherwise"			 { return OTHERWISE; }
"finish"			 { return FINISH; }

"("                  { return LPAREN; }
")"                  { return RPAREN; }
"{"                  { return LCURLYBRACKET; }
"}"                  { return RCURLYBRACKET; }
"["                  { return LSQUAREBRACKET; }
"]"                  { return RSQUAREBRACKET; }
";"                  { return SEMICOLON; }
"="                  { return ASSIGN; }
","                  { return COMMA; }
"++"                 { return INCREMENT; }

"+"                  { yylval.i = ADD; return AROP; }
"-"                  { yylval.i = SUB; return AROP; }

"<"                  { yylval.i = LT; return RELOP; }
">"                  { yylval.i = GT; return RELOP; }
"<="                 { yylval.i = LE; return RELOP; }
">="                 { yylval.i = GE; return RELOP; }
"=="                 { yylval.i = EQ; return RELOP; }
"!="                 { yylval.i = NE; return RELOP; }

[a-zA-Z][a-zA-Z0-9]* { yylval.s = strdup(yytext); 
                       return ID; }
[+-]?[0-9]{1,10}     { yylval.s = strdup(yytext); 
                       return INT_NUMBER;}
[0-9]{1,10}[uU]      { yylval.s = strdup(yytext); 
                       yylval.s[yyleng-1] = 0;
                       return UINT_NUMBER;}

\/\*(.*\n)*.*\*\/	 { /* Viselinijski komentar */ }
\/\/.*               { /* Jednolinijski komentar */ }
.                    { printf("line %d: LEXICAL ERROR on char %c\n", yylineno, *yytext);}

%%