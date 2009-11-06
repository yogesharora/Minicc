/*
 * s3inst.h
 *
 *  Created on: Sep 17, 2009
 *      Author: yogesh
 */

#ifndef S3INST_H_
#define S3INST_H_

typedef struct inst_st
{
	int opcode; // e.g., AND, ADD, LDR
	int predicate; // Not used for this project . . .
	int nzp; // for branch instructions
	int addr;
	int index16;
	int destreg;
	int src1;
	int src2;
	int exp_reg; // See note below
	char *label;
	char *comment; // reminder of where the instruction came from
	struct inst_st *next; // for linked list building
} S3inst;

#endif /* S3INST_H_ */
