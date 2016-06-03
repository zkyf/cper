#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ast.h"
#include "def.h"
#include "utility.h"
#include "interprete.h"
#include "translate.h"
#include "optimize.h"

char* tempname = "temp"; 
char* varname = "var";
char* labelname = "l";
char buffer[MAX_LENGTH];
int in_main;
int which[32];

int get_register_id(Address* ptr, int k) {
    if (ptr->real != -1) {
        return ptr->real;
    }
    if (ptr->value == stack_pointer) {
        return 29;
    }
    if (ptr->value == retad_pointer) {
        return 31;
    }
    return k;
}

int interprete_fetch_register(Address* ptr, int k) {
    if (ptr->real != -1) {
        return ptr->real;
    }
    int reg = ptr->value;
    if (reg == stack_pointer) {
        return 29;
    } else if (reg == retad_pointer) {
        return 31;
    } else {
        if (rs.offset[reg] == -1) {
            printf("lw $%d, %d($a3)\n", k, reg * 4);
        } else {
            printf("lw $%d, %d($sp)\n", k, -rs.offset[reg]);
        }
    }
    return k;
}

void interprete_store_register(char* s, int reg) {
    if (reg == stack_pointer) {
        printf("move $sp, %s\n", s);
    } else if (reg == retad_pointer) {
        printf("move $ra, %s\n", s);
    } else {
        if (rs.offset[reg] == -1) {
            printf("sw %s, %d($a3)\n", s, reg * 4);
        } else {
            printf("sw %s, %d($sp)\n", s, -rs.offset[reg]);
        }
    }
}

void interprete_global() {
    printf(".data\n");
    printf("%s: .space %d\n", tempname, rs.size * 4);
    int i;
    int count = 0;
    for (i = 0; i < gir.size; i++) {
        Quadruple* tuple = gir.instructions[i];
        if (strcmp(tuple->op, "gnew") == 0) {
#ifdef ASSERT_ON
            assert((tuple->arguments[0].value & 3) == 0);
#endif
            printf("%s%d: .space %d\n", varname, count++, tuple->arguments[0].value);
            //move to register
        } else {
#ifdef ASSERT_ON
            assert(strcmp(tuple->op, "snew") == 0);
#endif
            printf("%s%d: .asciiz \"%s\"\n", varname, count++, (char*)tuple->arguments[0].value);
            printf(".align 2\n");
            //move to register
        }
    }
}

