.data
str_exit: .asciiz "test.txt"
str_data: .asciiz "This is a test!"
str_data_end:

#define OPEN_FILE 13

.text
.align 2

file_open:

    sub		$sp, $sp, SS		# $sp = $sp - SS
    sw		$fp, O_FP($sp)		# Save FP
    sw		$gp, O_GP($sp)		# save GP
    move 	$fp, $sp	        # fp = sp

    # Get char* file_name
    sw      $a0, O_A0($fp)      # a0 = fp + O_AO 
    # Get mode
    sw      $a1, O_A1($fp)      # a1 = fp + O_A1
    
    li $v0, OPEN_FILE
    la $a0, str_exi
    li $a1, 
    li $a2, 0
    syscall  # File descriptor gets returned in $v0


file_write:
    move $a0, $v0  # Syscall 15 requieres file descriptor in $a0
    li $v0, 15
    la $a1, str_data
    la $a2, str_data_end
    la $a3, str_data
    subu $a2, $a2, $a3  # computes the length of the string, this is really a constant
    syscall
file_close:
    li $v0, 16  # $a0 already has the file descriptor
    syscall