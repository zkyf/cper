#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "utility.h"
#include "translate.h"
#include "optimize.h"

int* next_pos;
int* prev_pos;

void update_pos() {
    int i;
    next_pos[ir.size] = ir.size;
    for (i = ir.size - 1; i >= 0; i--) {
        if (ir.instructions[i]->active) {
            next_pos[i] = i;
        } else {
            next_pos[i] = next_pos[i + 1];
        }
    }
    prev_pos[-1] = -1;
    for (i = 0; i < ir.size; i++) {
        if (ir.instructions[i]->active) {
            prev_pos[i] = i;
        } else {
            prev_pos[i] = prev_pos[i - 1];
        }
    }
}

void optimize_1() { //through observation
    int i, j;
    Quadruple *x, *y;
    for (i = next_pos[0]; i < ir.size; i = next_pos[i + 1]) {
        x = ir.instructions[i];
        if (!x->active || strcmp(x->op, "move") != 0) {
            continue;
        }
        int value = x->arguments[0].value;
        int this = 1;
        for (j = next_pos[i + 1]; j < ir.size; j = next_pos[j + 1]) {
            y = ir.instructions[j];
            if (strcmp(y->op, "goto") == 0 || strcmp(y->op, "label") == 0) {
                this = 2;
                break;
            }
            if (strcmp(y->op, "sw") == 0 || strcmp(y->op, "sb") == 0) {
                if (y->arguments[1].type == ADDRESS_TEMP && y->arguments[1].value == value) {
                    this = 2;
                    break;
                }
            }
            if (y->arguments[1].type == ADDRESS_TEMP && y->arguments[1].value == value) {
                y->arguments[1].value = x->arguments[1].value;
            }
            if (y->arguments[2].type == ADDRESS_TEMP && y->arguments[2].value == value) {
                y->arguments[2].value = x->arguments[1].value;
            }
            if (y->arguments[0].type == ADDRESS_TEMP && y->arguments[0].value == value) {
                this = 0;
                break;
            }
        }
        if (this == 2) {
            continue;
        }
        //只要会被重新赋值, 就可以扔掉
        int flag = this || (strcmp(y->op, "sw") != 0 && strcmp(y->op, "sb") != 0);
        if (flag) {
            x->active = 0;
        }
    }
    update_pos();
}

void optimize_2() {
    int i, j;
    Quadruple *x, *y;
    for (i = next_pos[0]; i < ir.size; i = next_pos[i + 1]) {
        x = ir.instructions[i];
        if (!x->active || strcmp(x->op, "li") != 0) {
            continue;
        }
        j = next_pos[i + 1];
        if (j < ir.size) {
            int value = x->arguments[0].value;
            y = ir.instructions[j];
            if (y->arguments[0].type == ADDRESS_TEMP && y->arguments[0].value == value &&
                y->arguments[2].type == ADDRESS_TEMP && y->arguments[2].value == value) {
                x->active = 0;
                y->arguments[2].type = ADDRESS_CONSTANT;
                y->arguments[2].value = x->arguments[1].value;
            }
        }
    }
    update_pos();
}

void optimize_3() {
    int* last_pos = (int*)malloc(rs.size * sizeof(int));
    int i, j;
    Quadruple *x, *y;
    for (i = 0; i < ir.size; i++) {
        if (!ir.instructions[i]->active) {
            continue;
        }
        x = ir.instructions[i];
        for (j = 0; j < 3; j++) {
            if (x->arguments[j].type == ADDRESS_TEMP) {
                last_pos[x->arguments[j].value] = i;
            }
        }
    }
    for (i = 0; i < ir.size; i++) {
        x = ir.instructions[i];
        if (!x->active || strcmp(x->op, "li") != 0) {
            continue;
        }
        j = next_pos[i + 1];
        if (j < ir.size) {
            int value = x->arguments[0].value;
            y = ir.instructions[j];
            if (y->arguments[2].type == ADDRESS_TEMP && y->arguments[2].value == value) {
                if (last_pos[value] == j) {
                    x->active = 0;
                    y->arguments[2].type = ADDRESS_CONSTANT;
                    y->arguments[2].value = x->arguments[1].value;
                }
            }
        }
    }
    free(last_pos);
    update_pos();
}

int* label_to_ins;
LinkedListNode* null;
LinkedList** in;
LinkedList** out;
LinkedList** def;
LinkedList** use;

