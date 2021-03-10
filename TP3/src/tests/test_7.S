.text
j		label
addi	$t1, $zero, 12		
sub 	$zero, $zero, $zero 
addi    $t2, $zero, 98      
label:  and     $t3, $t1, $t2 # Jumped to here
nor     $t1, $t3, $t2
add     $t2, $t1, $t3
