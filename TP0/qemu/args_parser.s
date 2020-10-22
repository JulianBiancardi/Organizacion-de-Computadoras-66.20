	.file	1 "args_parser.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.rdata
	.align	2
$LC0:
	.ascii	"Vhi:o:d\000"
	.text
	.align	2
	.globl	get_arguments
	.set	nomips16
	.set	nomicromips
	.ent	get_arguments
	.type	get_arguments, @function
get_arguments:
	.frame	$fp,48,$31		# vars= 8, regs= 2/0, args= 24, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$fp,40($sp)
	move	$fp,$sp
	.cprestore	24
	sw	$4,48($fp)
	sw	$5,52($fp)
	sw	$6,56($fp)
	sw	$7,60($fp)
	lw	$2,64($fp)
	sb	$0,0($2)
$L12:
	sw	$0,16($sp)
	lw	$2,%got(arguments.2664)($28)
	addiu	$7,$2,%lo(arguments.2664)
	lw	$2,%got($LC0)($28)
	addiu	$6,$2,%lo($LC0)
	lw	$5,52($fp)
	lw	$4,48($fp)
	lw	$2,%call16(getopt_long)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,getopt_long
1:	jalr	$25
	nop

	lw	$28,24($fp)
	sw	$2,32($fp)
	lw	$3,32($fp)
	li	$2,-1			# 0xffffffffffffffff
	beq	$3,$2,$L14
	nop

	lw	$2,32($fp)
	addiu	$2,$2,-86
	sltu	$3,$2,26
	beq	$3,$0,$L4
	nop

	sll	$3,$2,2
	lw	$2,%got($L6)($28)
	addiu	$2,$2,%lo($L6)
	addu	$2,$3,$2
	lw	$2,0($2)
	addu	$2,$2,$28
	jr	$2
	nop

	.rdata
	.align	2
	.align	2
$L6:
	.gpword	$L5
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L7
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L8
	.gpword	$L9
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L4
	.gpword	$L10
	.text
$L5:
	lw	$2,%got(print_version)($28)
	addiu	$2,$2,%lo(print_version)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,print_version
1:	jalr	$25
	nop

	lw	$28,24($fp)
	move	$4,$0
	lw	$2,%call16(exit)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,exit
1:	jalr	$25
	nop

$L8:
	lw	$2,%got(print_help)($28)
	addiu	$2,$2,%lo(print_help)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,print_help
1:	jalr	$25
	nop

	lw	$28,24($fp)
	move	$4,$0
	lw	$2,%call16(exit)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,exit
1:	jalr	$25
	nop

$L10:
	lw	$2,%got(optarg)($28)
	lw	$2,0($2)
	li	$6,32			# 0x20
	move	$5,$2
	lw	$4,60($fp)
	lw	$2,%call16(strncpy)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,strncpy
1:	jalr	$25
	nop

	lw	$28,24($fp)
	b	$L11
	nop

$L9:
	lw	$2,%got(optarg)($28)
	lw	$2,0($2)
	li	$6,32			# 0x20
	move	$5,$2
	lw	$4,56($fp)
	lw	$2,%call16(strncpy)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,strncpy
1:	jalr	$25
	nop

	lw	$28,24($fp)
	b	$L11
	nop

$L7:
	lw	$2,64($fp)
	li	$3,1			# 0x1
	sb	$3,0($2)
	b	$L11
	nop

$L4:
	lw	$2,%got(print_help)($28)
	addiu	$2,$2,%lo(print_help)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,print_help
1:	jalr	$25
	nop

	lw	$28,24($fp)
	li	$4,-1			# 0xffffffffffffffff
	lw	$2,%call16(exit)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,exit
1:	jalr	$25
	nop

$L11:
	b	$L12
	nop

$L14:
	nop
	nop
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	addiu	$sp,$sp,48
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	get_arguments
	.size	get_arguments, .-get_arguments
	.rdata
	.align	2
$LC1:
	.ascii	"Version: %d\012\000"
	.text
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	print_version
	.type	print_version, @function
print_version:
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
	li	$5,8			# 0x8
	lw	$2,%got($LC1)($28)
	addiu	$4,$2,%lo($LC1)
	lw	$2,%call16(printf)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,printf
1:	jalr	$25
	nop

	lw	$28,16($fp)
	nop
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	print_version
	.size	print_version, .-print_version
	.rdata
	.align	2
$LC2:
	.ascii	"Usage:\012\000"
	.align	2
$LC3:
	.ascii	"\011tp0 -h\000"
	.align	2
$LC4:
	.ascii	"\011tp0 -V\000"
	.align	2
$LC5:
	.ascii	"\011tp0 [options]\000"
	.align	2
$LC6:
	.ascii	"\012Options:\012\000"
	.align	2
$LC7:
	.ascii	"\011-V, --version\011\011Print version and quit.\000"
	.align	2
$LC8:
	.ascii	"\011-h, --help\011\011Print this information.\000"
	.align	2
$LC9:
	.ascii	"\011-o, --output\011\011Path to output file.\000"
	.align	2
$LC10:
	.ascii	"\011-i, --input\011\011Path to input file.\000"
	.align	2
$LC11:
	.ascii	"\011-d, --decode\011\011Decode a base64-encoded file.\000"
	.align	2
$LC12:
	.ascii	"\012Examples:\012\000"
	.align	2
$LC13:
	.ascii	"\011tp0 -i input.txt -o output.txt\000"
	.text
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	print_help
	.type	print_help, @function
print_help:
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
	lw	$2,%got($LC2)($28)
	addiu	$4,$2,%lo($LC2)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,%got($LC3)($28)
	addiu	$4,$2,%lo($LC3)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,%got($LC4)($28)
	addiu	$4,$2,%lo($LC4)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,%got($LC5)($28)
	addiu	$4,$2,%lo($LC5)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,%got($LC6)($28)
	addiu	$4,$2,%lo($LC6)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,%got($LC7)($28)
	addiu	$4,$2,%lo($LC7)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,%got($LC8)($28)
	addiu	$4,$2,%lo($LC8)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,%got($LC9)($28)
	addiu	$4,$2,%lo($LC9)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,%got($LC10)($28)
	addiu	$4,$2,%lo($LC10)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,%got($LC11)($28)
	addiu	$4,$2,%lo($LC11)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,%got($LC12)($28)
	addiu	$4,$2,%lo($LC12)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,%got($LC13)($28)
	addiu	$4,$2,%lo($LC13)
	lw	$2,%call16(puts)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,puts
1:	jalr	$25
	nop

	lw	$28,16($fp)
	nop
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	print_help
	.size	print_help, .-print_help
	.rdata
	.align	2
$LC14:
	.ascii	"version\000"
	.align	2
$LC15:
	.ascii	"help\000"
	.align	2
$LC16:
	.ascii	"input\000"
	.align	2
$LC17:
	.ascii	"output\000"
	.align	2
$LC18:
	.ascii	"decode\000"
	.section	.data.rel.local,"aw",@progbits
	.align	2
	.type	arguments.2664, @object
	.size	arguments.2664, 96
arguments.2664:
	.word	$LC14
	.word	0
	.word	0
	.word	86
	.word	$LC15
	.word	0
	.word	0
	.word	104
	.word	$LC16
	.word	1
	.word	0
	.word	105
	.word	$LC17
	.word	1
	.word	0
	.word	111
	.word	$LC18
	.word	0
	.word	0
	.word	100
	.word	0
	.word	0
	.word	0
	.word	0
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
