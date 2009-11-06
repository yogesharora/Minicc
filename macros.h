/*
 * macros.h
 *
 *  Created on: Sep 16, 2009
 *      Author: yogesh
 */

#ifndef MACROS_H_
#define MACROS_H_
#include <stdio.h>

#define VERBOSE

#ifdef VERBOSE
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF( ...)
#endif

#define FPRINTF(...) fprintf(__VA_ARGS__)


#define TRUE 1
#define FALSE 0

#define CIN "cin"
#define COUT "cout"
#define LABEL_ARRAY_LENGTH 20

enum {
	R0=0,
	R1,
	R2,
	R3,
	R4,
	R5, // frame pointer
	R6, // stack pointer
	R7, // return address pointer
	LastSystemRegister,
}registers;
#endif /* MACROS_H_ */
