#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "utility.h"
#include "ast.h"
#include "def.h"
#include "semantics.h"
#include "translate.h"

/*
label n         ("label", n, -, -)
goto n          ("goto", n, -, -) 
func __s        ("func", __s, -, -)
call __s        ("call", __s, -, -)
ret             ("ret", -, -, -)

or a, b, c      ("or", a, b, c)     a = b | c
xor a, b, c     ("xor", a, b, c)    a = b ^ c
and a, b, c     ("and", a, b, c)    a = b & c
shl a, b, c     ("sll", a, b, c)    a = b << c
shr a, b, c     ("srl", a, b, c)    a = b >> c

add a, b, c     ("add", a, b, c)    a = b + c
sub a, b, c     ("sub", a, b, c)    a = b - c
mul a, b, c     ("mul", a, b, c)    a = b * c
div a, b, c     ("div", a, b, c)    a = b / c
rem a, b, c     ("rem", a, b, c)    a = b % c

neg a, b        ("neg", a, b)       a = -b
not a, b        ("not", a, b)       a = ~b
lnot a, b       ("lnot", a, b)      a = !b

beqz a, b       ("beqz", a, b, -)   if a == 0 goto b
bnez a, b       ("bnez", a, b, -)   if a != 0 goto b
bgez a, b       ("bgez", a, b, -)   if a >= 0 goto b
bgtz a, b       ("bgtz", a, b, -)   if a >  0 goto b
blez a, b       ("blez", a, b, -)   if a <= 0 goto b
bltz a, b       ("bltz", a, b, -)   if a <  0 goto b

li a, b         ("li", a, b -)      a = 3
lw a, b         ("lw", a, b, -)     a = *b, 4 bytes
sb a, b         ("sw", a, b, -)     *b = a, 1 byte
sw a, b         ("sw", a, b, -)     *b = a, 4 bytes
move a, b       ("move", a, b, -)   a = b
gnew a, b       ("gnew", a, b, -)   in global memory, new a bytes, store the address at register b
*/

int label_count, level, global_flag, quadruple_flag, main_flag;
IntermediateRepresentation ir, gir, mir;
int stack_pointer, retad_pointer;
int current_sp, function_begin_sp, local_register_count;
Register rs;
LoopStack ls;
VariablesToRegistersStack vs;

/*
 * Quadruple Implementation
 */

Quadruple* new_quadruple() {
    Quadruple* ret = (Quadruple*)malloc(sizeof(Quadruple));
    ret->flag = quadruple_flag;
    ret->active = 1;
    ret->arguments[0].type = -1;
    ret->arguments[0].value = -1;
		ret->arguments[0].dvalue = -1;
    ret->arguments[0].real = -1;
    ret->arguments[0].needload = 0;
    ret->arguments[0].needclear = 0;

    ret->arguments[1].type = -1;
    ret->arguments[1].value = -1;
		ret->arguments[1].dvalue = -1;
    ret->arguments[1].real = -1;
    ret->arguments[1].needload = 0;
    ret->arguments[1].needclear = 0;

    ret->arguments[2].type = -1;
    ret->arguments[2].value = -1;
		ret->arguments[2].dvalue = -1;
    ret->arguments[2].real = -1;
    ret->arguments[2].needload = 0;
    ret->arguments[2].needclear = 0;
    return ret;
}

Quadruple* new_quadruple_label() {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("label");
    ret->arguments[0].type = ADDRESS_LABEL;
    ret->arguments[0].value = label_count++;
    return ret;
}

Quadruple* new_quadruple_function(char *s) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("func");
    ret->arguments[0].type = ADDRESS_NAME;
    if (strcmp(s, "main") != 0) {
        int n = strlen(s);
        char* t = (char*)malloc(sizeof(char) * (n + 3));
        t[0] = t[1] = '_';
        memcpy(t + 2, s, sizeof(char) * n);
        t[n + 2] = '\0';
        ret->arguments[0].value = (int)t;
    } else {
        ret->arguments[0].value = (int)strdup(s);
    }
    return ret;
}

Quadruple* new_quadruple_call(char *s) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("call");
    ret->arguments[0].type = ADDRESS_NAME;
    if (strcmp(s, "main") != 0) {
        int n = strlen(s);
        char* t = (char*)malloc(sizeof(char) * (n + 3));
        t[0] = t[1] = '_';
        memcpy(t + 2, s, sizeof(char) * n);
        t[n + 2] = '\0';
        ret->arguments[0].value = (int)t;
    } else {
        ret->arguments[0].value = (int)strdup(s);
    }
    return ret;
}

Quadruple* new_quadruple_ret() {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("ret");
    return ret;
}

Quadruple* new_quadruple_goto(int value) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("goto");
    ret->arguments[0].type = ADDRESS_LABEL;
    ret->arguments[0].value = value;
    return ret;
}

Quadruple* new_quadruple_branch(char *s, int a, int b) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup(s);
    ret->arguments[0].type = ADDRESS_TEMP;
    ret->arguments[0].value = a;
    ret->arguments[1].type = ADDRESS_LABEL;
    ret->arguments[1].value = b;
    return ret;
}

Quadruple* new_quadruple_arithmetic_im(char *s, int ra, int rb, int im) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup(s);
    ret->arguments[0].type = ADDRESS_TEMP;
    ret->arguments[0].value = ra;
    ret->arguments[1].type = ADDRESS_TEMP;
    ret->arguments[1].value = rb;
    ret->arguments[2].type = ADDRESS_CONSTANT;
    ret->arguments[2].value = im;
    return ret;
}

Quadruple* new_quadruple_arithmetic(char *s, int ra, int rb, int rc) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup(s);
    ret->arguments[0].type = ADDRESS_TEMP;
    ret->arguments[0].value = ra;
    ret->arguments[1].type = ADDRESS_TEMP;
    ret->arguments[1].value = rb;
    ret->arguments[2].type = ADDRESS_TEMP;
    ret->arguments[2].value = rc;
    return ret;
}

Quadruple* new_quadruple_arithmetic_unary(char *s, int ra, int rb) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup(s);
    ret->arguments[0].type = ADDRESS_TEMP;
    ret->arguments[0].value = ra;
    ret->arguments[1].type = ADDRESS_TEMP;
    ret->arguments[1].value = rb;
    return ret;
}

Quadruple* new_quadruple_li(int ra, int im) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("li");
    ret->arguments[0].type = ADDRESS_TEMP;
    ret->arguments[0].value = ra;
    ret->arguments[1].type = ADDRESS_CONSTANT;
    ret->arguments[1].value = im;
    return ret;
}

Quadruple* new_quadruple_lw(int ra, int rb) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("lw");
    ret->arguments[0].type = ADDRESS_TEMP;
    ret->arguments[0].value = ra;
    ret->arguments[1].type = ADDRESS_TEMP;
    ret->arguments[1].value = rb;
    ret->arguments[2].type = ADDRESS_CONSTANT;
    ret->arguments[2].value = 0;
    return ret;
}

Quadruple* new_quadruple_lb(int ra, int rb) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("lb");
    ret->arguments[0].type = ADDRESS_TEMP;
    ret->arguments[0].value = ra;
    ret->arguments[1].type = ADDRESS_TEMP;
    ret->arguments[1].value = rb;
    ret->arguments[2].type = ADDRESS_CONSTANT;
    ret->arguments[2].value = 0;
    return ret;
}

