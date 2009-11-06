/*
 * c-codegen-stmt.c
 *
 *  Created on: Sep 21, 2009
 *      Author: yogesh
 */

#include "cmdline.h"
#include "c-tree.h"
#include "c-parse.h"
#include "c-symbol.h"
#include "c-typecheck.h"
#include "c-codegen-stmt.h"
#include "c-codegen.h"
#include "c-asmgen.h"
#include "macros.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int ifCodeGen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel)
{
	static int endifLabelNo = 0;
	static char endifLabelPrefix[] = "ENDIF";
	char endifLabelArray[LABEL_ARRAY_LENGTH];

	static int elseLabelNo = 0;
	static char elseLabelPrefix[] = "ELSE";
	char elseLabelArray[LABEL_ARRAY_LENGTH];

	sprintf(endifLabelArray, "%s%d", endifLabelPrefix, endifLabelNo++);
	sprintf(elseLabelArray, "%s%d", elseLabelPrefix, elseLabelNo++);

	int conditionReg = c_codegen_recurse(IFELSE_STMT(tree)->cond, registerNo,
			FALSE, FALSE, breakLabel, continueLabel);

	if (IFELSE_STMT(tree)->elsestmt)
		BRnzp(conditionReg, elseLabelArray, "branch to else condition", NULL, "z");
	else
		BRnzp(conditionReg, endifLabelArray, "branch to end of if", NULL, "z");

	c_codegen_recurse(IFELSE_STMT(tree)->ifstmt, registerNo, topLevel,
			getAddress, breakLabel, continueLabel);

	if (IFELSE_STMT(tree)->elsestmt)
	{
		BRA(endifLabelArray, "after then skip the else part", NULL);
		NOP("end of if", elseLabelArray);
		c_codegen_recurse(IFELSE_STMT(tree)->elsestmt, registerNo, topLevel,
				getAddress, breakLabel, continueLabel);
	}

	NOP("end of if", endifLabelArray);
	return *registerNo;
}

int forCodeGen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel)
{
	static int endForLabelNo = 0;
	static char endForLabelPrefix[] = "EFOR";
	char endForLabelArray[LABEL_ARRAY_LENGTH];

	static int condForLabelNo = 0;
	static char condForLabelPrefix[] = "CFOR";
	char condForLabelArray[LABEL_ARRAY_LENGTH];

	static int reInitForLabelNo = 0;
	static char reInitLabelPrefix[] = "RFOR";
	char reInitLabelArray[LABEL_ARRAY_LENGTH];

	sprintf(endForLabelArray, "%s%d", endForLabelPrefix, endForLabelNo++);
	sprintf(condForLabelArray, "%s%d", condForLabelPrefix, condForLabelNo++);
	sprintf(reInitLabelArray, "%s%d", reInitLabelPrefix, reInitForLabelNo++);

	c_codegen_recurse(FORLOOP_STMT(tree)->init_expr, registerNo, topLevel,
			getAddress, breakLabel, continueLabel);

	NOP("condition of for", condForLabelArray);

	int conditionReg = c_codegen_recurse(FORLOOP_STMT(tree)->cond_expr,
			registerNo, FALSE, FALSE, breakLabel, continueLabel);

	BRnzp(conditionReg, endForLabelArray, "branch on for condition", NULL, "z");

	c_codegen_recurse(FORLOOP_STMT(tree)->stmt, registerNo, topLevel,
			getAddress, endForLabelArray, reInitLabelArray);

	NOP("re-init of for loop", reInitLabelArray);
	c_codegen_recurse(FORLOOP_STMT(tree)->reinit_expr, registerNo, TRUE, FALSE,
			breakLabel, continueLabel);

	BRA(condForLabelArray, "go back to for condition check", NULL);

	NOP("end of for", endForLabelArray);
	return *registerNo;

}

int whileCodeGen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel)
{
	static int whileLabelNo = 0;
	static char whileLabelPrefix[] = "WHI";
	char whileLabelArray[LABEL_ARRAY_LENGTH];

	static int whileEndLabelNo = 0;
	static char whileEndLabelPrefix[] = "WEND";
	char whileEndLabelArray[LABEL_ARRAY_LENGTH];

	sprintf(whileLabelArray, "%s%d", whileLabelPrefix, whileLabelNo++);
	sprintf(whileEndLabelArray, "%s%d", whileEndLabelPrefix, whileEndLabelNo++);

	NOP("beginning of while", whileLabelArray);

	int conditionReg = c_codegen_recurse(WHILE_STMT(tree)->cond, registerNo,
			FALSE, FALSE, breakLabel, continueLabel);
	BRnzp(conditionReg, whileEndLabelArray, "branch on while condition", NULL,
			"z");

	c_codegen_recurse(WHILE_STMT(tree)->stmt, registerNo, topLevel, getAddress,
			whileEndLabelArray, whileLabelArray);

	BRA(whileLabelArray, "go back to while condition check", NULL);

	NOP("end of while", whileEndLabelArray);
	return *registerNo;
}

void breakCodeGen(const char* breakLabel)
{
	BRA(breakLabel, "breaking out", NULL);
}

void continueCodeGen(const char* continueLabel)
{
	BRA(continueLabel, "continuing again", NULL);
}


