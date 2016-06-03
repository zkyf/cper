#ifndef FILE_SEMANTICS_H
#define FILE_SEMANTICS_H

#include "ast.h"

struct InfoNode;

typedef enum {
    INT, CHAR, VOID, DOUBLE,
    ARRAY, POINTER, STRUCT, UNION, FUNCTION,
    NAME
} EnumInfoNode;

typedef struct {
    int size;
    struct InfoNode* ptr;
    int width;
} InfoNodeArray;

typedef struct {
    char* name;
    int size;
    struct InfoNode** field;
    int* offset;
    int width;
} InfoNodeRecord;

typedef struct {
    int size;
    struct InfoNode** pars;
    int* offset;
    int width;                  //此处的width只是参数的width之和
    struct InfoNode* ret;
} InfoNodeFunction;

typedef struct InfoNode {
    char isinstance;            //default: 0
    char isconst;               //defualt: 0
    EnumInfoNode type;
		union {
			int val;
			double real;
		};
    char isleftvalue;           //default: 0
    char* identifier;           //default: NULL
    int width;                  //default: 4
    union {
        InfoNodeArray* array; 
        struct InfoNode* pointer;
        InfoNodeRecord* record;
        InfoNodeFunction* function;
    }info;
} InfoNode;

typedef struct {
    int size, capacity;
    InfoNode** array;
} SymbolTable;

#define MAX_LEVEL (233)

/*
 * auxiliary functions
 */
int isint(EnumInfoNode);
int isnumber(EnumInfoNode);
int isdouble(EnumInfoNode);
int ispointer(EnumInfoNode);
int isscalar(EnumInfoNode);
int string_to_int(char*);
double string_to_double(char*);
char* int_to_name(int);

/*
 * malloc simplification functions
 */
int* new_int_n(int);
InfoNode* new_info_node();
InfoNode** new_info_node_n(int);
InfoNodeFunction* new_info_node_function();
InfoNodeRecord* new_info_node_record();
InfoNodeArray* new_info_node_array();
char* copy_string(char*);
InfoNodeArray* copy_info_node_array(InfoNodeArray*);
InfoNodeRecord* copy_info_node_record(InfoNodeRecord*);
InfoNodeFunction* copy_info_node_function(InfoNodeFunction*);
InfoNode* copy_info_node(InfoNode*);

/*
 * symbol table functions
 */
void symbol_table_initialize();
void symbol_table_next_level();
void symbol_table_prev_level();
void symbol_table_enlarge(SymbolTable*);
void debug_print_symbol_table();
void symbol_table_insert_0(InfoNode*);
void symbol_table_insert(InfoNode*);
int symbol_table_query_top_level_variable(char*);
int symbol_table_query_type(InfoNode*);
int symbol_table_query_function(char*);
InfoNode* symbol_table_fetch_function(char*);
InfoNode* symbol_table_fetch_identifier(char*);
InfoNode* symbol_table_fetch_type_instance(InfoNode*);

/*
 * semantics check functions
 */
void semantics_check(TreeNode*);
void semantics_check_program(TreeNode*);
void semantics_check_declaration(TreeNode*);
InfoNode* semantics_check_type_specifier(TreeNode*);
InfoNodeRecord* semantics_check_type_specifiers(TreeNode*, int);
InfoNode* semantics_check_declarator(TreeNode*, InfoNode*);
InfoNode* semantics_check_plain_declarator(TreeNode*, InfoNode*);
InfoNode* semantics_check_plain_declarators(TreeNode*, InfoNode*);
void semantics_check_init_declarator(TreeNode*, InfoNode*);
void semantics_check_initializier(TreeNode*, InfoNode*);
void semantics_check_function_definition(TreeNode*);
InfoNode* semantics_check_function_definition_1(TreeNode*);
InfoNodeFunction* semantics_check_parameters(TreeNode*);
InfoNode* semantics_check_plain_declaration(TreeNode*);
void semantics_check_compound_statement(TreeNode*);
void semantics_check_selection_statement(TreeNode*);
void semantics_check_iteration_statement(TreeNode*);
void semantics_check_jump_statement(TreeNode*);
int semantics_check_same_type(InfoNode*, InfoNode*);
InfoNode* semantics_check_expression(TreeNode*);
InfoNode* semantics_check_assignment_expression(TreeNode*);
InfoNode* semantics_check_constant_expression(TreeNode*);
InfoNode* semantics_check_logical_or_expression(TreeNode*);
InfoNode* semantics_check_logical_and_expression(TreeNode*);
InfoNode* semantics_check_inclusive_or_expression(TreeNode*);
InfoNode* semantics_check_exclusive_or_expression(TreeNode*);
InfoNode* semantics_check_and_expression(TreeNode*);
InfoNode* semantics_check_equality_expression(TreeNode*);
InfoNode* semantics_check_relational_expression(TreeNode*);
InfoNode* semantics_check_shift_expression(TreeNode*);
InfoNode* semantics_check_additive_expression(TreeNode*);
InfoNode* semantics_check_multiplicative_expression(TreeNode*);
InfoNode* semantics_check_cast_expression(TreeNode*);
InfoNode* semantics_check_type_name(TreeNode*);
InfoNode* semantics_check_unary_expression(TreeNode*);
InfoNode* semantics_check_postfix_expression(TreeNode*);
InfoNode* semantics_check_primary_expression(TreeNode*);
void phase_2_semantics_check();

#endif
