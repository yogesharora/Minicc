/*
 * c-asmgen.h
 *
 *  Created on: Sep 13, 2009
 *      Author: yogesh
 */

#ifndef CASMGEN_H_
#define CASMGEN_H_

void ORIG();

void HALT();

void END();

void CINASM(const char *comment, const char* label);

void COUTASM(const char *comment, const char* label);

void ADDi(int Rx, int Ry, int immi, const char *comment, const char *label);

void ADD(int Rx, int Ry, int Rz, const char *comment, const char *label);

void ANDi(int Rx, int Ry, int immi, const char *comment, const char *label);

void AND(int Rx, int Ry, int Rz, const char *comment, const char *label);

void ANDL(int Rx, int Ry, int Rz, const char *comment, const char *label);

void ANDLi(int Rx, int Ry, int immi, const char *comment, const char *label);

void BRnzp(int Rx, const char* LABEL, const char *comment, const char *label,char *condition);

void BRA(const char *LABEL, const char *comment, const char *label);

void DIV(int Rx, int Ry, int Rz, const char *comment, const char *label);

void DIVi(int Rx, int Ry, int immi, const char *comment, const char *label);

void JSR(const char *LABEL, const char *comment, const char *label);

void LDR(int Rx, int Ry, int Rz, const char *comment, const char *label);

void LDRi(int Rx, int Ry, int immi, const char *comment, const char *label);

void MUL(int Rx, int Ry, int Rz, const char *comment, const char *label);

void MULi(int Rx, int Ry, int immi, const char *comment, const char *label);

void NOP(const char *comment, const char *label);

void NOT(int Rx, int Ry, const char *comment, const char *label);

void NOTL(int Rx, int Ry, const char *comment, const char *label);

void OR(int Rx, int Ry, int Rz, const char *comment, const char *label);

void ORL(int Rx, int Ry, int Rz, const char *comment, const char *label);

void ORLi(int Rx, int Ry, int immi, const char *comment, const char *label);

void ORi(int Rx, int Ry, int immi, const char *comment, const char *label);

void RET(const char *comment, const char *label);

void SET(int Rx, int immi, const char *comment, const char *label);

void STR(int Rx, int Ry, int Rz, const char *comment, const char *label);

void STRi(int Rx, int Ry, int immi, const char *comment, const char *label);

void SUB(int Rx, int Ry, int Rz, const char *comment, const char *label);

void SUBi(int Rx, int Ry, int immi, const char *comment, const char *label);

#endif /* CASMGEN_H_ */
