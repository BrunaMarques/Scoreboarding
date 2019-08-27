addi $t1, $zero, 5
addi $t2, $zero, 2    
mul $t1, $t2, $t1        # RAW
addi $t0, $zero, 44    
add $t0, $t1, $s2         # WAW
addi $t1, $zero, 8       # WAR
#esse teste mostra que o mul fica 5 ciclos na execução, 
#e o addi que vem logo depois consegue ser executado paralelamente sem nenhum problema
#Além disso mostramos o tratamento das dependências
