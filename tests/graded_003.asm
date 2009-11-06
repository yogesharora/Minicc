	.ORIG  x2000
	JSR MAIN ;
	HALT
foo:	ADD R6, R6, -1 ;allocate space for return value which will be popped by calling function
	ADD R6, R6, -1 ;allocate space for storing return address
	STR R7, R6, 0 ;push the return address into allocated space
	ADD R6, R6, -1 ;allocate space for storing frame pointer of caller
	STR R5, R6, 0 ;push the frame pointer of the caller
	ADD R5, R6, -1 ;Calculate the new frame pointer
	LDR R8, R5, 4 ;load a local variable
	STR R8, R5, 3 ;store return values
	BRA EPI0 ;branching to epilogue
EPI0:	LDR R5, R6, 0 ;get the frame pointer
	ADD R6, R6, 1 ;
	LDR R7, R6, 0 ;get the return address
	ADD R6, R6, 1 ;leave the return value on stack
	RET  ;
main:	ADD R6, R6, -1 ;allocate space for return value which will be popped by calling function
	ADD R6, R6, -1 ;allocate space for storing return address
	STR R7, R6, 0 ;push the return address into allocated space
	ADD R6, R6, -1 ;allocate space for storing frame pointer of caller
	STR R5, R6, 0 ;push the frame pointer of the caller
	ADD R5, R6, -1 ;Calculate the new frame pointer
	ADD R6, R6, -2 ;Allocate space for the locals
	IN ;
	ADD R8, R5, 0 ;get address of local variable
	STR R0, R8, 0 ;assignment
	LDR R9, R5, 0 ;load a local variable
	ADD R6, R6, -1 ;growing stack to push variable
	STR R9, R6, 0 ;pushing variable onto stack
	JSR foo ;
	LDR R10, R6, 0 ;load the return value into register to return
	ADD R6, R6, 2 ;unwind stack allocated for return and pushed variable
	ADD R11, R5, -1 ;get address of local variable
	STR R10, R11, 0 ;assignment
	LDR R12, R5, -1 ;load a local variable
	ADD R0, R12, 0 ;copying into R0
	OUT ;Displaying to COUT
	SET R13, 0 ;integer constant
	STR R13, R5, 3 ;store return values
	BRA EPI1 ;branching to epilogue
EPI1:	ADD R6, R6, 2 ;unwind stack, deallocate locals
	LDR R5, R6, 0 ;get the frame pointer
	ADD R6, R6, 1 ;
	LDR R7, R6, 0 ;get the return address
	ADD R6, R6, 1 ;leave the return value on stack
	RET  ;
	.END
