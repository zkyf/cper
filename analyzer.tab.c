/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "analyzer.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "def.h"
#include "ast.h"

void yyerror(char*);

#line 76 "analyzer.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "analyzer.tab.h".  */
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
#line 11 "analyzer.y" /* yacc.c:355  */

    TreeNode* node;
    char* string;

#line 186 "analyzer.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ANALYZER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 201 "analyzer.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   843

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  154
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  260

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    40,    40,    41,    42,    43,    46,    47,    50,    53,
      58,    59,    62,    63,    66,    67,    70,    71,    74,    75,
      78,    79,    82,    83,    84,    85,    86,    89,    92,    97,
     100,   105,   106,   109,   112,   113,   114,   115,   118,   119,
     122,   123,   126,   127,   128,   129,   130,   133,   134,   137,
     138,   139,   140,   143,   144,   147,   148,   151,   154,   159,
     162,   165,   168,   171,   174,   177,   180,   183,   188,   189,
     190,   191,   197,   198,   201,   202,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   220,   223,   224,
     229,   230,   235,   236,   241,   242,   247,   248,   251,   252,
     257,   258,   261,   262,   267,   268,   269,   270,   273,   274,
     279,   280,   283,   284,   289,   290,   293,   294,   299,   300,
     301,   304,   305,   310,   311,   314,   315,   316,   317,   318,
     319,   324,   325,   326,   327,   328,   329,   332,   333,   336,
     337,   338,   339,   340,   341,   342,   345,   346,   349,   350,
     351,   352,   355,   356,   357
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "COMMA", "PARENTHESES_L",
  "PARENTHESES_R", "BRACES_L", "BRACES_R", "BRACKETS_L", "BRACKETS_R",
  "VOID_T", "INT_T", "CHAR_T", "STRUCT_T", "UNION_T", "DOUBLE_T", "IF_C",
  "ELSE_C", "FOR_C", "WHILE_C", "CONTINUE_C", "BREAK_C", "RETURN_C",
  "SIZEOF_OP", "DOUBLE_OR_OP", "DOUBLE_AND_OP", "INC_OP", "DEC_OP",
  "DOT_OP", "PTR_OP", "OR_OP", "XOR_OP", "AND_OP", "EQ_OP", "NE_OP",
  "SLE_OP", "SGE_OP", "LE_OP", "GE_OP", "SHL_OP", "SHR_OP", "ADD_OP",
  "SUB_OP", "MUL_OP", "DIV_OP", "MOD_OP", "EQUAL_SIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "SHL_ASSIGN",
  "SHR_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "IDENTIFIER_O",
  "INT_CONST", "DOUBLE_CONST", "CHAR_CONST", "STRING_CONST", "COM_OP",
  "NOT_OP", "$accept", "program", "declaration", "function_definition",
  "parameters", "declarators", "init_declarators", "init_declarator",
  "initializer", "t_initializer", "type_specifier", "t_type_specifier",
  "struct_or_union", "plain_declaration", "declarator", "t_declarator",
  "plain_declarator", "statement", "expression_statement",
  "compound_statement", "t_declaration", "t_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "expression", "assignment_expression", "assignment_operator",
  "constant_expression", "logical_or_expression", "logical_and_expression",
  "inclusive_or_expression", "exclusive_or_expression", "and_expression",
  "equality_experssion", "equality_operator", "relational_expression",
  "relational_operator", "shift_expression", "shift_operator",
  "additive_expression", "additive_operator", "multiplicative_expression",
  "multiplicative_operator", "cast_expression", "type_name",
  "unary_expression", "unary_operator", "postfix_expressoin", "postfix",
  "arguments", "primary_expressoin", "constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319
};
# endif

