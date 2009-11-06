/*
 * c-codegen-func.h
 *
 *  Created on: Sep 14, 2009
 *      Author: yogesh
 */

#ifndef CCODEGENFUNC_H_
#define CCODEGENFUNC_H_

#include "c-tree.h"

int funcCodegen(c_tree func, int *registerNo, int getAddress,
		const char *breakLabel, const char *continueLabel);

int returnCodegen(c_tree func, int *registerNo, int getAddress,
		const char *breakLabel, const char *continueLabel);

#endif /* CCODEGENFUN_H_ */
