%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "def.h"
#include "ast.h"

void yyerror(char*);
%}

%union {
    TreeNode* node;
    char* string;
}

%token <string> SEMICOLON COMMA COLON
%token <string> PARENTHESES_L PARENTHESES_R BRACES_L BRACES_R BRACKETS_L BRACKETS_R
%token <string> VOID_T INT_T CHAR_T STRUCT_T UNION_T DOUBLE_T
%token <string> IF_C ELSE_C FOR_C WHILE_C CONTINUE_C BREAK_C RETURN_C SWITCH_C CASE_C DEFAULT_C
%token <string> SIZEOF_OP
%token <string> DOUBLE_OR_OP DOUBLE_AND_OP INC_OP DEC_OP DOT_OP PTR_OP
%token <string> OR_OP XOR_OP AND_OP EQ_OP NE_OP SLE_OP SGE_OP LE_OP GE_OP SHL_OP SHR_OP ADD_OP SUB_OP MUL_OP DIV_OP MOD_OP
%token <string> EQUAL_SIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN SHL_ASSIGN SHR_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token <string> IDENTIFIER_O INT_CONST DOUBLE_CONST CHAR_CONST STRING_CONST
%token <string> COM_OP NOT_OP

%type <node> program declaration function_definition parameters declarators init_declarators
%type <node> init_declarator initializer type_specifier struct_or_union plain_declaration declarator plain_declarator
%type <node> statement expression_statement compound_statement selection_statement iteration_statement jump_statement
%type <node> expression assignment_expression assignment_operator constant_expression logical_or_expression logical_and_expression
%type <node> inclusive_or_expression exclusive_or_expression and_expression equality_experssion equality_operator relational_expression
%type <node> relational_operator shift_expression shift_operator additive_expression additive_operator multiplicative_expression
%type <node> multiplicative_operator cast_expression type_name unary_expression unary_operator postfix_expressoin postfix arguments
%type <node> primary_expressoin constant
%type <node> t_initializer t_type_specifier t_declarator t_declaration t_statement
 
%%

program
    : declaration { treeroot = $$ = create_node(PROGRAM, "program", 1, $1); }
    | function_definition { treeroot = $$ = create_node(PROGRAM, "program", 1, $1); }
    | program declaration { treeroot = $$ = merge_node($1, $2); }
    | program function_definition { treeroot = $$ = merge_node($1, $2); }
    ;
declaration
    : type_specifier SEMICOLON { $$ = create_node(DECLARATION, "declaration", 1, $1); }
    | type_specifier init_declarators SEMICOLON { $$ = create_node(DECLARATION, "declaration", 2, $1, $2); }
    ;
function_definition
    : type_specifier plain_declarator PARENTHESES_L PARENTHESES_R compound_statement { 
        $$ = create_node(FUNCTION_DEFINITION, "function_definition ()", 3, $1, $2, $5); 
    }
    | type_specifier plain_declarator PARENTHESES_L parameters PARENTHESES_R compound_statement {
        $$ = create_node(FUNCTION_DEFINITION, "function_definition ()", 4, $1, $2, $4, $6); 
    }
    ;
parameters
    : plain_declaration { $$ = create_node(PARAMETERS, "parameters", 1, $1); }
    | parameters COMMA plain_declaration { $$ = merge_node($1, $3); }
    ;
declarators
    : declarator { $$ = create_node(DECLARATORS, "declarators", 1, $1); }
    | declarators COMMA declarator { $$ = merge_node($1, $3); }
    ;
init_declarators
    : init_declarator { $$ = create_node(INIT_DECLARATORS, "init_declarators", 1, $1); }
    | init_declarators COMMA init_declarator { $$ = merge_node($1, $3); }
    ;
init_declarator
    : declarator { $$ = create_node(INIT_DECLARATOR, "init_declarator", 1, $1); }
    | declarator EQUAL_SIGN initializer { $$ = create_node(INIT_DECLARATOR, "init_declarator =", 2, $1, $3); }
    ;
initializer
    : assignment_expression
    | BRACES_L t_initializer BRACES_R { $$ = create_node(INITIALIZER, "initializer {}", 1, $2); }
    ;
t_initializer
    : initializer { $$ = create_node(INITIALIZER, "initializers", 1, $1); }
    | t_initializer COMMA initializer { $$ = merge_node($1, $3); }
    ;