Quadruple* new_quadruple_lw_offset(int ra, int rb, int offset) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("lw");
    ret->arguments[0].type = ADDRESS_TEMP;
    ret->arguments[0].value = ra;
    ret->arguments[1].type = ADDRESS_TEMP;
    ret->arguments[1].value = rb;
    ret->arguments[2].type = ADDRESS_CONSTANT;
    ret->arguments[2].value = offset;
    return ret;
}

Quadruple* new_quadruple_sb(int ra, int rb) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("sb");
    ret->arguments[0].type = ADDRESS_TEMP;
    ret->arguments[0].value = ra;
    ret->arguments[1].type = ADDRESS_TEMP;
    ret->arguments[1].value = rb;
    ret->arguments[2].type = ADDRESS_CONSTANT;
    ret->arguments[2].value = 0;
    return ret;
}

Quadruple* new_quadruple_sw(int ra, int rb) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("sw");
    ret->arguments[0].type = ADDRESS_TEMP;
    ret->arguments[0].value = ra;
    ret->arguments[1].type = ADDRESS_TEMP;
    ret->arguments[1].value = rb;
    ret->arguments[2].type = ADDRESS_CONSTANT;
    ret->arguments[2].value = 0;
    return ret;
}

Quadruple* new_quadruple_sw_offset(int ra, int rb, int offset) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("sw");
    ret->arguments[0].type = ADDRESS_TEMP;
    ret->arguments[0].value = ra;
    ret->arguments[1].type = ADDRESS_TEMP;
    ret->arguments[1].value = rb;
    ret->arguments[2].type = ADDRESS_CONSTANT;
    ret->arguments[2].value = offset;
    return ret;
}

Quadruple* new_quadruple_move(int ra, int rb) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("move");
    ret->arguments[0].type = ADDRESS_TEMP;
    ret->arguments[0].value = ra;
    ret->arguments[1].type = ADDRESS_TEMP;
    ret->arguments[1].value = rb;
    return ret;
}

Quadruple* new_quadruple_gnew(int size, int reg) {  //为了方便调试, 或许可以把名字打进去
    Quadruple* ret = new_quadruple();
    ret->op = strdup("gnew");
    ret->arguments[0].type = ADDRESS_CONSTANT;
    ret->arguments[0].value = size;
    ret->arguments[1].type = ADDRESS_TEMP;
    ret->arguments[1].value = reg;
    return ret;
}

Quadruple* new_quadruple_string_const(int reg, char* s) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup("snew");
    ret->arguments[0].type = ADDRESS_NAME;
    ret->arguments[0].value = (int)strdup(s);
    ret->arguments[1].type = ADDRESS_TEMP;
    ret->arguments[1].value = reg;
    return ret;
}

Quadruple* copy_quadruple(Quadruple* p) {
    Quadruple* ret = new_quadruple();
    ret->op = strdup(p->op);
    int i;
    for (i = 0; i < 3; i++) {                       //这里名字的拷贝可能会有点问题, 先无视了
        ret->arguments[i] = p->arguments[i];
    }
    return ret;
}

int get_label_number(Quadruple* qr) {
#ifdef ASSERT_ON
    assert(strcmp(qr->op, "label") == 0);
#endif
    return qr->arguments[0].value;
}

void ir_enlarge(IntermediateRepresentation* ir) {
    if (ir->size == ir->capacity) {
        ir->capacity <<= 1;
        Quadruple** array = (Quadruple**)malloc(sizeof(Quadruple*) * ir->capacity);
        int i;
        for (i = 0; i < ir->size; i++) {
            array[i] = ir->instructions[i];
        }
        free(ir->instructions);
        ir->instructions = array;
    }
}

void ir_push_back(IntermediateRepresentation* ir, Quadruple* key) {
    if (global_flag && ir != (&gir)) {
        ir = &mir;
    }
    ir_enlarge(ir);
    ir->instructions[ir->size++] = key;     //这里应该是没有必要拷贝的, 毕竟new出来就是push进来的
}

void ir_print(IntermediateRepresentation* ir) {
    FILE* fout = stderr;
    int i, j;
    for (i = 0; i < ir->size; i++) {
        if (!ir->instructions[i]->active) {
            fprintf(fout, "#%d\n", i);
            continue;
        }
        if (strcmp(ir->instructions[i]->op, "func") != 0) {
            fprintf(fout, "#%d\t\t", i);
        } else {
            fprintf(fout, "#%d", i);
        }
#ifdef COLOR_ON
        fprintf(fout, "\033[31;1m%s\033[0m", ir->instructions[i]->op);
#else
        fprintf(fout, "%s", ir->instructions[i]->op);
#endif
        for (j = 0; j < 3; j++) {
            Address* ptr = &(ir->instructions[i]->arguments[j]);
            if (ptr->value == -1) {
                break;
            }
            fprintf(fout, "%s", j > 0 ? "\t" : "\t");
            switch (ptr->type) {
                case ADDRESS_LABEL:
#ifdef COLOR_ON
                    fprintf(fout, "\033[32;1ml%d\033[0m", ptr->value);
#else
                    fprintf(fout, "l%d", ptr->value);
#endif
                    break;
                case ADDRESS_NAME:
#ifdef COLOR_ON
                    fprintf(fout, "\033[33;1m%s\033[0m", (char*)ptr->value);
#else
                    fprintf(fout, "%s", (char*)ptr->value);
#endif
                    break;
                case ADDRESS_TEMP: 
#ifdef COLOR_ON
                    if (ptr->value == stack_pointer) {
                        fprintf(fout, "\033[35;1m$sp\033[0m");
                    } else if (ptr->value == retad_pointer) {
                        fprintf(fout, "\033[35;1m$ra\033[0m");
                    } else if (ptr->real != -1) {
                        fprintf(fout, "\033[35;1m$%d\033[0m", ptr->real);
                    } else {
                        fprintf(fout, "\033[35;1mt%d\033[0m", ptr->value);
                    }
#else
                    if (ptr->value == stack_pointer) {
                        fprintf(fout, "$sp");
                    } else if (ptr->value == retad_pointer) {
                        fprintf(fout, "$ra");
                    } else if (ptr->real != -1) {
                        fprintf(fout, "$%d", ptr->real);
                    } else {
                        fprintf(fout, "t%d", ptr->value);
                    }
#endif
                    break;
                case ADDRESS_CONSTANT:
#ifdef COLOR_ON
                    fprintf(fout, "\033[34;1m%d\033[0m", ptr->value);
#else
                    fprintf(fout, "%d", ptr->value);
#endif
                    break;
            }
        }
        fprintf(fout, "\n");
    }
}

void ir_initialize(IntermediateRepresentation* ir) {
    ir->size = 0;
    ir->capacity = 1;
    ir->instructions = (Quadruple**)malloc(sizeof(Quadruple*) * ir->capacity);
}

/*
 * Register Implementation
 */

