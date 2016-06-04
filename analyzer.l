%{
#define YY_NO_UNISTD_H

#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "analyzer.tab.h"

void ignore_this_line();
void ignore_multi_line();
%}

%%
^#.*$               { }

"//"                { ignore_this_line(); }
"/*"                { ignore_multi_line(); }

"void"              { yylval.string = strdup(yytext); return VOID_T; }
"char"              { yylval.string = strdup(yytext); return CHAR_T; }
"int"               { yylval.string = strdup(yytext); return INT_T; }
"double"            { yylval.string = strdup(yytext); return DOUBLE_T; }
"struct"            { yylval.string = strdup(yytext); return STRUCT_T; }
"union"             { yylval.string = strdup(yytext); return UNION_T; }
"if"                { yylval.string = strdup(yytext); return IF_C; }
"else"              { yylval.string = strdup(yytext); return ELSE_C; }
"while"             { yylval.string = strdup(yytext); return WHILE_C; }
"for"               { yylval.string = strdup(yytext); return FOR_C; }
"continue"          { yylval.string = strdup(yytext); return CONTINUE_C; }
"break"             { yylval.string = strdup(yytext); return BREAK_C; }
"return"            { yylval.string = strdup(yytext); return RETURN_C; }
"sizeof"            { yylval.string = strdup(yytext); return SIZEOF_OP; }
"switch"			{ yylval.string = strdup(yytext); return SWITCH_C; }
"case"				{ yylval.string = strdup(yytext); return CASE_C; }
"default"			{ yylval.string = strdup(yytext); return DEFAULT_C; }

"("                 { yylval.string = strdup(yytext); return PARENTHESES_L; }
")"                 { yylval.string = strdup(yytext); return PARENTHESES_R; }
";"                 { yylval.string = strdup(yytext); return SEMICOLON; }
":"					{ yylval.string = strdup(yytext); return COLON; }
","                 { yylval.string = strdup(yytext); return COMMA; }
"="                 { yylval.string = strdup(yytext); return EQUAL_SIGN; }
"{"                 { yylval.string = strdup(yytext); return BRACES_L; }
"}"                 { yylval.string = strdup(yytext); return BRACES_R; }
"["                 { yylval.string = strdup(yytext); return BRACKETS_L; }
"]"                 { yylval.string = strdup(yytext); return BRACKETS_R; }
"*"                 { yylval.string = strdup(yytext); return MUL_OP; }
"|"                 { yylval.string = strdup(yytext); return OR_OP; }
"^"                 { yylval.string = strdup(yytext); return XOR_OP; }
"&"                 { yylval.string = strdup(yytext); return AND_OP; }
"<"                 { yylval.string = strdup(yytext); return SLE_OP; }
">"                 { yylval.string = strdup(yytext); return SGE_OP; }
"+"                 { yylval.string = strdup(yytext); return ADD_OP; }
"-"                 { yylval.string = strdup(yytext); return SUB_OP; }
"/"                 { yylval.string = strdup(yytext); return DIV_OP; }
"%"                 { yylval.string = strdup(yytext); return MOD_OP; }
"~"                 { yylval.string = strdup(yytext); return COM_OP; }
"!"                 { yylval.string = strdup(yytext); return NOT_OP; }
"."                 { yylval.string = strdup(yytext); return DOT_OP; }

"||"                { yylval.string = strdup(yytext); return DOUBLE_OR_OP; }
"&&"                { yylval.string = strdup(yytext); return DOUBLE_AND_OP; }
"=="                { yylval.string = strdup(yytext); return EQ_OP; }
"!="                { yylval.string = strdup(yytext); return NE_OP; }
"<="                { yylval.string = strdup(yytext); return LE_OP; }
">="                { yylval.string = strdup(yytext); return GE_OP; }
"<<"                { yylval.string = strdup(yytext); return SHL_OP; }
">>"                { yylval.string = strdup(yytext); return SHR_OP; }
"++"                { yylval.string = strdup(yytext); return INC_OP; }
"--"                { yylval.string = strdup(yytext); return DEC_OP; }
"->"                { yylval.string = strdup(yytext); return PTR_OP; }

"*="                { yylval.string = strdup(yytext); return MUL_ASSIGN; }
"/="                { yylval.string = strdup(yytext); return DIV_ASSIGN; }
"%="                { yylval.string = strdup(yytext); return MOD_ASSIGN; }
"+="                { yylval.string = strdup(yytext); return ADD_ASSIGN; }
"-="                { yylval.string = strdup(yytext); return SUB_ASSIGN; }
"<<="               { yylval.string = strdup(yytext); return SHL_ASSIGN; }
">>="               { yylval.string = strdup(yytext); return SHR_ASSIGN; }
"&="                { yylval.string = strdup(yytext); return AND_ASSIGN; }
"^="                { yylval.string = strdup(yytext); return XOR_ASSIGN; }
"|="                { yylval.string = strdup(yytext); return OR_ASSIGN; }

[a-zA-Z_$][a-zA-Z_$0-9]*            { yylval.string = strdup(yytext); return IDENTIFIER_O; }
([0-9]*|0[xX][0-9a-fA-F]+)          { yylval.string = strdup(yytext); return INT_CONST; }
([0-9]*\.[0-9]*)                    { yylval.string = strdup(yytext); return DOUBLE_CONST; }
'([^\n']|\\')+'                     { yylval.string = strdup(yytext); return CHAR_CONST; }
\"([^\n\r\"]|\\\")*\"               { yylval.string = strdup(yytext); return STRING_CONST; }

[ \t\n\r]                   { }

.                   { printf("%d\n", (int)yytext[0]); yyerror("invalid character"); }

%%

void ignore_this_line() {
    char c;
    while (c = input(), c != '\n');
}

void ignore_multi_line() {
    char a = input(), b;
    while (1) {
        b = input();
        if (a == '*' && b == '/') {
            break;
        }
        a = b;
    }
}

int yywrap() {
    return 1;
}
