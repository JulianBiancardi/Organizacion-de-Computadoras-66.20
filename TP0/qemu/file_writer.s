	.file	1 "file_writer.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.rdata
	.align	2
$LC0:
	.ascii	"stdout\000"
	.align	2
$LC1:
	.ascii	"w\000"
	.text
	.align	2
	.globl	file_writer_init
	.set	nomips16
	.set	nomicromips
	.ent	file_writer_init
	.type	file_writer_init, @function
file_writer_init:
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

	lw	$2,%got(stdout)($28)
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
	.end	file_writer_init
	.size	file_writer_init, .-file_writer_init
	.align	2
	.globl	file_writer_write
	.set	nomips16
	.set	nomicromips
	.ent	file_writer_write
	.type	file_writer_write, @function
file_writer_write:
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
	sw	$6,40($fp)
	lw	$2,32($fp)
	lw	$2,0($2)
	move	$7,$2
	lw	$6,40($fp)
	li	$5,1			# 0x1
	lw	$4,36($fp)
	lw	$2,%call16(fwrite)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,fwrite
1:	jalr	$25
	nop

	lw	$28,16($fp)
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	file_writer_write
	.size	file_writer_write, .-file_writer_write
	.align	2
	.globl	file_writer_destroy
	.set	nomips16
	.set	nomicromips
	.ent	file_writer_destroy
	.type	file_writer_destroy, @function
file_writer_destroy:
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
	lw	$2,%got(stdout)($28)
	lw	$2,0($2)
	beq	$3,$2,$L9
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
$L9:
	nop
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	file_writer_destroy
	.size	file_writer_destroy, .-file_writer_destroy
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