void rs_enlarge() {
    if (rs.size == rs.capacity) {
        rs.capacity <<= 1;
        int* a1 = (int*)malloc(sizeof(int) * rs.capacity);
        int* a2 = (int*)malloc(sizeof(int) * rs.capacity);
        int i;
        for (i = 0; i < rs.size; i++) {
            a1[i] = rs.state[i];
            a2[i] = rs.offset[i];
        }
        free(rs.state);
        free(rs.offset);
        rs.state = a1;
        rs.offset = a2;
    }
}

int new_register() {
    rs_enlarge();
    rs.state[rs.size] = 0;
    if (function_begin_sp == -1) {
        rs.offset[rs.size] = -1;
    } else {
        local_register_count++;
        rs.offset[rs.size] = local_register_count * 4;
    }
    return rs.size++;
}

int get_register_state(int k) {
    return rs.state[k];
}

//  int catch_value(int k) {
//      if (get_register_state(k) == REGISTER_STATE_VALUE) {
//          return k;
//      }
//      int ret = new_register();
//      ir_push_back(&ir, new_quadruple_lw(ret, k));            //TO SPEED UP
//      return ret;
//  }

void catch_value_self(InfoNode* p, int k) {
    if (get_register_state(k) == REGISTER_STATE_ADDRESS) {  //ERROR, without considering width
        if (p->width == 4) {
            ir_push_back(&ir, new_quadruple_lw(k, k));
        } else {
            ir_push_back(&ir, new_quadruple_lb(k, k));
        }
        set_register_state_to_value(k);
    }
}

void set_register_state_to_address(int k) {
    rs.state[k] = 1;
}

void set_register_state_to_value(int k) {
    rs.state[k] = 0;
}

/*
 * Loop Stack Implementation
 */

void ls_enlarge() {
    if (ls.size == ls.capacity) {
        ls.capacity <<= 1;
        int* a1 = (int*)malloc(sizeof(int) * ls.capacity);
        int* a2 = (int*)malloc(sizeof(int) * ls.capacity);
        int i;
        for (i = 0; i < ls.size; i++) {
            a1[i] = ls.label_continue[i];
            a2[i] = ls.label_break[i];
        }
        free(ls.label_continue);
        free(ls.label_break);
        ls.label_continue = a1;
        ls.label_break = a2;
    }
}

void ls_push_back(int x, int y) {
    ls_enlarge();
    ls.label_continue[ls.size] = x;
    ls.label_break[ls.size] = y;
    ls.size++;
}

void ls_pop_back() {
    ls.size--;
}

/*
 * Variables to Registers Stack Implementation
 */

void vs_enlarge() {
    if (vs.size == vs.capacity) {
        vs.capacity <<= 1;
        char** a1 = (char**)malloc(sizeof(char*) * vs.capacity);
        int* a2 = (int*)malloc(sizeof(int) * vs.capacity);
        int i;
        for (i = 0; i < vs.size; i++) {
            a1[i] = vs.identifier[i];
            a2[i] = vs.to[i];
        }
        free(vs.identifier);
        free(vs.to);
        vs.identifier = a1;
        vs.to = a2;
    }
}

void vs_push_back(char* s, int reg) {
    vs_enlarge();
    vs.identifier[vs.size] = strdup(s);
    vs.to[vs.size] = reg;
    vs.size++;
}

int vs_fetch_register(char* s) {
    int i;
    for (i = vs.size - 1; i >= 0; i--) {
        if (strcmp(vs.identifier[i], s) == 0) {
            return vs.to[i];
        }
    }
    assert(0);
}

/*
 * Translation Implementation
 */

/* Top level */

void phase_3_translate() {
    main_flag = 0;
    function_begin_sp = -1;
    quadruple_flag = 0;
    label_count = level = 0;

    ir_initialize(&ir);
    ir_initialize(&gir);
    ir_initialize(&mir);
    global_flag = 0;

    ls.size = 0;
    ls.capacity = 1;
    ls.label_continue = (int*)malloc(sizeof(int) * ls.capacity);
    ls.label_break = (int*)malloc(sizeof(int) * ls.capacity);

    rs.size = 0;
    rs.capacity = 1;
    rs.state = (int*)malloc(sizeof(int) * rs.capacity);
    rs.offset = (int*)malloc(sizeof(int) * rs.capacity);

    vs.size = 0;
    vs.capacity = 1;
    vs.identifier = (char**)malloc(sizeof(char*) * vs.capacity);
    vs.to = (int*)malloc(sizeof(int) * vs.capacity);

    stack_pointer = new_register();
    set_register_state_to_address(stack_pointer);
    retad_pointer = new_register();
    current_sp = 0;

    translate(treeroot);
}

void translate(TreeNode* p) {
    int i, j;
		if (!p)
		{
			printf("sytax error\n");
			return;
		}
    switch (p->type) {
        case PROGRAM:
            for (i = 0; i < p->size; i++) {
                translate(p->children[i]);
            }
            break;
        case DECLARATION:
            if (p->size > 1) {
                for (i = 0; i < p->children[1]->size; i++) {
                    translate_init_declarator(p->children[1]->children[i]);
                }
            }
            break;
        case FUNCTION_DEFINITION: translate_function_definition(p); break;
        case INIT_DECLARATOR: translate_init_declarator(p); break;
        case COMPOUND_STATEMENT:
            level++;
            int pos = vs.size;
            int old_current_sp = current_sp;
            for (i = 0; i < p->size; i++) {
                for (j = 0; j < p->children[i]->size; j++) {
                    translate(p->children[i]->children[j]);
                }
            }
            current_sp = old_current_sp;
            vs.size = pos;
            level--;
            break;
        case SELECTION_STATEMENT: translate_selection_statement(p); break;
        case ITERATION_STATEMENT: translate_iteration_statement(p); break;
        case JUMP_STATEMENT: translate_jump_statement(p); break;
        case EXPRESSION: translate_expression(p, new_register()); break;
        case EXPRESSION_STATEMENT:
            if (p->size > 0) {
                translate(p->children[0]);
            }
            break;
#ifdef ASSERT_ON
        default: fprintf(stderr, "%d\n", p->type); assert(0);
#endif
    }
}

void translate_init_declarator(TreeNode* p) {
    InfoNode* ptr = p->info;
    int reg = new_register();
    if (level == 0) {
        global_flag = 1;
    }
    if (level == 0) {
        if (ptr->type != ARRAY) {
            ir_push_back(&gir, new_quadruple_gnew(ptr->width, reg));
        } else {
            ir_push_back(&gir, new_quadruple_gnew(ptr->info.array->width, reg));
        }
    } else {
        if (ptr->type != ARRAY) {
            current_sp += ptr->width;
        } else {
            current_sp += ptr->info.array->width;
        }
        int t = new_register();
        quadruple_flag = 1;
        ir_push_back(&ir, new_quadruple_arithmetic_im("add", t, stack_pointer, -current_sp + function_begin_sp));
        quadruple_flag = 0;
        ir_push_back(&ir, new_quadruple_move(reg, t));
    }
    set_register_state_to_address(reg);
    vs_push_back(ptr->identifier, reg);
    if (p->size > 1) {
        int tmp = new_register();
        translate_initializer(p->children[1], tmp);
        translate_assignment(ptr, reg, tmp);
    }
    global_flag = 0;
}

void translate_initializer(TreeNode* p, int reg) {  //to_do, array initailize case
    if (p->type != INITIALIZER) {
        translate_assignment_expression(p, reg);
        return;
    }
}

