.text
addi $t0, $zero, 8
add $t0, $t0, $t0
add $t0, $t0, $t0
sw   $t0, 0($t0) # Hazardous. Requires NOP between SW and LW
lw   $t2, 0($t0)
j   label
nop
addi $t1, $t2, 4
sub  $t0, $t0, $t1
label: or   $t0, $t0, $t1
nop
sw   $t0, 0($t1)
nop
