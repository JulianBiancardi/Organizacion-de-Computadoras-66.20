.text
addi	$t0, $zero, 8    
jalr	$ra, $t0         
sw      $t2, 0($t0)         # Jumped to Here
nor     $t1, $t3, $t2       
addi	$t1, $zero, 12		
addi    $t2, $zero, 98      
and     $t3, $t1, $t2
add     $t2, $t1, $t3