#define YYPACT_NINF -130

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-130)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     163,  -130,  -130,  -130,  -130,  -130,  -130,    28,  -130,  -130,
       6,     0,  -130,  -130,  -130,  -130,   -32,  -130,    49,  -130,
     -37,    27,   163,    31,  -130,  -130,   -32,   587,    60,   731,
      52,   -32,   129,   163,  -130,    42,   563,   587,   755,   779,
     779,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,    69,    71,    83,    68,    92,    -4,
      80,   147,   127,   -28,  -130,   100,   731,    40,  -130,  -130,
     131,    84,   -32,  -130,   171,    69,  -130,   731,   187,  -130,
    -130,   -32,   223,   152,  -130,    97,  -130,    18,  -130,    78,
     563,  -130,   731,  -130,  -130,   731,   731,   731,   731,   731,
    -130,  -130,   731,  -130,  -130,  -130,  -130,   731,  -130,  -130,
     731,  -130,  -130,   731,  -130,  -130,  -130,   731,  -130,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,   731,
    -130,   611,   731,  -130,  -130,   135,   146,  -130,   200,  -130,
     163,   131,  -130,  -130,   175,  -130,   -32,   192,  -130,  -130,
     102,   731,  -130,   731,  -130,   587,  -130,    21,    71,    83,
      68,    92,    -4,    80,   147,   127,   -28,  -130,  -130,  -130,
    -130,   105,    15,  -130,  -130,  -130,  -130,   201,   204,   213,
     229,   242,   448,  -130,     6,  -130,  -130,  -130,   262,   310,
    -130,  -130,  -130,   194,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,   731,  -130,  -130,   731,   455,   731,
    -130,  -130,  -130,   198,  -130,  -130,   358,  -130,  -130,  -130,
    -130,   122,   497,   222,   126,  -130,  -130,   406,   635,   226,
     539,   406,   228,   406,   130,   659,   683,   237,  -130,   406,
    -130,   406,   406,   155,   406,   156,   707,  -130,  -130,  -130,
     406,  -130,   406,   406,   178,  -130,  -130,  -130,   406,  -130
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    22,    24,    23,    31,    32,    25,     0,     2,     3,
       0,     0,     1,     4,     5,     6,     0,    40,     0,    14,
      16,    36,     0,    28,    41,     7,     0,     0,     0,     0,
      37,     0,     0,     0,    15,    36,     0,     0,     0,     0,
       0,   131,   133,   134,   132,   148,   152,   153,   154,   150,
     135,   136,    17,    18,    74,    88,    90,    92,    94,    96,
      98,   102,   108,   112,   116,   121,     0,   125,   137,   149,
      34,     0,     0,    10,     0,    87,   121,     0,     0,    12,
      26,     0,     0,     0,   123,     0,    72,     0,    20,     0,
       0,   129,     0,   126,   127,     0,     0,     0,     0,     0,
     100,   101,     0,   104,   105,   106,   107,     0,   110,   111,
       0,   114,   115,     0,   118,   119,   120,     0,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,     0,
     128,     0,     0,   144,   145,     0,     0,   138,     0,     8,
       0,    35,    33,    38,     0,    29,     0,     0,    27,    34,
       0,     0,   151,     0,   124,     0,    19,     0,    89,    91,
      93,    95,    97,    99,   103,   109,   113,   117,    75,   140,
     146,     0,     0,   142,   143,    47,    49,     0,     0,     0,
       0,     0,     0,    53,     0,    55,    42,    43,     0,     0,
      44,    45,    46,     0,    11,     9,    39,    13,    30,    35,
      73,   122,    21,   130,     0,   141,   139,     0,     0,     0,
      68,    69,    70,     0,    50,    54,     0,    51,    56,    48,
     147,     0,     0,     0,     0,    71,    52,     0,     0,     0,
       0,     0,    57,     0,     0,     0,     0,     0,    59,     0,
      60,     0,     0,     0,     0,     0,     0,    58,    61,    62,
       0,    64,     0,     0,     0,    63,    65,    66,     0,    67
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -130,  -130,    -5,   240,   165,   168,  -130,   224,   -33,  -130,
       1,   218,  -130,   112,   -26,  -130,    19,  -129,  -130,   -56,
    -130,    65,  -130,  -130,  -130,   -36,   -24,  -130,   177,   -14,
     160,   161,   159,   170,   167,  -130,   169,  -130,   173,  -130,
     162,  -130,   174,  -130,   -60,   202,   -18,  -130,  -130,  -130,
    -130,  -130,  -130
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    71,    78,    18,    19,    52,    89,
      72,    32,    11,    73,    20,    30,    35,   185,   186,   187,
     188,   189,   190,   191,   192,   193,    86,   129,    74,    54,
      55,    56,    57,    58,    59,   102,    60,   107,    61,   110,
      62,   113,    63,   117,    64,    87,    65,    66,    67,   137,
     171,    68,    69
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      85,    10,    13,    53,    88,    79,   130,    22,    10,    15,
      27,    76,    16,    53,   139,    75,   114,   115,   116,   151,
      91,    93,    94,    31,   153,   206,    17,   203,    12,    21,
     100,   101,    28,    81,    31,    24,    29,    84,    33,     1,
       2,     3,     4,     5,     6,   131,   142,    83,    76,   132,
      16,    29,    25,    26,    85,    79,    85,   167,    23,    76,
     218,    77,   154,    75,    17,   154,    70,   133,   134,   135,
     136,     1,     2,     3,     4,     5,     6,    76,    76,    76,
      76,    76,   155,    81,    76,   195,   156,   218,   140,    76,
     141,    84,    76,   201,    95,    76,   172,    96,   232,    76,
      98,   151,   238,   152,   240,   168,   140,   170,   199,   204,
     247,   205,   248,   249,    97,   251,   103,   104,   105,   106,
     197,   255,   202,   256,   257,    99,   151,   200,   227,   259,
     151,    53,   231,   183,   151,    76,   241,    80,   138,   184,
       1,     2,     3,     4,     5,     6,   213,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   149,   151,
     151,   250,   252,     1,     2,     3,     4,     5,     6,   111,
     112,   221,   223,   224,     1,     2,     3,     4,     5,     6,
     220,   143,   151,   215,   258,   196,   229,   108,   109,   184,
     145,   146,   234,   173,   237,   198,   146,   219,   151,   243,
     245,   225,   151,   175,   174,    36,   207,   138,   176,   208,
     254,     1,     2,     3,     4,     5,     6,   177,   209,   178,
     179,   180,   181,   182,    38,   230,   151,    39,    40,   235,
     151,   148,   210,    41,     1,     2,     3,     4,     5,     6,
     246,   151,    42,    43,    44,   211,   239,    14,   150,   147,
      34,    82,   194,   216,   144,   158,   160,   159,    45,    46,
      47,    48,    49,    50,    51,   175,   162,    36,   161,   138,
     214,   163,   165,     1,     2,     3,     4,     5,     6,   177,
     164,   178,   179,   180,   181,   182,    38,   166,     0,    39,
      40,     0,   157,     0,     0,    41,     0,     0,     0,     0,
       0,     0,     0,     0,    42,    43,    44,     0,     0,     0,
       0,     0,     0,   175,     0,    36,     0,   138,   217,     0,
      45,    46,    47,    48,    49,    50,    51,   177,     0,   178,
     179,   180,   181,   182,    38,     0,     0,    39,    40,     0,
       0,     0,     0,    41,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    43,    44,     0,     0,     0,     0,     0,
       0,   175,     0,    36,     0,   138,   226,     0,    45,    46,
      47,    48,    49,    50,    51,   177,     0,   178,   179,   180,
     181,   182,    38,     0,     0,    39,    40,     0,     0,     0,
       0,    41,     0,     0,     0,     0,     0,     0,     0,     0,
      42,    43,    44,     0,     0,     0,     0,     0,     0,   175,
       0,    36,     0,   138,     0,     0,    45,    46,    47,    48,
      49,    50,    51,   177,     0,   178,   179,   180,   181,   182,
      38,     0,     0,    39,    40,     0,     0,     0,     0,    41,
       0,     0,     0,     0,     0,     0,     0,     0,    42,    43,
      44,   212,     0,    36,     0,     0,     0,     0,   222,     0,
      36,     0,     0,     0,    45,    46,    47,    48,    49,    50,
      51,     0,    38,     0,     0,    39,    40,     0,     0,    38,
       0,    41,    39,    40,     0,     0,     0,     0,    41,     0,
      42,    43,    44,     0,     0,     0,     0,    42,    43,    44,
     228,     0,    36,     0,     0,     0,    45,    46,    47,    48,
      49,    50,    51,    45,    46,    47,    48,    49,    50,    51,
       0,    38,     0,     0,    39,    40,     0,     0,     0,     0,
      41,     0,     0,     0,     0,     0,     0,     0,     0,    42,
      43,    44,   236,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    45,    46,    47,    48,    49,
      50,    51,     0,    38,     0,     0,    39,    40,    36,     0,
       0,     0,    41,     0,     1,     2,     3,     4,     5,     6,
       0,    42,    43,    44,     0,     0,     0,    38,     0,     0,
      39,    40,    36,     0,    37,     0,    41,    45,    46,    47,
      48,    49,    50,    51,     0,    42,    43,    44,     0,     0,
       0,    38,     0,     0,    39,    40,    36,   169,     0,     0,
      41,    45,    46,    47,    48,    49,    50,    51,     0,    42,
      43,    44,     0,     0,     0,    38,     0,     0,    39,    40,
      36,   233,     0,     0,    41,    45,    46,    47,    48,    49,
      50,    51,     0,    42,    43,    44,     0,     0,     0,    38,
       0,     0,    39,    40,    36,   242,     0,     0,    41,    45,
      46,    47,    48,    49,    50,    51,     0,    42,    43,    44,
       0,     0,     0,    38,     0,     0,    39,    40,    36,   244,
       0,     0,    41,    45,    46,    47,    48,    49,    50,    51,
       0,    42,    43,    44,     0,     0,     0,    38,     0,     0,
      39,    40,    36,   253,     0,     0,    41,    45,    46,    47,
      48,    49,    50,    51,     0,    42,    43,    44,     0,     0,
       0,    38,     0,     0,    39,    40,    36,     0,     0,     0,
      41,    45,    46,    47,    48,    49,    50,    51,     0,    42,
      43,    44,     0,     0,     0,    38,     0,     0,    39,    40,
      90,     0,     0,     0,    41,    45,    46,    47,    48,    49,
      50,    51,     0,    42,    43,    44,     0,     0,     0,    38,
       0,     0,    39,    40,    92,     0,     0,     0,    41,    45,
      46,    47,    48,    49,    50,    51,     0,    42,    43,    44,
       0,     0,     0,    38,     0,     0,    39,    40,     0,     0,
       0,     0,    41,    45,    46,    47,    48,    49,    50,    51,
       0,    42,    43,    44,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    45,    46,    47,
      48,    49,    50,    51
};

