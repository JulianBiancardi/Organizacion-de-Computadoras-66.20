.text
nop
addi	$t1, $t1, 20
addi	$t0, $t0, 20
sw      $t0, 0($t0) # Hazardous. Requires a NOP between sw and bew
beq $t0,$t1,return
nor     $t1, $t3, $t2
return:       
addi	$t1, $zero, 12	# Jumped to Here	
addi    $t2, $zero, 98    
nop  
and     $t3, $t1, $t2
add     $t2, $t1, $t3