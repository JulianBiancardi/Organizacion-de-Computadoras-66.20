	.file	1 "main.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.rdata
	.align	2
$LC2:
	.ascii	"El archivo indicado para lectura no existe.\000"
	.align	2
$LC3:
	.ascii	"Error procesando el archivo de entrada. Un caracter no p"
	.ascii	"udo ser decodificado.\000"
	.align	2
$LC1:
	.ascii	"stdout\000"
	.space	25
	.align	2
$LC0:
	.ascii	"stdin\000"
	.space	26
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,120,$31		# vars= 80, regs= 2/0, args= 24, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-120
	sw	$31,116($sp)
	sw	$fp,112($sp)
	move	$fp,$sp
	.cprestore	24
	sw	$4,120($fp)
	sw	$5,124($fp)
	lw	$2,%got($LC0)($28)
	lw	$3,%lo($LC0)($2)
	sw	$3,36($fp)
	addiu	$2,$2,%lo($LC0)
	lhu	$2,4($2)
	sh	$2,40($fp)
	sh	$0,42($fp)
	sh	$0,44($fp)
	sh	$0,46($fp)
	sh	$0,48($fp)
	sh	$0,50($fp)
	sh	$0,52($fp)
	sh	$0,54($fp)
	sh	$0,56($fp)
	sh	$0,58($fp)
	sh	$0,60($fp)
	sh	$0,62($fp)
	sh	$0,64($fp)
	sh	$0,66($fp)
	lw	$2,%got($LC1)($28)
	lw	$3,%lo($LC1)($2)
	sw	$3,68($fp)
	addiu	$2,$2,%lo($LC1)
	lhu	$3,4($2)
	sh	$3,72($fp)
	lbu	$2,6($2)
	sb	$2,74($fp)
	addiu	$2,$fp,75
	li	$3,25			# 0x19
	move	$6,$3
	move	$5,$0
	move	$4,$2
	lw	$2,%call16(memset)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,memset
1:	jalr	$25
	nop

	lw	$28,24($fp)
	addiu	$4,$fp,68
	addiu	$3,$fp,36
	addiu	$2,$fp,100
	sw	$2,16($sp)
	move	$7,$4
	move	$6,$3
	lw	$5,124($fp)
	lw	$4,120($fp)
	lw	$2,%call16(get_arguments)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,get_arguments
1:	jalr	$25
	nop

	lw	$28,24($fp)
	addiu	$2,$fp,36
	li	$5,4			# 0x4
	move	$4,$2
	lw	$2,%call16(access)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,access
1:	jalr	$25
	nop

	lw	$28,24($fp)
	move	$3,$2
	li	$2,-1			# 0xffffffffffffffff
	bne	$3,$2,$L2
	nop

	lw	$2,%got($LC2)($28)
	addiu	$4,$2,%lo($LC2)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,24($fp)
	li	$2,-1			# 0xffffffffffffffff
	b	$L7
	nop

$L2:
	addiu	$3,$fp,36
	addiu	$2,$fp,104
	move	$5,$3
	move	$4,$2
	lw	$2,%call16(file_reader_init)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,file_reader_init
1:	jalr	$25
	nop

	lw	$28,24($fp)
	addiu	$3,$fp,68
	addiu	$2,$fp,108
	move	$5,$3
	move	$4,$2
	lw	$2,%call16(file_writer_init)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,file_writer_init
1:	jalr	$25
	nop

	lw	$28,24($fp)
	lbu	$2,100($fp)
	beq	$2,$0,$L4
	nop

	addiu	$2,$fp,108
	addiu	$3,$fp,104
	move	$6,$2
	lw	$2,%got(decode_and_output)($28)
	addiu	$5,$2,%lo(decode_and_output)
	move	$4,$3
	lw	$2,%call16(file_reader_process)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,file_reader_process
1:	jalr	$25
	nop

	lw	$28,24($fp)
	sw	$2,32($fp)
	b	$L5
	nop

$L4:
	addiu	$2,$fp,108
	addiu	$3,$fp,104
	move	$6,$2
	lw	$2,%got(encode_and_output)($28)
	addiu	$5,$2,%lo(encode_and_output)
	move	$4,$3
	lw	$2,%call16(file_reader_process)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,file_reader_process
1:	jalr	$25
	nop

	lw	$28,24($fp)
	sw	$2,32($fp)
$L5:
	addiu	$2,$fp,108
	move	$4,$2
	lw	$2,%call16(file_writer_destroy)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,file_writer_destroy
1:	jalr	$25
	nop

	lw	$28,24($fp)
	addiu	$2,$fp,104
	move	$4,$2
	lw	$2,%call16(file_reader_destroy)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,file_reader_destroy
1:	jalr	$25
	nop

	lw	$28,24($fp)
	lw	$3,32($fp)
	li	$2,-1			# 0xffffffffffffffff
	bne	$3,$2,$L6
	nop

	lw	$2,%got($LC3)($28)
	addiu	$4,$2,%lo($LC3)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,24($fp)
	addiu	$3,$fp,68
	lw	$2,%got($LC1)($28)
	addiu	$2,$2,%lo($LC1)
	beq	$3,$2,$L6
	nop

	addiu	$2,$fp,68
	move	$4,$2
	lw	$2,%call16(remove)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,remove
1:	jalr	$25
	nop

	lw	$28,24($fp)
$L6:
	lw	$2,32($fp)
$L7:
	move	$sp,$fp
	lw	$31,116($sp)
	lw	$fp,112($sp)
	addiu	$sp,$sp,120
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	min
	.type	min, @function
min:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	sw	$4,8($fp)
	sw	$5,12($fp)
	lw	$2,8($fp)
	lw	$4,12($fp)
	lw	$3,12($fp)
	slt	$4,$2,$4
	movz	$2,$3,$4
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	min
	.size	min, .-min
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	encode_and_output
	.type	encode_and_output, @function
encode_and_output:
	.frame	$fp,56,$31		# vars= 16, regs= 3/0, args= 16, gp= 8
	.mask	0xc0010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-56
	sw	$31,52($sp)
	sw	$fp,48($sp)
	sw	$16,44($sp)
	move	$fp,$sp
	.cprestore	16
	sw	$4,56($fp)
	sw	$5,60($fp)
	sw	$6,64($fp)
	lw	$2,64($fp)
	sw	$2,28($fp)
	sw	$0,24($fp)
	b	$L11
	nop

$L14:
	lw	$2,24($fp)
	lw	$3,56($fp)
	addu	$16,$3,$2
	lw	$2,24($fp)
	lw	$3,60($fp)
	subu	$2,$3,$2
	li	$5,3			# 0x3
	move	$4,$2
	lw	$2,%got(min)($28)
	addiu	$2,$2,%lo(min)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,min
1:	jalr	$25
	nop

	lw	$28,16($fp)
	move	$3,$2
	addiu	$2,$fp,32
	move	$6,$2
	move	$5,$3
	move	$4,$16
	lw	$2,%call16(encode64)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,encode64
1:	jalr	$25
	nop

	lw	$28,16($fp)
	move	$3,$2
	li	$2,-1			# 0xffffffffffffffff
	bne	$3,$2,$L12
	nop

	li	$2,-1			# 0xffffffffffffffff
	b	$L15
	nop

$L12:
	addiu	$2,$fp,32
	li	$6,4			# 0x4
	move	$5,$2
	lw	$4,28($fp)
	lw	$2,%call16(file_writer_write)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,file_writer_write
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,24($fp)
	addiu	$2,$2,3
	sw	$2,24($fp)
$L11:
	lw	$3,24($fp)
	lw	$2,60($fp)
	sltu	$2,$3,$2
	bne	$2,$0,$L14
	nop

	move	$2,$0
$L15:
	move	$sp,$fp
	lw	$31,52($sp)
	lw	$fp,48($sp)
	lw	$16,44($sp)
	addiu	$sp,$sp,56
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	encode_and_output
	.size	encode_and_output, .-encode_and_output
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	decode_and_output
	.type	decode_and_output, @function
decode_and_output:
	.frame	$fp,48,$31		# vars= 16, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$fp,40($sp)
	move	$fp,$sp
	.cprestore	16
	sw	$4,48($fp)
	sw	$5,52($fp)
	sw	$6,56($fp)
	lw	$2,56($fp)
	sw	$2,28($fp)
	sw	$0,24($fp)
	b	$L17
	nop

$L20:
	lw	$2,24($fp)
	lw	$3,48($fp)
	addu	$2,$3,$2
	addiu	$3,$fp,36
	move	$5,$3
	move	$4,$2
	lw	$2,%call16(decode64)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,decode64
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sw	$2,32($fp)
	lw	$3,32($fp)
	li	$2,-1			# 0xffffffffffffffff
	bne	$3,$2,$L18
	nop

	li	$2,-1			# 0xffffffffffffffff
	b	$L21
	nop

$L18:
	lw	$3,32($fp)
	addiu	$2,$fp,36
	move	$6,$3
	move	$5,$2
	lw	$4,28($fp)
	lw	$2,%call16(file_writer_write)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,file_writer_write
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,24($fp)
	addiu	$2,$2,4
	sw	$2,24($fp)
$L17:
	lw	$3,24($fp)
	lw	$2,52($fp)
	sltu	$2,$3,$2
	bne	$2,$0,$L20
	nop

	move	$2,$0
$L21:
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	addiu	$sp,$sp,48
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	decode_and_output
	.size	decode_and_output, .-decode_and_output
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
