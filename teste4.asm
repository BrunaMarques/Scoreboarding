addi $t0, $zero, 2      # i = 5
addi $s0, $zero, 3      # A = 3
add $s1, $zero, $s0     # aux = A
addi $t1, $zero, 0      # switch 0
addi $t2, $zero, 1      # switch 1
addi $t3, $zero, 2      # switch 2
add $s0, $zero, $t1     # a = 0
beq $t0, $t1, break     # pula se i = case 0
add $s0, $zero, $s1     # A = aux
beq $t0, $t2, break     # pula se i = case 1
add $s0, $zero, $t2     # a = 1
beq $t0, $t3, break     # pula se i = case 2
add $s0, $zero, $t3     # a = 2
break: