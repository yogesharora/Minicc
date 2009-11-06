/*
 * c-codegen-stmt.h
 *
 *  Created on: Sep 21, 2009
 *      Author: yogesh
 */

#ifndef CCODEGENSTMT_H_
#define CCODEGENSTMT_H_

#include "c-tree.h"

int ifCodeGen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel);

int forCodeGen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel);

int whileCodeGen(c_tree tree, int *registerNo, int topLevel, int getAddress,
		const char *breakLabel, const char *continueLabel);

void breakCodeGen(const char* breakLabel);

void continueCodeGen(const char* continueLabel);

#endif /* CCODEGENSTMT_H_ */