void translate_function_definition(TreeNode* p) {
    InfoNode* ptr = p->info;
    ir_push_back(&ir, new_quadruple_function(ptr->identifier));
    if (strcmp(ptr->identifier, "main") == 0) {
        main_flag = 1;
    }
    int j = ir.size - 1;        //为了修改后面与stack_pointer相关的指令
    local_register_count = 0;
    function_begin_sp = current_sp;

    InfoNodeFunction* rec = ptr->info.function;
    int pos = vs.size;
    int i;
    for (i = 0; i < rec->size; i++) {
        int reg = new_register();
        ir_push_back(&ir, new_quadruple_arithmetic_im("add", reg, stack_pointer, rec->offset[i]));     //EXTRA
        if (rec->pars[i]->type != ARRAY) {          //special case
            set_register_state_to_address(reg);
        } else {
            set_register_state_to_value(reg);
        }
        vs_push_back(rec->pars[i]->identifier, reg);
    }
    translate(p->children[p->size - 1]);
    vs.size = pos;

    ir_push_back(&ir, new_quadruple_ret());
    for (i = j; i < ir.size; i++) {
        if (ir.instructions[i]->flag == 1) {
            ir.instructions[i]->arguments[2].value -= local_register_count * 4;
        }
    }
    current_sp = function_begin_sp;
    function_begin_sp = -1;
}

/* Statements */

void translate_selection_statement(TreeNode* p) {
    //if (a) then b; else c     ->      (a->L1) | b | goto L2 | label: L1 | c | label: L2
    Quadruple* t1 = new_quadruple_label();
    Quadruple* t2 = new_quadruple_label();
    Quadruple* t3 = new_quadruple_goto(get_label_number(t2));
    int reg = new_register();

//  translate_expression(p->children[0], reg);
//  catch_value_self(p->children[0]->info, reg);
//  ir_push_back(&ir, new_quadruple_branch("beqz", reg, get_label_number(t1)));
    translate_expression_1(p->children[0], 0, get_label_number(t1));

    translate(p->children[1]);
    ir_push_back(&ir, t3);
    ir_push_back(&ir, t1);
    if (p->size == 3) {
        translate(p->children[2]);
    }
    ir_push_back(&ir, t2);
}

void translate_iteration_statement(TreeNode* p) {
    Quadruple* t1 = new_quadruple_label();
    Quadruple* t2 = new_quadruple_label();
    if (strcmp(p->data, "while()") == 0) {
        int old_current_sp = current_sp;
        Quadruple* t3 = new_quadruple_goto(t1->arguments[0].value);
        //while (a) b;      ->      label L1 | (a->L2) | b | goto L1 | label L2
        ls_push_back(get_label_number(t1), get_label_number(t2));
        ir_push_back(&ir, t1);

//      int reg = new_register();
//      translate_expression(p->children[0], reg);
//      catch_value_self(p->children[0]->info, reg);
//      ir_push_back(&ir, new_quadruple_branch("beqz", reg, get_label_number(t2)));
        translate_expression_1(p->children[0], 0, get_label_number(t2));

        translate(p->children[1]);
        ir_push_back(&ir, t3);
        ir_push_back(&ir, t2);
        current_sp = old_current_sp;
        ls_pop_back();
    } else {
        /*for(a;b;c)d;      ->      a | (b->L3) | label L1 | d | label L2 | c | (!b->L1) | label L3*/
        TreeNode *a = NULL, *b = NULL, *c = NULL;
        if (strcmp(p->data, "for(;;*)") == 0) {
            c = p->children[0];
        } else if (strcmp(p->data, "for(;*;)") == 0) {
            b = p->children[0];
        } else if (strcmp(p->data, "for(;*;*)") == 0) {
            b = p->children[0];
            c = p->children[1];
        } else if (strcmp(p->data, "for(*;;)") == 0) {
            a = p->children[0];
        } else if (strcmp(p->data, "for(*;;*)") == 0) {
            a = p->children[0];
            c = p->children[1];
        } else if (strcmp(p->data, "for(*;*;)") == 0) {
            a = p->children[0];
            b = p->children[1];
        } else if (strcmp(p->data, "for(*;*;*)") == 0) {
            a = p->children[0];
            b = p->children[1];
            c = p->children[2];
        }
        int old_current_sp = current_sp;

        Quadruple* t3 = new_quadruple_label();
        ls_push_back(t2->arguments[0].value, t3->arguments[0].value);
        int reg = new_register();
        translate_expression(a, reg);

//      translate_expression(b, reg);
//      if (b != NULL) {
//          catch_value_self(b->info, reg);
//      }
//      ir_push_back(&ir, new_quadruple_branch("beqz", reg, get_label_number(t3)));
        if (b != NULL) {
            translate_expression_1(b, 0, get_label_number(t3));
        } else {
            ir_push_back(&ir, new_quadruple_goto(get_label_number(t3)));
        }

        ir_push_back(&ir, t1);
        translate(p->children[p->size - 1]);
        ir_push_back(&ir, t2);
        translate_expression(c, reg);

//      translate_expression(b, reg);
//      if (b != NULL) {
//          catch_value_self(b->info, reg);
//      }
//      ir_push_back(&ir, new_quadruple_branch("bnez", reg, get_label_number(t1)));
        if (b != NULL) {
            translate_expression_1(b, 1, get_label_number(t1));
        } else {
            ir_push_back(&ir, new_quadruple_goto(get_label_number(t1)));
        }

        ir_push_back(&ir, t3);

        current_sp = old_current_sp;
        ls_pop_back();
    }
}

void translate_jump_statement(TreeNode* p) {
    if (strcmp(p->children[0]->data, "return") == 0) {
        if (p->size > 1) {
            int t0 = new_register(), t1 = new_register();
            translate_expression(p->children[1], t1);
            ir_push_back(&ir, new_quadruple_arithmetic_im("add", t0, stack_pointer, p->info->info.function->width + 4)); //EXTRA
            translate_assignment(p->info->info.function->ret, t0, t1);
        }
        ir_push_back(&ir, new_quadruple_ret());
    } else if (strcmp(p->children[0]->data, "continue") == 0) {
        ir_push_back(&ir, new_quadruple_goto(ls.label_continue[ls.size - 1]));
    } else { //break
        ir_push_back(&ir, new_quadruple_goto(ls.label_break[ls.size - 1]));
    }
}

/* Expressions */

void translate_expression(TreeNode* p, int reg) {
    if (p == NULL) { //handle for (; ; ), a little ugly
        return;
    }
#ifdef ASSERT_ON
    assert(p->type == EXPRESSION);
#endif
    if (p->size > 1) {
        int tmp = new_register();
        translate_expression(p->children[0], tmp);
    }
    translate_assignment_expression(p->children[p->size - 1], reg);
}

void translate_expression_1(TreeNode* p, int flag, int num) {
    if (p == NULL) { //handle for (; ; ), a little ugly
        return;
    }
    if (p->size > 1) {
        int tmp = new_register();
        translate_expression(p->children[0], tmp);
    }
    translate_assignment_expression_1(p->children[p->size - 1], flag, num);
}

