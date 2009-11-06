/*
 * c-asmgen.c
 *
 *  Created on: Sep 16, 2009
 *      Author: yogesh
 */

#include "c-asmgen.h"
#include "macros.h"
#include <string.h>
#include <stdio.h>

extern FILE* outputFile;

void ORIG()
{
	FPRINTF(outputFile,"\t.ORIG  x2000\n");
}

void HALT()
{
	FPRINTF(outputFile,"\tHALT\n");
}

void END()
{
	FPRINTF(outputFile,"\t.END\n");
}

void CINASM(const char *comment, const char* label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tIN ;%s\n", comment ? comment : "");
}

void COUTASM(const char *comment, const char* label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tOUT ;%s\n", comment ? comment : "");
}

void ADDi(int Rx, int Ry, int immi, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tADD R%d, R%d, %d ;%s\n", Rx, Ry, immi,comment ? comment : "");
}

void ADD(int Rx, int Ry, int Rz, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tADD R%d, R%d, R%d ;%s\n", Rx, Ry, Rz,comment ? comment : "");
}

void ANDi(int Rx, int Ry, int immi, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tAND R%d, R%d, %d ;%s\n", Rx, Ry, immi,comment ? comment : "");
}

void AND(int Rx, int Ry, int Rz, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tAND R%d, R%d, R%d ;%s\n", Rx, Ry, Rz,comment ? comment : "");
}

void ANDL(int Rx, int Ry, int Rz, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tANDL R%d, R%d, R%d ;%s\n", Rx, Ry, Rz,comment ? comment : "");
}

void ANDLi(int Rx, int Ry, int immi, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tANDL R%d, R%d, R%d ;%s\n", Rx, Ry, immi,comment ? comment : "");
}

void BRnzp(int Rx,const char* LABEL, const char *comment, const char *label, char *condition)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tBR%s R%d, %s ;%s\n", condition, Rx, LABEL,comment ? comment : "");
}

void BRA(const char *LABEL, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tBRA %s ;%s\n", LABEL,comment ? comment : "");
}

void DIV(int Rx, int Ry, int Rz, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tDIV R%d, R%d, R%d ;%s\n", Rx, Ry, Rz,comment ? comment : "");
}

void DIVi(int Rx, int Ry, int immi, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tDIV R%d, R%d, %d ;%s\n", Rx, Ry, immi,comment ? comment : "");
}

void JSR(const char *LABEL, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tJSR %s ;%s\n", LABEL,comment ? comment : "");
}

void LDR(int Rx, int Ry, int Rz, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tLDR R%d, R%d, R%d ;%s\n", Rx, Ry, Rz,comment ? comment : "");
}

void LDRi(int Rx, int Ry, int immi, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tLDR R%d, R%d, %d ;%s\n", Rx, Ry, immi,comment ? comment : "");
}

void MUL(int Rx, int Ry, int Rz, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tMUL R%d, R%d, R%d ;%s\n", Rx, Ry, Rz,comment ? comment : "");
}

void MULi(int Rx, int Ry, int immi, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tMUL R%d, R%d, %d ;%s\n", Rx, Ry, immi,comment ? comment : "");
}

void NOP(const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tNOP ;%s\n",comment ? comment : "");
}

void NOT(int Rx, int Ry, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tNOT R%d, R%d ;%s\n", Rx, Ry,comment ? comment : "");
}

void NOTL(int Rx, int Ry, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tNOTL R%d, R%d ;%s\n", Rx, Ry,comment ? comment : "");
}

void OR(int Rx, int Ry, int Rz, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tOR R%d, R%d, R%d ;%s\n", Rx, Ry, Rz,comment ? comment : "");
}

void ORL(int Rx, int Ry, int Rz, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tOR R%d, R%d, R%d ;%s\n", Rx, Ry, Rz,comment ? comment : "");
}

void ORLi(int Rx, int Ry, int immi, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tOR R%d, R%d, R%d ;%s\n", Rx, Ry,immi,comment ? comment : "");
}

void ORi(int Rx, int Ry, int immi, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tOR R%d, R%d, %d ;%s\n", Rx, Ry, immi,comment ? comment : "");
}

void RET(const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tRET  ;%s\n",comment ? comment : "");
}

void SET(int Rx, int immi, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tSET R%d, %d ;%s\n", Rx, immi,comment ? comment : "");
}

void STR(int Rx, int Ry, int Rz, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tSTR R%d, R%d, R%d ;%s\n", Rx, Ry, Rz,comment ? comment : "");
}

void STRi(int Rx, int Ry, int immi, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tSTR R%d, R%d, %d ;%s\n", Rx, Ry, immi,comment ? comment : "");
}

void SUB(int Rx, int Ry, int Rz, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tSUB R%d, R%d, R%d ;%s\n", Rx, Ry, Rz,comment ? comment : "");
}

void SUBi(int Rx, int Ry, int immi, const char *comment, const char *label)
{
	if (label && strlen(label)>0)
		FPRINTF(outputFile,"%s:", label);
	FPRINTF(outputFile,"\tSUB R%d, R%d, %d ;%s\n", Rx, Ry, immi,comment ? comment : "");
}

