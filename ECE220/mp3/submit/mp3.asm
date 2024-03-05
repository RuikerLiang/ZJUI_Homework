
.ORIG x3000
	LDI R0, STARTING_NODE	;

	;ST R0, DIJ_TMP_R0	;
	;ST R1, DIJ_TMP_R1	;
	;ST R2, DIJ_TMP_R2	;
	;ST R3, DIJ_TMP_R3	;
	;ST R4, DIJ_TMP_R4	;
	;ST R5, DIJ_TMP_R5	;
	;ST R6, DIJ_TMP_R6	;
	JSR DIJKSTRA	;
	;LD R0, DIJ_TMP_R0	;
	;LD R1, DIJ_TMP_R1	;
	;LD R2, DIJ_TMP_R2	;
	;LD R3, DIJ_TMP_R3	;
	;LD R4, DIJ_TMP_R4	;
	;LD R5, DIJ_TMP_R5	;
	;LD R6, DIJ_TMP_R6	;
	LD R1, MINUS_ONE	;
	LDI R2, VECTOR_SIZE	;
	OUTPUT_VECTOR
		LD R6, STACK	;
		ADD R1, R1, #1	;
		JSR FILL_STACK	;
		JSR PRINT_PATH	;
		ADD R2, R2, #-1	;
		BRp OUTPUT_VECTOR
HALT

;	Input:	R4, R5
; Output:	R6 the index of distace from R4 to R5
GET_EDGE_ADDRESS
	ST R3, GDI_TMP_R3	;
	ST R4, GDI_TMP_R4	;
	ST R5, GDI_TMP_R5	;
	ST R7, GDI_TMP_R7	;
	LD R6, MATRIX	;
	LDI R3, VECTOR_SIZE	;
	ADD R4, R4, #0	;
	BRz END_MUL	;
	MUL_GET_DISTANCE_INDEX
		ADD R6, R6, R3	;
		ADD R4, R4, #-1	;
		BRp MUL_GET_DISTANCE_INDEX	;
	END_MUL	;
	ADD R6, R6, R5	;
	LD R3, GDI_TMP_R3	;
	LD R4, GDI_TMP_R4	;
	LD R5, GDI_TMP_R5	;
	LD R7, GDI_TMP_R7	;
	RET
GDI_TMP_R3 .BLKW #1
GDI_TMP_R4 .BLKW #1
GDI_TMP_R5 .BLKW #1
GDI_TMP_R7 .BLKW #1

;	Input:	R3, index of the elementk
HEAP_PUSH
	ST R0, HP_TMP_R0	;
	ST R1, HP_TMP_R1	;

	;	HEAP_SIZE = HEAP_SIZE + 1
	LDI R0, HEAP_SIZE	;
	ADD R0, R0, #1	;
	STI R0, HEAP_SIZE	;

	;	HEAP[HEAP_SIZE - 1] = new element
	ADD R0, R0, #-1	;
	LD R1, HEAP	;
	ADD R1, R0, R1	;
	STR R3, R1, #0	;

	;	INDICE[element] = HEAP_SIZE - 1
	LD R1, INDICE	;
	ADD R1, R3, R1	;
	STR R0, R1, #0	;

	LD R0, HP_TMP_R0	;
	LD R1, HP_TMP_R1	;
	RET
HP_TMP_R0 .BLKW #1
HP_TMP_R1 .BLKW #1

;	Input: R0, R1
;	Output: R2	dis[R0]
;					R3	dis[R1]
GET_DIS_FOR_TWO
	ST R6, GDFT_TMP_R6	;

	LD R6, DISTANCE	;
	ADD R6, R0, R6	;
	LDR R2, R6, #0	;

	LD R6, DISTANCE	;
	ADD R6, R1, R6	;
	LDR R3, R6, #0	;

	LD R6, GDFT_TMP_R6	;
	RET
GDFT_TMP_R6 .BLKW #1
;	Input: R0, starting noed
;	Used Register:
;		R1	temp register to calculate vector size
;				iterate the matrix when update the distance
;		R2	dis[R0]
;		R3	dis[R1]
DIJKSTRA
	ST R7, DIJ_TMP_R7	;
	LDI R1, VECTOR_SIZE	;
	ADD R1, R1, #-1	;
	INITIALIZE_PREDECESSOR
		;	Initialize Predecessor
		LD R2, PREDECESSOR	;
		ADD R2, R1, R2	;
		LD R3, MINUS_ONE	;
		STR R3, R2, #0	;
		;	Initialize Heap indices
		LD R2, INDICE	;
		ADD R2, R2, #0	;
		ADD R2, R1, R2	;
		LD R3, MINUS_ONE	;
		STR R3, R2, #0	;
		;	Initialize dis[i]
		LD R2, DISTANCE	;
		ADD R2, R1, R2	;
		LD R3, INFINITY	;
		STR R3, R2, #0	;
		ADD R1, R1, #-1	;
		BRzp INITIALIZE_PREDECESSOR	;


	;	set matrix[starting_node][starting_node] = 0
	ADD R4, R0, #0	;
	ADD R5, R0, #0	;
	JSR GET_EDGE_ADDRESS	;
	AND R1, R1, #0	;
	STR R1, R0, #0	;
	;	set dis[starting_node] = 0
	LD R4, DISTANCE	;
	ADD R4, R0, R4	;
	AND R5, R5, #0	;
	STR R5, R4, #0	;

	ADD R3, R0, #0	;
	JSR HEAP_PUSH	;

	JSR GET_CLOSEST	;
	HEAP_POP
		LDI R1, VECTOR_SIZE	;
		ADD R1, R1, #-1	;
		RELAXATION
			JSR GET_DIS_FOR_TWO	;

			ADD R4, R0, #0	;
			ADD R5, R1, #0	;
			JSR GET_EDGE_ADDRESS	;
			LDR R6, R6, #0	;
			ADD R6, R6, R2	;
			ADD R6, R6, #1	;
			BRn NEXT_EDGE	;

			ADD R6, R6, #-1	;
			NOT R3, R3	;
			ADD R3, R3, #1	;
			;	if (dis[R0] + edge >= dis[R1])
			;	dis[R0] + edge - dis[R1] >= 0
			ADD R3, R3, R6	;
			BRzp NEXT_EDGE	;
				;	dis[R1] = dis[R0] + edge (R6)
				LD R5, DISTANCE	;
				ADD R5, R5, R1	;
				STR R6, R5, #0	;
				;	pre[R1] = R0	;
				LD R5, PRE_NODE	;
				ADD R5, R1, R5	;
				STR R0, R5, #0	;


				;	if (!indices[R1])
				LD R5, INDICE	;
				ADD R5, R5, R1	;
				LDR R6, R5, #0	;
				BRzp NEXT_EDGE	;
					ADD R3, R1, #0	;
					JSR HEAP_PUSH	;
					ST R0, DIJ_TMP__	;
					LDI R0, HEAP_SIZE	;
					ADD R0, R0, #-1	;
					JSR PERCOLATE_UP	;
					LD R0, DIJ_TMP__	;
			NEXT_EDGE
			ADD R1, R1, #-1	;
			BRzp RELAXATION
		JSR GET_CLOSEST	;
		ADD R0, R0, #0	;
		BRzp HEAP_POP	;
	LD R7, DIJ_TMP_R7	;
	RET
STARTING_NODE	.FILL x3FFE
STACK					.FILL xC000
VECTOR_SIZE		.FILL x3FFF
MATRIX				.FILL x4000
PREDECESSOR		.FILL x5000
MINUS_ONE			.FILL #-1
INFINITY			.FILL x7FFF
PRE_NODE			.FILL x5000

DIJ_TMP__			.BLKW #1
DIJ_TMP_R1		.BLKW #1
DIJ_TMP_R0		.BLKW #1
DIJ_TMP_R2		.BLKW #1
DIJ_TMP_R3		.BLKW #1
DIJ_TMP_R4		.BLKW #1
DIJ_TMP_R5		.BLKW #1
DIJ_TMP_R6		.BLKW #1
DIJ_TMP_R7		.BLKW #1

;  ***** WRITE THE REQUIRED MP2 SUBROUTINES HERE *****
;  (also add a copy of your MP1 code to the bottom of the file)

