addi $t0, $zero, 6      # N = 6
addi $t1, $zero, 10     # MAX_SIZE = 10
addi $t2, $zero, 0      #fi = 0
addi $s0, $zero, 0      # A
begin:
beq $t2, $t0, end
addi $t2, $t2, 1
add $s0, $s0, $t1
j begin
end:
