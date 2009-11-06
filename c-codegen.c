#include "cmdline.h"
#include "c-tree.h"
#include "c-parse.h"
#include "c-symbol.h"
#include "c-typecheck.h"
#include "c-codegen.h"
#include "c-codegen-func.h"
#include "c-codegen-expr.h"
#include "c-codegen-decl.h"
#include "c-codegen-stmt.h"
#include "c-asmgen.h"
#include "macros.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *outputFile;

void c_codegen_entry()
{
	outputFile = fopen ( outfile, "w");

	ORIG();
	JSR("MAIN", "", NULL);
	HALT();
}

void c_codegen_exit()
{
	END();
	fclose(outputFile);
}

void c_codegen(c_tree func)
{
	int initialReg = LastSystemRegister;
	c_codegen_recurse(func, &initialReg, TRUE, FALSE, NULL, NULL);
}

int c_codegen_recurse(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	if (tree == NULL)
		return *registerNo;

	switch (TREE_CODE(tree))
	{
		case TREE_INTEGER_CST :
			if (!topLevel)
			{
				SET(*registerNo, INTEGER_CST(tree)->val, "integer constant", "");
				return (*registerNo)++;
			}
			break;
		case TREE_IDENTIFIER :
			break;
		case TREE_CHAIN :
			while (tree)
			{
				c_codegen_recurse(CHAIN_VALUE(tree), registerNo, topLevel,
						getAddress, breakLabel, continueLabel);
				tree = CHAIN_NEXT(tree);
			}
			break;
		case TREE_EXPR :
			return exprCodeGen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case TREE_EXPR_LIST :
			if (EXPR_LIST(tree)->chain)
				c_codegen_recurse(EXPR_LIST(tree)->chain, registerNo, TRUE,
						getAddress, breakLabel, continueLabel);
			break;
		case TREE_WHILE :
			return whileCodeGen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case TREE_FOR :
			return forCodeGen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case TREE_IFELSE :
			return ifCodeGen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case TREE_EXPRSTMT :
			c_codegen_recurse(EXPR_STMT(tree)->expr, registerNo, topLevel,
					getAddress, breakLabel, continueLabel);
			break;
		case TREE_COMPOUND :
			if (COMPOUND_STMT(tree)->decllist)
				c_codegen_recurse(COMPOUND_STMT(tree)->decllist, registerNo,
						topLevel, getAddress, breakLabel, continueLabel);
			if (COMPOUND_STMT(tree)->stmtlist)
				c_codegen_recurse(COMPOUND_STMT(tree)->stmtlist, registerNo,
						topLevel, getAddress, breakLabel, continueLabel);
			break;
		case TREE_RETURN :
			return returnCodegen(tree, registerNo, getAddress, breakLabel,
					continueLabel);
			break;
		case TREE_DECL :
			return declCodeGen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
			//			}
			break;
		case TREE_STMT_LIST :
			if (STMT_LIST(tree)->head)
			{
				c_codegen_recurse(STMT_LIST(tree)->head, registerNo, topLevel,
						getAddress, breakLabel, continueLabel);
			}
			break;
		case TREE_BREAK :
			breakCodeGen(breakLabel);
			break;
		case TREE_CONTINUE :
			continueCodeGen(continueLabel);
			break;
		default :
			break;
	}

	return *registerNo;
}
