	.file	1 "file_reader.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.rdata
	.align	2
$LC0:
	.ascii	"stdin\000"
	.align	2
$LC1:
	.ascii	"r\000"
	.text
	.align	2
	.globl	file_reader_init
	.set	nomips16
	.set	nomicromips
	.ent	file_reader_init
	.type	file_reader_init, @function
file_reader_init:
	.frame	$fp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	.cprestore	16
	sw	$4,32($fp)
	sw	$5,36($fp)
	lw	$2,%got($LC0)($28)
	addiu	$5,$2,%lo($LC0)
	lw	$4,36($fp)
	lw	$2,%call16(strcmp)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,strcmp
1:	jalr	$25
	nop

	lw	$28,16($fp)
	bne	$2,$0,$L2
	nop

	lw	$2,%got(stdin)($28)
	lw	$3,0($2)
	lw	$2,32($fp)
	sw	$3,0($2)
	b	$L3
	nop

$L2:
	lw	$2,%got($LC1)($28)
	addiu	$5,$2,%lo($LC1)
	lw	$4,36($fp)
	lw	$2,%call16(fopen)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,fopen
1:	jalr	$25
	nop

	lw	$28,16($fp)
	move	$3,$2
	lw	$2,32($fp)
	sw	$3,0($2)
$L3:
	move	$2,$0
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	file_reader_init
	.size	file_reader_init, .-file_reader_init
	.align	2
	.globl	file_reader_process
	.set	nomips16
	.set	nomicromips
	.ent	file_reader_process
	.type	file_reader_process, @function
file_reader_process:
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
	b	$L6
	nop

$L8:
	lw	$2,48($fp)
	lw	$3,0($2)
	addiu	$2,$fp,28
	move	$7,$3
	li	$6,12			# 0xc
	li	$5,1			# 0x1
	move	$4,$2
	lw	$2,%call16(fread)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,fread
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sw	$2,24($fp)
	addiu	$3,$fp,28
	lw	$2,52($fp)
	lw	$6,56($fp)
	lw	$5,24($fp)
	move	$4,$3
	move	$25,$2
	jalr	$25
	nop

	lw	$28,16($fp)
	move	$3,$2
	li	$2,-1			# 0xffffffffffffffff
	bne	$3,$2,$L6
	nop

	li	$2,-1			# 0xffffffffffffffff
	b	$L9
	nop

$L6:
	lw	$2,48($fp)
	lw	$2,0($2)
	move	$4,$2
	lw	$2,%call16(feof)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,feof
1:	jalr	$25
	nop

	lw	$28,16($fp)
	beq	$2,$0,$L8
	nop

	move	$2,$0
$L9:
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	addiu	$sp,$sp,48
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	file_reader_process
	.size	file_reader_process, .-file_reader_process
	.align	2
	.globl	file_reader_destroy
	.set	nomips16
	.set	nomicromips
	.ent	file_reader_destroy
	.type	file_reader_destroy, @function
file_reader_destroy:
	.frame	$fp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	.cprestore	16
	sw	$4,32($fp)
	lw	$2,32($fp)
	lw	$3,0($2)
	lw	$2,%got(stdin)($28)
	lw	$2,0($2)
	beq	$3,$2,$L12
	nop

	lw	$2,32($fp)
	lw	$2,0($2)
	move	$4,$2
	lw	$2,%call16(fclose)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,fclose
1:	jalr	$25
	nop

	lw	$28,16($fp)
$L12:
	nop
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	file_reader_destroy
	.size	file_reader_destroy, .-file_reader_destroy
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