type_specifier
    : VOID_T { $$ = create_node(KEYWORDS, $1, 0); }
    | CHAR_T { $$ = create_node(KEYWORDS, $1, 0); }
    | INT_T { $$ = create_node(KEYWORDS, $1, 0); }
    | DOUBLE_T { $$ = create_node(KEYWORDS, $1, 0); }
    | struct_or_union BRACES_L t_type_specifier BRACES_R {
        $$ = create_node(TYPE_SPECIFIER, "type_specifier {}", 2, $1, $3);
    }
    | struct_or_union IDENTIFIER_O BRACES_L t_type_specifier BRACES_R {
        $$ = create_node(TYPE_SPECIFIER, "type_specifier identifier {}", 3, $1, create_node(IDENTIFIER, $2, 0), $4);
    }
    | struct_or_union IDENTIFIER_O {
        $$ = create_node(TYPE_SPECIFIER, "type_specifier", 2, $1, create_node(IDENTIFIER, $2, 0));
    }
    ;
t_type_specifier
    : type_specifier declarators SEMICOLON {
        $$ = create_node(TYPE_SPECIFIERS, "type_specifiers", 2, $1, $2);
    }
    | t_type_specifier type_specifier declarators SEMICOLON {
        $$ = merge_node(merge_node($1, $2), $3);
    }
    ;
struct_or_union
    : STRUCT_T { $$ = create_node(KEYWORDS, $1, 0); }
    | UNION_T { $$ = create_node(KEYWORDS, $1, 0); }
    ;
plain_declaration
    : type_specifier declarator { $$ = create_node(PLAIN_DECLARATION, "plain_declaration", 2, $1, $2); }
    ;
declarator
    : plain_declarator PARENTHESES_L PARENTHESES_R { $$ = create_node(DECLARATOR, "declarator ()", 1, $1); }
    | plain_declarator PARENTHESES_L parameters PARENTHESES_R { $$ = create_node(DECLARATOR, "declarator ()", 2, $1, $2); }
    | plain_declarator { $$ = create_node(DECLARATOR, "declarator", 1, $1); }
    | plain_declarator t_declarator { $$ = create_node(DECLARATOR, "declarator", 2, $1, $2); }
    ;
t_declarator
    : BRACKETS_L constant_expression BRACKETS_R { $$ = create_node(DECLARATOR, "declarators []", 1, $2); }
    | t_declarator BRACKETS_L constant_expression BRACKETS_R { $$ = merge_node($1, $3); }
    ;
plain_declarator
    : IDENTIFIER_O { $$ = create_node(IDENTIFIER, $1, 0);}
    | MUL_OP plain_declarator { $$ = create_node(PLAIN_DECLARATOR, "plain_declarator *", 1, $2); }

statement
    : expression_statement 
    | compound_statement 
    | selection_statement 
    | iteration_statement 
    | jump_statement 
    | switch_statement
    ;
expression_statement
    : SEMICOLON { $$ = create_node(EXPRESSION_STATEMENT, "expression_statement", 0); }
    | expression SEMICOLON { $$ = $1; }
    ;
compound_statement
    : BRACES_L BRACES_R { $$ = create_node(COMPOUND_STATEMENT, "compound_statement {}", 0); }
    | BRACES_L t_declaration BRACES_R { $$ = create_node(COMPOUND_STATEMENT, "compound_statement {}", 1, $2); }
    | BRACES_L t_statement BRACES_R { $$ = create_node(COMPOUND_STATEMENT, "compound_statement {}", 1, $2); }
    | BRACES_L t_declaration t_statement BRACES_R  { $$ = create_node(COMPOUND_STATEMENT, "compound_statement {}", 2, $2, $3); }
    ;
t_declaration
    : declaration { $$ = create_node(DECLARATION, "declarations", 1, $1); }
    | t_declaration declaration { $$ = merge_node($1, $2); }
    ;
t_statement
    : statement { $$ = create_node(STATEMENT, "statements", 1, $1); }
    | t_statement statement { $$ = merge_node($1, $2); }
    ;
case_statement
    : CASE_C case_label COLON t_statement { $$ = create_node(CASE_STATEMENT, "case label", 2, $2, $4); }
    | CASE_C DEFAULT_C COLON t_statement { $$ = create_node(CASE_STATEMENT, "case default", 1, $4); }
