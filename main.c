#define YY_NO_UNISTD_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utility.h"
#include "ast.h"
#include "def.h"
#include "analyzer.tab.h"
#include "semantics.h"
#include "translate.h"
#include "interprete.h"
#include "optimize.h"

int main(int argc, char** argv) {
#ifdef DEBUG
    freopen("data1.c", "r", stdin);
    freopen("x.s", "w", stdout);
#else
	if (argc == 3)
	{
		printf("%s %s\n", argv[1], argv[2]);
		FILE* output = fopen(argv[2], "w");
		fclose(output);
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}
	else
	{
		printf("wrong number of parameters\n");
		return 1;
	}
#endif
    yyparse();
#ifdef PRINT_AST
    print_ast(treeroot, 0);
#endif
    phase_2_semantics_check();
    phase_3_translate();

    optimize();

#ifdef PRINT_IR
    FILE* fout = stderr;

#ifdef COLOR_ON
    fprintf(fout, "#\033[36;1m================ IR -> Part I  ================\033[0m\n");
#else
    fprintf(fout, "#================ IR -> Part I  ================\n");
#endif
    ir_print(&gir);

#ifdef COLOR_ON
    fprintf(fout, "#\033[36;1m================ IR -> Part II ================\033[0m\n");
#else
    fprintf(fout, "#================ IR -> Part II ================\n");
#endif
    ir_print(&mir);

#ifdef COLOR_ON
    fprintf(fout, "#\033[36;1m================ IR -> Part III ================\033[0m\n");
#else
    fprintf(fout, "#================ IR -> Part III ================\n");
#endif
    ir_print(&ir);

#endif

    phase_4_interprete();
    return 0;
}