void translate_assignment(InfoNode* p, int reg_l, int reg_r) {
    if (p->width <= 4) {
        if (p->width == 1) {
            catch_value_self(p, reg_r);
            ir_push_back(&ir, new_quadruple_sb(reg_r, reg_l));
        } else {
            catch_value_self(p, reg_r);
            ir_push_back(&ir, new_quadruple_sw(reg_r, reg_l));
        }
    } else {
        int t1 = new_register();
        int t2 = new_register();
        int t3 = new_register();
        ir_push_back(&ir, new_quadruple_move(t1, reg_l));
        ir_push_back(&ir, new_quadruple_move(t2, reg_r));
        int i;
        for (i = 0; i < p->width; i += 4) {     //这里可以对非struct的情形进行优化
            ir_push_back(&ir, new_quadruple_lw(t3, t2));
            ir_push_back(&ir, new_quadruple_sw(t3, t1));
            ir_push_back(&ir, new_quadruple_arithmetic_im("add", t1, t1, 4));
            ir_push_back(&ir, new_quadruple_arithmetic_im("add", t2, t2, 4));
        }
    }
}

void translate_assignment_expression(TreeNode* p, int reg) {
    if (p->type != ASSIGN_EXPRESSION) {
        translate_logical_or_expression(p, reg);
        return;
    }
    translate_unary_expression(p->children[0], reg);
    int tmp = new_register();
    translate_assignment_expression(p->children[2], tmp);
    assert(get_register_state(reg) == REGISTER_STATE_ADDRESS);
    if (strcmp(p->children[1]->data, "=") == 0) {
        translate_assignment(p->children[0]->info, reg, tmp);
    } else {
        int t = new_register();
        char *op;
        switch (p->children[1]->data[0]) {
            case '*': op = "mul"; break;
            case '/': op = "div"; break;
            case '%': op = "rem"; break;
            case '+': op = "add"; break;
            case '-': op = "sub"; break;
            case '<': op = "sll"; break;
            case '>': op = "srl"; break;
            case '&': op = "and"; break;
            case '^': op = "xor"; break;
            case '|': op = "or"; break;
        }
#ifdef ASSERT_ON
        assert(get_register_state(reg) == REGISTER_STATE_ADDRESS);
#endif
        ir_push_back(&ir, new_quadruple_lw(t, reg));
        catch_value_self(p->children[2]->info, tmp);
        ir_push_back(&ir, new_quadruple_arithmetic(op, t, t, tmp));
        ir_push_back(&ir, new_quadruple_sw(t, reg));
    }
}

void translate_assignment_expression_1(TreeNode* p, int flag, int num) {
    if (p->type != ASSIGN_EXPRESSION) {
        translate_logical_or_expression_1(p, flag, num);
        return;
    }
    int reg = new_register();
    translate_unary_expression(p->children[0], reg);
    int tmp = new_register();
    translate_assignment_expression(p->children[2], tmp);
    if (strcmp(p->children[1]->data, "=") == 0) {
        translate_assignment(p->children[0]->info, reg, tmp);
        catch_value_self(p->children[0]->info, reg);
        if (flag == 0) {
            ir_push_back(&ir, new_quadruple_branch("beqz", reg, num));
        } else {
            ir_push_back(&ir, new_quadruple_branch("bnez", reg, num));
        }
    } else {
        int t = new_register();
        char *op;
        switch (p->children[1]->data[0]) {
            case '*': op = "mul"; break;
            case '/': op = "div"; break;
            case '%': op = "rem"; break;
            case '+': op = "add"; break;
            case '-': op = "sub"; break;
            case '<': op = "sll"; break;
            case '>': op = "srl"; break;
            case '&': op = "and"; break;
            case '^': op = "xor"; break;
            case '|': op = "or"; break;
        }
        catch_value_self(p->children[0]->info, reg);
        catch_value_self(p->children[2]->info, tmp);
        ir_push_back(&ir, new_quadruple_arithmetic(op, reg, reg, tmp));
        if (flag == 0) {
            ir_push_back(&ir, new_quadruple_branch("beqz", reg, num));
        } else {
            ir_push_back(&ir, new_quadruple_branch("bnez", reg, num));
        }
    }
}

void translate_logical_or_expression(TreeNode* p, int reg) {
    //store the value of a || b to register reg
    if (p->type != LOGICAL_OR_EXPRESSION) {
        translate_logical_and_expression(p, reg);
        return;
    }
    translate_logical_or_expression(p->children[0], reg);
    Quadruple* l = new_quadruple_label();
    catch_value_self(p->children[0]->info, reg);
    ir_push_back(&ir, new_quadruple_branch("bnez", reg, get_label_number(l)));
    translate_logical_and_expression(p->children[1], reg);
    catch_value_self(p->children[1]->info, reg);
    ir_push_back(&ir, l);
    ir_push_back(&ir, new_quadruple_arithmetic_im("and", reg, reg, 1));
}

void translate_logical_or_expression_1(TreeNode* p, int flag, int num) {
    //store the value of a || b to register reg
    if (p->type != LOGICAL_OR_EXPRESSION) {
        translate_logical_and_expression_1(p, flag, num);
        return;
    }
    if (flag == 0) {
        Quadruple* l = new_quadruple_label();
        translate_logical_or_expression_1(p->children[0], 1, get_label_number(l));
        translate_logical_and_expression_1(p->children[1], 0, num);
        ir_push_back(&ir, l);
    } else {
        translate_logical_or_expression_1(p->children[0], 1, num);
        translate_logical_and_expression_1(p->children[1], 1, num);
    }
}

void translate_logical_and_expression(TreeNode* p, int reg) {
    if (p->type != LOGICAL_AND_EXPRESSION) {
        translate_inclusive_or_expression(p, reg);
        return;
    }
    translate_logical_and_expression(p->children[0], reg);
    Quadruple* l = new_quadruple_label();
    catch_value_self(p->children[0]->info, reg);
    ir_push_back(&ir, new_quadruple_branch("beqz", reg, get_label_number(l)));
    translate_inclusive_or_expression(p->children[1], reg);
    catch_value_self(p->children[1]->info, reg);
    ir_push_back(&ir, l);
    ir_push_back(&ir, new_quadruple_arithmetic_im("and", reg, reg, 1));
}

void translate_logical_and_expression_1(TreeNode* p, int flag, int num) {
    if (p->type != LOGICAL_AND_EXPRESSION) {
        translate_inclusive_or_expression_1(p, flag, num);
        return;
    }
    if (flag == 0) {
        translate_logical_and_expression_1(p->children[0], 0, num);
        translate_inclusive_or_expression_1(p->children[1], 0, num);
    } else {
        Quadruple* l = new_quadruple_label();
        translate_logical_and_expression_1(p->children[0], 0, get_label_number(l));
        translate_inclusive_or_expression_1(p->children[1], 1, num);
        ir_push_back(&ir, l);
    }
}

void translate_inclusive_or_expression(TreeNode* p, int reg) {
    if (p->type != INCLUSIVE_OR_EXPRESSION) {
        translate_exclusive_or_expression(p, reg);
        return;
    }
    translate_inclusive_or_expression(p->children[0], reg);
    catch_value_self(p->children[0]->info, reg);
    int tmp = new_register();
    translate_exclusive_or_expression(p->children[1], tmp);
    catch_value_self(p->children[1]->info, tmp);
    ir_push_back(&ir, new_quadruple_arithmetic("or", reg, reg, tmp));
}