; Swap the content in M[R2] and M[R3]
; R4, R5 used as temp register for swap
SWAP_ADDRESS
	ST R4, SWAP_TMP_R4	;
	ST R5, SWAP_TMP_R5	;
	LDR R4, R2, #0	;
	LDR R5, R3, #0	;
	STR R4, R3, #0	;
	STR R5, R2, #0	;
	LD R4, SWAP_TMP_R4	;
	LD R5, SWAP_TMP_R5	;
	RET
SWAP_TMP_R4 .BLKW #1
SWAP_TMP_R5 .BLKW #1

;	Swap the elements in R0 and R1
;	Input:	R0, R1 is two Heap index which needed to be swwapped
;	Register used:
;		R2 heap index of R0
;		R3 heap index of R1
;		R4 store address of Heap index arrary
;		R7 The returen address
SWAP_ELEMENTS
	ST R2, SE_TMP_R2	;
	ST R3, SE_TMP_R3	;
	ST R4, SE_TMP_R4	;
	ST R7, SE_TMP_R7	;
	;	Swap in Heap
	LD R2, HEAP	;
	LD R3, HEAP	;
	ADD R2, R2, R0	;
	ADD R3, R3, R1	;
	JSR SWAP_ADDRESS

	;	Swap in Heap index array
	LDR R2, R2, #0	;
	LDR R3, R3, #0	;
	LD R4, INDICE
	ADD R2, R4, R2	;
	ADD R3, R4, R3	;
	JSR SWAP_ADDRESS
	LD R2, SE_TMP_R2	;
	LD R3, SE_TMP_R3	;
	LD R4, SE_TMP_R4	;
	LD R7, SE_TMP_R7	;
	RET

;	Get the left child of R0
;	Input:	R0
;	Output:	R2
LEFT_CHILD
	ADD R2, R0, R0	;
	ADD R2, R2, #1	;
	RET
;	Get the right child of R0
;	Input:	R0
;	Output:	R3
RIGHT_CHILD
	ADD R3, R0, R0	;
	ADD R3, R3, #2	;
	RET
;	Get - Heap size
;	Output: R4
MINUS_HEAP_SIZE
	LDI R4, HEAP_SIZE	;
	NOT R4, R4	;
	ADD R4, R4, #1	;
	RET
;	Get distance of left child 
;	Output: R5
GET_DISTANCE_LEFT
	LD R4, HEAP	;
	ADD R5, R4, R2	;
	LDR R5, R5, #0	;
	LD R4, DISTANCE	;
	ADD R5, R4, R5	;
	LDR R5, R5, #0	;
	RET
;	Get distance of right child
;	Output: R6
GET_DISTANCE_RIGHT
	LD R4, HEAP	;
	ADD R6, R4, R3	;
	LDR R6, R6, #0	;
	LD R4, DISTANCE	;
	ADD R6, R4, R6	;
	LDR R6, R6, #0	;
	RET
;	Get distance of currnet element
;	Output: R1
GET_DISTANCE_CURRENT
	LD R4, HEAP	;
	ADD R1, R4, R0	;
	LDR R1, R1, #0	;
	LD R4, DISTANCE	;
	ADD R1, R4, R1	;
	LDR R1, R1, #0	;
	RET

HEAP_SIZE .FILL x7FFF
HEAP			.FILL x8000
INDICE		.FILL x7000
DISTANCE	.FILL x6000
INF				.FILL #-1