static const yytype_int16 yycheck[] =
{
      36,     0,     7,    27,    37,    31,    66,     7,     7,     3,
      47,    29,    44,    37,    70,    29,    44,    45,    46,     4,
      38,    39,    40,    22,     6,    10,    58,     6,     0,    10,
      34,    35,     5,    32,    33,    16,     9,    36,     7,    11,
      12,    13,    14,    15,    16,     5,    72,     5,    66,     9,
      44,     9,     3,     4,    90,    81,    92,   117,    58,    77,
     189,     9,    44,    77,    58,    44,     6,    27,    28,    29,
      30,    11,    12,    13,    14,    15,    16,    95,    96,    97,
      98,    99,     4,    82,   102,   141,     8,   216,     4,   107,
       6,    90,   110,   153,    25,   113,   132,    26,   227,   117,
      32,     4,   231,     6,   233,   129,     4,   131,     6,     4,
     239,     6,   241,   242,    31,   244,    36,    37,    38,    39,
     146,   250,   155,   252,   253,    33,     4,   151,     6,   258,
       4,   155,     6,   138,     4,   153,     6,     8,     7,   138,
      11,    12,    13,    14,    15,    16,   182,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,     6,     4,
       4,     6,     6,    11,    12,    13,    14,    15,    16,    42,
      43,   207,   208,   209,    11,    12,    13,    14,    15,    16,
     204,    10,     4,   188,     6,    10,   222,    40,    41,   188,
       3,     4,   228,    58,   230,     3,     4,     3,     4,   235,
     236,     3,     4,     3,    58,     5,     5,     7,     8,     5,
     246,    11,    12,    13,    14,    15,    16,    17,     5,    19,
      20,    21,    22,    23,    24,     3,     4,    27,    28,     3,
       4,     8,     3,    33,    11,    12,    13,    14,    15,    16,
       3,     4,    42,    43,    44,     3,    18,     7,    83,    81,
      26,    33,   140,   188,    77,    95,    97,    96,    58,    59,
      60,    61,    62,    63,    64,     3,    99,     5,    98,     7,
       8,   102,   110,    11,    12,    13,    14,    15,    16,    17,
     107,    19,    20,    21,    22,    23,    24,   113,    -1,    27,
      28,    -1,    90,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    -1,     5,    -1,     7,     8,    -1,
      58,    59,    60,    61,    62,    63,    64,    17,    -1,    19,
      20,    21,    22,    23,    24,    -1,    -1,    27,    28,    -1,
      -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,     5,    -1,     7,     8,    -1,    58,    59,
      60,    61,    62,    63,    64,    17,    -1,    19,    20,    21,
      22,    23,    24,    -1,    -1,    27,    28,    -1,    -1,    -1,
      -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      -1,     5,    -1,     7,    -1,    -1,    58,    59,    60,    61,
      62,    63,    64,    17,    -1,    19,    20,    21,    22,    23,
      24,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
      44,     3,    -1,     5,    -1,    -1,    -1,    -1,     3,    -1,
       5,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      64,    -1,    24,    -1,    -1,    27,    28,    -1,    -1,    24,
      -1,    33,    27,    28,    -1,    -1,    -1,    -1,    33,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    42,    43,    44,
       3,    -1,     5,    -1,    -1,    -1,    58,    59,    60,    61,
      62,    63,    64,    58,    59,    60,    61,    62,    63,    64,
      -1,    24,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      43,    44,     3,    -1,     5,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,
      63,    64,    -1,    24,    -1,    -1,    27,    28,     5,    -1,
      -1,    -1,    33,    -1,    11,    12,    13,    14,    15,    16,
      -1,    42,    43,    44,    -1,    -1,    -1,    24,    -1,    -1,
      27,    28,     5,    -1,     7,    -1,    33,    58,    59,    60,
      61,    62,    63,    64,    -1,    42,    43,    44,    -1,    -1,
      -1,    24,    -1,    -1,    27,    28,     5,     6,    -1,    -1,
      33,    58,    59,    60,    61,    62,    63,    64,    -1,    42,
      43,    44,    -1,    -1,    -1,    24,    -1,    -1,    27,    28,
       5,     6,    -1,    -1,    33,    58,    59,    60,    61,    62,
      63,    64,    -1,    42,    43,    44,    -1,    -1,    -1,    24,
      -1,    -1,    27,    28,     5,     6,    -1,    -1,    33,    58,
      59,    60,    61,    62,    63,    64,    -1,    42,    43,    44,
      -1,    -1,    -1,    24,    -1,    -1,    27,    28,     5,     6,
      -1,    -1,    33,    58,    59,    60,    61,    62,    63,    64,
      -1,    42,    43,    44,    -1,    -1,    -1,    24,    -1,    -1,
      27,    28,     5,     6,    -1,    -1,    33,    58,    59,    60,
      61,    62,    63,    64,    -1,    42,    43,    44,    -1,    -1,
      -1,    24,    -1,    -1,    27,    28,     5,    -1,    -1,    -1,
      33,    58,    59,    60,    61,    62,    63,    64,    -1,    42,
      43,    44,    -1,    -1,    -1,    24,    -1,    -1,    27,    28,
       5,    -1,    -1,    -1,    33,    58,    59,    60,    61,    62,
      63,    64,    -1,    42,    43,    44,    -1,    -1,    -1,    24,
      -1,    -1,    27,    28,     5,    -1,    -1,    -1,    33,    58,
      59,    60,    61,    62,    63,    64,    -1,    42,    43,    44,
      -1,    -1,    -1,    24,    -1,    -1,    27,    28,    -1,    -1,
      -1,    -1,    33,    58,    59,    60,    61,    62,    63,    64,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,
      61,    62,    63,    64
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    12,    13,    14,    15,    16,    66,    67,    68,
      75,    77,     0,    67,    68,     3,    44,    58,    71,    72,
      79,    81,     7,    58,    81,     3,     4,    47,     5,     9,
      80,    75,    76,     7,    72,    81,     5,     7,    24,    27,
      28,    33,    42,    43,    44,    58,    59,    60,    61,    62,
      63,    64,    73,    91,    94,    95,    96,    97,    98,    99,
     101,   103,   105,   107,   109,   111,   112,   113,   116,   117,
       6,    69,    75,    78,    93,    94,   111,     9,    70,    79,
       8,    75,    76,     5,    75,    90,    91,   110,    73,    74,
       5,   111,     5,   111,   111,    25,    26,    31,    32,    33,
      34,    35,   100,    36,    37,    38,    39,   102,    40,    41,
     104,    42,    43,   106,    44,    45,    46,   108,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    92,
     109,     5,     9,    27,    28,    29,    30,   114,     7,    84,
       4,     6,    79,    10,    93,     3,     4,    70,     8,     6,
      69,     4,     6,     6,    44,     4,     8,   110,    95,    96,
      97,    98,    99,   101,   103,   105,   107,   109,    91,     6,
      91,   115,    90,    58,    58,     3,     8,    17,    19,    20,
      21,    22,    23,    67,    75,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    78,    84,    10,    79,     3,     6,
      91,   109,    73,     6,     4,     6,    10,     5,     5,     5,
       3,     3,     3,    90,     8,    67,    86,     8,    82,     3,
      91,    90,     3,    90,    90,     3,     8,     6,     3,    90,
       3,     6,    82,     6,    90,     3,     3,    90,    82,    18,
      82,     6,     6,    90,     6,    90,     3,    82,    82,    82,
       6,    82,     6,     6,    90,    82,    82,    82,     6,    82
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    66,    66,    66,    67,    67,    68,    68,
      69,    69,    70,    70,    71,    71,    72,    72,    73,    73,
      74,    74,    75,    75,    75,    75,    75,    75,    75,    76,
      76,    77,    77,    78,    79,    79,    79,    79,    80,    80,
      81,    81,    82,    82,    82,    82,    82,    83,    83,    84,
      84,    84,    84,    85,    85,    86,    86,    87,    87,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    89,    89,
      89,    89,    90,    90,    91,    91,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    93,    94,    94,
      95,    95,    96,    96,    97,    97,    98,    98,    99,    99,
     100,   100,   101,   101,   102,   102,   102,   102,   103,   103,
     104,   104,   105,   105,   106,   106,   107,   107,   108,   108,
     108,   109,   109,   110,   110,   111,   111,   111,   111,   111,
     111,   112,   112,   112,   112,   112,   112,   113,   113,   114,
     114,   114,   114,   114,   114,   114,   115,   115,   116,   116,
     116,   116,   117,   117,   117
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     2,     3,     5,     6,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     4,     5,     2,     3,
       4,     1,     1,     2,     3,     4,     1,     2,     3,     4,
       1,     2,     1,     1,     1,     1,     1,     1,     2,     2,
       3,     3,     4,     1,     2,     1,     2,     5,     7,     5,
       6,     7,     7,     8,     7,     8,     8,     9,     2,     2,
       2,     3,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     4,     1,     2,     1,     2,     2,     2,     2,
       4,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       2,     3,     2,     2,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 40 "analyzer.y" /* yacc.c:1646  */
    { treeroot = (yyval.node) = create_node(PROGRAM, "program", 1, (yyvsp[0].node)); }
#line 1601 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 41 "analyzer.y" /* yacc.c:1646  */
    { treeroot = (yyval.node) = create_node(PROGRAM, "program", 1, (yyvsp[0].node)); }
#line 1607 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 42 "analyzer.y" /* yacc.c:1646  */
    { treeroot = (yyval.node) = merge_node((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1613 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 43 "analyzer.y" /* yacc.c:1646  */
    { treeroot = (yyval.node) = merge_node((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1619 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 46 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(DECLARATION, "declaration", 1, (yyvsp[-1].node)); }
#line 1625 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 47 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(DECLARATION, "declaration", 2, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 1631 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 50 "analyzer.y" /* yacc.c:1646  */
    { 
        (yyval.node) = create_node(FUNCTION_DEFINITION, "function_definition ()", 3, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[0].node)); 
    }
#line 1639 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 53 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(FUNCTION_DEFINITION, "function_definition ()", 4, (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); 
    }
#line 1647 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 58 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(PARAMETERS, "parameters", 1, (yyvsp[0].node)); }
#line 1653 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 59 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = merge_node((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1659 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 62 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(DECLARATORS, "declarators", 1, (yyvsp[0].node)); }
#line 1665 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 63 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = merge_node((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1671 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 66 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(INIT_DECLARATORS, "init_declarators", 1, (yyvsp[0].node)); }
#line 1677 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 67 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = merge_node((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1683 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 70 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(INIT_DECLARATOR, "init_declarator", 1, (yyvsp[0].node)); }
#line 1689 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 71 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(INIT_DECLARATOR, "init_declarator =", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1695 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 75 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(INITIALIZER, "initializer {}", 1, (yyvsp[-1].node)); }
#line 1701 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 78 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(INITIALIZER, "initializers", 1, (yyvsp[0].node)); }
#line 1707 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 79 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = merge_node((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1713 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 82 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(KEYWORDS, (yyvsp[0].string), 0); }
#line 1719 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 83 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(KEYWORDS, (yyvsp[0].string), 0); }
#line 1725 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 84 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(KEYWORDS, (yyvsp[0].string), 0); }
#line 1731 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 85 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(KEYWORDS, (yyvsp[0].string), 0); }
#line 1737 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 86 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(TYPE_SPECIFIER, "type_specifier {}", 2, (yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 1745 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 89 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(TYPE_SPECIFIER, "type_specifier identifier {}", 3, (yyvsp[-4].node), create_node(IDENTIFIER, (yyvsp[-3].string), 0), (yyvsp[-1].node));
    }
#line 1753 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 92 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(TYPE_SPECIFIER, "type_specifier", 2, (yyvsp[-1].node), create_node(IDENTIFIER, (yyvsp[0].string), 0));
    }
#line 1761 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 97 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(TYPE_SPECIFIERS, "type_specifiers", 2, (yyvsp[-2].node), (yyvsp[-1].node));
    }
#line 1769 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 100 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = merge_node(merge_node((yyvsp[-3].node), (yyvsp[-2].node)), (yyvsp[-1].node));
    }
