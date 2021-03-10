.text
nop
addi	$t0, $t0, 20 
sw      $t0, 0($t0)   
nop  
jr		$t0
nor     $t1, $t3, $t2       
addi	$t1, $zero, 12	# Jumped to Here	
addi    $t2, $zero, 98    
nop  
and     $t3, $t1, $t2
add     $t2, $t1, $t3