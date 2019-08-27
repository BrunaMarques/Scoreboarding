# verifica se o número é par
# se é, armazena o número em $ra
# se não é, coloca zero em $ra
# o previsor irá acertar pois o número é par
addi $t0, $zero, 2   #fetch 2
addi $t1, $zero, 4 #fetch X
div $t1, $t0
mfhi $t2
add $s0, $zero, $t1
bgez $t2, par
# add $s0, $zero, $zero
par: