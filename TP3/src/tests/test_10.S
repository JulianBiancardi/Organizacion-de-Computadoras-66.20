.text
addi $t0, $zero, 8
add $t0, $t0, $t0
add $t0, $t0, $t0
sw   $t0, 0($t0)
nop
lw   $t0, 0($t0)
jr   $t0
nop
addi $t1, $t2, 4
sub  $t0, $t0, $t1
or   $t0, $t0, $t1
nop
sw   $t0, 0($t1)
nop

