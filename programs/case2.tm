; judge perfect square num
; Input: a stirng of 1's, e.g. '11111' 

; the finite set of states
#Q = {0,sub,ml2,increase,increase1,reject,reject1,reject2,reject3,reject4,halt_reject,accept,accept1,accept2,accept3,halt_accept}

; the finite set of input symbols
#S = {1}

; the complete set of tape symbols
#G = {1,_,t,r,u,e,f,a,l,s}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the number of tapes
#N = 2

; the transition functions
0 1_ 11 ** sub
0 __ __ ** accept

; state sub: 1st tape sub 2nd tape
sub 11 _1 rr sub
sub 1_ 1_ ** increase ;increase 2nd tape by 2
sub _1 _1 ** reject ; 2nd tape last 
sub __ __ ** accept

; state increase: increase 2nd tape by 2
increase 1_ 11 *r increase1
increase1 1_ 11 ** ml2

; state ml2: move 2nd head to the left
ml2 11 11 *l ml2
ml2 1_ 1_ *r sub


; state accept: print true in 1st tape
accept __ t_ r* accept1
accept1 __ r_ r* accept2
accept2 __ u_ r* accept3
accept3 __ e_ ** halt_accept 

; state reject: print false in 2nd tape
reject _1 f1 r* reject1
reject1 _1 a1 r* reject2
reject2 _1 l1 r* reject3
reject3 _1 s1 r* reject4
reject4 _1 e1 ** halt_reject