#line 1777 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 105 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(KEYWORDS, (yyvsp[0].string), 0); }
#line 1783 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 106 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(KEYWORDS, (yyvsp[0].string), 0); }
#line 1789 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 109 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(PLAIN_DECLARATION, "plain_declaration", 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1795 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 112 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(DECLARATOR, "declarator ()", 1, (yyvsp[-2].node)); }
#line 1801 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 113 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(DECLARATOR, "declarator ()", 2, (yyvsp[-3].node), (yyvsp[-2].string)); }
#line 1807 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 114 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(DECLARATOR, "declarator", 1, (yyvsp[0].node)); }
#line 1813 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 115 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(DECLARATOR, "declarator", 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1819 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 118 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(DECLARATOR, "declarators []", 1, (yyvsp[-1].node)); }
#line 1825 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 119 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = merge_node((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1831 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 122 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(IDENTIFIER, (yyvsp[0].string), 0);}
#line 1837 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 123 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(PLAIN_DECLARATOR, "plain_declarator *", 1, (yyvsp[0].node)); }
#line 1843 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 133 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(EXPRESSION_STATEMENT, "expression_statement", 0); }
#line 1849 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 134 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1855 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 137 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(COMPOUND_STATEMENT, "compound_statement {}", 0); }
#line 1861 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 138 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(COMPOUND_STATEMENT, "compound_statement {}", 1, (yyvsp[-1].node)); }
#line 1867 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 139 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(COMPOUND_STATEMENT, "compound_statement {}", 1, (yyvsp[-1].node)); }
#line 1873 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 140 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(COMPOUND_STATEMENT, "compound_statement {}", 2, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 1879 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 143 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(DECLARATION, "declarations", 1, (yyvsp[0].node)); }
#line 1885 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 144 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = merge_node((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1891 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 147 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(STATEMENT, "statements", 1, (yyvsp[0].node)); }
#line 1897 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 148 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = merge_node((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1903 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 151 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(SELECTION_STATEMENT, "selection_statement if", 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1911 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 154 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(SELECTION_STATEMENT, "selection_statement if else", 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1919 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 159 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(ITERATION_STATEMENT, "while()", 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1927 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 162 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(ITERATION_STATEMENT, "for(;;)", 1, (yyvsp[0].node));
    }
#line 1935 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 165 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(ITERATION_STATEMENT, "for(;;*)", 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1943 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 168 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(ITERATION_STATEMENT, "for(;*;)", 2, (yyvsp[-3].node), (yyvsp[0].node));
    }
#line 1951 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 171 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(ITERATION_STATEMENT, "for(;*;*)", 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1959 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 174 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(ITERATION_STATEMENT, "for(*;;)", 2, (yyvsp[-4].node), (yyvsp[0].node));
    }
#line 1967 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 177 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(ITERATION_STATEMENT, "for(*;;*)", 3, (yyvsp[-5].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1975 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 180 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(ITERATION_STATEMENT, "for(*;*;)", 3, (yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[0].node));
    }
#line 1983 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 183 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(ITERATION_STATEMENT, "for(*;*;*)", 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1991 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 188 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(JUMP_STATEMENT, "jump_statement", 1, create_node(KEYWORDS, (yyvsp[-1].string), 0)); }
#line 1997 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 189 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(JUMP_STATEMENT, "jump_statement", 1, create_node(KEYWORDS, (yyvsp[-1].string), 0)); }
#line 2003 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 190 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(JUMP_STATEMENT, "jump_statement", 1, create_node(KEYWORDS, (yyvsp[-1].string), 0)); }
#line 2009 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 191 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(JUMP_STATEMENT, "jump_statement", 2, create_node(KEYWORDS, (yyvsp[-2].string), 0), (yyvsp[-1].node)); 
    }