case_part
    | case_part case_statement { $$ = merge_node($1, $2); }
selection_statement
    : IF_C PARENTHESES_L expression PARENTHESES_R statement {
        $$ = create_node(SELECTION_STATEMENT, "selection_statement if", 2, $3, $5);
    }
    | IF_C PARENTHESES_L expression PARENTHESES_R statement ELSE_C statement {
        $$ = create_node(SELECTION_STATEMENT, "selection_statement if else", 3, $3, $5, $7);
    }
    ;
switch_statement
    : SWITCH_C PARENTHESES_L expression PARENTHESES_R case_part {
        $$ = create_node(SWICTH_STATEMENT, "switch_statement", 2, $3, $5);
    }
iteration_statement
    : WHILE_C PARENTHESES_L expression PARENTHESES_R statement {
        $$ = create_node(ITERATION_STATEMENT, "while()", 2, $3, $5);
    }
    | FOR_C PARENTHESES_L            SEMICOLON            SEMICOLON            PARENTHESES_R statement {
        $$ = create_node(ITERATION_STATEMENT, "for(;;)", 1, $6);
    }
    | FOR_C PARENTHESES_L            SEMICOLON            SEMICOLON expression PARENTHESES_R statement {
        $$ = create_node(ITERATION_STATEMENT, "for(;;*)", 2, $5, $7);
    }
    | FOR_C PARENTHESES_L            SEMICOLON expression SEMICOLON            PARENTHESES_R statement {
        $$ = create_node(ITERATION_STATEMENT, "for(;*;)", 2, $4, $7);
    }
    | FOR_C PARENTHESES_L            SEMICOLON expression SEMICOLON expression PARENTHESES_R statement {
        $$ = create_node(ITERATION_STATEMENT, "for(;*;*)", 3, $4, $6, $8);
    }
    | FOR_C PARENTHESES_L expression SEMICOLON            SEMICOLON            PARENTHESES_R statement {
        $$ = create_node(ITERATION_STATEMENT, "for(*;;)", 2, $3, $7);
    }
    | FOR_C PARENTHESES_L expression SEMICOLON            SEMICOLON expression PARENTHESES_R statement {
        $$ = create_node(ITERATION_STATEMENT, "for(*;;*)", 3, $3, $6, $8);
    }
    | FOR_C PARENTHESES_L expression SEMICOLON expression SEMICOLON            PARENTHESES_R statement {
        $$ = create_node(ITERATION_STATEMENT, "for(*;*;)", 3, $3, $5, $8);
    }
    | FOR_C PARENTHESES_L expression SEMICOLON expression SEMICOLON expression PARENTHESES_R statement {
        $$ = create_node(ITERATION_STATEMENT, "for(*;*;*)", 4, $3, $5, $7, $9);
    }
    ;
jump_statement
    : CONTINUE_C SEMICOLON { $$ = create_node(JUMP_STATEMENT, "jump_statement", 1, create_node(KEYWORDS, $1, 0)); }
    | BREAK_C SEMICOLON { $$ = create_node(JUMP_STATEMENT, "jump_statement", 1, create_node(KEYWORDS, $1, 0)); }
    | RETURN_C SEMICOLON { $$ = create_node(JUMP_STATEMENT, "jump_statement", 1, create_node(KEYWORDS, $1, 0)); }
    | RETURN_C expression SEMICOLON {
        $$ = create_node(JUMP_STATEMENT, "jump_statement", 2, create_node(KEYWORDS, $1, 0), $2); 
    }
    ;

expression
    : assignment_expression { $$ = create_node(EXPRESSION, "expression", 1, $1); }
    | expression COMMA assignment_expression { $$ = create_node(EXPRESSION, "expression", 2, $1, $3); }
    ;
assignment_expression
    : logical_or_expression
    | unary_expression assignment_operator assignment_expression {
        $$ = create_node(ASSIGN_EXPRESSION, "assignment_expression", 3, $1, $2, $3); 
    }
    ;
