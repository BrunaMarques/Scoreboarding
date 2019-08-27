addi $t0, $zero, 1      # pri
addi $t1, $zero, 1     # seg
addi $t2, $zero, 3      # ter
addi $t3, $zero, 2      # qua
addi $t4, $zero, 14      # qui
addi $t5, $zero, 5      # sex
addi $t6, $zero, 6      # set
addi $t7, $zero, 7      # oit
addi $s0, $zero, 8      # non
addi $s1, $zero, 9      # dec
add $s2, $zero, $t0     # a = pri
sub $s3, $s2, $t1       # b = a - seg
bgtz $s3, aaa      # pula se b > 0
add $s2, $zero, $t1     # a = seg
aaa:
sub $s3, $s2, $t2       # b = a - ter
bgtz $s3, bb      # pula se b > 0
add $s2, $zero, $t2     # a = ter
bb:
sub $s3, $s2, $t3       # b = a - qua .....
bgtz $s3, ccc
add $s2, $zero, $t3
ccc:
sub $s3, $s2, $t4
bgtz $s3, dddd
add $s2, $zero, $t4
dddd:
sub $s3, $s2, $t5
bgtz $s3, eeeee
add $s2, $zero, $t5
eeeee:
sub $s3, $s2, $t6
bgtz $s3, ffffff
add $s2, $zero, $t6
ffffff:
sub $s3, $s2, $t7
bgtz $s3, ggggggg
add $s2, $zero, $t7
ggggggg:
sub $s3, $s2, $s0
bgtz $s3, hhhhhhhh
add $s2, $zero, $s0
hhhhhhhh:
sub $s3, $s2, $s1
bgtz $s3, iiiiiiiii
add $s2, $zero, $s1
iiiiiiiii:
add $s4, $zero, $s2