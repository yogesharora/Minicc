	.ORIG  x2000
	JSR MAIN ;
	HALT
main:	ADD R6, R6, -1 ;allocate space for return value which will be popped by calling function
	ADD R6, R6, -1 ;allocate space for storing return address
	STR R7, R6, 0 ;push the return address into allocated space
	ADD R6, R6, -1 ;allocate space for storing frame pointer of caller
	STR R5, R6, 0 ;push the frame pointer of the caller
	ADD R5, R6, -1 ;Calculate the new frame pointer
	ADD R6, R6, -13 ;Allocate space for the locals
	IN ;
	ADD R8, R5, -1 ;get address of local variable
	STR R0, R8, 0 ;assignment
	SET R9, 0 ;integer constant
	ADD R10, R5, -2 ;get address of local variable
	STR R9, R10, 0 ;assignment
	SET R11, 0 ;integer constant
	ADD R12, R5, 0 ;get address of local variable
	STR R11, R12, 0 ;assignment
CFOR0:	NOP ;condition of for
	SET R13, 1 ;comparison expression result register intial value true
	LDR R14, R5, 0 ;load a local variable
	SUB R15, R14, 10 ;comparison expression subtract c=a-b
	BRn R15, COMP0 ;comparison expression branch on condition
	SET R13, 0 ;comparison expression false value
COMP0:	NOP ;comparison expression just to create a label
	BRz R13, EFOR0 ;branch on for condition
	SET R16, 10 ;integer constant
	ADD R17, R5, -12 ;starting address of local array
	SET R18, 0 ;integer constant
	ADD R19, R17, R18 ;getting address of array at index location
	STR R16, R19, 0 ;assignment
	ADD R20, R5, -12 ;starting address of local array
	SET R21, 0 ;integer constant
	LDR R22, R20, R21 ;load the array value into register
	ADD R0, R22, 0 ;copying into R0
	OUT ;Displaying to COUT
RFOR0:	NOP ;re-init of for loop
	LDR R23, R5, 0 ;load a local variable
	ADD R24, R23, 1 ;
	ADD R25, R5, 0 ;get address of local variable
	STR R24, R25, 0 ;assignment
	BRA CFOR0 ;go back to for condition check
EFOR0:	NOP ;end of for
	SET R26, 0 ;integer constant
	ADD R27, R5, 0 ;get address of local variable
	STR R26, R27, 0 ;assignment
CFOR1:	NOP ;condition of for
	SET R28, 1 ;comparison expression result register intial value true
	LDR R29, R5, 0 ;load a local variable
	LDR R31, R5, -1 ;load a local variable
	SUB R30, R29, R31 ;comparison expression subtract c=a-b
	BRn R30, COMP1 ;comparison expression branch on condition
	SET R28, 0 ;comparison expression false value
COMP1:	NOP ;comparison expression just to create a label
	BRz R28, EFOR1 ;branch on for condition
	LDR R32, R5, -1 ;load a local variable
	ADD R33, R5, -12 ;starting address of local array
	LDR R34, R5, 0 ;load a local variable
	LDR R35, R33, R34 ;load the array value into register
	ADD R36, R32, R35 ;
	ADD R37, R5, -12 ;starting address of local array
	LDR R38, R5, 0 ;load a local variable
	ADD R39, R37, R38 ;getting address of array at index location
	STR R36, R39, 0 ;assignment
	ADD R40, R5, -12 ;starting address of local array
	LDR R41, R5, 0 ;load a local variable
	LDR R42, R40, R41 ;load the array value into register
	ADD R0, R42, 0 ;copying into R0
	OUT ;Displaying to COUT
RFOR1:	NOP ;re-init of for loop
	LDR R43, R5, 0 ;load a local variable
	ADD R44, R43, 1 ;
	ADD R45, R5, 0 ;get address of local variable
	STR R44, R45, 0 ;assignment
	BRA CFOR1 ;go back to for condition check
EFOR1:	NOP ;end of for
	SET R46, 0 ;integer constant
	ADD R47, R5, 0 ;get address of local variable
	STR R46, R47, 0 ;assignment
CFOR2:	NOP ;condition of for
	SET R48, 1 ;comparison expression result register intial value true
	LDR R49, R5, 0 ;load a local variable
	LDR R51, R5, -1 ;load a local variable
	SUB R50, R49, R51 ;comparison expression subtract c=a-b
	BRn R50, COMP2 ;comparison expression branch on condition
	SET R48, 0 ;comparison expression false value
COMP2:	NOP ;comparison expression just to create a label
	BRz R48, EFOR2 ;branch on for condition
	LDR R52, R5, -2 ;load a local variable
	ADD R53, R5, -12 ;starting address of local array
	LDR R54, R5, 0 ;load a local variable
	LDR R55, R53, R54 ;load the array value into register
	ADD R56, R52, R55 ;
	ADD R57, R5, -2 ;get address of local variable
	STR R56, R57, 0 ;assignment
	LDR R58, R5, -2 ;load a local variable
	ADD R0, R58, 0 ;copying into R0
	OUT ;Displaying to COUT
RFOR2:	NOP ;re-init of for loop
	LDR R59, R5, 0 ;load a local variable
	ADD R60, R59, 1 ;
	ADD R61, R5, 0 ;get address of local variable
	STR R60, R61, 0 ;assignment
	BRA CFOR2 ;go back to for condition check
EFOR2:	NOP ;end of for
	LDR R62, R5, -2 ;load a local variable
	ADD R0, R62, 0 ;copying into R0
	OUT ;Displaying to COUT
	SET R63, 0 ;integer constant
	STR R63, R5, 3 ;store return values
	BRA EPI0 ;branching to epilogue
EPI0:	ADD R6, R6, 13 ;unwind stack, deallocate locals
	LDR R5, R6, 0 ;get the frame pointer
	ADD R6, R6, 1 ;
	LDR R7, R6, 0 ;get the return address
	ADD R6, R6, 1 ;leave the return value on stack
	RET  ;
	.END
