.text
addi $t0, $zero, 8
addi $t1, $zero, 8
add  $t2, $t1, $t0
jr   $t2
sw   $t2, 0($zero)
nor  $t0, $t2, $t1
nop