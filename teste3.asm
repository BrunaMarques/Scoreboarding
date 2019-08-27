addi $t0, $zero, 10 #i
addi $t1, $zero, 14 #N
sub $t2, $t0, $t1 #i-N
blez $t2, skip #se (i-N)< 0  pula
addi $t3, $zero, 5 # A = 5
skip: