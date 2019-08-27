addi $t0, $zero, 5      # N = 5
addi $t1, $zero, 10     # MAX_SIZE = 10
addi $t2, $zero, 0      # i = 0
addi $t3, $zero, 0      # A = 0
for:
beq $t2, $t0, break     # sai do for se i = N
addi $t2, $t2, 1        # i ++
add $t3, $t3, $t1       # A += MAX_SIZE
j for                   # executa o laço
break:
