/*
 * c-codegen-func.c
 *
 *  Created on: Sep 14, 2009
 *      Author: yogesh
 */

#include "cmdline.h"
#include "c-tree.h"
#include "c-parse.h"
#include "c-symbol.h"
#include "c-typecheck.h"
#include "c-codegen-func.h"
#include "c-codegen.h"
#include "c-asmgen.h"
#include "macros.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int epiloguelabelNo = 0;
static char epiloguePrefix[] = "EPI";
static char epilogueArray[LABEL_ARRAY_LENGTH];

void genFunctionHeader(c_tree func, int symbolTableSize);
void genFunctionEpilogue(c_tree func, int symbolTableSize);

int funcCodegen(c_tree func, int *registerNo, int getAddress,
		const char *breakLabel, const char *continueLabel)
{
	int symbolTableSize = get_symbol_table_size();

	sprintf(epilogueArray, "%s%d", epiloguePrefix, epiloguelabelNo++);

	genFunctionHeader(func, symbolTableSize);

	if (DECL(func)->func.compound_stmt)
		c_codegen_recurse(DECL(func)->func.compound_stmt, registerNo, TRUE,
				getAddress, breakLabel, continueLabel);

	genFunctionEpilogue(func, symbolTableSize);

	return *registerNo;
}

int returnCodegen(c_tree tree, int *registerNo, int getAddress,
		const char *breakLabel, const char *continueLabel)
{
	if (RETURN_STMT(tree)->expr)
	{
		int retReg = c_codegen_recurse(RETURN_STMT(tree)->expr, registerNo,
				FALSE, getAddress, breakLabel, continueLabel);
		STRi(retReg, R5, 3, "store return values", "");
	}
	BRA(epilogueArray, "branching to epilogue", NULL);
	return *registerNo;
}

void genFunctionHeader(c_tree func, int symbolTableSize)
{
	ADDi(R6, R6,-1,
			"allocate space for return value which will be popped by calling function",
			(IDENTIFIER(DECL(func)->id)->id));
	ADDi(R6, R6, -1, "allocate space for storing return address", "");
	STRi(R7, R6, 0, "push the return address into allocated space", "");
	ADDi(R6, R6, -1, "allocate space for storing frame pointer of caller", "");
	STRi(R5, R6, 0, "push the frame pointer of the caller", "");
	ADDi(R5, R6, -1, "Calculate the new frame pointer", "");

	if (symbolTableSize > 0)
		ADDi(R6, R6, -symbolTableSize, "Allocate space for the locals", "");
}

void genFunctionEpilogue(c_tree func, int symbolTableSize)
{
	if (symbolTableSize > 0)
	{
		ADDi(R6, R6, symbolTableSize, "unwind stack, deallocate locals",
				epilogueArray);
		LDRi(R5, R6, 0, "get the frame pointer", "");
	}
	else
	{
		LDRi(R5, R6, 0, "get the frame pointer", epilogueArray);
	}
	ADDi(R6, R6, 1, "", "");
	LDRi(R7, R6, 0, "get the return address", "");
	ADDi(R6, R6, 1, "leave the return value on stack", "");
	RET("", "");
}
