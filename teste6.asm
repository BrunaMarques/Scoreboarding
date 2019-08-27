addi $t0, $zero, 6      # termo do fibonacci (n)
addi $t1, $zero, 1      # a = 1
addi $t3, $zero, 1      # aux = 1
beq $t0, $t1, fim       # pula se n = a
add $t3, $zero, $zero   # aux = 0
add $t5, $zero, $zero   # b = 0
addi $t4, $zero, 1      # aux = 1 
beq $t0, $zero, fim     # pula se n = 0
for:
addi $t1, $t1, 1        # a += 1
add $t3, $t5, $t4       # aux = b + c
addi $t5, $t4, 0        # b = c
addi $t4, $t3, 0        # c = aux
bne $t0, $t1, for       # pula se n = a
fim: