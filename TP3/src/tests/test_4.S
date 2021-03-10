.text
addi	$t0, $zero, 16    	
jalr	$ra, $t0					
addi	$t1, $zero, 12		
sub 	$zero, $zero, $zero 
sw      $ra, 4($t1)         # Jumped to here
addi    $t2, $zero, 98    
nor     $t1, $t3, $t2  
neg     $t3, $t1
add     $t2, $t1, $t3