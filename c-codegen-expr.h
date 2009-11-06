/*
 * c-codegen-expr.h
 *
 *  Created on: Sep 17, 2009
 *      Author: yogesh
 */

#ifndef CCODEGENEXPR_H_
#define CCODEGENEXPR_H_

#include "c-tree.h"

int exprCodeGen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel);

#endif /* CCODEGENEXPR_H_ */
