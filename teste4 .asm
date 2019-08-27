addi $t0, $zero, 3    # i = 3
addi $ra, $zero, 10    # valor inicial de a
add $t5, $zero, $ra     # auxiliar para valor inicial de a
addi $t1, $zero, 0    #switch = 0
addi $t2, $zero, 1    #switch = 1
addi $t3, $zero, 2    #switch = 2
add $ra, $zero, $t1     # a = 0
beq $t0, $t1, end
add $ra, $zero, $t5     # a = valor inicial
beq $t0, $t2, end
add $ra, $zero, $t2     # a = 1
beq $t0, $t3, end
add $ra, $zero, $t3     # a = 2
end: