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

char flag_print_ast = 0;
char flag_print_ir = 0;

int main(int argc, char** argv)
{
	if (argc >= 3)
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
    yyparse();
    if (flag_print_ast)
    {
      print_ast(treeroot, 0);
    }
    phase_2_semantics_check();
    phase_3_translate();
    optimize();
    if (flag_print_ir)
    {
      FILE* fout = stderr;
      fprintf(fout, "#================ IR -> Part I  ================\n");
      ir_print(&gir);
      fprintf(fout, "#================ IR -> Part II ================\n");
      ir_print(&mir);
      fprintf(fout, "#================ IR -> Part III ================\n");
      ir_print(&ir);
    }

    phase_4_interprete();
    return 0;
}
