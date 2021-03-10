.text
addi	$t0, $zero, 16    	
jr		$t0					
addi	$t1, $zero, 12		
sub 	$zero, $zero, $zero 
addi    $t2, $zero, 98      # Jumped to here
and     $t3, $t1, $t2
nor     $t1, $t3, $t2
add     $t2, $t1, $t3