void translate_inclusive_or_expression_1(TreeNode* p, int flag, int num) {
    if (p->type != INCLUSIVE_OR_EXPRESSION) {
        translate_exclusive_or_expression_1(p, flag, num);
        return;
    }
    int t = new_register();
    translate_inclusive_or_expression(p, t);
    catch_value_self(p->info, t);
    if (flag == 0) {
        ir_push_back(&ir, new_quadruple_branch("beqz", t, num));
    } else {
        ir_push_back(&ir, new_quadruple_branch("bnez", t, num));
    }
}

void translate_exclusive_or_expression(TreeNode* p, int reg) {
    if (p->type != EXCLUSIVE_OR_EXPRESSION) {
        translate_and_expression(p, reg);
        return;
    }
    translate_exclusive_or_expression(p->children[0], reg);
    catch_value_self(p->children[0]->info, reg);
    int tmp = new_register();
    translate_and_expression(p->children[1], tmp);
    catch_value_self(p->children[1]->info, tmp);
    ir_push_back(&ir, new_quadruple_arithmetic("xor", reg, reg, tmp));
}

void translate_exclusive_or_expression_1(TreeNode* p, int flag, int num) {
    if (p->type != EXCLUSIVE_OR_EXPRESSION) {
        translate_and_expression_1(p, flag, num);
        return;
    }
    int t = new_register();
    translate_exclusive_or_expression(p, t);
    catch_value_self(p->info, t);
    if (flag == 0) {
        ir_push_back(&ir, new_quadruple_branch("beqz", t, num));
    } else {
        ir_push_back(&ir, new_quadruple_branch("bnez", t, num));
    }
}

void translate_and_expression(TreeNode* p, int reg) {
    if (p->type != AND_EXPRESSION) {
        translate_equality_expression(p, reg);
        return;
    }
    translate_and_expression(p->children[0], reg);
    catch_value_self(p->children[0]->info, reg);
    int tmp = new_register();
    translate_equality_expression(p->children[1], tmp);
    catch_value_self(p->children[1]->info, tmp);
    ir_push_back(&ir, new_quadruple_arithmetic("and", reg, reg, tmp));
}

void translate_and_expression_1(TreeNode* p, int flag, int num) {
    if (p->type != AND_EXPRESSION) {
        translate_equality_expression_1(p, flag, num);
        return;
    }
    int t = new_register();
    translate_and_expression(p, t);
    catch_value_self(p->info, t);
    if (flag == 0) {
        ir_push_back(&ir, new_quadruple_branch("beqz", t, num));
    } else {
        ir_push_back(&ir, new_quadruple_branch("bnez", t, num));
    }
}

void translate_equality_expression(TreeNode* p, int reg) {
    if (p->type != EQUALITY_EXPRESSION) {
        translate_relational_expression(p, reg);
        return;
    }
    translate_relational_expression(p->children[0], reg);
    catch_value_self(p->children[0]->info, reg);
    int tmp = new_register();
    translate_relational_expression(p->children[2], tmp);
    catch_value_self(p->children[2]->info, tmp);
    //reg = 1 | if tmp == 0 goto L | reg = 0 | label L
    ir_push_back(&ir, new_quadruple_arithmetic("xor", tmp, tmp, reg));
    ir_push_back(&ir, new_quadruple_li(reg, 1));
    Quadruple* l = new_quadruple_label();
    if (p->children[1]->data[0] == '=') {
        ir_push_back(&ir, new_quadruple_branch("beqz", tmp, get_label_number(l)));
    } else {
        ir_push_back(&ir, new_quadruple_branch("bnez", tmp, get_label_number(l)));
    }
    ir_push_back(&ir, new_quadruple_li(reg, 0));
    ir_push_back(&ir, l);
}

void translate_equality_expression_1(TreeNode* p, int flag, int num) {
    if (p->type != EQUALITY_EXPRESSION) {
        translate_relational_expression_1(p, flag, num);
        return;
    }
    int reg = new_register();
    translate_relational_expression(p->children[0], reg);
    catch_value_self(p->children[0]->info, reg);
    int tmp = new_register();
    translate_relational_expression(p->children[2], tmp);
    catch_value_self(p->children[2]->info, tmp);
    ir_push_back(&ir, new_quadruple_arithmetic("xor", tmp, tmp, reg));
    if (flag == 0) {
        if (p->children[1]->data[0] == '=') {
            ir_push_back(&ir, new_quadruple_branch("bnez", tmp, num));
        } else {
            ir_push_back(&ir, new_quadruple_branch("beqz", tmp, num));
        }
    } else {
        if (p->children[1]->data[0] == '=') {
            ir_push_back(&ir, new_quadruple_branch("beqz", tmp, num));
        } else {
            ir_push_back(&ir, new_quadruple_branch("bnez", tmp, num));
        }
    }
}

void translate_relational_expression(TreeNode* p, int reg) {
    if (p->type != RELATIONAL_EXPERSSION) {
        translate_shift_expression(p, reg);
        return;
    }
    translate_relational_expression(p->children[0], reg);
    catch_value_self(p->children[0]->info, reg);
    int tmp = new_register();
    translate_shift_expression(p->children[2], tmp);
    catch_value_self(p->children[2]->info, tmp);
    ir_push_back(&ir, new_quadruple_arithmetic("sub", tmp, reg, tmp));
    ir_push_back(&ir, new_quadruple_li(reg, 1));
    Quadruple* l = new_quadruple_label();
    if (strcmp(p->children[1]->data, ">=") == 0) {
        ir_push_back(&ir, new_quadruple_branch("bgez", tmp, get_label_number(l)));
    } else if (strcmp(p->children[1]->data, ">") == 0) {
        ir_push_back(&ir, new_quadruple_branch("bgtz", tmp, get_label_number(l)));
    } else if (strcmp(p->children[1]->data, "<=") == 0) {
        ir_push_back(&ir, new_quadruple_branch("blez", tmp, get_label_number(l)));
    } else {
        ir_push_back(&ir, new_quadruple_branch("bltz", tmp, get_label_number(l)));
    }
    ir_push_back(&ir, new_quadruple_li(reg, 0));
    ir_push_back(&ir, l);
}

void translate_relational_expression_1(TreeNode* p, int flag, int num) {
    if (p->type != RELATIONAL_EXPERSSION) {
        int tmp = new_register();
        translate_shift_expression(p, tmp);
        catch_value_self(p->info, tmp);
        if (flag == 0) {
            ir_push_back(&ir, new_quadruple_branch("beqz", tmp, num));
        } else {
            ir_push_back(&ir, new_quadruple_branch("bnez", tmp, num));
        }
        return;
    }
    int reg = new_register();
    translate_relational_expression(p->children[0], reg);
    catch_value_self(p->children[0]->info, reg);
    int tmp = new_register();
    translate_shift_expression(p->children[2], tmp);
    catch_value_self(p->children[2]->info, tmp);
    ir_push_back(&ir, new_quadruple_arithmetic("sub", tmp, reg, tmp));
    if (flag == 0) {
        if (strcmp(p->children[1]->data, ">=") == 0) {
            ir_push_back(&ir, new_quadruple_branch("bltz", tmp, num));
        } else if (strcmp(p->children[1]->data, ">") == 0) {
            ir_push_back(&ir, new_quadruple_branch("blez", tmp, num));
        } else if (strcmp(p->children[1]->data, "<=") == 0) {
            ir_push_back(&ir, new_quadruple_branch("bgtz", tmp, num));
        } else {
            ir_push_back(&ir, new_quadruple_branch("bgez", tmp, num));
        }
    } else {
        if (strcmp(p->children[1]->data, ">=") == 0) {
            ir_push_back(&ir, new_quadruple_branch("bgez", tmp, num));
        } else if (strcmp(p->children[1]->data, ">") == 0) {
            ir_push_back(&ir, new_quadruple_branch("bgtz", tmp, num));
        } else if (strcmp(p->children[1]->data, "<=") == 0) {
            ir_push_back(&ir, new_quadruple_branch("blez", tmp, num));
        } else {
            ir_push_back(&ir, new_quadruple_branch("bltz", tmp, num));
        }
    }
}

