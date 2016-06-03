#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "utility.h"
#include "def.h"
#include "semantics.h"
#include "ast.h"
#include "analyzer.tab.h"

int level, loop_count, empty_count;
SymbolTable env[MAX_LEVEL];
InfoNode* top_function; //先当没有函数嵌套处理

//auxiliary function {{{

int isint(EnumInfoNode x) {
    return x == INT || x == CHAR;
}

int isnumber(EnumInfoNode x) {
	return x == DOUBLE || x == INT || x == CHAR;
}

int isdouble(EnumInfoNode x) {
	return x == DOUBLE;
}

int ispointer(EnumInfoNode x) {
    return x == POINTER || x == ARRAY;
}

int isscalar(EnumInfoNode x) {
    return isint(x) || ispointer(x);
}

int string_to_int(char* s) {
    int ret = 0;
    int n = strlen(s), i;
    if (n > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        for (i = 2; i < n; i++) {
            ret = ret * 16;
            if ('a' <= s[i] && s[i] <= 'f') {
                ret += s[i] - 'a' + 10;
            } else if ('A' <= s[i] && s[i] <= 'F') {
                ret += s[i] - 'A' + 10;
            } else {
                ret += s[i] - '0';
            }
        }
    } else {
        int base = s[0] == '0' ? 8 : 10;
        for (i = 0; i < n; i++) {
            ret = ret * base + s[i] - '0';
        }
    }
    return ret;
}

double string_to_double(char* s){
	double ret;
	sscanf(s, "%lf", &ret);
	return ret;
}

char* int_to_name(int x) {
    assert(x >= 1);
    int n = 0, t;
    for (t = x; t > 0; n++, t /= 10);
    char* s = (char*)malloc(sizeof(char) * (n + 2));
    s[0] = '+';
    s[n + 1] = '\0';
    for (t = x; t > 0; s[n--] = t % 10, t /= 10);
    return s;
}

//}}}

//malloc simplification functions {{{

int* new_int_n(int n) {
    return (int*)malloc(sizeof(int) * n);
}

InfoNode* new_info_node() {
    InfoNode* ret = (InfoNode*)malloc(sizeof(InfoNode));
    ret->isinstance = 0;
    ret->isconst = 0;
    ret->isleftvalue = 0;
    ret->identifier = NULL;
    ret->width = 4;
    return ret;
}

InfoNode** new_info_node_n(int n) {
    return n <= 0 ? NULL : (InfoNode**)malloc(sizeof(InfoNode*) * n);
}

InfoNodeFunction* new_info_node_function() {
    return (InfoNodeFunction*)malloc(sizeof(InfoNodeFunction));
}

InfoNodeRecord* new_info_node_record() {
    return (InfoNodeRecord*)malloc(sizeof(InfoNodeRecord));
}

InfoNodeArray* new_info_node_array() {
    return (InfoNodeArray*)malloc(sizeof(InfoNodeArray));
}

char* copy_string(char* s) {
//  if (s == NULL) {
//      fprintf(stderr, "copy_string empty address\n");
//  }
    return s == NULL ? NULL : strdup(s);
}

InfoNodeArray* copy_info_node_array(InfoNodeArray* p) {
    InfoNodeArray* ret = new_info_node_array();
    ret->size = p->size;
    ret->ptr = copy_info_node(p->ptr);
    ret->width = p->width;
    return ret;
}

InfoNodeRecord* copy_info_node_record(InfoNodeRecord* p) {
    InfoNodeRecord* ret = new_info_node_record();
    ret->name = copy_string(p->name);
    ret->size = p->size;
    ret->field = new_info_node_n(p->size);
    ret->offset = new_int_n(p->size + 1);
    int i;
    for (i = 0; i < ret->size; i++) {
        ret->field[i] = copy_info_node(p->field[i]);
        ret->offset[i] = p->offset[i];
    }
    ret->offset[ret->size] = p->offset[p->size];
    ret->width = p->width;
    return ret;
}

InfoNodeFunction* copy_info_node_function(InfoNodeFunction* p) {
    InfoNodeFunction* ret = new_info_node_function();
    ret->size = p->size;
    ret->pars = new_info_node_n(p->size == -1 ? 1 : p->size);
    ret->offset = new_int_n(p->size == -1 ? 1 : p->size + 1);
    ret->offset[0] = 0;
    ret->width = p->width;
    ret->ret = copy_info_node(p->ret);
    int i;
    for (i = 0; i < ret->size; i++) {
        ret->pars[i] = copy_info_node(p->pars[i]);
        ret->offset[i] = p->offset[i];
    }
    if (ret->size != -1) {
        ret->offset[ret->size] = p->offset[p->size];
    }
    return ret;
}

InfoNode* copy_info_node(InfoNode* p) {
    InfoNode* ret = new_info_node();
    ret->isinstance = p->isinstance;
    ret->isconst = p->isconst;
    ret->type = p->type;
    ret->val = p->val;
		ret->real = p->real;
    ret->isleftvalue = p->isleftvalue;
    ret->width = p->width;
    if (p->type == ARRAY) {
        ret->info.array = copy_info_node_array(p->info.array);
        ret->identifier = ret->info.array->ptr->identifier;
    } else if (p->type == POINTER) {
        ret->info.pointer = copy_info_node(p->info.pointer);
        ret->identifier = ret->info.pointer->identifier;
    } else if (p->type == STRUCT || p->type == UNION) {
        ret->info.record = copy_info_node_record(p->info.record);
        ret->identifier = copy_string(p->identifier);
    } else if (p->type == FUNCTION) {
        ret->info.function = copy_info_node_function(p->info.function);
        ret->identifier = copy_string(p->identifier);
    } else if (ret->type == NAME) {
        ret->info.record = new_info_node_record();
        ret->info.record->name = copy_string(p->info.record->name);
        ret->identifier = copy_string(p->identifier);
    } else {
        ret->identifier = copy_string(p->identifier);
    }
    return ret;
}

//}}}

// symbol table functions {{{

void symbol_table_initialize() {
    level = 0;
    int i;
    for (i = 0; i < MAX_LEVEL; i++) {
        env[i].size = 0;
        env[i].capacity = 1;
        env[i].array = new_info_node_n(1);
    }
}

void symbol_table_next_level() {
    //进入下一层的时候允许已经有entry存在，但是在退出的时候默认清空
    level++;
}

void symbol_table_prev_level() { //to_review
    env[level--].size = 0; //这样做是为了处理pars和compound-statement在同一层的情况
    //直接这样做会有内存泄露，先不管这么多了
}

void symbol_table_enlarge(SymbolTable* p) {
    assert(p->capacity != 0);
    if (p->size == p->capacity) {
        p->capacity <<= 1;
        InfoNode** array = new_info_node_n(p->capacity);
        int i;
        for (i = 0; i < p->size; i++) {
            array[i] = p->array[i];
        }
        free(p->array);
        p->array = array;
    }
}

void debug_print_symbol_table() {
    puts("\033[31;1m************************symbol table************************\033[0m");
    int i, j;
    for (i = 0; i <= level; i++) {
        printf("\033[32m========================level %d========================\033[0m\n", i);
        for (j = 0; j < env[i].size; j++) {
            InfoNode* p = env[i].array[j];
            printf("|\t");
            printf("%s", p->isleftvalue || p->type == FUNCTION ? p->identifier : 
                (p->type == STRUCT || p->type == UNION) ? p->info.record->name :
                p->identifier);
            printf("\t\t(isleftvalue = %d)", p->isleftvalue);
            puts("");
        }
    }
    puts("");
}

void symbol_table_insert_0(InfoNode* p) { //很丑地处理了struct命名空间的问题
    symbol_table_enlarge(&env[0]);
    env[0].array[env[0].size++] = copy_info_node(p);
#ifdef PRINT_SYMBOL_TABLE
    printf("add -> %s, isleftvalue = %d\n", 
        p->isleftvalue || p->type == FUNCTION ? p->identifier : 
        (p->type == STRUCT || p->type == UNION) ? p->info.record->name :
        p->identifier, p->isleftvalue);
    debug_print_symbol_table();
#endif
}

void symbol_table_insert(InfoNode* p) {
    symbol_table_enlarge(&env[level]);
    env[level].array[env[level].size++] = copy_info_node(p);
#ifdef PRINT_SYMBOL_TABLE
    printf("add -> %s, isleftvalue = %d\n", 
        p->isleftvalue || p->type == FUNCTION ? p->identifier : 
        (p->type == STRUCT || p->type == UNION) ? p->info.record->name :
        p->identifier, p->isleftvalue);
    debug_print_symbol_table();
#endif
}

int symbol_table_query_top_level_variable(char* s) {
    int i;
    for (i = 0; i < env[level].size; i++) {
        InfoNode* tmp = env[level].array[i];
        if (tmp->isinstance && strcmp(tmp->identifier, s) == 0) {
            return 1;
        }
    }
    return 0;
}

int symbol_table_query_type(InfoNode* p) {
    assert(p->type != ARRAY);
    assert(p->type != FUNCTION);
    if (p->type == INT || p->type == CHAR || p->type == VOID || p->type == DOUBLE) {
        return 1;
    }
    if (p->type == POINTER) {
        return 1;
    }
    int i, j, type = p->type, offset = 0;
    char* s = p->info.record->name;
    if (p->type == NAME) {
        type = s[0] == 's' ? STRUCT : UNION;
        offset = 1;
    }
    for (i = 0; i <= level; i++) {
        for (j = 0; j < env[i].size; j++) {
            InfoNode* tmp = env[i].array[j];
            if (tmp->isinstance) {
                continue;
            }
            if (tmp->type == type && strcmp(tmp->info.record->name, s + offset) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int symbol_table_query_function(char* s) {
    int j;
    for (j = 0; j < env[0].size; j++) {
        InfoNode* tmp = env[0].array[j];
        if (tmp->type == FUNCTION && strcmp(tmp->identifier, s) == 0) {
            return 1;
        }
    }
    return 0;
}

InfoNode* symbol_table_fetch_function(char* s) {
    int j;
    for (j = 0; j < env[0].size; j++) {
        InfoNode* tmp = env[0].array[j];
        if (tmp->type == FUNCTION && strcmp(tmp->identifier, s) == 0) {
            return tmp;
        }
    }
    return NULL;
}

InfoNode* symbol_table_fetch_identifier(char* s) {
    int i, j;
    for (i = level; i >= 0; i--) {
        for (j = 0; j < env[i].size; j++) {
            InfoNode* tmp = env[i].array[j];
            if ((tmp->type == FUNCTION || tmp->isinstance) && strcmp(tmp->identifier, s) == 0) {
                return copy_info_node(tmp);
            }
        }
    }
    return NULL;
}

InfoNode* symbol_table_fetch_type_instance(InfoNode* p) {
    assert(p->type != ARRAY);
    assert(p->type != POINTER);
    assert(p->type != FUNCTION);
    if (p->type == INT || p->type == CHAR || p->type == VOID || p->type == DOUBLE) {
        return copy_info_node(p);
    }
    int i, j, type = p->type, offset = 0;
    char *s = p->info.record->name;
    if (p->type == NAME) {
        type = s[0] == 's' ? STRUCT : UNION;
        offset = 1;
    }
    for (i = level; i >= 0; i--) {
        for (j = 0; j < env[i].size; j++) {
            InfoNode* tmp = env[i].array[j];
            if (tmp->isinstance) {
                continue;
            }
            if (tmp->type == type && strcmp(tmp->info.record->name, s + offset) == 0) {
                return copy_info_node(tmp);
            }
        }
    }
    return NULL;
}

//}}}

void semantics_check(TreeNode* p) { /*{{{*/
	if (!p)
	{
		printf("sytax error\n");
		return;
	}
    switch (p->type) {
        case PROGRAM: semantics_check_program(p); break;
        case DECLARATION: semantics_check_declaration(p); break;
        case FUNCTION_DEFINITION: semantics_check_function_definition(p); break;
        case EXPRESSION_STATEMENT: break; 
        case COMPOUND_STATEMENT: semantics_check_compound_statement(p); break;
        case SELECTION_STATEMENT: semantics_check_selection_statement(p); break;
        case ITERATION_STATEMENT: semantics_check_iteration_statement(p); break;
        case JUMP_STATEMENT: semantics_check_jump_statement(p); break;
        case EXPRESSION: p->info = copy_info_node(semantics_check_expression(p)); break;
				default: printf("sytax error\n");
    }
} //}}}

void semantics_check_program(TreeNode* p) { /* {{{ */
    int i;
    for (i = 0; i < p->size; i++) {
        semantics_check(p->children[i]);
    }
} //}}}

void semantics_check_declaration(TreeNode* p) { /* {{{ */
    InfoNode* base = semantics_check_type_specifier(p->children[0]);
    if (base->type == STRUCT || base->type == UNION) {
        assert(base->info.record->size > 0);
        base->isleftvalue = 0;
        symbol_table_insert_0(base);
    } else if (base->type == NAME) {
        if (symbol_table_query_type(base)) {
            base = symbol_table_fetch_type_instance(base);
            //fprintf(stderr, "width = %d\n", base->width);
        }
    } else if (!symbol_table_query_type(base)) {
        report_error("type error, such type undefined");
    }
    if (p->size == 1) {
        return;
    }
    if (base->type == VOID) {
        report_error("varaible type can't be 'void'");
    }
    int i;
    for (i = 0; i < p->children[1]->size; i++) {
        semantics_check_init_declarator(p->children[1]->children[i], base);
    }
} //}}}

InfoNode* semantics_check_type_specifier(TreeNode* p) { /* {{{ */
    InfoNode* ret = new_info_node();
    if (p->type == KEYWORDS) { //'void' | 'char' | 'int' | 'double'
        if (strcmp(p->data, "void") == 0) {
            ret->type = VOID;
            ret->width = WIDTH_VOID;
				}
				else if (strcmp(p->data, "char") == 0) {
					ret->type = CHAR;
					ret->width = WIDTH_CHAR;
				}
				else if (strcmp(p->data, "double")==0)
				{
					ret->type = DOUBLE;
					ret->width = WIDTH_DOUBLE;
        } else {
            ret->type = INT;
        }
        return ret;
    }
    ret->type = p->children[0]->data[0] == 's' ? STRUCT : UNION;
    if (p->size == 2) {
        if (p->children[1]->type == IDENTIFIER) {
            ret->type = NAME;
            int length = strlen(p->children[1]->data);
            ret->info.record = new_info_node_record();
            ret->info.record->name = (char*)malloc(length + 2);
            if (p->children[0]->data[0] == 's') {
                ret->info.record->name[0] = 's';
            } else {
                ret->info.record->name[0] = 'u';
            }
            memcpy(ret->info.record->name + 1, p->children[1]->data, sizeof(char) * length);
            ret->info.record->name[length + 1] = 0;
        } else {
            symbol_table_next_level();
            ret->info.record = semantics_check_type_specifiers(p->children[1], ret->type == STRUCT);
            symbol_table_prev_level();
            empty_count++;
            ret->info.record->name = int_to_name(empty_count);
            ret->width = ret->info.record->width;
        }
    } else {
        assert(p->size == 3);
        symbol_table_next_level();
        ret->info.record = semantics_check_type_specifiers(p->children[2], ret->type == STRUCT);
        symbol_table_prev_level();
        ret->info.record->name = p->children[1]->data;
        ret->width = ret->info.record->width;
    }
    return ret;
} //}}}

InfoNodeRecord* semantics_check_type_specifiers(TreeNode* p, int isstruct) { /* {{{ */
    assert(p->type == TYPE_SPECIFIERS);
    //struct内部的 type-specifier declarators
    InfoNodeRecord* ret = new_info_node_record();
    ret->size = 0;
    int i, j, k = 0;
    assert((p->size & 1) == 0);
    for (i = 1; i < p->size; i += 2) { //type-specifier & declarators成对出现
        ret->size += p->children[i]->size;
    }
    ret->field = new_info_node_n(ret->size);
    ret->offset = new_int_n(ret->size);
    ret->offset[0] = 0;     //at least one element
    int current = 0;
    for (i = 1; i < p->size; i += 2) {
        InfoNode* ptr = semantics_check_type_specifier(p->children[i - 1]);
        if ((ptr->type == STRUCT || ptr->type == UNION) && ptr->info.record->size > 0) {
            symbol_table_insert_0(ptr);
        }
        for (j = 0; j < p->children[i]->size; j++) {
            InfoNode* tmp = semantics_check_declarator(p->children[i]->children[j], ptr);
            if (symbol_table_query_top_level_variable(tmp->identifier)) {
                report_error("same names in struct/union");
            }
            symbol_table_insert(tmp);
            ret->field[k] = tmp;
            if (isstruct) {
                if (tmp->type == ARRAY) {
                    current += tmp->info.array->width;
                } else {
                    current += tmp->width;
                }
                current += (4 - (current & 3)) & 3; //align
                ret->offset[k + 1] = current;
            } else {
                int t;
                if (tmp->type == ARRAY) {
                    t = tmp->info.array->width;
                } else {
                    t = tmp->width;
                }
                t += (4 - (t & 3)) & 3;
                if (t > current) {
                    current = t;
                }
                ret->offset[k + 1] = 0;
            }
            k++;
        }
    }
    if (isstruct) {
        ret->width = ret->offset[ret->size];
    } else {
        ret->width = current;
    }
    return ret;
} //}}}

InfoNode* semantics_check_declarator(TreeNode* p, InfoNode* ptr) { /* {{{ */
    assert(p->type == DECLARATOR);
    //temporarily ignore case 1 & 2
    ptr = semantics_check_plain_declarator(p->children[0], ptr);
    if (ptr->type == NAME) {
        printf("%s\n", ptr->identifier);
        report_error("no such type, NAME case");
    }
    if (p->size > 1) {
        ptr = semantics_check_plain_declarators(p->children[1], ptr);
    }
    return ptr;
} // }}}

InfoNode* semantics_check_plain_declarator(TreeNode* p, InfoNode* ptr) { /* {{{ */ //***f
    if (p->type == IDENTIFIER) {
        if (symbol_table_query_type(ptr)) {
            ptr = symbol_table_fetch_type_instance(ptr);
        } else {
            ptr = copy_info_node(ptr);
        }
        ptr->identifier = strdup(p->data);
        ptr->isinstance = 1;
        ptr->isleftvalue = 1;
        return ptr;
    }
    InfoNode* ret = new_info_node();
    ret->isinstance = 1;
    ret->isleftvalue = 1;
    ret->type = POINTER;
    ret->info.pointer = semantics_check_plain_declarator(p->children[0], ptr);
    ret->identifier = ret->info.pointer->identifier;
    ret->width = 4;
    return ret;
} //}}}

InfoNode* semantics_check_plain_declarators(TreeNode* p, InfoNode* ptr) { /* {{{ */ //ok, f[][][]
    int i;
    int width = ptr->width;
    for (i = p->size - 1; i >= 0; i--) {
        InfoNode* ret = new_info_node();
        ret->isinstance = 1;
        ret->type = ARRAY;
        ret->isleftvalue = 0;
        ret->identifier = ptr->identifier;
        ret->info.array = new_info_node_array();
        InfoNode* tmp = semantics_check_constant_expression(p->children[i]);
        if (!tmp->isconst) {
            report_error("array definition's subscript is not const");
        }
        ret->info.array->size = tmp->val;
        if (ret->info.array->size < 0) {
            report_error("wrong array size");
        }
        ret->info.array->ptr = ptr;
        ret->info.array->width = width * ret->info.array->size;
        ret->width = 4;
        width = ret->info.array->width;
        ptr = ret;
    }
    ptr->info.array->width += (4 - (ptr->info.array->width & 3)) & 3;
    return ptr;
} //}}}

void semantics_check_init_declarator(TreeNode* p, InfoNode* ptr) { /* {{{ */ //to-review
    ptr = semantics_check_declarator(p->children[0], ptr);
    if (ptr->width != 4) {
        ptr->width += (4 - (ptr->width & 3)) & 3;
    }
    if (symbol_table_query_top_level_variable(ptr->identifier)) {
        puts(ptr->identifier);
        report_error("variable defined multiple times");
    }
    symbol_table_insert(ptr);
    p->info = copy_info_node(ptr);
    //先暂时不管初始化和translation相关的问题，只做语义检查，只把ptr放到symbol table里去
    if (p->size > 1) {
        semantics_check_initializier(p->children[1], ptr);
    }
} //}}}

void semantics_check_initializier(TreeNode* p, InfoNode* ptr) { /* {{{ */ //TO BE CONTINUED
    if (p->type != INITIALIZER) {
        semantics_check_assignment_expression(p);
        return;
    }
    //鉴于数据没有这种情况，先暂时空缺一下，主要是我觉得数组初始化很难处理
} //}}}

void semantics_check_function_definition(TreeNode* p) { /* {{{ */ //ok
    assert(p->type == FUNCTION_DEFINITION);
    InfoNode* a = semantics_check_function_definition_1(p);
    InfoNodeFunction* b;
    if (p->size == 4) {
        b = semantics_check_parameters(p->children[2]);
    } else {
        b = new_info_node_function();
        b->size = 0;
        b->offset = new_int_n(1);
        b->offset[0] = 0;
        b->width = 0;
    }
    InfoNode* c = new_info_node();
    c->type = FUNCTION;
    c->isleftvalue = 0;
    c->identifier = a->identifier;
    c->info.function = b;
    c->info.function->ret = a;

    top_function = c;
    if (!symbol_table_query_type(c->info.function->ret)) {
        report_error("functoin return type undefined");
    }
    if (symbol_table_query_function(c->identifier)) {
        report_error("function previously defined");
    }
    if (level != 0) {
        report_error("function recursively defined");
    }
    symbol_table_insert(c);

    level++; //参数和compound-statement处于同一个namespace
    int i;
    for (i = 0; i < c->info.function->size; i++) {
        if (symbol_table_query_top_level_variable(c->info.function->pars[i]->identifier) == 1) {
            report_error("variable previously defined");
        }
        symbol_table_insert(c->info.function->pars[i]);
    }
    level--;
    semantics_check(p->children[p->size - 1]);

    p->info = copy_info_node(top_function);
    top_function = NULL;
} //}}}

InfoNode* semantics_check_function_definition_1(TreeNode* p) { /* {{{ */ //ok
    InfoNode* ptr = semantics_check_type_specifier(p->children[0]);
    ptr = semantics_check_plain_declarator(p->children[1], ptr);
    //函数定义是否存在之类的检查，均在最高层进行
    return ptr;
} //}}}

InfoNodeFunction* semantics_check_parameters(TreeNode* p) { /* {{{ */ //ok
    InfoNodeFunction* ret = new_info_node_function();
    ret->size = p->size;
    ret->offset = new_int_n(ret->size + 1);
    ret->offset[0] = 0;
    ret->pars = new_info_node_n(p->size);
    int i;
    int current = 0;
    for (i = 0; i < p->size; i++) {
        ret->pars[i] = semantics_check_plain_declaration(p->children[i]);
        current += ret->pars[i]->width;
        current += (4 - (current & 3)) & 3;
        ret->offset[i + 1] = current;
    }
    ret->width = ret->offset[ret->size];
    return ret;
} //}}}

InfoNode* semantics_check_plain_declaration(TreeNode* p) { /* {{{ */ //ok
    assert(p->type == PLAIN_DECLARATION);
    InfoNode* ret = semantics_check_type_specifier(p->children[0]);
    ret = semantics_check_declarator(p->children[1], ret);
    return ret;
} //}}}

void semantics_check_compound_statement(TreeNode* p) { /* {{{ */ //ok
    symbol_table_next_level();
    int i, j;
    for (i = 0; i < p->size; i++) {
        for (j = 0; j < p->children[i]->size; j++) {
            semantics_check(p->children[i]->children[j]); //declaration* statements*
        }
    }
    symbol_table_prev_level();
}//}}}

void semantics_check_selection_statement(TreeNode* p) { /* {{{ */ //ok
    InfoNode* tmp = semantics_check_expression(p->children[0]);
    if (!isscalar(tmp->type)) {
        report_error("if expression type error, not a scalar");
    }
    semantics_check(p->children[1]);
    if (p->size == 3) {
        semantics_check(p->children[2]);
    }
} //}}}

void semantics_check_iteration_statement(TreeNode* p) { /*{{{*/ //ok
    int i;
    InfoNode *tmp;
    if (strcmp(p->data, "while()") == 0) {
        tmp = semantics_check_expression(p->children[0]);
        if (!isscalar(tmp->type)) {
            report_error("if expression type error, not a scalar");
        }
    } else {
        int marker = -1;
        if (strcmp(p->data, "for(;*;)") == 0) {
            marker = 0;
        } else if (strcmp(p->data, "for(;*;*)") == 0) {
            marker = 0;
        } else if (strcmp(p->data, "for(*;*;)") == 0) {
            marker = 1;
        } else if (strcmp(p->data, "for(*;*;*)") == 0) {
            marker = 1;
        }
        for (i = 0; i < p->size - 1; i++) {
            tmp = semantics_check_expression(p->children[i]);
            if (i == marker && !isscalar(tmp->type)) {
                report_error("if expression type error, not a scalar");
            }
        }
    }
    loop_count++;
    semantics_check(p->children[p->size - 1]);
    loop_count--;
} //}}}

void semantics_check_jump_statement(TreeNode* p) { /* {{{ */
    if (strcmp(p->children[0]->data, "return") == 0) {
        if (top_function == NULL) {
            report_error("'return' is not in a function");
        }
        if (p->size == 1) {
            if (top_function->info.function->ret->type != VOID) {
                report_error("return type error, mismatch");
            }
        } else {
            InfoNode* tmp = semantics_check_expression(p->children[1]);
            if (!semantics_check_same_type(top_function->info.function->ret, tmp)) {
                report_error("return type error, mismatch");
            }
        }
        p->info = copy_info_node(top_function);
    } else {
        if (loop_count == 0) {
            report_error("jump statement not in a loop!!!");
        }
    }
} //}}}

int semantics_check_same_type(InfoNode* x, InfoNode* y) { /*{{{*/ //ok
    //只是检查类型，不需要考虑isleftvalue的问题
    //注意POINTER和ARRAY的本质都是一样的
    if (isscalar(x->type) && isscalar(y->type)) {
        return 1;
    }
		if (isnumber(x->type) && isnumber(y->type)) {
			return 1;
		}
    if (x->type != y->type) {
        return 0;
    }
    if (x->type == STRUCT || x->type == UNION) {
        return strcmp(x->info.record->name, y->info.record->name) == 0;
    }
    assert(0); //应该是不能到这里的
} //}}}

InfoNode* semantics_check_expression(TreeNode* p) { /* {{{ */ //ok
    InfoNode* ret;
    if (p->size == 1) {
        ret = semantics_check_assignment_expression(p->children[0]);
    } else {
        semantics_check_expression(p->children[0]);
        ret = semantics_check_assignment_expression(p->children[1]);
    }
    p->info = copy_info_node(ret);
    return ret;
} //}}}

InfoNode* semantics_check_assignment_expression(TreeNode* p) { /*{{{*/ //ok
    if (p->type != ASSIGN_EXPRESSION) {
        return semantics_check_logical_or_expression(p);
    }
    InfoNode* x = semantics_check_unary_expression(p->children[0]);
    if (!x->isleftvalue) {
        report_error("left value is const");
    }
    InfoNode* y = semantics_check_assignment_expression(p->children[2]);
    if (strcmp(p->children[1]->data, "=") == 0) {
        if (!semantics_check_same_type(x, y)) {
            report_error("assignment error, left&right value don't have the same type");
        }
    } else {
			if (!isnumber(x->type) || !isnumber(y->type)) {
            report_error("assignment error, they aren't number");
        }
    }
    p->info = copy_info_node(x);
    return x;
} //}}}
 
InfoNode* semantics_check_constant_expression(TreeNode* p) { /* {{{ */ //ok
    return semantics_check_logical_or_expression(p);
} //}}}

InfoNode* semantics_check_logical_or_expression(TreeNode* p) { /*{{{*/ //ok
    if (p->type != LOGICAL_OR_EXPRESSION) { //用!=是因为还可能继续递归下去
        return semantics_check_logical_and_expression(p);
    }
    InfoNode* x = semantics_check_logical_or_expression(p->children[0]);
    InfoNode* y = semantics_check_logical_and_expression(p->children[1]);
		if (!isscalar(x->type) || !isscalar(y->type) || !isnumber(x->type) || !isnumber(y->type)) {
			report_error("|| opeator type error");
		}
		x->isconst &= y->isconst;

		if (x->isconst) {
			if (x->type == DOUBLE)
			{
				if (y->type == DOUBLE)
				{
					x->val = x->real || y->real;
				}
				else
				{
					x->val = x->real || y->val;
				}
			}
			else
			{
				if (y->type == DOUBLE)
				{
					x->val = x->val || y->real;
				}
				else
				{
					x->val = x->val || y->val;
				}
			}
		}
		x->type = INT;
		x->isleftvalue = 0;
    p->info = copy_info_node(x);
    return x;
} //}}}

InfoNode* semantics_check_logical_and_expression(TreeNode* p) { /*{{{*/ //ok
    if (p->type != LOGICAL_AND_EXPRESSION) {
        return semantics_check_inclusive_or_expression(p);
    }
    InfoNode* x = semantics_check_logical_and_expression(p->children[0]);
    InfoNode* y = semantics_check_inclusive_or_expression(p->children[1]);
		if (!isscalar(x->type) || !isscalar(y->type) || !isnumber(x->type) || !isnumber(y->type)) {
        report_error("&& opeator type error");
    }
    x->isconst &= y->isconst;
    
    if (x->isconst) {
			if (x->type == DOUBLE)
			{
				if (y->type == DOUBLE)
				{
					x->val = x->real && y->real;
				}
				else
				{
					x->val = x->real && y->val;
				}
			}
			else
			{
				if (y->type == DOUBLE)
				{
					x->val = x->val && y->real;
				}
				else
				{
					x->val = x->val && y->val;
				}
			}
    }
		x->type = INT;
    x->isleftvalue = 0;
    p->info = copy_info_node(x);
    return x;
} //}}}

InfoNode* semantics_check_inclusive_or_expression(TreeNode* p) { /*{{{*/ //ok
    if (p->type != INCLUSIVE_OR_EXPRESSION) {
        return semantics_check_exclusive_or_expression(p);
    }
    InfoNode* x = semantics_check_inclusive_or_expression(p->children[0]);
    InfoNode* y = semantics_check_exclusive_or_expression(p->children[1]);
    if (!isint(x->type) || !isint(y->type)) {
        report_error("| opeator type error");
    }
    x->isconst &= y->isconst;
    if (x->type == INT || y->type == INT) {
        x->type = INT;
    }
    if (x->isconst) {
        x->val |= y->val;
    }
    x->isleftvalue = 0;
    p->info = copy_info_node(x);
    return x;
} //}}}

InfoNode* semantics_check_exclusive_or_expression(TreeNode* p) { /*{{{*/ //ok
    if (p->type != EXCLUSIVE_OR_EXPRESSION) {
        return semantics_check_and_expression(p);
    }
    InfoNode* x = semantics_check_exclusive_or_expression(p->children[0]);
    InfoNode* y = semantics_check_and_expression(p->children[1]);
    if (!isint(x->type) || !isint(y->type)) {
        report_error("^ opeator type error");
    }
    x->isconst &= y->isconst;
    if (x->type == INT || y->type == INT) {
        x->type = INT;
    }
    if (x->isconst) {
        x->val ^= y->val;
    }
    x->isleftvalue = 0;
    p->info = copy_info_node(x);
    return x;
} //}}}

InfoNode* semantics_check_and_expression(TreeNode* p) { /* {{{ */ //ok
    if (p->type != AND_EXPRESSION) {
        return semantics_check_equality_expression(p);
    }
    InfoNode* x = semantics_check_and_expression(p->children[0]);
    InfoNode* y = semantics_check_equality_expression(p->children[1]);
    if (!isint(x->type) || !isint(y->type)) {
        report_error("& opeator type error");
    }
    x->isconst &= y->isconst;
    if (x->type == INT || y->type == INT) {
        x->type = INT;
    }
    if (x->isconst) {
        x->val &= y->val;
    }
    x->isleftvalue = 0;
    p->info = copy_info_node(x);
    return x;
} //}}}

InfoNode* semantics_check_equality_expression(TreeNode* p) { /* {{{ */ //ok
    if (p->type != EQUALITY_EXPRESSION) {
        return semantics_check_relational_expression(p);
    }
    InfoNode* x = semantics_check_equality_expression(p->children[0]);
    InfoNode* y = semantics_check_relational_expression(p->children[2]);
    if (!isscalar(x->type) || !isscalar(y->type)) {
        report_error("==/!= opeator type error");
    }
    x->isconst &= y->isconst;
    
    if (x->isconst) {
        if (p->children[1]->data[0] == '=') {   //==
					if (x->type == DOUBLE)
					{
						if (y->type == DOUBLE)
						{
							x->val = x->real == y->real;
						}
						else
						{
							x->val = x->real == y->val;
						}
					}
					else
					{
						if (y->type == DOUBLE)
						{
							x->val = x->val == y->real;
						}
						else
						{
							x->val = x->val == y->val;
						}
					}
        } else {                                //!=
					if (x->type == DOUBLE)
					{
						if (y->type == DOUBLE)
						{
							x->val = x->real != y->real;
						}
						else
						{
							x->val = x->real != y->val;
						}
					}
					else
					{
						if (y->type == DOUBLE)
						{
							x->val = x->val != y->real;
						}
						else
						{
							x->val = x->val != y->val;
						}
					}
        }
    }
    x->isleftvalue = 0;
		x->type = INT;
    p->info = copy_info_node(x);
    return x;
} //}}}

InfoNode* semantics_check_relational_expression(TreeNode* p) { /*{{{*/  //ok
    if (p->type != RELATIONAL_EXPERSSION) {
        return semantics_check_shift_expression(p);
    }
    InfoNode* x = semantics_check_relational_expression(p->children[0]);
    InfoNode* y = semantics_check_shift_expression(p->children[2]);
    if (!isscalar(x->type) || !isscalar(y->type)) {
        report_error("</>/<=/>= opeator type error");
    }
    x->isconst &= y->isconst;
    if (x->isconst) {
        if (strlen(p->children[1]->data) == 2) {
            if (p->children[1]->data[0] == '>') {   //>=
							if (x->type == DOUBLE)
							{
								if (y->type == DOUBLE)
								{
									x->val = x->real >= y->real;
								}
								else
								{
									x->val = x->real >= y->val;
								}
							}
							else
							{
								if (y->type == DOUBLE)
								{
									x->val = x->val >= y->real;
								}
								else
								{
									x->val = x->val >= y->val;
								}
							}
            } else {                                //<=
							if (x->type == DOUBLE)
							{
								if (y->type == DOUBLE)
								{
									x->val = x->real <= y->real;
								}
								else
								{
									x->val = x->real <= y->val;
								}
							}
							else
							{
								if (y->type == DOUBLE)
								{
									x->val = x->val <= y->real;
								}
								else
								{
									x->val = x->val <= y->val;
								}
							}
            }
        } else {
            if (p->children[1]->data[0] == '>') {   //>
							if (x->type == DOUBLE)
							{
								if (y->type == DOUBLE)
								{
									x->val = x->real > y->real;
								}
								else
								{
									x->val = x->real > y->val;
								}
							}
							else
							{
								if (y->type == DOUBLE)
								{
									x->val = x->val > y->real;
								}
								else
								{
									x->val = x->val > y->val;
								}
							}
            } else {                                //<
							if (x->type == DOUBLE)
							{
								if (y->type == DOUBLE)
								{
									x->val = x->real < y->real;
								}
								else
								{
									x->val = x->real < y->val;
								}
							}
							else
							{
								if (y->type == DOUBLE)
								{
									x->val = x->val < y->real;
								}
								else
								{
									x->val = x->val < y->val;
								}
							}
            }
        }
    }
    x->isleftvalue = 0;
		x->type = INT;
    p->info = copy_info_node(x);
    return x;
} //}}}

InfoNode* semantics_check_shift_expression(TreeNode* p) { /* {{{ */ //ok
    if (p->type != SHIFT_EXPRESSION) {
        return semantics_check_additive_expression(p);
    }
    InfoNode* x = semantics_check_shift_expression(p->children[0]);
    InfoNode* y = semantics_check_additive_expression(p->children[2]);
    if (!isint(x->type) || !isint(y->type)) {
        report_error(">>/<< opeator type error");
    }
    x->isconst &= y->isconst;
    if (x->type == INT || y->type == INT) {
        x->type = INT;
    }
    if (x->isconst) {
        if (p->children[1]->data[0] == '>') {
            x->val >>= y->val;
        } else {
            x->val <<= y->val;
        }
    }
    x->isleftvalue = 0;
    p->info = copy_info_node(x);
    return x;
} //}}}

InfoNode* semantics_check_additive_expression(TreeNode* p) { /*{{{*/ //ok
    if (p->type != ADDITIVE_EXPRESSION) {
        return semantics_check_multiplicative_expression(p);
    }
    InfoNode* x = semantics_check_additive_expression(p->children[0]);
    InfoNode* y = semantics_check_multiplicative_expression(p->children[2]);
    if (!isscalar(x->type) || !isscalar(y->type) || !isnumber(x->type) || !isnumber(y->type)) {
        report_error("+/- opeator type error");
    }
    x->isconst = y->isconst = (x->isconst & y->isconst);
    if (p->children[1]->data[0] == '+') {
        if ((ispointer(x->type) && ispointer(y->type)) ||
						(ispointer(x->type) && isdouble(y->type)) ||
						(ispointer(y->type) && isdouble(x->type))) {
            report_error("+ opeator type error");
        }
        if (ispointer(y->type)) {
            x = y;
        } else if (x->isconst) {
					if (x->type == DOUBLE)
					{
						if (y->type == DOUBLE)
						{
							x->real += y->real;
						}
						else
						{
							x->real += y->val;
						}
					}
					else
					{
						if (y->type == DOUBLE)
						{
							x->real = x->val + y->real;
							x->type = DOUBLE;
						}
						else
						{
							x->val += y->val;
						}
					}
        }
    } else {
			if ((ispointer(x->type) && ispointer(y->type)) ||
					(ispointer(x->type) && isdouble(y->type)) ||
					(ispointer(y->type) && isdouble(x->type))) {
            report_error("- opeator type error");
        }
        if (ispointer(x->type) && ispointer(y->type)) {
            x->type = INT;
            x->isleftvalue = 0;
        } else if (x->isconst) {
					if (x->type == DOUBLE)
					{
						if (y->type == DOUBLE)
						{
							x->real -= y->real;
						}
						else
						{
							x->real -= y->val;
						}
					}
					else
					{
						if (y->type == DOUBLE)
						{
							x->real = x->val - y->real;
							x->type = DOUBLE;
						}
						else
						{
							x->val -= y->val;
						}
					}
        }
    }
    p->info = copy_info_node(x);
    return x;
} //}}}

InfoNode* semantics_check_multiplicative_expression(TreeNode* p) { /*{{{*/ //ok
    if (p->type != MULTIPLICATIVE_EXPRESSION) {
        return semantics_check_cast_expression(p);
    }
    InfoNode* x = semantics_check_multiplicative_expression(p->children[0]);
    InfoNode* y = semantics_check_cast_expression(p->children[2]);
		if (!isnumber(x->type) || !isnumber(y->type)) {
        report_error("*/%// opeator type error");
    }
		if (x->type == DOUBLE || y->type == DOUBLE) {
			x->type = DOUBLE;
		} else if (x->type == INT || y->type == INT) {
        x->type = INT;
    }
    if (x->isconst &= y->isconst) {
        if (p->children[1]->data[0] == '*') {
					if (x->type == DOUBLE) {
						if (y->type == DOUBLE) {
							x->real *= y->real;
						}
						else {
							x->real *= y->val;
						}
					}
					else {
						if (y->type == DOUBLE) {
							x->real *= y->real;
							x->type = DOUBLE;
						}
						else {
							x->val *= y->val;
						}
					}
        } else if (p->children[1]->data[0] == '/') {
					if (x->type == DOUBLE) {
						if (y->type == DOUBLE) {
							x->real /= y->real;
						}
						else {
							x->real /= y->val;
						}
					}
					else {
						if (y->type == DOUBLE) {
							x->val /= y->real;
						}
						else {
							x->val /= y->val;
						}
					}
        } else {
					if (x->type == INT && y->type == INT) {
						x->val %= y->val;
					}
					else {
						report_error("% operator type error");
					}
        }
    }
    x->isleftvalue = 0;
    p->info = copy_info_node(x);
    return x;
} //}}}

InfoNode* semantics_check_cast_expression(TreeNode* p) { /*{{{*/ //ok
    if (p->type != CAST_EXPRESSION) {
        return semantics_check_unary_expression(p);
    }
    //(x)y, (char)3
    InfoNode* x = semantics_check_type_name(p->children[0]);
    InfoNode* y = semantics_check_cast_expression(p->children[1]);
    if (x->type == FUNCTION || x->type == STRUCT || x->type == UNION 
            || x->type == NAME || x->type == VOID
            || x->type == ARRAY
            ) {
        report_error("cast error");
    }
    InfoNode* ret;
    if (x->type != POINTER) {
        ret = y;
        ret->type = x->type;
    } else {
        ret = copy_info_node(x);
        if (y->isconst) {
            ret->isconst = 1;
            ret->val = y->val;
        }
    }
    ret->isleftvalue = 0;
    p->info = copy_info_node(ret);
    return ret;
} //}}}

InfoNode* semantics_check_type_name(TreeNode* p) { /*{{{*/ //ok
    if (p->size == 1) {
        InfoNode* ret = semantics_check_type_specifier(p->children[0]);
        p->info = copy_info_node(ret);
        return ret;
    }
    InfoNode* ret = new_info_node();
    ret->type = POINTER;
    ret->info.pointer = semantics_check_type_name(p->children[0]);
    p->info = copy_info_node(ret);
    return ret;
} //}}}

InfoNode* semantics_check_unary_expression(TreeNode* p) { /*{{{*/ //ok
    if (p->type != UNARY_EXPRESSION) {
        return semantics_check_postfix_expression(p);
    }
    if (p->children[0]->type == UNARY_OPERATOR) {/*{{{*/ //ok  unary-operator cast-expression
        InfoNode* ret = semantics_check_cast_expression(p->children[1]);
        //printf("type check: %d\n", ret->type == FUNCTION);
        if (strcmp(p->children[0]->data, "&") == 0) {
            InfoNode* tmp = new_info_node();
            if (!ret->isleftvalue) {
                report_error("unary-operator & error, right side must be left value");
            }
            tmp->type = POINTER;
            tmp->info.pointer = ret;
            ret = tmp;
        } else if (strcmp(p->children[0]->data, "*") == 0) {
            //STR不用处理, 因为*STR是非法的
            if (ret->type != POINTER && ret->type != ARRAY) {
                report_error("unary-opeator * error, right side is not a pointer");
            } else if (ret->type == POINTER) {
                ret = ret->info.pointer;
            } else if (ret->type == ARRAY) {      
                ret = ret->info.array->ptr;
            }
        } else {
            if (!isint(ret->type)) {
                report_error("unary-operator +/-/~/! error, rigth side is not a int");
            }
            if (ret->isconst) {
                switch (p->children[0]->data[0]) {
                    case '-': ret->val = -ret->val; break;
                    case '~': ret->val = ~ret->val; break;
                    case '!': ret->val = !ret->val; break;
                }
            }
        }
        p->info = copy_info_node(ret);
        return ret;
    } //}}}
    if (strcmp(p->children[0]->data, "++") == 0) { //'++' unary-expression {{{
        InfoNode* ret = semantics_check_unary_expression(p->children[1]);
        if (!ret->isleftvalue) {
            report_error("++ operator error, left side is not left value");
        }
        ret->isleftvalue = 0;
        p->info = copy_info_node(ret);
        return ret;
    } //}}}
    if (strcmp(p->children[0]->data, "--") == 0) { //'--' unary-expression {{{
        InfoNode* ret = semantics_check_unary_expression(p->children[1]);
        if (!ret->isleftvalue) {
            report_error("-- operator error, left side is not left value");
        }
        ret->isleftvalue = 0;
        p->info = copy_info_node(ret);
        return ret;
    } //}}}
    if (p->children[1]->type == TYPE_NAME) { //'sizeof' '(' type-name ')' {{{
        InfoNode* tmp = semantics_check_type_name(p->children[1]);
        if (!symbol_table_query_type(tmp)) {
            report_error("sizeof() argument type-name doesn't exist");
        }
        if (tmp->type == NAME) {
            tmp = symbol_table_fetch_type_instance(tmp);
        }
        InfoNode* ret = new_info_node();
        ret->isconst = 1;
        ret->type = INT;
        ret->val = tmp->width;
        ret->width = 4;
        p->info = copy_info_node(ret);
        return ret;
    } //}}}
    //'sizeof' unary-expression {{{
    InfoNode* tmp = semantics_check_unary_expression(p->children[1]);
    InfoNode* ret = new_info_node();
    ret->isconst = 1;
    ret->type = INT;
    ret->val = tmp->width;
    ret->width = 4;
    p->info = copy_info_node(ret);
    return ret;//}}}
} //}}}

InfoNode* semantics_check_postfix_expression(TreeNode* p) { /*{{{*/ //ok
    if (p->type != POSTFIX_EXPRESSION) {
        return semantics_check_primary_expression(p);
    }
    InfoNode* ret = semantics_check_postfix_expression(p->children[0]);
    TreeNode* postfix = p->children[1]; 
    if (strcmp(postfix->data, "postfix []") == 0) { //'[' expression ']' {{{
        InfoNode* subscript = semantics_check_expression(postfix->children[0]);
        if (!isint(subscript->type)) { //下标必须是整数，指针也不行
            report_error("postfix [] error, subscript is not integer");
        }
        if (ret->type != ARRAY && ret->type != POINTER) {
            report_error("postfix [] error, primary-expression is not array or pointer");
        }
        if (ret->type == ARRAY) {
            ret = ret->info.array->ptr;
        } else {
            ret = ret->info.pointer;
        }
        p->info = copy_info_node(ret);
        return ret;
    } //}}}
    if (strcmp(postfix->data, "postfix ()") == 0) {//'(' arguments? ')' {{{
        if (ret->type != FUNCTION) {
            report_error("primary_expression () error, primary_expression is not identifier");
        }
        //printf("isleftvalue %d\n", ret->isleftvalue);
        if (postfix->size == 0) {
            //print, malloc都需要至少一个参数 
            if (ret->info.function->size != 0) {
                report_error("function arguments number dismatch");
            }
        } else if (ret->info.function->size != -1) {
            TreeNode* arguments = postfix->children[0];
            if (arguments->size != ret->info.function->size) {
                report_error("function arguments number dismatch");
            }
            int i;
            for (i = 0; i < arguments->size; i++) {
                InfoNode* tmp = semantics_check_assignment_expression(arguments->children[i]);
                if (semantics_check_same_type(ret->info.function->pars[i], tmp) == 0) {
                    report_error("function arguments type dismatch");
                }
            }
        } else {
            TreeNode* arguments = postfix->children[0];
            InfoNodeFunction* rec = ret->info.function;
            rec->size = arguments->size;
            rec->pars = new_info_node_n(rec->size);
            rec->offset = new_int_n(rec->size + 1);
            rec->offset[0] = 0;
            rec->ret = new_info_node();
            rec->ret->type = VOID;
            rec->ret->width = 0;
            int current = 0, i, j = 0;
            for (i = 0; i < arguments->size; i++) {
                rec->pars[i] = copy_info_node(semantics_check_assignment_expression(arguments->children[i]));
                current += rec->pars[i]->width;         //把char也补成4个字节
                current += (4 - (current & 3)) & 3;
                rec->offset[i + 1] = current;
            }
            rec->width = current;
            p->children[0]->info = ret;
        }
        ret = ret->info.function->ret;
        ret->isleftvalue = 0;
        p->info = copy_info_node(ret);
        return ret;
    } //}}}
    if (strcmp(postfix->data, "postfix .") == 0) { //'.' identifier {{{
        char* id = postfix->children[1]->data;
        if (ret->type != STRUCT && ret->type != UNION) {
            report_error("postfix . error, postfix is not struct or union");
        }
        InfoNodeRecord* record = ret->info.record;
        int i, flag = 0;
        for (i = 0; i < record->size; i++) {
            if (strcmp(record->field[i]->identifier, id) == 0) {
                ret = record->field[i];
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            report_error("postfix . error, has no such member");
        }
        p->info = copy_info_node(ret);
        return ret;
    } //}}}
    if (strcmp(postfix->data, "postfix ->") == 0) { //'->' identifier {{{
        char* id = postfix->children[1]->data;
        if (ret->type != POINTER) {
            report_error("postifx -> error, postfix is not pointer");
        }
        ret = ret->info.pointer;
        if (ret->type == NAME) {
            ret = symbol_table_fetch_type_instance(ret);
        }
        if (ret->type != STRUCT && ret->type != UNION) {
            report_error("postifx -> error, postfix is not the pointer of struct or union");
        }
        int i, flag = 0;
        for (i = 0; i < ret->info.record->size; i++) {
            char* s = ret->info.record->field[i]->identifier;
            if (strcmp(id, s) == 0) {
                flag = 1;
                ret = ret->info.record->field[i];
                break;
            }
        }
        if (flag == 0) {
            printf("%s\n", id);
            report_error("postifx -> error, has no such member");
        }
        p->info = copy_info_node(ret);
        return ret;
    } //}}}
    if (strcmp(postfix->data, "postfix ++") == 0) { //'++' {{{
        if (!ret->isleftvalue) {
            report_error("postfix ++ error, postfix is not left value");
        }
        ret->isleftvalue = 0;
        p->info = copy_info_node(ret);
        return ret;
    } //}}}
    if (strcmp(postfix->data, "postfix --") == 0) { //'--' {{{
        if (!ret->isleftvalue) {
            report_error("postfix ++ error, postfix is not left value");
        }
        ret->isleftvalue = 0;
        p->info = copy_info_node(ret);
        return ret;
    } //}}}
} //}}}

InfoNode* semantics_check_primary_expression(TreeNode* p) { /*{{{*/ //ok
    InfoNode* ret;
    if (p->type == STRING_CONSTANT) {
        ret = new_info_node();
        ret->isinstance = 1;
        ret->type = POINTER;
        InfoNode* tchar = new_info_node();
        tchar->type = CHAR;
        tchar->width = WIDTH_CHAR;
        ret->info.pointer = tchar;
        //ret->val = (int)p->data;
    } else if (p->type == INTEGER_CONSTANT) {
        ret = new_info_node();
        ret->isinstance = 1;
        ret->isconst = 1;
        ret->type = INT;
        ret->val = string_to_int(p->data);
		} else if (p->type == DOUBLE_CONSTANT){
			ret = new_info_node();
			ret->isinstance = 1;
			ret->isconst = 1;
			ret->type = DOUBLE;
			ret->real = string_to_double(p->data);
		} else if (p->type == CHARACTER_CONSTANT) {
        ret = new_info_node();
        ret->isconst = 1;
        ret->type = CHAR;
        if (p->data[1] == '\\') {
            if (p->data[2] == 'n') {
                ret->val = 10;
            } else if (p->data[2] == 't') {
                ret->val = 9;
            } else {
                char* c;
                ret->val = 0;
                for (c = p->data + 2; *c != '\''; c++) {
                    ret->val = ret->val * 8 + *c - '0';
                }
            }
        } else {
            ret->val = p->data[1];
        }
    } else if (p->type == IDENTIFIER) {
        if (strcmp(p->data, "NULL") == 0) {
            ret = new_info_node();
            ret->isconst = 1;
            ret->type = INT;
            ret->val = 0;
        } else {
            ret = symbol_table_fetch_identifier(p->data);
            if (ret == NULL) {
                report_error("no such identifier");
            }
            ret = copy_info_node(ret);
        }
    } else {
        ret = semantics_check_expression(p->children[0]);
    }
    p->info = copy_info_node(ret);
    return ret;
}

void phase_2_semantics_check() {
	  //ok
    loop_count = 0;
    empty_count = 0;
    top_function = NULL;
    symbol_table_initialize();
		//char
		InfoNode* type_char = new_info_node();
		type_char->type = CHAR;
		type_char->width = WIDTH_CHAR;
		//double
		InfoNode* type_double = new_info_node();
		type_double->type = DOUBLE;
		type_double->width = WIDTH_DOUBLE;
    //int
    InfoNode* type_int = new_info_node();
    type_int->type = INT;
		//void
    InfoNode* type_void = new_info_node();
    type_void->type = VOID;
    type_void->width = WIDTH_VOID;
    //printf
		InfoNode* ptr;
    ptr = new_info_node();
    ptr->type = FUNCTION;
    ptr->identifier = strdup("printf");
    ptr->info.function = new_info_node_function();
    ptr->info.function->size = -1; //-1表示参数个数不定
    ptr->info.function->offset = new_int_n(1);
    ptr->info.function->offset[0] = 0;
    ptr->info.function->width = 0;
    ptr->info.function->ret = type_void;
    symbol_table_insert(ptr);
    //malloc
    ptr = new_info_node();
    ptr->type = FUNCTION;
    ptr->identifier = strdup("malloc");
    ptr->info.function = new_info_node_function();
    ptr->info.function->size = 1;
    ptr->info.function->pars = new_info_node_n(1);
    ptr->info.function->pars[0] = type_int;
    ptr->info.function->offset = new_int_n(2);
    ptr->info.function->offset[0] = 0;
    ptr->info.function->offset[1] = 4;
    ptr->info.function->width = 4;
    ptr->info.function->ret = type_int;
    symbol_table_insert(ptr);

    semantics_check(treeroot);
} //}}}

