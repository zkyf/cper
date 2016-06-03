/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_ANALYZER_TAB_H_INCLUDED
# define YY_YY_ANALYZER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    COMMA = 259,
    PARENTHESES_L = 260,
    PARENTHESES_R = 261,
    BRACES_L = 262,
    BRACES_R = 263,
    BRACKETS_L = 264,
    BRACKETS_R = 265,
    VOID_T = 266,
    INT_T = 267,
    CHAR_T = 268,
    STRUCT_T = 269,
    UNION_T = 270,
    DOUBLE_T = 271,
    IF_C = 272,
    ELSE_C = 273,
    FOR_C = 274,
    WHILE_C = 275,
    CONTINUE_C = 276,
    BREAK_C = 277,
    RETURN_C = 278,
    SIZEOF_OP = 279,
    DOUBLE_OR_OP = 280,
    DOUBLE_AND_OP = 281,
    INC_OP = 282,
    DEC_OP = 283,
    DOT_OP = 284,
    PTR_OP = 285,
    OR_OP = 286,
    XOR_OP = 287,
    AND_OP = 288,
    EQ_OP = 289,
    NE_OP = 290,
    SLE_OP = 291,
    SGE_OP = 292,
    LE_OP = 293,
    GE_OP = 294,
    SHL_OP = 295,
    SHR_OP = 296,
    ADD_OP = 297,
    SUB_OP = 298,
    MUL_OP = 299,
    DIV_OP = 300,
    MOD_OP = 301,
    EQUAL_SIGN = 302,
    MUL_ASSIGN = 303,
    DIV_ASSIGN = 304,
    MOD_ASSIGN = 305,
    ADD_ASSIGN = 306,
    SUB_ASSIGN = 307,
    SHL_ASSIGN = 308,
    SHR_ASSIGN = 309,
    AND_ASSIGN = 310,
    XOR_ASSIGN = 311,
    OR_ASSIGN = 312,
    IDENTIFIER_O = 313,
    INT_CONST = 314,
    DOUBLE_CONST = 315,
    CHAR_CONST = 316,
    STRING_CONST = 317,
    COM_OP = 318,
    NOT_OP = 319
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 11 "analyzer.y" /* yacc.c:1909  */

    TreeNode* node;
    char* string;

#line 124 "analyzer.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ANALYZER_TAB_H_INCLUDED  */
