/*
 * c-codegen-expr.c
 *
 *  Created on: Sep 17, 2009
 *      Author: yogesh
 */
#include "c-codegen-expr.h"
#include "c-codegen.h"
#include "c-symbol.h"
#include "macros.h"
#include "c-asmgen.h"
#include "c-typecheck.h"
#include <string.h>

typedef void (*BasicAsmExprPtr)(int, int, int, const char *, const char*);

typedef enum
{
	gtCond = 0, gteCond, ltCond, lteCond, eqCond, neqCond
} condition;

int assignExprCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel);

int basicExprCodegen(c_tree tree, int *registerNo, int topLevel,
		BasicAsmExprPtr asmFunc, BasicAsmExprPtr immiAsmfunc, int getAddress,
		const char *breakLabel, const char *continueLabel);

int basicExprWithPointerArthCodegen(c_tree tree, int *registerNo, int topLevel,
		BasicAsmExprPtr asmFunc, BasicAsmExprPtr immiAsmfunc, int getAddress,
		const char *breakLabel, const char *continueLabel);

int comparisonExprCodegen(c_tree tree, int *registerNo, int topLevel,
		condition cond, int getAddress, const char *breakLabel,
		const char *continueLabel);

void checkConditionAndBranch(condition cond, int Rx, char* LABEL,
		const char *comment, const char *label);

int moduloExprCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel);

int unaryMinusCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel);

int unaryPlusCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel);

int logicalNotCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel);

int arrayRefCodegen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel);

int memberExprCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel);

int callExprCodegen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel);

void recurseExpressionList(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel);

int addrExprCodegen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel);

int indirectRefCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel);

int commaExprCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel);

int sizeofExprCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel);

int getSizeOfExpr(c_tree tree);

int getSize(c_tree tree);

int exprCodeGen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel)
{
	switch (EXPR_TYPE(tree))
	{
		case ASSIGN_EXPR :
			return assignExprCodegen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
		case ADD_EXPR :
			return basicExprWithPointerArthCodegen(tree, registerNo, topLevel,
					&ADD, &ADDi, getAddress, breakLabel, continueLabel);
		case SUBTRACT_EXPR :
			return basicExprWithPointerArthCodegen(tree, registerNo, topLevel,
					&SUB, &SUBi, getAddress, breakLabel, continueLabel);
		case MULTIPLY_EXPR :
			return basicExprCodegen(tree, registerNo, topLevel, &MUL, &MULi,
					getAddress, breakLabel, continueLabel);
		case DIVIDE_EXPR :
			return basicExprCodegen(tree, registerNo, topLevel, &DIV, &DIVi,
					getAddress, breakLabel, continueLabel);
		case LOGICAL_OR_EXPR :
			return basicExprCodegen(tree, registerNo, topLevel, &ORL, &ORLi,
					getAddress, breakLabel, continueLabel);
		case LOGICAL_AND_EXPR :
			return basicExprCodegen(tree, registerNo, topLevel, &ANDL, &ANDLi,
					getAddress, breakLabel, continueLabel);
		case MODULO_EXPR :
			return moduloExprCodegen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
		case LOGICAL_GT_EXPR :
			return comparisonExprCodegen(tree, registerNo, topLevel, gtCond,
					getAddress, breakLabel, continueLabel);
		case LOGICAL_GTE_EXPR :
			return comparisonExprCodegen(tree, registerNo, topLevel, gteCond,
					getAddress, breakLabel, continueLabel);
		case LOGICAL_LT_EXPR :
			return comparisonExprCodegen(tree, registerNo, topLevel, ltCond,
					getAddress, breakLabel, continueLabel);
		case LOGICAL_LTE_EXPR :
			return comparisonExprCodegen(tree, registerNo, topLevel, lteCond,
					getAddress, breakLabel, continueLabel);
		case LOGICAL_EQ_EXPR :
			return comparisonExprCodegen(tree, registerNo, topLevel, eqCond,
					getAddress, breakLabel, continueLabel);
		case LOGICAL_NEQ_EXPR :
			return comparisonExprCodegen(tree, registerNo, topLevel, neqCond,
					getAddress, breakLabel, continueLabel);
		case COMMA_EXPR :
			return commaExprCodegen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case UMINUS_EXPR :
			return unaryMinusCodegen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case UPLUS_EXPR :
			return unaryPlusCodegen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case LOGICAL_NOT_EXPR :
			return logicalNotCodegen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case ARRAY_REF_EXPR :
			return arrayRefCodegen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case CALL_EXPR :
			return callExprCodegen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case SIZEOF_EXPR :
			return sizeofExprCodegen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case ADDR_EXPR :
			return addrExprCodegen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
		case INDIRECT_REF_EXPR :
			return indirectRefCodegen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case MEMBER_EXPR :
			return memberExprCodegen(tree, registerNo, topLevel, getAddress,
					breakLabel, continueLabel);
			break;
		case BAD_EXPR :
		default :
			//PRINTF( "\n");
			break;
	}
	return *registerNo;
}

int sizeofExprCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	c_tree op = TREE_EXPR_OPERAND(tree,0);
	if (!topLevel)
	{
		int size = getSize(op);

		c_codegen_recurse(op, registerNo, topLevel, getAddress, breakLabel,
				continueLabel);

		int sizeReg = (*registerNo)++;
		SET(sizeReg, size, "size of", NULL);

		return sizeReg;
	}
	else
	{
		c_codegen_recurse(op, registerNo, topLevel, getAddress, breakLabel,
				continueLabel);

		return *registerNo;
	}
}

int getSize(c_tree tree)
{
	int size = 1;
	int code = TREE_CODE(tree);
	switch (code)
	{
		case TREE_EXPR :
			size = getSizeOfExpr(tree);
			break;
		case TREE_DECL :
			size = get_type_size(TREE_TYPE(tree));
			break;
		case TREE_TYPE :
			size = get_type_size(tree);
			break;
		default :
			size = 1;
			break;
	}
	return size;
}
int getSizeOfExpr(c_tree tree)
{
	int size = 1;
	int type = EXPR_TYPE(tree);
	switch (type)
	{
		case MEMBER_EXPR :
		{
			size = get_type_size(TREE_TYPE(tree));
			break;
		}
		case ARRAY_REF_EXPR :
		{
			c_tree arrayVarName = TREE_EXPR_OPERAND(tree,0);
			size = get_type_size(TREE_TYPE(arrayVarName)->type.info.a.type);
			break;
		}
		default :
			break;
	}
	return size;
}

int assignExprCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	c_tree rhs = TREE_EXPR_OPERAND(tree,1);
	c_tree lhs = TREE_EXPR_OPERAND(tree,0);
	if (TREE_CODE(lhs) == TREE_DECL && (strcmp(DECL_NAME_STRING(lhs), COUT)
			== 0))
	{
		int rhsValue = c_codegen_recurse(rhs, registerNo, FALSE, FALSE,
				breakLabel, continueLabel);
		ADDi(R0, rhsValue, 0, "copying into R0", NULL);
		COUTASM("Displaying to COUT", "");
		return R0;
	}
	else
	{

		c_tree type = get_type_for_uid(TYPE(TREE_TYPE(lhs))->uid);
		int typeSize = getSize(TREE_TYPE(lhs));

		if(TYPE(type)->code!=STRUCT_TYPE || typeSize==1 )
		{
			int rhsValue = c_codegen_recurse(rhs, registerNo, FALSE, FALSE,
					breakLabel, continueLabel);
			int lhsAddress = c_codegen_recurse(lhs, registerNo, FALSE, TRUE,
					breakLabel, continueLabel);
			STRi(rhsValue, lhsAddress, 0, "assignment", NULL);
		}
		else
		{

			int rhsAddress = c_codegen_recurse(rhs, registerNo, FALSE, TRUE,
					breakLabel, continueLabel);
			int lhsAddress = c_codegen_recurse(lhs, registerNo, FALSE, TRUE,
					breakLabel, continueLabel);

			static int copyCondLabelNo = 0;
			static char copyCondLabelPrefix[] = "SCC";
			char copyCondLabelArray[LABEL_ARRAY_LENGTH];

			static int copyEndLabelNo = 0;
			static char copyEndLabelPrefix[] = "SCE";
			char copyEndLabelArray[LABEL_ARRAY_LENGTH];

			sprintf(copyCondLabelArray, "%s%d", copyCondLabelPrefix,
					copyCondLabelNo++);
			sprintf(copyEndLabelArray, "%s%d", copyEndLabelPrefix,
								copyEndLabelNo++);

			int counterRegister = (*registerNo)++;
			int subResultRegister = (*registerNo)++;
			int tempCopyRegister = (*registerNo)++;

			// loop for copying
			SET(counterRegister, 0, "struct copy counter initial value", NULL);
			SUBi(subResultRegister, counterRegister, typeSize,
					"struct copy condition to end copying", copyCondLabelArray);
			BRnzp(subResultRegister, copyEndLabelArray,
					"struct copy branch to end", NULL, "z");
			LDR(tempCopyRegister, rhsAddress, counterRegister, "struct assignment", NULL);
			STR(tempCopyRegister, lhsAddress, counterRegister, "struct assignment", NULL);
			ADDi(counterRegister, counterRegister, 1, "struct copy increment counter", NULL);
			BRA(copyCondLabelArray, "struct copy branch to condition", NULL);
			NOP("end of struct copying", copyEndLabelArray);

		}

		return c_codegen_recurse(lhs, registerNo,
				topLevel, getAddress, breakLabel, continueLabel);
	}
}

int basicExprCodegen(c_tree tree, int *registerNo, int topLevel,
		BasicAsmExprPtr asmFunc, BasicAsmExprPtr immiAsmfunc, int getAddress,
		const char *breakLabel, const char *continueLabel)
{
	c_tree op2 = TREE_EXPR_OPERAND(tree,1);
	c_tree op1 =TREE_EXPR_OPERAND(tree,0);
	if (!topLevel)
	{
		int op1Register = c_codegen_recurse(op1, registerNo, topLevel,
				getAddress, breakLabel, continueLabel);

		if (TREE_CODE(op2) == TREE_INTEGER_CST)
		{
			immiAsmfunc(*registerNo, op1Register, INTEGER_CST(op2)->val, NULL,
					NULL);
		}
		else
		{
			int op2Register = c_codegen_recurse(op2, registerNo, topLevel,
					getAddress, breakLabel, continueLabel);

			asmFunc(*registerNo, op1Register, op2Register, NULL, NULL);
		}
		return (*registerNo)++;
	}
	else
	{
		// evaluate the LHS and RHS....but dont do the operation
		c_codegen_recurse(op1, registerNo, topLevel, getAddress, breakLabel,
						continueLabel);

		c_codegen_recurse(op2, registerNo, topLevel, getAddress, breakLabel,
				continueLabel);

		return *registerNo;
	}
}

int basicExprWithPointerArthCodegen(c_tree tree, int *registerNo, int topLevel,
		BasicAsmExprPtr asmFunc, BasicAsmExprPtr immiAsmfunc, int getAddress,
		const char *breakLabel, const char *continueLabel)
{
	// to implement pointer arthmetic
	if (!getAddress)
		return basicExprCodegen(tree, registerNo, topLevel, asmFunc,
				immiAsmfunc, getAddress, breakLabel, continueLabel);

	c_tree op2 = TREE_EXPR_OPERAND(tree,1);
	c_tree op1 = TREE_EXPR_OPERAND(tree,0);

	if (!topLevel)
	{
		int op1Register = c_codegen_recurse(op1, registerNo, topLevel, getAddress,
				breakLabel, continueLabel);

		int typeSize = get_type_size(TYPE(TREE_TYPE(op1))->info.reftype);

		int resultReg;
		if (TREE_CODE(op2) == TREE_INTEGER_CST)
		{
			resultReg = (*registerNo)++;
			immiAsmfunc(resultReg, op1Register, typeSize
					* INTEGER_CST(op2)->val, "Pointer Arthmetic", NULL);
		}
		else
		{
			int op2Register = c_codegen_recurse(op2, registerNo, topLevel,
					getAddress, breakLabel, continueLabel);
			int mulReg = (*registerNo)++;
			resultReg = (*registerNo)++;
			MULi(mulReg, op1Register, typeSize,
					"calculating size for Pointer Arthmetic", NULL);
			asmFunc(resultReg, op1Register, op2Register, "Pointer Arthmetic",
					NULL);
		}
		return resultReg;
	}
	else
	{
		// evaluate the LHS and RHS....but dont do the operation
		c_codegen_recurse(op1, registerNo, topLevel, getAddress, breakLabel,
						continueLabel);

		c_codegen_recurse(op2, registerNo, topLevel, getAddress, breakLabel,
				continueLabel);

		return *registerNo;
	}
}

