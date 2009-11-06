#ifndef CODEGEN_H
#define CODEGEN_H

#include "c-tree.h"

void c_codegen(c_tree);
void c_codegen_entry(void);
void c_codegen_exit(void);
int c_codegen_recurse(c_tree t, int *registerNo, int topLevel, int getAddress, const char *breakLabel, const char *continueLabel);
#endif
