#ifndef FILE_AST_H
#define FILE_AST_H

#include "def.h"

//type, data, count, if count==0, meaning terminal node
TreeNode* create_node(TreeNodeType, char*, int, ...);
TreeNode* merge_node(TreeNode*, TreeNode*);
void double_space(TreeNode*);

void print_ast(TreeNode*, int);

extern TreeNode* treeroot;
#endif
