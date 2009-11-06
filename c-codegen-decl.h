/*
 * c-codegen-decl.h
 *
 *  Created on: Sep 19, 2009
 *      Author: yogi
 */

#ifndef CCODEGENDECL_H_
#define CCODEGENDECL_H_

#include "c-tree.h"

int declCodeGen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel);

#endif /* CCODEGENDECL_H_ */
