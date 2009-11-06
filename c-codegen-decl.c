/*
 * c-codegen-decl.c
 *
 *  Created on: Sep 19, 2009
 *      Author: yogesh
 */

#include "cmdline.h"
#include "c-tree.h"
#include "c-parse.h"
#include "c-symbol.h"
#include "c-typecheck.h"
#include "c-codegen-decl.h"
#include "c-codegen-func.h"
#include "c-codegen.h"
#include "c-asmgen.h"
#include "macros.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int variableDeclCodeGen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel);

int arrayDeclCodeGen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel);

int declCodeGen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel)
{
	switch (DECL(tree)->type)
	{
		case VAR_DECL :
			return variableDeclCodeGen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case FUNCTION_DECL :
			return funcCodegen(tree, registerNo, getAddress, breakLabel,
					continueLabel);
			break;
		case ARRAY_DECL :
			return arrayDeclCodeGen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		default :
			break;
	}
	return *registerNo;
}

int arrayDeclCodeGen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	if (!topLevel)
	{
		symbol_table_entry_t entry = symbol_table_get_entry(
				DECL_NAME_STRING(tree));
		int offset = entry->offset; // get the offset
		int startingAddressReg = (*registerNo)++;
		if (entry->local)
		{
			ADDi(startingAddressReg, R5, offset,
					"starting address of local array", NULL);
		}
		else
		{
			ADDi(startingAddressReg, R4, offset,
					"starting address of global array", NULL);
		}
		return startingAddressReg;
	}
	return *registerNo;

}

int variableDeclCodeGen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	if (!topLevel)
	{
		const char * variableName = DECL_NAME_STRING(tree);
		if (strcmp(variableName, CIN) == 0)
		{
			CINASM("", "");
			return R0;
		}
		else
		{
			symbol_table_entry_t entry = symbol_table_get_entry(variableName);
			int offset = entry->offset; // get the offset
			if (entry->local)
			{
				if (getAddress)
					ADDi(*registerNo, R5, offset,
							"get address of local variable", NULL);
				else
					LDRi(*registerNo, R5, offset, "load a local variable", NULL);
			}
			else
			{
				if (getAddress)
					ADDi(*registerNo, R4, offset,
							"get address of global variable", NULL);
				else
					LDRi(*registerNo, R4, offset, "load a global variable",
							NULL);
			}
			return (*registerNo)++;
		}
	}

	return *registerNo;
}
