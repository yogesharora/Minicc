	.ORIG  x2000
	JSR MAIN ;
	HALT
main:	ADD R6, R6, -1 ;allocate space for return value which will be popped by calling function
	ADD R6, R6, -1 ;allocate space for storing return address
	STR R7, R6, 0 ;push the return address into allocated space
	ADD R6, R6, -1 ;allocate space for storing frame pointer of caller
	STR R5, R6, 0 ;push the frame pointer of the caller
	ADD R5, R6, -1 ;Calculate the new frame pointer
	ADD R6, R6, -205 ;Allocate space for the locals
	SET R8, 10 ;integer constant
	ADD R9, R5, -1 ;get address of local variable
	ADD R10, R9, 0 ;struct member address
	STR R8, R10, 0 ;assignment
	SET R11, 1 ;integer constant
	ADD R12, R5, -1 ;get address of local variable
	ADD R13, R12, 1 ;struct member address
	STR R11, R13, 0 ;assignment
	ADD R14, R5, -1 ;get address of local variable
	ADD R15, R5, -2 ;get address of local variable
	STR R14, R15, 0 ;assignment
	ADD R16, R5, -2 ;get address of local variable
	ADD R17, R5, -3 ;get address of local variable
	STR R16, R17, 0 ;assignment
	ADD R18, R5, -3 ;get address of local variable
	ADD R19, R5, -4 ;get address of local variable
	STR R18, R19, 0 ;assignment
	SET R20, 0 ;integer constant
	STR R20, R5, 3 ;store return values
	BRA EPI0 ;branching to epilogue
EPI0:	ADD R6, R6, 205 ;unwind stack, deallocate locals
	LDR R5, R6, 0 ;get the frame pointer
	ADD R6, R6, 1 ;
	LDR R7, R6, 0 ;get the return address
	ADD R6, R6, 1 ;leave the return value on stack
	RET  ;
	.END