;	Percolate down current element to maintain Heap feature
;	Input:	R0	Current element index in Heap
;	Register used:
;		R1	Current element distance
;		R2	Left child index
;		R3	Right child index
;		R4	-L, L is the length of the Heap
;				Temp variable to store address of array
;		R5	Left child distance
;		R6	Right child distance
;		R7 Return address
PERCOLATE_DOWN
	ST R0, PD_TMP_R0	;
	ST R1, PD_TMP_R1	;
	ST R2, PD_TMP_R2	;
	ST R3, PD_TMP_R3	;
	ST R4, PD_TMP_R4	;
	ST R5, PD_TMP_R5	;
	ST R6, PD_TMP_R6	;
	ST R7, PD_TMP_R7	;

	NEXT_ROUND
	JSR LEFT_CHILD	;
	JSR RIGHT_CHILD	;

	;	R4 = -Heap size
	JSR MINUS_HEAP_SIZE
	;	R4 = Left child index - Heap size
	ADD R4, R4, R2	;

	BRzp PD_DONE

		;	R4 = Right child index - Heap Size
		JSR MINUS_HEAP_SIZE
		ADD R4, R4, R3	;
		BRzp JUDGE_LEFT

		;	R5 = Left child distance
		;	R6 = - Right child distance
		JSR GET_DISTANCE_LEFT	;
		JSR GET_DISTANCE_RIGHT	;
		NOT R6, R6	;
		ADD R6, R6, #1	;

		;	if 2X + 2 < L && distance(value(2X + 2)) < distance(value(2X + 1))
		;	goto JUDGE_LEFT
		ADD R6, R6, R5	;
		BRnz JUDGE_LEFT

		;	JUDGE_RIGHT
			JSR GET_DISTANCE_RIGHT	;
			JSR GET_DISTANCE_CURRENT	;

			;	R6 = - Right child distace
			NOT R6, R6	;
			ADD R6, R6, #1	;

			; R6 = Current element distance - Right child distance
			ADD R6, R6, R1	;
			BRnz PD_DONE
				ADD R1, R3, #0	;
				JSR SWAP_ELEMENTS	;
				ADD R0, R1, #0	;
				BRnzp NEXT_ROUND	;

		JUDGE_LEFT 
			JSR GET_DISTANCE_CURRENT	;
			JSR GET_DISTANCE_LEFT	;
			;	R5 = - Left child distance
			NOT R5, R5	;
			ADD R5, R5, #1	;
			ADD R5, R5, R1	;
			BRnz PD_DONE
				ADD R1, R2, #0	;
				JSR SWAP_ELEMENTS	;
				ADD R0, R1, #0	;
				BRnzp NEXT_ROUND	;

	PD_DONE
	LD R0, PD_TMP_R0	;
	LD R1, PD_TMP_R1	;
	LD R2, PD_TMP_R2	;
	LD R3, PD_TMP_R3	;
	LD R4, PD_TMP_R4	;
	LD R5, PD_TMP_R5	;
	LD R6, PD_TMP_R6	;
	LD R7, PD_TMP_R7	;
	RET


;	Output: R0 the samllest element
;	Register used:
;		R1	used to calculate Heap size and set -1 for index
;		R4	used to trace address
GET_CLOSEST
	ST R1, GC_TMP_R1	;
	ST R4, GC_TMP_R4	;
	ST R7, GC_TMP_R7	;
	LDI R4, HEAP_SIZE	;
	ADD R0, R4, #-1	;
	;	if the heap is not empty
	BRn GC_DONE
		;	R0 = first element
		LDI R0, HEAP	;
		;	set heap index of R0 to -1
		LD R4, INDICE	;
		ADD R4, R4, R0;
		LD R1, INF	;
		STR R1, R4, #0	;

		ST R0, GC_TMP_R0	;

		; heap[0] = heap[n - 1]
		LDI R1, HEAP_SIZE	;
		ADD R1, R1, #-1	;
		LD R4, HEAP	;
		ADD R4, R1, R4	;
		LDR R0, R4, #0	;
		LD R4, HEAP	;
		STR R0, R4, #0	;

		;	indice[heap[0]] = 0
		LD R4, INDICE	;
		ADD R4, R4, R0	;
		AND R0, R0, #0	;
		STR R0, R4, #0	;

		LDI R4, HEAP_SIZE	;
		ADD R0, R4, #-1	;
		STI R0, HEAP_SIZE	;
		AND R0, R0, #0	;

		LD R0, GC_TMP_R0	;
		JSR PERCOLATE_DOWN	;

	GC_DONE
	LD R1, GC_TMP_R1	;
	LD R4, GC_TMP_R4	;
	LD R7, GC_TMP_R7	;
	RET

