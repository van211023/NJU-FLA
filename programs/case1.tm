; This case program cyclic shift right 
; Input: a string of 0's and 1's, e.g. '1001001'

; the finite set of states
#Q = {0,mr,ml,ml2,cp,cp1,cp2,halt}

; the finite set of input symbols
#S = {0,1}

; the complete set of tape symbols
#G = {0,1,_,t,r,u,e,f,a,l,s}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt}

; the number of tapes
#N = 2

; the transition functions

; State 0: start state
0 1_ 1_ ** mr
0 0_ 0_ ** mr
0 __ __ ** halt ; empty input

; state mr: move 1st head to the right
mr 1_ 1_ r* mr
mr 0_ 0_ r* mr
mr __ __ l* cp1

; state cp1: copy last sym of 1st tape to the 2nd
cp1 1_ _1 lr ml
cp1 0_ _0 lr ml

; state ml: move 1st head to the left
ml 1_ 1_ l* ml
ml 0_ 0_ l* ml
ml __ __ r* cp

; state cp: copy the remaining syms of 1st tape to the 2nd
cp 1_ 11 rr cp
cp 0_ 00 rr cp
cp __ __ ll ml2

; state ml2: move two heads to the left
ml2 __ __ rr cp2
ml2 *_ *_ l* ml2
ml2 _* _* *l ml2
ml2 ** ** ll ml2

; state cp2: copy 2nd tape to the 1st
cp2 *1 11 rr cp2
cp2 *0 00 rr cp2
cp2 _1 11 rr cp2
cp2 _0 00 rr cp2
cp2 __ __ ll halt