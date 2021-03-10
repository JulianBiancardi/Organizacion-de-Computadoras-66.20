addi $t0, $zero, 8
addi $t1, $zero, 12
add  $t2, $t1, $t0
jalr   $t2
sw   $t2, 0($zero)
nop
nor  $t0, $t2, $t1  
nop