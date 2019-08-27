addi $t0, $zero, 1
addi $t1, $zero, 15
addi $t2, $zero, 3
addi $t3, $zero, 2
addi $t4, $zero, 4
addi $t5, $zero, 5
addi $t6, $zero, 6
addi $t7, $zero, 7
addi $t8, $zero, 8
addi $t9, $zero, 9
add $s0, $zero, $t0
sub $s1, $s0, $t1
bgtz $s1, primeira_comp
add $s0, $zero, $t1
primeira_comp:
sub $s1, $s0, $t2
bgtz $s1, segunda_comp
add $s0, $zero, $t2
segunda_comp:
sub $s1, $s0, $t3
bgtz $s1, terceira_comp
add $s0, $zero, $t3
terceira_comp:
sub $s1, $s0, $t4
bgtz $s1, quarta_comp
add $s0, $zero, $t4
quarta_comp:
sub $s1, $s0, $t5
bgtz $s1, quinta_comp
add $s0, $zero, $t5
quinta_comp:
sub $s1, $s0, $t6
bgtz $s1, sexta_comp
add $s0, $zero, $t6
sexta_comp:
sub $s1, $s0, $t7
bgtz $s1, setima_comp
add $s0, $zero, $t7
setima_comp:
sub $s1, $s0, $t8
bgtz $s1, oitava_comp
add $s0, $zero, $t8
oitava_comp:
sub $s1, $s0, $t9
bgtz $s1, nona_comp
add $s0, $zero, $t9
nona_comp:
add $ra, $zero, $s0