#line 2017 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 197 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(EXPRESSION, "expression", 1, (yyvsp[0].node)); }
#line 2023 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 198 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(EXPRESSION, "expression", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2029 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 202 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(ASSIGN_EXPRESSION, "assignment_expression", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2037 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 207 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2043 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 208 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2049 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 209 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2055 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 210 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2061 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 211 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2067 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 212 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2073 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 213 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2079 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 214 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2085 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 215 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2091 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 216 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2097 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 217 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2103 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 224 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(LOGICAL_OR_EXPRESSION, "logical_or_expression ||", 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2111 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 230 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(LOGICAL_AND_EXPRESSION, "logical_and_expression &&", 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2119 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 236 "analyzer.y" /* yacc.c:1646  */
    { 
        (yyval.node) = create_node(INCLUSIVE_OR_EXPRESSION, "inclusive_or_expression or", 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2127 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 242 "analyzer.y" /* yacc.c:1646  */
    { 
        (yyval.node) = create_node(EXCLUSIVE_OR_EXPRESSION, "exclusive_or_expression xor", 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2135 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 248 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(AND_EXPRESSION, "and_expression", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2141 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 252 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(EQUALITY_EXPRESSION, "equality_experssion", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2149 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 257 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2155 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 258 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2161 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 262 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(RELATIONAL_EXPERSSION, "relational_expression", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2169 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 267 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2175 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 268 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2181 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 269 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2187 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 270 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2193 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 274 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(SHIFT_EXPRESSION, "shift_expression", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2201 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 279 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2207 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 280 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2213 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 284 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(ADDITIVE_EXPRESSION, "additive_expression", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2221 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 289 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2227 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 290 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2233 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 294 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(MULTIPLICATIVE_EXPRESSION, "multiplicative_expression", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2241 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 299 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2247 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 300 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2253 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 301 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(OPERATOR, (yyvsp[0].string), 0); }
#line 2259 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 305 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(CAST_EXPRESSION, "cast_expression ()", 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2267 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 310 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(TYPE_NAME, "type_name", 1, (yyvsp[0].node)); }
#line 2273 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 311 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(TYPE_NAME, "type_name", 2, (yyvsp[-1].node), create_node(OPERATOR, (yyvsp[0].string), 0)); }
#line 2279 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 315 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(UNARY_EXPRESSION, "unary_expression", 2, create_node(OPERATOR, (yyvsp[-1].string), 0), (yyvsp[0].node)); }
#line 2285 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 316 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(UNARY_EXPRESSION, "unary_expression", 2, create_node(OPERATOR, (yyvsp[-1].string), 0), (yyvsp[0].node)); }
#line 2291 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 317 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(UNARY_EXPRESSION, "unary_expression", 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2297 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 318 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(UNARY_EXPRESSION, "unary_expression", 2, create_node(OPERATOR, (yyvsp[-1].string), 0), (yyvsp[0].node)); }
#line 2303 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 319 "analyzer.y" /* yacc.c:1646  */
    {
        (yyval.node) = create_node(UNARY_EXPRESSION, "unary_expression ()", 2, create_node(OPERATOR, (yyvsp[-3].string), 0), (yyvsp[-1].node));
    }
#line 2311 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 324 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(UNARY_OPERATOR, (yyvsp[0].string), 0); }
#line 2317 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 325 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(UNARY_OPERATOR, (yyvsp[0].string), 0); }
#line 2323 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 326 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(UNARY_OPERATOR, (yyvsp[0].string), 0); }
#line 2329 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 327 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(UNARY_OPERATOR, (yyvsp[0].string), 0); }
#line 2335 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 328 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(UNARY_OPERATOR, (yyvsp[0].string), 0); }
#line 2341 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 329 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(UNARY_OPERATOR, (yyvsp[0].string), 0); }
#line 2347 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 333 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(POSTFIX_EXPRESSION, "postfix_expression", 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2353 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 336 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(POSTFIX, "postfix []", 1, (yyvsp[-1].node)); }
#line 2359 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 337 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(POSTFIX, "postfix ()", 0); }
#line 2365 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 338 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(POSTFIX, "postfix ()", 1, (yyvsp[-1].node)); }
#line 2371 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 339 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(POSTFIX, "postfix .", 2, create_node(OPERATOR, (yyvsp[-1].string), 0), create_node(IDENTIFIER, (yyvsp[0].string), 0)); }
#line 2377 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 340 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(POSTFIX, "postfix ->", 2, create_node(OPERATOR, (yyvsp[-1].string), 0), create_node(IDENTIFIER, (yyvsp[0].string), 0)); }
#line 2383 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 341 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(POSTFIX, "postfix ++", 1, create_node(OPERATOR, (yyvsp[0].string), 0)); }
#line 2389 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 342 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(POSTFIX, "postfix --", 1, create_node(OPERATOR, (yyvsp[0].string), 0)); }
#line 2395 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 345 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(ARGUMENTS, "arguments", 1, (yyvsp[0].node)); }
#line 2401 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 346 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = merge_node((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2407 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 349 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(IDENTIFIER, (yyvsp[0].string), 0); }
#line 2413 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 351 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(STRING_CONSTANT, (yyvsp[0].string), 0); }
#line 2419 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 352 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(PRIMARY_EXPRESSION, "primary_expressoin ()", 1, (yyvsp[-1].node)); }
#line 2425 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 355 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(INTEGER_CONSTANT, (yyvsp[0].string), 0); }
#line 2431 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 356 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(DOUBLE_CONSTANT, (yyvsp[0].string), 0); }
#line 2437 "analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 357 "analyzer.y" /* yacc.c:1646  */
    { (yyval.node) = create_node(CHARACTER_CONSTANT, (yyvsp[0].string), 0); }
#line 2443 "analyzer.tab.c" /* yacc.c:1646  */
    break;


#line 2447 "analyzer.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 359 "analyzer.y" /* yacc.c:1906  */


void yyerror(char* s) {
    printf("error ocurred: %s\n", s);
}

/*
int main(int argc, char** argv) {
    freopen(argv[1], "r", stdin);
    yyparse();
    print_ast(treeroot, 0);
    return 0;
}
*/