void translate_shift_expression(TreeNode* p, int reg) {
    if (p->type != SHIFT_EXPRESSION) {
        translate_additive_expression(p, reg);
        return;
    }
    translate_shift_expression(p->children[0], reg);
    catch_value_self(p->children[0]->info, reg);
    int tmp = new_register();
    translate_additive_expression(p->children[2], tmp);
    catch_value_self(p->children[2]->info, tmp);
    if (p->children[1]->data[0] == '>') {
        ir_push_back(&ir, new_quadruple_arithmetic("srl", reg, reg, tmp));
    } else {
        ir_push_back(&ir, new_quadruple_arithmetic("sll", reg, reg, tmp));
    }
}

void translate_additive_expression(TreeNode* p, int reg) {
    if (p->type != ADDITIVE_EXPRESSION) {
        translate_multiplicative_expression(p, reg);
        return;
    }
    translate_additive_expression(p->children[0], reg);
    catch_value_self(p->children[0]->info, reg);
    int tmp = new_register();
    translate_multiplicative_expression(p->children[2], tmp);
    catch_value_self(p->children[2]->info, tmp);
    if (p->children[1]->data[0] == '+') {
        if (ispointer(p->children[0]->info->type)) {
            ir_push_back(&ir, new_quadruple_arithmetic_im("mul", tmp, tmp, p->children[0]->info->width));
            ir_push_back(&ir, new_quadruple_arithmetic("add", reg, reg, tmp));
        } else if (ispointer(p->children[2]->info->type)) {
            ir_push_back(&ir, new_quadruple_arithmetic_im("mul", reg, reg, p->children[1]->info->width));
            ir_push_back(&ir, new_quadruple_arithmetic("add", reg, reg, tmp));
        } else {
            ir_push_back(&ir, new_quadruple_arithmetic("add", reg, reg, tmp));
        }
    } else {
        if (ispointer(p->children[0]->info->type) && ispointer(p->children[2]->info->type)) {
            ir_push_back(&ir, new_quadruple_arithmetic("sub", reg, reg, tmp));
            ir_push_back(&ir, new_quadruple_arithmetic_im("div", reg, reg, p->children[0]->info->width));
        } if (ispointer(p->children[0]->info->type)) {
            ir_push_back(&ir, new_quadruple_arithmetic_im("mul", tmp, tmp, p->children[0]->info->width));
            ir_push_back(&ir, new_quadruple_arithmetic("sub", reg, reg, tmp));
        } else {
            ir_push_back(&ir, new_quadruple_arithmetic("sub", reg, reg, tmp));
        }
    }
}

void translate_multiplicative_expression(TreeNode* p, int reg) {
    if (p->type != MULTIPLICATIVE_EXPRESSION) {
        translate_cast_expression(p, reg);
        return;
    }
    translate_multiplicative_expression(p->children[0], reg);
    catch_value_self(p->children[0]->info, reg);
    int tmp = new_register();
    translate_multiplicative_expression(p->children[2], tmp);
    catch_value_self(p->children[2]->info, tmp);
    if (p->children[1]->data[0] == '*') {
        ir_push_back(&ir, new_quadruple_arithmetic("mul", reg, reg, tmp));
    } else if (p->children[1]->data[0] == '/') {
        ir_push_back(&ir, new_quadruple_arithmetic("div", reg, reg, tmp));
    } else {
        ir_push_back(&ir, new_quadruple_arithmetic("rem", reg, reg, tmp));
    }
}

void translate_cast_expression(TreeNode* p, int reg) {
    if (p->type != CAST_EXPRESSION) {
        translate_unary_expression(p, reg);
        return;
    }
    translate_cast_expression(p->children[1], reg);
    if (p->children[0]->info->type == INT || p->children[0]->info->type == CHAR) {
        catch_value_self(p->children[1]->info, reg);
        set_register_state_to_value(reg);
    } else if (p->children[0]->info->type == POINTER) {
        catch_value_self(p->children[1]->info, reg);
        set_register_state_to_value(reg);
    } else {
#ifdef ASSERT_ON
        assert(0);
#endif
    }
}

void translate_unary_expression(TreeNode* p, int reg) {
    if (p->type != UNARY_EXPRESSION) {
        translate_postfix_expression(p, reg);
        return;
    }
    if (p->children[0]->type == UNARY_OPERATOR) {
        translate_unary_expression(p->children[1], reg);
        if (p->children[0]->data[0] == '&') {
            assert(get_register_state(reg) == REGISTER_STATE_ADDRESS);
            set_register_state_to_value(reg);
        } else if (p->children[0]->data[0] == '*') {
            if (get_register_state(reg) == REGISTER_STATE_VALUE) {
                set_register_state_to_address(reg);
            } else {
                set_register_state_to_address(reg);
                ir_push_back(&ir, new_quadruple_lw(reg, reg));
            }
        } else {
            catch_value_self(p->children[1]->info, reg);
            switch(p->children[0]->data[0]) {
                case '-': ir_push_back(&ir, new_quadruple_arithmetic_unary("neg", reg, reg));
                          break;
                case '~': ir_push_back(&ir, new_quadruple_arithmetic_unary("not", reg, reg));
                          break;
                case '!': ir_push_back(&ir, new_quadruple_arithmetic_unary("lnot", reg, reg));
                          break;
            }
        }
    } else if (p->children[0]->data[0] == '+' || p->children[0]->data[0] == '-') {
        translate_unary_expression(p->children[1], reg);
        int delta = p->children[0]->data[0] == '+' ? 1 : -1;
        assert(get_register_state(reg) == REGISTER_STATE_ADDRESS);
        int t0 = new_register();
        ir_push_back(&ir, new_quadruple_move(t0, reg));
        set_register_state_to_value(reg);
        ir_push_back(&ir, new_quadruple_lw(reg, reg));
        ir_push_back(&ir, new_quadruple_arithmetic_im("add", reg, reg, delta));
        ir_push_back(&ir, new_quadruple_sw(reg, t0));
    } else { //sizeof (type-name) or sizeof unary-expression
        ir_push_back(&ir, new_quadruple_li(reg, p->info->val));
        set_register_state_to_value(reg);
    }
}