SE_TMP_R3	.BLKW #1
SE_TMP_R2	.BLKW #1
SE_TMP_R4	.BLKW #1
SE_TMP_R7	.BLKW #1
PD_TMP_R0	.BLKW #1
PD_TMP_R1 .BLKW #1
PD_TMP_R2 .BLKW #1
PD_TMP_R3 .BLKW #1
PD_TMP_R4 .BLKW #1
PD_TMP_R5 .BLKW #1
PD_TMP_R6 .BLKW #1
PD_TMP_R7	.BLKW #1
GC_TMP_R0 .BLKW #1
GC_TMP_R1 .BLKW #1
GC_TMP_R4 .BLKW #1
GC_TMP_R7 .BLKW #1

PERCOLATE_UP
; Percolates the heap element with index given by R0 upward in the heap if necessary.
; Heap stores node numbers and is sorted by distance (smallest first).  Distances
; are stored in a separate table.  Uses SWAP_ELEMENTS to swap heap elements during
; percolation, so this subroutine does not need the heap index array.
;   INPUT: R0 -- the index of the heap element to percolate upward
;          M[x7FFF] -- the heap length
;          M[x8000..] -- a heap with length at M[x7FFF] and contents starting at M[x8000]
;            (each heap element consists of one memory location and holds a node number)
;          M[x6000..] -- an array of node distances, indexed by node number
;   OUTPUT: a modified heap and array of heap indices (latter modified by SWAP_ELEMENTS)
;   REGISTERS: All registers except R7 are callee-saved.
;   NOTES: modifies heap and array of heap indices
;          IMPLICITLY ASSUMES that heap elements are valid (< length of heap) and that
;            nodes in the heap are not at distance INFINITY (x7FFF)
;          For N > 0, parent of node N is ((N - 1) >> 1) = floor ((N - 1) / 2)

; Registers are used as follows:
;   R0 - heap element to percolate up if necessary
;   R1 - heap element index of parent
;   R2 - points to heap
;   R3 - points to node distance array
;   R4 - element distance
;   R5 - parent distance
	ST R0,PU_R0	; Save callee-saved registers.
	ST R1,PU_R1
	ST R2,PU_R2
	ST R3,PU_R3
	ST R4,PU_R4
	ST R5,PU_R5
	ST R7,PU_R7
	LD R2,PU_HEAP	; Get pointers to heap and distance arrays.
	LD R3,PU_DIST
	
PU_NEXT	ADD R0,R0,#0	; Can't move root up.
	BRz PU_DONE
	ADD R4,R2,R0	; Get element distance in R4.
	LDR R4,R4,#0
	ADD R4,R4,R3
	LDR R4,R4,#0
	JSR FIND_PARENT	; Find parent element index in R1.
	ADD R5,R2,R1	; Get parent distance in R5.
	LDR R5,R5,#0
	ADD R5,R5,R3
	LDR R5,R5,#0
	; Need to percolate up if parent distance is larger.
	; Compute (parent distance - element distance - 1) in R4.
	; NOTE: ASSUMES THAT ELEMENTS IN HEAP ARE NOT AT INFINITY
	NOT R4,R4
	ADD R4,R4,R5
	BRn PU_DONE
	; Swaps heap elements in R0 and R1 (in heap and in heap index array).
	JSR SWAP_ELEMENTS
	ADD R0,R1,#0	; Try again with parent.
	BRnzp PU_NEXT

PU_DONE	LD R0,PU_R0	; Restore callee-saved registers.
	LD R1,PU_R1
	LD R2,PU_R2
	LD R3,PU_R3
	LD R4,PU_R4
	LD R5,PU_R5
	LD R7,PU_R7
	RET

PU_HEAP	.FILL x8000
PU_DIST	.FILL x6000
PU_R0	.BLKW #1
PU_R1	.BLKW #1
PU_R2	.BLKW #1
PU_R3	.BLKW #1
PU_R4	.BLKW #1
PU_R5	.BLKW #1
PU_R7	.BLKW #1

;  ***** PUT A COPY OF YOUR MP1 CODE HERE *****

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
TMP_R0 .BLKW #1
TMP_R7 .BLKW #1

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
TMP_R1 .BLKW #1
TMP_R2 .BLKW #1
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