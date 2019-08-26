add $t0, $zero, $zero
nor $S5, $S6, $S7
or $t1, $t2, $t3
xor $gp, $SP, $T5
madd $v0, $V1
msub $T0, $t1
andi $S0, $s4, 1
lui $AT, 2
ori $FP, $RA, 7
xori $V0, $V1, 0
add $t0, $zero, $zero
and $T0, $T1, $T2
addi $T0, $T1, 10
div $T3, $T0
mfhi $t1
mflo $t2
movn $s1, $a2, $s0
movz $ZERO, $t0, $t1
mthi $t0
mtlo $k1
mult $T8, $T9
mul $S1, $t1, $t4
sub $T3, $s0, $s1
# b a
# a:
# beq $s0, $s1, b
# b:
# beql $t3, $t4, c
# c:
# bgez $t0, aaa
# aaa:
# bgtz $t2, d
# d:
# blez $t4, e
# e:
# bltz$t1, oi
# oi:
# bne $t0, $t1, f
# f:
# j j
# j:
# jr $t0
# nop