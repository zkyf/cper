#include <stdio.h>
#include "def.h"
#include "analyzer.tab.h"
#include "semantics.h"

int main(int argc, char** argv) {
    freopen(argv[1], "r", stdin);
    yyparse();
    print_ast(treeroot, 0);
    return 0;
}