int comparisonExprCodegen(c_tree tree, int *registerNo, int topLevel,
		condition cond, int getAddress, const char *breakLabel,
		const char *continueLabel)
{
	static int labelNo = 0;
	static char labelPrefix[] = "COMP";
	char labelArray[LABEL_ARRAY_LENGTH];

	c_tree op1 = TREE_EXPR_OPERAND(tree,0);
	c_tree op2 = TREE_EXPR_OPERAND(tree,1);

	if (!topLevel)
	{
		int resultReg = (*registerNo)++;
		// intially set the result to false
		SET(resultReg, TRUE,
				"comparison expression result register intial value true", NULL);

		int op1Register = c_codegen_recurse(op1, registerNo, topLevel,
				getAddress, breakLabel, continueLabel);

		int subResultReg = (*registerNo)++;
		if (TREE_CODE(op2) == TREE_INTEGER_CST)
		{
			// substract the two values to be compared
			SUBi(subResultReg, op1Register, INTEGER_CST(op2)->val,
					"comparison expression subtract c=a-b", NULL);
		}
		else
		{
			// substract the two values to be compared
			int op2Register = c_codegen_recurse(op2, registerNo, topLevel,
					getAddress, breakLabel, continueLabel);
			SUB(subResultReg, op1Register, op2Register,
					"comparison expression subtract c=a-b", NULL);
		}
		sprintf(labelArray, "%s%d", labelPrefix, labelNo++);

		// create a branch depending upon the condition
		checkConditionAndBranch(cond, subResultReg, labelArray,
				"comparison expression branch on condition", NULL);

		// this set will be skipped depending on condition
		// this set sets the result to false
		SET(resultReg, FALSE, "comparison expression false value", NULL);

		//NOP just to create the label
		NOP("comparison expression just to create a label", labelArray);
		return resultReg;
	}
	else
	{
		// evaluate the LHS and RHS....but dont do the operation
		c_codegen_recurse(op1, registerNo, topLevel, getAddress, breakLabel,
						continueLabel);

		c_codegen_recurse(op2, registerNo, topLevel, getAddress, breakLabel,
				continueLabel);

		return *registerNo;
	}
}

void checkConditionAndBranch(condition cond, int Rx, char* LABEL,
		const char *comment, const char *label)
{
	switch (cond)
	{
		case gtCond :
			BRnzp(Rx, LABEL, comment, NULL, "p");
			break;
		case gteCond :
			BRnzp(Rx, LABEL, comment, NULL, "zp");
			break;
		case ltCond :
			BRnzp(Rx, LABEL, comment, NULL, "n");
			break;
		case lteCond :
			BRnzp(Rx, LABEL, comment, NULL, "nz");
			break;
		case eqCond :
			BRnzp(Rx, LABEL, comment, NULL, "z");
			break;
		case neqCond :
			BRnzp(Rx, LABEL, comment, NULL, "np");
			break;
		default :
			break;
	}
}

int moduloExprCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	c_tree op2 = TREE_EXPR_OPERAND(tree,1);

	c_tree op1 = TREE_EXPR_OPERAND(tree,0);

	if (!topLevel)
	{
		int op1Register = c_codegen_recurse(op1,
				registerNo, topLevel, getAddress, breakLabel, continueLabel);

		if (TREE_CODE(op2) == TREE_INTEGER_CST)
		{
			int divReg = (*registerNo)++;
			int mulReg = (*registerNo)++;
			int resReg = (*registerNo)++;

			int immiValue = INTEGER_CST(op2)->val;
			DIVi(divReg, op1Register, immiValue, "modulo", NULL);
			MULi(mulReg, divReg, immiValue, "modulo", NULL);
			SUB(resReg, op1Register, mulReg, "modulo", NULL);

			return resReg;
		}
		else
		{
			int op2Register = c_codegen_recurse(op2, registerNo, topLevel,
					getAddress, breakLabel, continueLabel);

			int divReg = (*registerNo)++;
			int mulReg = (*registerNo)++;
			int resReg = (*registerNo)++;

			DIV(divReg, op1Register, op2Register, "modulo", NULL);
			MUL(mulReg, divReg, op2Register, "modulo", NULL);
			SUB(resReg, op1Register, mulReg, "modulo", NULL);

			return resReg;
		}
	}
	else
	{
		c_codegen_recurse(op1, registerNo, topLevel, getAddress, breakLabel,
						continueLabel);

		c_codegen_recurse(op2, registerNo, topLevel, getAddress, breakLabel,
				continueLabel);

		return *registerNo;
	}
}

int unaryMinusCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	c_tree op = TREE_EXPR_OPERAND(tree,0);
	if (!topLevel)
	{
		int zeroReg = (*registerNo)++;
		SET(zeroReg, 0, "unary minus getting zero into register", NULL);
		if (TREE_CODE(op) == TREE_INTEGER_CST)
		{
			SUBi(*registerNo, zeroReg, INTEGER_CST(op)->val,
					"unary minus sub the integer const from zero", NULL);
		}
		else
		{
			int opRegister = c_codegen_recurse(op, registerNo, FALSE,
					getAddress, breakLabel, continueLabel);
			SUB(*registerNo, zeroReg, opRegister,
					"unary minus sub the register from zero", NULL);
		}
		return (*registerNo)++;
	}
	else
	{
		c_codegen_recurse(op, registerNo, topLevel, getAddress, breakLabel,
				continueLabel);

		return *registerNo;
	}
}

int unaryPlusCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	// here get address/topLevel doesnt matter
	c_tree op = TREE_EXPR_OPERAND(tree,0);
	return c_codegen_recurse(op, registerNo, topLevel, getAddress, breakLabel,
			continueLabel);
}
int logicalNotCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	c_tree op = TREE_EXPR_OPERAND(tree,0);
	if (!topLevel)
	{
		int opRegister = c_codegen_recurse(op, registerNo, FALSE, getAddress,
				breakLabel, continueLabel);
		NOTL(*registerNo, opRegister, "logical not", NULL);
		return (*registerNo)++;
	}
	else
	{
		c_codegen_recurse(op, registerNo, topLevel, getAddress, breakLabel,
				continueLabel);

		return *registerNo;
	}
}

int arrayRefCodegen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel)
{
	c_tree index = TREE_EXPR_OPERAND(tree,1);
	if (!topLevel)
	{
		c_tree array = TREE_EXPR_OPERAND(tree,0);

		int startingAddReg = c_codegen_recurse(array, registerNo, FALSE, TRUE,
				breakLabel, continueLabel);
		int indexReg = c_codegen_recurse(index, registerNo, FALSE, FALSE,
				breakLabel, continueLabel);

		int size = get_type_size(TREE_TYPE(array)->type.info.a.type);

		int offsetFromStartingAddressReg = indexReg;
		if (size > 1)
		{
			offsetFromStartingAddressReg = (*registerNo)++;

			MULi(offsetFromStartingAddressReg, indexReg, size,
					"calculate offset from start of array", NULL);
		}

		if (!getAddress)
		{
			int resultReg = (*registerNo)++;

			LDR(resultReg, startingAddReg, offsetFromStartingAddressReg,
					"load the array value into register", NULL);
			return resultReg;
		}
		else
		{
			int resultReg = (*registerNo)++;
			ADD(resultReg, startingAddReg, offsetFromStartingAddressReg,
					"getting address of array at index location", NULL);
			return resultReg;
		}
	}
	else
	{
		c_codegen_recurse(index, registerNo, topLevel, FALSE,
				breakLabel, continueLabel);

		return *registerNo;
	}
}

int memberExprCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	if (!topLevel)
	{
		c_tree structName = TREE_EXPR_OPERAND(tree,0);

		c_tree memberName = TREE_EXPR_OPERAND(tree,1);
		int startingStructAddressReg = c_codegen_recurse(structName,
				registerNo, FALSE, TRUE, breakLabel, continueLabel);

		int offset = get_field_offset(TREE_TYPE(structName), memberName);

		int resultReg = (*registerNo)++;

		if (getAddress)
			ADDi(resultReg, startingStructAddressReg, offset,
					"struct member address", NULL);
		else
			LDRi(resultReg, startingStructAddressReg, offset,
					"struct member value", NULL);

		return resultReg;

	}
	return *registerNo;
}

int callExprCodegen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel)
{
	c_tree fndecl = TREE_EXPR_OPERAND(tree,0);

	c_tree fnArguments = TREE_EXPR_OPERAND(tree,1);

	if (EXPR_LIST(fnArguments)->chain)
	{
		recurseExpressionList(EXPR_LIST(fnArguments)->chain, registerNo, FALSE,
				FALSE, breakLabel, continueLabel);
	}

	// call the function
	JSR(DECL_NAME_STRING(fndecl), "", "");

	// get the return value
	int returnValueReg = *registerNo;
	if (!topLevel)
	{
		returnValueReg = (*registerNo)++;
		LDRi(returnValueReg, R6, 0,
				"load the return value into register to return", NULL);
	}

	// unwind stack allocated for return and pushed variable
	int noOfArgs = 1;
	if (EXPR_LIST(fnArguments)->chain)
	{
		c_tree args = EXPR_LIST(fnArguments)->chain;
		while (args)
		{
			noOfArgs++;
			args = CHAIN_NEXT(args);
		}
	}
	ADDi(R6, R6, noOfArgs,
			"unwind stack allocated for return and pushed variable ", NULL);

	return returnValueReg;
}

void recurseExpressionList(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	if (tree)
	{
		recurseExpressionList(CHAIN_NEXT(tree), registerNo, topLevel,
				getAddress, breakLabel, continueLabel);
		c_tree argument = CHAIN_VALUE(tree);
		int functionArgumentReg = c_codegen_recurse(argument, registerNo,
				topLevel, getAddress, breakLabel, continueLabel);
		// push it on to stack
		ADDi(R6, R6, -1, "growing stack to push variable", NULL);
		STRi(functionArgumentReg, R6, 0, "pushing variable onto stack", NULL);
	}
}

int addrExprCodegen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel)
{
	return c_codegen_recurse(TREE_EXPR_OPERAND(tree,0), registerNo, topLevel,
			TRUE, breakLabel, continueLabel);
}

int indirectRefCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	c_tree op = TREE_EXPR_OPERAND(tree,0);
	if (!topLevel)
	{
		int pointerAddress = c_codegen_recurse(op,
				registerNo, topLevel, TRUE, breakLabel, continueLabel);
		if (getAddress)
		{
			int resultReg = (*registerNo)++;
			LDRi(resultReg, pointerAddress, 0,
					"get address stored in pointer variable", NULL);
			return resultReg;
		}
		else
		{
			int addressReg = (*registerNo)++;
			LDRi(addressReg, pointerAddress, 0,
					"get address stored in pointer variable", NULL);
			int resultReg = (*registerNo)++;
			LDRi(resultReg, addressReg, 0,
					"get value stored in pointer variable", NULL);
			return resultReg;
		}
	}
	else
	{
		c_codegen_recurse(op,
			registerNo, topLevel, FALSE, breakLabel, continueLabel);

		return *registerNo;
	}
}

int commaExprCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	c_tree expression = TREE_EXPR_OPERAND(tree,0);
	c_tree commaExpression = TREE_EXPR_OPERAND(tree,1);
	c_codegen_recurse(expression, registerNo, TRUE, getAddress, breakLabel,
			continueLabel);
	return c_codegen_recurse(commaExpression, registerNo, FALSE, getAddress,
			breakLabel, continueLabel);
}