assignment_operator
    : EQUAL_SIGN { $$ = create_node(OPERATOR, $1, 0); }
    | MUL_ASSIGN { $$ = create_node(OPERATOR, $1, 0); }
    | DIV_ASSIGN { $$ = create_node(OPERATOR, $1, 0); }
    | MOD_ASSIGN { $$ = create_node(OPERATOR, $1, 0); }
    | ADD_ASSIGN { $$ = create_node(OPERATOR, $1, 0); }
    | SUB_ASSIGN { $$ = create_node(OPERATOR, $1, 0); }
    | SHL_ASSIGN { $$ = create_node(OPERATOR, $1, 0); }
    | SHR_ASSIGN { $$ = create_node(OPERATOR, $1, 0); }
    | AND_ASSIGN { $$ = create_node(OPERATOR, $1, 0); }
    | XOR_ASSIGN { $$ = create_node(OPERATOR, $1, 0); }
    | OR_ASSIGN { $$ = create_node(OPERATOR, $1, 0); }
    ;
constant_expression
    : logical_or_expression
    ;
logical_or_expression
    : logical_and_expression
    | logical_or_expression DOUBLE_OR_OP logical_and_expression {
        $$ = create_node(LOGICAL_OR_EXPRESSION, "logical_or_expression ||", 2, $1, $3);
    }
    ;
logical_and_expression
    : inclusive_or_expression
    | logical_and_expression DOUBLE_AND_OP inclusive_or_expression {
        $$ = create_node(LOGICAL_AND_EXPRESSION, "logical_and_expression &&", 2, $1, $3);
    }
    ;
inclusive_or_expression
    : exclusive_or_expression 
    | inclusive_or_expression OR_OP exclusive_or_expression { 
        $$ = create_node(INCLUSIVE_OR_EXPRESSION, "inclusive_or_expression or", 2, $1, $3);
    }
    ;
exclusive_or_expression
    : and_expression
    | exclusive_or_expression XOR_OP and_expression { 
        $$ = create_node(EXCLUSIVE_OR_EXPRESSION, "exclusive_or_expression xor", 2, $1, $3);
    }
    ;
and_expression
    : equality_experssion
    | and_expression AND_OP equality_experssion { $$ = create_node(AND_EXPRESSION, "and_expression", 2, $1, $3); }
    ;
equality_experssion
    : relational_expression
    | equality_experssion equality_operator relational_expression {
        $$ = create_node(EQUALITY_EXPRESSION, "equality_experssion", 3, $1, $2, $3);
    }
    ;
equality_operator
    : EQ_OP { $$ = create_node(OPERATOR, $1, 0); }
    | NE_OP { $$ = create_node(OPERATOR, $1, 0); }
    ;
relational_expression
    : shift_expression
    | relational_expression relational_operator shift_expression {
        $$ = create_node(RELATIONAL_EXPERSSION, "relational_expression", 3, $1, $2, $3);
    }
    ;
relational_operator
    : SLE_OP { $$ = create_node(OPERATOR, $1, 0); }
    | SGE_OP { $$ = create_node(OPERATOR, $1, 0); }
    | LE_OP { $$ = create_node(OPERATOR, $1, 0); }
    | GE_OP { $$ = create_node(OPERATOR, $1, 0); }
    ;
shift_expression 
    : additive_expression
    | shift_expression shift_operator additive_expression {
        $$ = create_node(SHIFT_EXPRESSION, "shift_expression", 3, $1, $2, $3);
    }
    ;
shift_operator
    : SHL_OP { $$ = create_node(OPERATOR, $1, 0); }
    | SHR_OP { $$ = create_node(OPERATOR, $1, 0); }
    ;
additive_expression
    : multiplicative_expression
    | additive_expression additive_operator multiplicative_expression {
        $$ = create_node(ADDITIVE_EXPRESSION, "additive_expression", 3, $1, $2, $3);
    }
    ;
additive_operator
    : ADD_OP { $$ = create_node(OPERATOR, $1, 0); }
    | SUB_OP { $$ = create_node(OPERATOR, $1, 0); }
    ;
multiplicative_expression
    : cast_expression
    | multiplicative_expression multiplicative_operator cast_expression {
        $$ = create_node(MULTIPLICATIVE_EXPRESSION, "multiplicative_expression", 3, $1, $2, $3); 
    }
    ;
multiplicative_operator
    : MUL_OP { $$ = create_node(OPERATOR, $1, 0); }
    | DIV_OP { $$ = create_node(OPERATOR, $1, 0); }
    | MOD_OP { $$ = create_node(OPERATOR, $1, 0); }
    ;