void translate_postfix_expression(TreeNode* p, int reg) {
    if (p->type != POSTFIX_EXPRESSION) {
        translate_primary_expression(p, reg);
        return;
    }
    translate_postfix_expression(p->children[0], reg);
    InfoNode* expr = p->children[0]->info;
    TreeNode* postfix = p->children[1];
    if (strcmp(postfix->data, "postfix []") == 0) {
        int t0 = new_register(), t1 = new_register();
        translate_expression(postfix->children[0], t0);
        catch_value_self(postfix->children[0]->info, t0);
        catch_value_self(p->children[0]->info, reg);
        if (p->info->type == ARRAY) {
            ir_push_back(&ir, new_quadruple_arithmetic_im("mul", t1, t0, p->info->info.array->width));
            set_register_state_to_value(reg);
        } else {
            ir_push_back(&ir, new_quadruple_arithmetic_im("mul", t1, t0, p->info->width));
            set_register_state_to_address(reg);
        }
        ir_push_back(&ir, new_quadruple_arithmetic("add", reg, reg, t1));
    } else if (strcmp(postfix->data, "postfix ()") == 0) {
        InfoNodeFunction* rec = expr->info.function;
        TreeNode* arguments = postfix->children[0];
        current_sp += rec->ret->width;
        current_sp += 4;
        quadruple_flag = 1;
        if (!main_flag) {
            ir_push_back(&ir, new_quadruple_sw_offset(retad_pointer, stack_pointer, -current_sp + function_begin_sp));
        }
        quadruple_flag = 0;
        int i;
        for (i = rec->size - 1; i >= 0; i--) {
            int width = rec->offset[i + 1] - rec->offset[i];
            current_sp += width;
            int t0 = new_register();
            translate_assignment_expression(arguments->children[i], t0);
            int t1 = new_register();
            set_register_state_to_address(t1);
            quadruple_flag = 1;
            ir_push_back(&ir, new_quadruple_arithmetic_im("add", t1, stack_pointer, -current_sp + function_begin_sp));
            quadruple_flag = 0;
            translate_assignment(rec->pars[i], t1, t0);
        }
        quadruple_flag = 1;
        ir_push_back(&ir, new_quadruple_arithmetic_im("add", stack_pointer, stack_pointer, -current_sp + function_begin_sp));
        quadruple_flag = 0;

        if (rec->size == 1 && strcmp(expr->identifier, "printf") == 0) {
            ir_push_back(&ir, new_quadruple_call("printf_one"));
        } else {
            ir_push_back(&ir, new_quadruple_call(expr->identifier));
        }

        quadruple_flag = 1;
        ir_push_back(&ir, new_quadruple_arithmetic_im("sub", stack_pointer, stack_pointer, -current_sp + function_begin_sp));
        quadruple_flag = 0;

        current_sp -= rec->width;

        quadruple_flag = 1;
        if (!main_flag) {
            ir_push_back(&ir, new_quadruple_lw_offset(retad_pointer, stack_pointer, -current_sp + function_begin_sp));
        }
        quadruple_flag = 0;
        current_sp -= 4;

        if (rec->ret->width > 0) {
            set_register_state_to_address(reg);
            int t = new_register();
            set_register_state_to_address(t);
            quadruple_flag = 1;
            ir_push_back(&ir, new_quadruple_arithmetic_im("add", t, stack_pointer, -current_sp + function_begin_sp));
            quadruple_flag = 0;
            ir_push_back(&ir, new_quadruple_move(reg, t));
            set_register_state_to_address(reg);
            current_sp -= rec->ret->width;
        }
    } else if (strcmp(postfix->data, "postfix .") == 0) {
        InfoNodeRecord* record = expr->info.record;
        int i, offset = -1;
        for (i = 0; i < record->size; i++) {
            if (strcmp(record->field[i]->identifier, postfix->children[1]->data) == 0) {
                offset = record->offset[i];
                break;
            }
        }
        assert(offset != -1);
        ir_push_back(&ir, new_quadruple_arithmetic_im("add", reg, reg, offset));
        if (p->info->type == ARRAY) {
            set_register_state_to_value(reg);
        } else {
            set_register_state_to_address(reg);
        }
    } else if (strcmp(postfix->data, "postfix ->") == 0) {
        expr = expr->info.pointer;
        if (expr->type == NAME) {
            expr = symbol_table_fetch_type_instance(expr);
        }
        InfoNodeRecord* record = expr->info.record;
        int i, offset = -1;
        for (i = 0; i < record->size; i++) {
            if (strcmp(record->field[i]->identifier, postfix->children[1]->data) == 0) {
                offset = record->offset[i];
                break;
            }
        }
        assert(offset != -1);
        assert(rs.state[reg] == 1);
        ir_push_back(&ir, new_quadruple_lw(reg, reg));
        ir_push_back(&ir, new_quadruple_arithmetic_im("add", reg, reg, offset));
        if (p->info->type == ARRAY) {
            set_register_state_to_value(reg);
        } else {
            set_register_state_to_address(reg);
        }
    } else {
        int delta = strcmp(postfix->data, "postfix ++") == 0 ? 1 : -1;
        assert(get_register_state(reg) == 1);
        int t0 = new_register(), t1 = new_register();
        ir_push_back(&ir, new_quadruple_move(t0, reg));
        ir_push_back(&ir, new_quadruple_lw(reg, reg));
        set_register_state_to_value(reg);
        ir_push_back(&ir, new_quadruple_arithmetic_im("add", t1, reg, delta));
        ir_push_back(&ir, new_quadruple_sw(t1, t0));
    }
}

void translate_primary_expression(TreeNode* p, int reg) {
    if (p->type == PRIMARY_EXPRESSION) {
        translate_expression(p->children[0], reg);
        return;
    }
    if (p->type == STRING_CONSTANT) {
        int n = strlen(p->data);
        char* s = (char*)malloc(sizeof(char) * (n - 1));
        memcpy(s, p->data + 1, sizeof(char) * (n - 2));
        s[n - 2] = '\0';
        int old_function_begin_sp = function_begin_sp;
        function_begin_sp = -1;
        int tmp = new_register();
        ir_push_back(&gir, new_quadruple_string_const(tmp, s));
        function_begin_sp = old_function_begin_sp;
        ir_push_back(&ir, new_quadruple_move(reg, tmp));
        set_register_state_to_value(reg);
    } else if (p->type == INTEGER_CONSTANT || p->type == CHARACTER_CONSTANT) {
        ir_push_back(&ir, new_quadruple_li(reg, p->info->val));
        set_register_state_to_value(reg);
    } else if (p->type == IDENTIFIER) {
        if (p->info->isconst) {
#ifdef ASSERT_ON
            assert(0);
            ir_push_back(&ir, new_quadruple_li(reg, p->info->val));
#endif
        } else if (p->info->type != FUNCTION) {
            int tmp = vs_fetch_register(p->info->identifier);
            if (get_register_state(tmp) == REGISTER_STATE_ADDRESS) {
                if (p->info->type == ARRAY) {
                    set_register_state_to_value(reg);
                } else {
                    set_register_state_to_address(reg);
                }
                ir_push_back(&ir, new_quadruple_move(reg, tmp));
            } else {        //array pointer
                set_register_state_to_value(reg);
                ir_push_back(&ir, new_quadruple_lw(reg, tmp));
            }
        }
    }
}