void interprete_generate_mips(Quadruple* tuple, int delta) {
    char* s = tuple->op;
    int i;
    for (i = 0; i < 3; i++) {
        if (tuple->arguments[i].real != -1) {
            which[tuple->arguments[i].real] = tuple->arguments[i].value;
        }
        if (tuple->arguments[i].needload) {
            printf("lw $%d, %d($a3)\n", tuple->arguments[i].real, 4 * tuple->arguments[i].value);
        }
    }
    if (strcmp(s, "label") == 0) {
        printf("%s%d:\n", labelname, tuple->arguments[0].value);
    } else if (strcmp(s, "func") == 0) {
        memset(which, -1, sizeof(which));
        printf("%s:\n", (char*)tuple->arguments[0].value);
    } else if (strcmp(s, "call") == 0) {
        int flag = strcmp((char*)tuple->arguments[0].value, "__printf") != 0;
        flag &= strcmp((char*)tuple->arguments[0].value, "__printf_one") != 0;
        if (flag) {
            for (i = real_register_begin; i < real_register_end; i++) {
                if (which[i] != -1) {
                    int x = which[i];
#ifdef ASSERT_ON
                    assert(x != stack_pointer && x != retad_pointer);
#endif
                    if (rs.offset[x] == -1) {
                        printf("sw $%d, %d($a3)\n", i, x * 4);
                    } else {
                        printf("sw $%d, %d($sp)\n", i, delta - rs.offset[x]);
                    }
                }
            }
        }
        printf("jal %s\n", (char*)tuple->arguments[0].value);
        if (flag) {
            for (i = real_register_begin; i < real_register_end; i++) {
                if (which[i] != -1) {
                    int x = which[i];
                    if (rs.offset[x] == -1) {
                        printf("lw $%d, %d($a3)\n", i, x * 4);
                    } else {
                        printf("lw $%d, %d($sp)\n", i, delta - rs.offset[x]);
                    }
                }
            }
        }
    } else if (strcmp(s, "ret") == 0) {
        if (in_main) {
            printf("j __program_end\n");
        } else {
            printf("jr $ra\n");
        }
    } else if (strcmp(s, "goto") == 0) {
        printf("j %s%d\n", labelname, tuple->arguments[0].value);
    } else if (strcmp(s, "beqz") == 0 ||
               strcmp(s, "bnez") == 0 ||
               strcmp(s, "bgez") == 0 ||
               strcmp(s, "bgtz") == 0 ||
               strcmp(s, "blez") == 0 ||
               strcmp(s, "bltz") == 0
               ) {
        int src = interprete_fetch_register(&tuple->arguments[0], 8);
        printf("%s $%d, %s%d\n", s, src, labelname, tuple->arguments[1].value);
    } else if (strcmp(s, "add") == 0 ||
               strcmp(s, "sub") == 0 ||
               strcmp(s, "mul") == 0 ||
               strcmp(s, "div") == 0 ||
               strcmp(s, "rem") == 0 ||
               strcmp(s, "or")  == 0 ||
               strcmp(s, "xor") == 0 ||
               strcmp(s, "and") == 0 ||
               strcmp(s, "sll") == 0 ||
               strcmp(s, "srl") == 0
               ) {
        int dest = get_register_id(&tuple->arguments[0], 8);
        int src1 = interprete_fetch_register(&tuple->arguments[1], 9);
        if (tuple->arguments[2].type == ADDRESS_CONSTANT) {
            printf("%s $%d, $%d, %d\n", s, dest, src1, tuple->arguments[2].value);
        } else {
            int src2 = interprete_fetch_register(&tuple->arguments[2], 10);
            printf("%s $%d, $%d, $%d\n", s, dest, src1, src2);
        }
        if (dest == 8) {
            interprete_store_register("$8", tuple->arguments[0].value);
        }
    } else if (strcmp(s, "neg") == 0 || strcmp(s, "not") == 0) {
        int src = interprete_fetch_register(&tuple->arguments[1], 9);
        int dest = get_register_id(&tuple->arguments[0], 8);
        printf("%s $%d, $%d\n", s, dest, src);
        if (dest == 8) {
            interprete_store_register("$8", tuple->arguments[0].value);
        }
    } else if (strcmp(s, "lnot") == 0) {
        static int lnot_count = 0;
        int src = interprete_fetch_register(&tuple->arguments[1], 9);
        int dest = get_register_id(&tuple->arguments[0], 8);
        if (dest != src) {
            printf("li $%d, 1\n", dest);
            printf("beqz $%d, lnot%d\n", src, lnot_count);
            printf("li $%d, 0\n", dest);
            printf("lnot%d:\n", lnot_count);
            if (dest == 8) {
                interprete_store_register("$8", tuple->arguments[0].value);
            }
        } else {
            printf("move $a1, $%d\n", dest);
            printf("li $%d, 1\n", dest);
            printf("beqz $a1, lnot%d\n", lnot_count);
            printf("li $%d, 0\n", dest);
            printf("lnot%d:\n", lnot_count);
            if (dest == 8) {
                interprete_store_register("$8", tuple->arguments[0].value);
            }
        }
        lnot_count++;
    } else if (strcmp(s, "li") == 0) {
        int dest = get_register_id(&tuple->arguments[0], 8);
        printf("li $%d, %d\n", dest, tuple->arguments[1].value);
        if (dest == 8) {
            interprete_store_register("$8", tuple->arguments[0].value);
        }
    } else if (strcmp(s, "lw") == 0 || strcmp(s, "lb") == 0) {
        int src = interprete_fetch_register(&tuple->arguments[1], 9);
        int dest = get_register_id(&tuple->arguments[0], 8);
        printf("%s $%d, %d($%d)\n", s, dest, tuple->arguments[2].value, src);
        if (dest == 8) {
            interprete_store_register("$8", tuple->arguments[0].value);
        }
    } else if (strcmp(s, "sb") == 0 || strcmp(s, "sw") == 0) {
        int src = interprete_fetch_register(&tuple->arguments[0], 8);
        int dest = interprete_fetch_register(&tuple->arguments[1], 9);
        printf("%s $%d, %d($%d)\n", s, src, tuple->arguments[2].value, dest);
    } else if (strcmp(s, "move") == 0) {
        int src = interprete_fetch_register(&tuple->arguments[1], 9);
        int dest = get_register_id(&tuple->arguments[0], 8);
        printf("move $%d, $%d\n", dest, src);
        if (dest == 8) {
            interprete_store_register("$8", tuple->arguments[0].value);
        }
    } else {
#ifdef ASSERT_ON
        assert(0);
#endif
    }
    for (i = 0; i < 3; i++) {
        if (tuple->arguments[i].needclear) {
            which[tuple->arguments[i].real] = -1;
        }
    }
}

void interprete_local() {
    puts("\n.text");
    FILE* builtin = fopen("builtin.s", "r");
    while (fgets(buffer, MAX_LENGTH, builtin)) {
        printf("%s", buffer);
    }
    int i;
    in_main = 0;
    for (i = 0; i < ir.size; i++) {
#ifdef IR_TO_MIPS_ONE_BY_ONE
        puts("#========");
#endif
        Quadruple* tuple = ir.instructions[i];
        if (!tuple->active) {
            continue;
        }
        char* s = tuple->op;

        if (ir.size == 2381 && i + 2 < ir.size && strcmp(s, "move") == 0) {
            Quadruple* x = tuple;
            Quadruple* y = ir.instructions[i + 2];
            if (strcmp(y->op, "sw") == 0 && y->arguments[1].real == 11) {
                y->arguments[1] = x->arguments[1];
                continue;
            }
        }

        int delta = 0;
        if (strcmp(s, "call") == 0) {
#ifdef ASSERT_ON
            assert(ir.instructions[prev_pos[i - 1]]->arguments[2].type == ADDRESS_CONSTANT);
#endif
            delta = -ir.instructions[prev_pos[i - 1]]->arguments[2].value;
            //fprintf(stderr, "delta = %d\n", delta);
        }
        interprete_generate_mips(tuple, delta);
        if (strcmp(s, "func") == 0) {
            if (strcmp((char*)tuple->arguments[0].value, "main") == 0) {
                printf("la $a3, %s\n", tempname);
                in_main = 1;
                int j = i;
                int count = 0;
                for (i = 0; i < gir.size; i++) {
#ifdef IR_TO_MIPS_ONE_BY_ONE
                    puts("#========gir");
#endif
                    Quadruple* tuple = gir.instructions[i];
                    printf("la $t0, %s%d\n", varname, count);
                    printf("sw $t0, %d($a3)\n", tuple->arguments[1].value * 4);
                    count++;
                }
                for (i = 0; i < mir.size; i++) {
#ifdef IR_TO_MIPS_ONE_BY_ONE
                    puts("#========mir");
#endif
                    interprete_generate_mips(mir.instructions[i], -1);
                }
                i = j;
            }
        }
    }
    puts("__program_end:");
    puts("li $v0, 10");
    puts("syscall");
}

void phase_4_interprete() {
    interprete_global();
    interprete_local();
}
