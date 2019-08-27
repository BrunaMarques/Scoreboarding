addi $t1, $zero, 5
addi $t2, $zero, 2    
mul $t1, $t2, $t1        # RAW
addi $t3, $zero, 44    
mflo $t0                 # RAW
or $t0, $t1, $t2         # WAW
addi $t1, $zero, 8       # WAR
