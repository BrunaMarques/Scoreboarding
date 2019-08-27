addi $t1, $zero, 5
addi $t2, $zero, 2    
mul $t1, $t2, $t1        # RAW
addi $t0, $zero, 44    
sub $t0, $t1, $t2         # WAW
addi $t1, $zero, 8       # WAR