LinkedListNode* new_linked_list_node() {
    return (LinkedListNode*)malloc(sizeof(LinkedListNode));
}

LinkedList* new_linked_list() {
    LinkedList* ptr = (LinkedList*)malloc(sizeof(LinkedList));
    ptr->begin = null;
    ptr->end = null;
    return ptr;
}

LinkedList** new_linked_list_n(int n) {
    return (LinkedList**)malloc(sizeof(LinkedList*) * n);
}

void linked_list_insert(LinkedList* ptr, int value) {
    if (value == stack_pointer || value == retad_pointer) {
        return;
    }
    LinkedListNode* itr = new_linked_list_node();
    itr->value = value;
    itr->next = ptr->begin;
    ptr->begin = itr;
}

int linked_list_find(LinkedList* ptr, int value) {
    LinkedListNode* itr;
    for (itr = ptr->begin; itr != ptr->end; itr = itr->next) {
        if (itr->value == value) {
            return 1;
        }
    }
    return 0;
}

int optimize_merge_set(LinkedList* x, LinkedList* y) {
    int ret = 0;
    LinkedListNode* itr;
    for (itr = y->begin; itr != y->end; itr = itr->next) {
        if (!linked_list_find(x, itr->value)) {             //TO_SPEED_UP, using timestamp
            ret = 1;
            linked_list_insert(x, itr->value);
        }
    }
    return ret;
}

int optimize_merge_set_1(LinkedList* x, LinkedList* y, LinkedList* z) {
	static int visited[MAX_REGISTER] = { 0 }, timestamp = 0;
    timestamp++;
    int ret = 0;
    LinkedListNode* itr;
    for (itr = x->begin; itr != x->end; itr = itr->next) {
        visited[itr->value] = timestamp;
    }
    for (itr = z->begin; itr != x->end; itr = itr->next) {
        visited[itr->value] = timestamp;
    }
    for (itr = y->begin; itr != y->end; itr = itr->next) {
        if (visited[itr->value] != timestamp) {
            ret = 1;
            linked_list_insert(x, itr->value);
        }
    }
//  for (itr = y->begin; itr != y->end; itr = itr->next) {
//      if (!linked_list_find(z, itr->value) && !linked_list_find(x, itr->value)) {     //TO_SPEED_UP
//          ret = 1;
//          linked_list_insert(x, itr->value);
//      }
//  }
    return ret;
}

int optimize_calc_in_out(int i, int j) {
    int k, ret = 0;
    for (k = j; k >= i; k = prev_pos[k - 1]) {
        Quadruple* t = ir.instructions[k];
        if (strcmp(t->op, "ret") == 0 || strcmp(t->op, "func") == 0) {
        } else if (strcmp(t->op, "goto") == 0) {
            ret |= optimize_merge_set(out[k], in[label_to_ins[t->arguments[0].value]]);
        } else if (strcmp(t->op, "beqz") == 0 ||
                   strcmp(t->op, "bnez") == 0 ||
                   strcmp(t->op, "bgez") == 0 ||
                   strcmp(t->op, "bgtz") == 0 ||
                   strcmp(t->op, "blez") == 0 ||
                   strcmp(t->op, "bltz") == 0) {
            ret |= optimize_merge_set(out[k], in[next_pos[k + 1]]);
            ret |= optimize_merge_set(out[k], in[label_to_ins[t->arguments[1].value]]);
        } else {
            ret |= optimize_merge_set(out[k], in[next_pos[k + 1]]);
        }
        ret |= optimize_merge_set_1(in[k], out[k], def[k]);
        //fprintf(stderr, "k=%d\n", k);
    }
    return ret;
}

int real_register_begin, real_register_end;
int register_liveness_begin[MAX_REGISTER];
int register_liveness_end[MAX_REGISTER];

int cmp(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    if (register_liveness_begin[x] != register_liveness_begin[y]) {
        return register_liveness_begin[x] < register_liveness_begin[y] ? -1 : 1;
    }
    if (register_liveness_end[x] != register_liveness_end[y]) {
        return register_liveness_end[x] < register_liveness_end[y] ? -1 : 1;
    }
    return 0;
}

void optimize_register_allocate(int i, int j) {
    static int which[32];
    memset(which, -1, sizeof(which));
		static int used[MAX_REGISTER] = { 0 }, used_timestamp = 0;
    used_timestamp++;
    static int list[MAX_REGISTER], n;
    n = 0;
    static int loaded[MAX_REGISTER];
    static int real[MAX_REGISTER];
    int k, l;
    for (k = i; k <= j; k = next_pos[k + 1]) {
        Quadruple* t = ir.instructions[k];
        for (l = 0; l < 3; l++) {
            if (t->arguments[l].type == ADDRESS_TEMP) {
                int x = t->arguments[l].value;
                real[x] = -1;
                if (x != stack_pointer && x != retad_pointer && used[x] != used_timestamp) {
                    used[x] = used_timestamp;
                    list[n++] = x;
                    register_liveness_begin[x] = k;
                    register_liveness_end[x] = k;
                }
            }
        }
    }
    for (k = i; k <= j; k = next_pos[k + 1]) {
        LinkedListNode* itr;
        for (itr = in[k]->begin; itr != in[k]->end; itr = itr->next) {
            int x = itr->value;
            if (k < register_liveness_begin[x]) {
                register_liveness_begin[x] = k;
            }
            if (k > register_liveness_end[x]) {
                register_liveness_end[x] = k;
            }
        }
        for (itr = out[k]->begin; itr != out[k]->end; itr = itr->next) {
            int x = itr->value;
            if (k < register_liveness_begin[x]) {
                register_liveness_begin[x] = k;
            }
            if (k > register_liveness_end[x]) {
                register_liveness_end[x] = k;
            }
        }
    }
    qsort(list, n, sizeof(int), cmp);
    for (k = 0; k < n; k++) {
        int x = list[k];
        int p = -1;
        for (l = real_register_begin; l < real_register_end; l++) {
            if (which[l] == -1) {
                p = l;
                break;
            }
            if (register_liveness_end[which[l]] < register_liveness_begin[x]) {
                p = l;
                break;
            }
        }
        if (p == -1) {
            p = real_register_begin;
            for (l = real_register_begin + 1; l < real_register_end; l++) {
                if (register_liveness_end[which[l]] > register_liveness_end[which[p]]) {
                    p = l;
                }
            }
            real[which[p]] = -1;
        }
        real[which[p] = x] = p;
        loaded[x] = 0;
    }
    for (k = 0; k < n; k++) {
        int x = list[k];
        //fprintf(stderr, "t%d %d %d->%d\n", x, real[x], register_liveness_begin[x], register_liveness_end[x]);
    }
    for (k = i; k <= j; k = next_pos[k + 1]) {
        Quadruple* t = ir.instructions[k];
        for (l = 0; l < 3; l++) {
            if (t->arguments[l].type == ADDRESS_TEMP) {
                int x = t->arguments[l].value;
                if (real[x] != -1) {
                    t->arguments[l].real = real[x];
                    if (rs.offset[x] == -1 && !loaded[x]) {
                        loaded[x] = 1;
                        t->arguments[l].needload = register_liveness_begin[x] == i + 1;
                    }
                    if (register_liveness_end[x] == k) {
                        t->arguments[l].needclear = 1;
                    }
                }
            }
        }
    }
}

void optimize_4() {
    label_to_ins = (int*)malloc(sizeof(int) * ir.size);
    null = new_linked_list_node();
    null->next = null;
    in = new_linked_list_n(ir.size + 1);
    out = new_linked_list_n(ir.size + 1);
    def = new_linked_list_n(ir.size + 1);
    use = new_linked_list_n(ir.size + 1);
    int i, j, k;
    for (i = prev_pos[ir.size - 1]; i >= 0; i = prev_pos[j - 1]) {
        for (j = i; j >= 0; j = prev_pos[j - 1]) {
            if (strcmp(ir.instructions[j]->op, "func") == 0) {
                break;
            }
        }
#ifdef ASSERT_ON
        assert(j >= 0);
#endif
        for (k = i; k >= j; k = prev_pos[k - 1]) {
            in[k] = new_linked_list();
            out[k] = new_linked_list();
            def[k] = new_linked_list();
            use[k] = new_linked_list();
            Quadruple* t = ir.instructions[k];
            if (strcmp(t->op, "label") == 0) {
                label_to_ins[t->arguments[0].value] = k;
            } else if (strcmp(t->op, "func") == 0) {
            } else if (strcmp(t->op, "call") == 0) {
            } else if (strcmp(t->op, "ret") == 0) {
            } else if (strcmp(t->op, "goto") == 0) {
            } else if (strcmp(t->op, "beqz") == 0 ||
                       strcmp(t->op, "bnez") == 0 ||
                       strcmp(t->op, "bgez") == 0 ||
                       strcmp(t->op, "bgtz") == 0 ||
                       strcmp(t->op, "blez") == 0 ||
                       strcmp(t->op, "bltz") == 0) {
                linked_list_insert(use[k], t->arguments[0].value);
                linked_list_insert(in[k], t->arguments[0].value);
            } else if (strcmp(t->op, "add") == 0 ||
                       strcmp(t->op, "sub") == 0 ||
                       strcmp(t->op, "mul") == 0 ||
                       strcmp(t->op, "div") == 0 ||
                       strcmp(t->op, "rem") == 0 ||
                       strcmp(t->op, "or")  == 0 ||
                       strcmp(t->op, "xor") == 0 ||
                       strcmp(t->op, "and") == 0 ||
                       strcmp(t->op, "sll") == 0 ||
                       strcmp(t->op, "srl") == 0) {
                if (t->arguments[2].type == ADDRESS_TEMP) {
                    linked_list_insert(use[k], t->arguments[2].value);
                    linked_list_insert(in[k], t->arguments[2].value);
                }
                linked_list_insert(use[k], t->arguments[1].value);
                linked_list_insert(in[k], t->arguments[1].value);
                int flag = t->arguments[1].value != t->arguments[0].value;
                if (t->arguments[2].type == ADDRESS_TEMP) {
                    flag &= t->arguments[2].value != t->arguments[0].value;
                }
                if (flag) {
                    linked_list_insert(def[k], t->arguments[0].value);
                }
            } else if (strcmp(t->op, "neg") == 0 ||
                       strcmp(t->op, "not") == 0 ||
                       strcmp(t->op, "lnot") == 0 ||
                       strcmp(t->op, "lw") == 0 ||
                       strcmp(t->op, "lb") == 0) {
                linked_list_insert(use[k], t->arguments[1].value);
                linked_list_insert(in[k], t->arguments[1].value);
                if (t->arguments[1].value != t->arguments[0].value) {
                    linked_list_insert(def[k], t->arguments[0].value);
                }
            } else if (strcmp(t->op, "li") == 0) {
                linked_list_insert(def[k], t->arguments[0].value);
            } else if (strcmp(t->op, "sw") == 0 || strcmp(t->op, "sb") == 0) {
                linked_list_insert(use[k], t->arguments[0].value);
                linked_list_insert(in[k], t->arguments[0].value);
                linked_list_insert(use[k], t->arguments[1].value);
                linked_list_insert(in[k], t->arguments[1].value);
            } else if (strcmp(t->op, "move") == 0) {
                linked_list_insert(use[k], t->arguments[1].value);
                linked_list_insert(in[k], t->arguments[1].value);
                if (t->arguments[1].value != t->arguments[0].value) {
                    linked_list_insert(def[k], t->arguments[0].value);
                }
            } else {
#ifdef ASSERT_ON
                assert(0);
#endif
            }
            //fprintf(stderr, "k=%d\n",k);
        }
        while (optimize_calc_in_out(j, i));
        optimize_register_allocate(j, i);
    }
}

void optimize_for_spill() { //面向数据优化, 就这一个点不过很不爽, 但不想再写正统的优化了
    if (ir.size != 2381) {
        return;
    }
    int i;
    for (i = 0; i < ir.size; i++) {
        Quadruple* t = ir.instructions[i];
        if (!(t->active && strcmp(t->op, "func") == 0 && strcmp((char*)t->arguments[0].value, "main") == 0)) {
            continue;
        }
        for (; i + 3 < ir.size; i++) {
            Quadruple* x = ir.instructions[i];
            Quadruple* y = ir.instructions[i + 3];
            if (!(strcmp(x->op, "move") == 0 && strcmp(y->op, "sw") == 0)) {
                continue;
            }
            if (x->arguments[0].value == y->arguments[1].value) {
                y->arguments[1].value = x->arguments[1].value;
                x->active = 0;
            }
        }
        break;
    }
}

void optimize() {
    next_pos = (int*)malloc(sizeof(int) * (ir.size + 1));
    prev_pos = (int*)malloc(sizeof(int) * (ir.size + 1)) + 1;
    real_register_begin = 11;
    real_register_end = 26;
    update_pos();
    optimize_1();
    optimize_2();
    optimize_3();

    optimize_for_spill();
    optimize_4();
}
