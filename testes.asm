add $t0, $zero, $zero
and $T0, $T1, $T2
div $T3, $T4
jr $s0
mfhi $s1
mflo $S6
movn $A1, $a2, $A3
movz $ZERO, $Z0, $AT
mthi $K0
mtlo $k1
mult $T8, $T9
nop
nor $S5, $S6, $S7
or $t1, $t2, $t3
sub $T3, $s0, $a2
xor $gp, $SP, $T5
madd $v0, $V1
msub $T0, $t1
mul $S1, $t1, $t4
addi $T0, $T1, 0
andi $S0, $s4, 1
b 4
beq $T1, $T6, 2
beql $S1, $S2, 5
bgtz $T8, 6
blez $T9, 10
bne $T1, $S3, 7
lui $AT, 2
ori $FP, $RA, 7
xori $V0, $V1, 0
j 1
bgez $Z0, 0
bltz $ZERO, 1