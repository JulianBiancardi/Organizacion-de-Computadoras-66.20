
.text
.align 2
.globl main
.ent main

main:
    /* Stack */
    subu	$sp, $sp, SS  		# sp = sp - SS
    sw		$fp, O_FP($sp)		# save FP
    sw		$gp, O_GP($sp)		# save GP
    move 	$fp, $sp            # fp =sp

    sw		$a0, O_AO($fp)		# get argc
    sw		$a1, O_A1($fp)		# get argv
    
    
    
    
    
    
    