cast_expression 
    : unary_expression
    | PARENTHESES_L type_name PARENTHESES_R cast_expression {
        $$ = create_node(CAST_EXPRESSION, "cast_expression ()", 2, $2, $4);
    }
    ;
type_name
    : type_specifier { $$ = create_node(TYPE_NAME, "type_name", 1, $1); }
    | type_name MUL_OP { $$ = create_node(TYPE_NAME, "type_name", 2, $1, create_node(OPERATOR, $2, 0)); }
    ;
unary_expression
    : postfix_expressoin
    | INC_OP unary_expression { $$ = create_node(UNARY_EXPRESSION, "unary_expression", 2, create_node(OPERATOR, $1, 0), $2); }
    | DEC_OP unary_expression { $$ = create_node(UNARY_EXPRESSION, "unary_expression", 2, create_node(OPERATOR, $1, 0), $2); }
    | unary_operator cast_expression { $$ = create_node(UNARY_EXPRESSION, "unary_expression", 2, $1, $2); }
    | SIZEOF_OP unary_expression { $$ = create_node(UNARY_EXPRESSION, "unary_expression", 2, create_node(OPERATOR, $1, 0), $2); }
    | SIZEOF_OP PARENTHESES_L type_name PARENTHESES_R {
        $$ = create_node(UNARY_EXPRESSION, "unary_expression ()", 2, create_node(OPERATOR, $1, 0), $3);
    }
    ;
unary_operator
    : AND_OP { $$ = create_node(UNARY_OPERATOR, $1, 0); }
    | MUL_OP { $$ = create_node(UNARY_OPERATOR, $1, 0); }
    | ADD_OP { $$ = create_node(UNARY_OPERATOR, $1, 0); }
    | SUB_OP { $$ = create_node(UNARY_OPERATOR, $1, 0); }
    | COM_OP { $$ = create_node(UNARY_OPERATOR, $1, 0); }
    | NOT_OP { $$ = create_node(UNARY_OPERATOR, $1, 0); }
    ;
postfix_expressoin
    : primary_expressoin
    | postfix_expressoin postfix { $$ = create_node(POSTFIX_EXPRESSION, "postfix_expression", 2, $1, $2); }
    ;
postfix
    : BRACKETS_L expression BRACKETS_R { $$ = create_node(POSTFIX, "postfix []", 1, $2); }
    | PARENTHESES_L PARENTHESES_R { $$ = create_node(POSTFIX, "postfix ()", 0); }
    | PARENTHESES_L arguments PARENTHESES_R { $$ = create_node(POSTFIX, "postfix ()", 1, $2); }
    | DOT_OP IDENTIFIER_O { $$ = create_node(POSTFIX, "postfix .", 2, create_node(OPERATOR, $1, 0), create_node(IDENTIFIER, $2, 0)); }
    | PTR_OP IDENTIFIER_O { $$ = create_node(POSTFIX, "postfix ->", 2, create_node(OPERATOR, $1, 0), create_node(IDENTIFIER, $2, 0)); }
    | INC_OP { $$ = create_node(POSTFIX, "postfix ++", 1, create_node(OPERATOR, $1, 0)); }
    | DEC_OP { $$ = create_node(POSTFIX, "postfix --", 1, create_node(OPERATOR, $1, 0)); }
    ;
arguments
    : assignment_expression { $$ = create_node(ARGUMENTS, "arguments", 1, $1); }
    | arguments COMMA assignment_expression { $$ = merge_node($1, $3); }
    ;
primary_expressoin
    : IDENTIFIER_O { $$ = create_node(IDENTIFIER, $1, 0); }
    | constant
    | STRING_CONST { $$ = create_node(STRING_CONSTANT, $1, 0); }
    | PARENTHESES_L expression PARENTHESES_R { $$ = create_node(PRIMARY_EXPRESSION, "primary_expressoin ()", 1, $2); }
    ;
constant
    : INT_CONST { $$ = create_node(INTEGER_CONSTANT, $1, 0); }
    | DOUBLE_CONST { $$ = create_node(DOUBLE_CONSTANT, $1, 0); }
    | CHAR_CONST { $$ = create_node(CHARACTER_CONSTANT, $1, 0); }
    ;
%%

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

