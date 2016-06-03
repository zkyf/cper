#ifndef FILE_TRANSLATE_H
#define FILE_TRANSLATE_H

/*
 * Quadruple Data Structure
 */

#include "semantics.h"

typedef struct {
    enum {
        ADDRESS_LABEL, ADDRESS_CONSTANT, ADDRESS_TEMP,
        ADDRESS_NAME
    } type;
    int value;
		double dvalue;
    int real;
    int needload;
    int needclear;
} Address;

typedef struct {
    char* op;
    char flag;
    char active;
    Address arguments[3];
} Quadruple;

typedef struct {
    int size, capacity;
    Quadruple** instructions;
} IntermediateRepresentation;

extern IntermediateRepresentation ir, gir, mir;

Quadruple* new_quadruple();
Quadruple* new_quadruple_label();
Quadruple* new_quadruple_function(char*);
Quadruple* new_quadruple_call(char*);
Quadruple* new_quadruple_ret();
Quadruple* new_quadruple_end();
Quadruple* new_quadruple_goto(int);
Quadruple* new_quadruple_branch(char*, int, int);
Quadruple* new_quadruple_arithmetic_im(char*, int, int, int);
Quadruple* new_quadruple_arithmetic(char*, int, int, int);
Quadruple* new_quadruple_arithmetic_unary(char*, int, int);
Quadruple* new_quadruple_li(int, int);
Quadruple* new_quadruple_lw(int, int);
Quadruple* new_quadruple_lb(int, int);
Quadruple* new_quadruple_lw_offset(int, int, int);
Quadruple* new_quadruple_sb(int, int);
Quadruple* new_quadruple_sw(int, int);
Quadruple* new_quadruple_sw_offset(int, int, int);
Quadruple* new_quadruple_move(int, int);
Quadruple* new_quadruple_gnew(int, int);
Quadruple* new_quadruple_string_const(int, char*);
Quadruple* copy_quadruple(Quadruple*);
int get_label_number(Quadruple*);
void ir_enlarge(IntermediateRepresentation*);
void ir_push_back(IntermediateRepresentation*, Quadruple*);
void ir_print();
void ir_initialize();

/*
 * Environment - Register Information
 */

#define REGISTER_STATE_VALUE (0)
#define REGISTER_STATE_ADDRESS (1)

typedef struct {
    int size, capacity;
    int* state;
    int* offset; //-1 global, o.w. sp
} Register;

extern int stack_pointer, retad_pointer;
extern Register rs;

void rs_enlarge();
int new_register();
int get_register_state();
//int catch_value(int);
void catch_value_self(InfoNode*, int);
void set_register_state_to_address(int);
void set_register_state_to_value(int);

/*
 * Environment - Loop Stack, for jump information
 */

typedef struct {
    int size, capacity;
    int* label_continue;
    int* label_break;
} LoopStack;

void ls_enlarge();
void ls_push_back();
void ls_pop_back();

/*
 * Environment - Variables to Registers Stack
 */

typedef struct {
    int size, capacity;
    char** identifier;
    int* to;
} VariablesToRegistersStack;

extern VariablesToRegistersStack vs;

void vs_enlarge();
void vs_push_back(char*, int);
int vs_fetch_register(char*);

/*
 * Translation Declaration
 */
void phase_3_translate();
void translate(TreeNode*);
void translate_init_declarator(TreeNode*);
void translate_initializer(TreeNode*, int);
void translate_function_definition();

void translate_selection_statement(TreeNode*);
void translate_iteration_statement(TreeNode*);
void translate_jump_statement(TreeNode*);

void translate_expression(TreeNode*, int);
void translate_expression_1(TreeNode*, int, int);
void translate_assignment(InfoNode*, int, int);
void translate_assignment_expression(TreeNode*, int);
void translate_assignment_expression_1(TreeNode*, int, int);
void translate_constant_expression(TreeNode*, int);
void translate_logical_or_expression(TreeNode*, int);
void translate_logical_or_expression_1(TreeNode*, int, int);
void translate_logical_and_expression(TreeNode*, int);
void translate_logical_and_expression_1(TreeNode*, int, int);
void translate_inclusive_or_expression(TreeNode*, int);
void translate_inclusive_or_expression_1(TreeNode*, int, int);
void translate_exclusive_or_expression(TreeNode*, int);
void translate_exclusive_or_expression_1(TreeNode*, int, int);
void translate_and_expression(TreeNode*, int);
void translate_and_expression_1(TreeNode*, int, int);
void translate_equality_expression(TreeNode*, int);
void translate_equality_expression_1(TreeNode*, int, int);
void translate_relational_expression(TreeNode*, int);
void translate_relational_expression_1(TreeNode*, int, int);
void translate_shift_expression(TreeNode*, int);
void translate_additive_expression(TreeNode*, int);
void translate_multiplicative_expression(TreeNode*, int);
void translate_cast_expression(TreeNode*, int);
void translate_unary_expression(TreeNode*, int);
void translate_postfix_expression(TreeNode*, int);
void translate_primary_expression(TreeNode*, int);

#endif

