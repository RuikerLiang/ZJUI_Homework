.ORIG x3000
; @SUBROUTINE1
; Calculate P = [(E - 1) / 2]
; input R0 as E
; output R1 as P
;
; Rigister used:
; R0	Sotre the value E and used in the process of calculating
; R1	Sotre the answer P
; R7	Store the return memory location
FIND_PARENT
	ST R7, TMP_R7 ;
	ST R0, TMP_R0 ;
	AND R1, R1, #0 ;
	; R0 <- E - 1
	ADD R0, R0, #-1 ;
	; Calculate R0 / 2
	LOOP_DIVISION
		ADD R1, R1, #1 ;
		ADD R0, R0, #-2 ;
		BRzp LOOP_DIVISION ;
	ADD R1, R1, #-1 ;
	LD R0, TMP_R0 ;
	LD R7, TMP_R7 ;
	RET ;
TMP_R0 .BLKW 1
TMP_R7 .BLKW 1

; @SUBROUTINE2
; Push the path to the stack
; The begin labeled with sentinel
; input:	R1 is the end node in the path
;					R6 is the begin memory location of stack
; output:	R6 memory location of the top of the stack 
;
; Rigister used:
;	R1 the end node in the path
; R2 memory location of the table
; R7 the return location
FILL_STACK
	ST R7, TMP_R7 ;
	ST R1, TMP_R1 ;
	ST R2, TMP_R2 ;
	LD R2, END ;
	; store sentinel value -1
	ADD R6, R6, #-1 ;
	STR R2, R6, #0 ;
	; store the path
	LOOP_FILL_STACK
		LD R2, TABLE ;
		ADD R6, R6, #-1 ;
		STR R1, R6, #0 ;
		ADD R2, R2, R1 ;
		; R1 <- Table[R1] to get to the fromer node
		LDR R1, R2, #0 ;
		BRzp LOOP_FILL_STACK ;
	LD R2, TMP_R2 ;
	LD R1, TMP_R1 ;
	LD R7, TMP_R7 ;
	RET
TABLE .FILL x5000
TMP_R1 .BLKW 1
TMP_R2 .BLKW 1
END .FILL xFFFF

; @SUBROUTINE3
; Ouput and pop all elements in the stack
; input:	R6 memory location of the stack
; output:	R6 the top of the stack
;					path to the screen
;
; Rigister used
; R0 character to be outputed
; R1 character 'A', used to transform number to charater
; R6 top of the stack
; R7 return memory location
PRINT_PATH
	ST R0, TMP_R0 ;
	ST R1, TMP_R1 ;
	ST R7, TMP_R7 ;
	LD R1, TRANS ;
	; special handling first element
	ADD R6, R6, #1 ;
	LDR R0, R6, #-1 ;
	BRn END_PRINT ;
	ADD R0, R0, R1 ;
	OUT
	; for the following elements in the stack
	LOOP_PRINT
		; pop the top element
		ADD R6, R6, #1 ;
		LDR R0, R6, #-1 ;
		; check if reach the sentinel value
		BRn END_PRINT
		; output "->"
		LEA R0, LINK ;
		PUTS ;
		LDR R0, R6, #-1 ;
		ADD R0, R0, R1 ;
		OUT ;
		BR LOOP_PRINT
	END_PRINT
	; all elements in the stack are poped out and printed
	; print a endline
	LD R0, ENDL ;
	OUT ;
	LD R0, TMP_R0 ;
	LD R1, TMP_R1 ;
	LD R7, TMP_R7 ;
	RET ;
LINK .STRINGZ "->"
TRANS .FILL x0041 ;	Charater 'A'
ENDL .FILL #10 ;
.END
