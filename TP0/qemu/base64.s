	.file	1 "base64.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.rdata
	.align	2
$LC0:
	.ascii	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123"
	.ascii	"456789+/\000"
	.text
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	_encodeValue
	.type	_encodeValue, @function
_encodeValue:
	.frame	$fp,96,$31		# vars= 64, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-96
	sw	$31,92($sp)
	sw	$fp,88($sp)
	move	$fp,$sp
	.cprestore	16
	sw	$4,96($fp)
	lw	$2,%got($LC0)($28)
	addiu	$3,$fp,24
	addiu	$2,$2,%lo($LC0)
	li	$4,64			# 0x40
	move	$6,$4
	move	$5,$2
	move	$4,$3
	lw	$2,%call16(memcpy)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,memcpy
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,96($fp)
	addiu	$3,$fp,24
	addu	$2,$3,$2
	lb	$2,0($2)
	move	$sp,$fp
	lw	$31,92($sp)
	lw	$fp,88($sp)
	addiu	$sp,$sp,96
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_encodeValue
	.size	_encodeValue, .-_encodeValue
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	_generate_phrase
	.type	_generate_phrase, @function
_generate_phrase:
	.frame	$fp,32,$31		# vars= 16, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$fp,28($sp)
	move	$fp,$sp
	sw	$4,32($fp)
	sw	$5,36($fp)
	sw	$0,8($fp)
	sw	$0,12($fp)
	b	$L4
	nop

$L7:
	lw	$3,12($fp)
	lw	$2,36($fp)
	sltu	$2,$3,$2
	beq	$2,$0,$L5
	nop

	lw	$3,32($fp)
	lw	$2,12($fp)
	addu	$2,$3,$2
	lb	$2,0($2)
	andi	$2,$2,0x00ff
	b	$L6
	nop

$L5:
	move	$2,$0
$L6:
	sb	$2,16($fp)
	li	$3,2			# 0x2
	lw	$2,12($fp)
	subu	$2,$3,$2
	sw	$2,20($fp)
	lbu	$3,16($fp)
	lw	$2,20($fp)
	sll	$2,$2,3
	sll	$2,$3,$2
	lw	$3,8($fp)
	addu	$2,$3,$2
	sw	$2,8($fp)
	lw	$2,12($fp)
	addiu	$2,$2,1
	sw	$2,12($fp)
$L4:
	lw	$2,12($fp)
	sltu	$2,$2,3
	bne	$2,$0,$L7
	nop

	lw	$2,8($fp)
	move	$sp,$fp
	lw	$fp,28($sp)
	addiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_generate_phrase
	.size	_generate_phrase, .-_generate_phrase
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	_decodeLetterAndShift
	.type	_decodeLetterAndShift, @function
_decodeLetterAndShift:
	.frame	$fp,40,$31		# vars= 8, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	.cprestore	16
	move	$2,$4
	sw	$5,44($fp)
	sb	$2,40($fp)
	lb	$3,40($fp)
	li	$2,61			# 0x3d
	bne	$3,$2,$L10
	nop

	move	$2,$0
	b	$L11
	nop

$L10:
	lb	$2,40($fp)
	move	$4,$2
	lw	$2,%got(_decodeValueLetter)($28)
	addiu	$2,$2,%lo(_decodeValueLetter)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,_decodeValueLetter
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sw	$2,24($fp)
	lw	$3,24($fp)
	li	$2,-1			# 0xffffffffffffffff
	bne	$3,$2,$L12
	nop

	li	$2,-1			# 0xffffffffffffffff
	b	$L11
	nop

$L12:
	lw	$3,44($fp)
	move	$2,$3
	sll	$2,$2,1
	addu	$2,$2,$3
	sll	$2,$2,1
	move	$3,$2
	lw	$2,24($fp)
	sll	$2,$2,$3
$L11:
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addiu	$sp,$sp,40
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_decodeLetterAndShift
	.size	_decodeLetterAndShift, .-_decodeLetterAndShift
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	_decodeValueLetter
	.type	_decodeValueLetter, @function
_decodeValueLetter:
	.frame	$fp,24,$31		# vars= 8, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$fp,20($sp)
	move	$fp,$sp
	move	$2,$4
	sb	$2,24($fp)
	lb	$2,24($fp)
	sw	$2,8($fp)
	lw	$2,8($fp)
	slt	$2,$2,65
	bne	$2,$0,$L14
	nop

	lw	$2,8($fp)
	slt	$2,$2,91
	beq	$2,$0,$L14
	nop

	lw	$2,8($fp)
	addiu	$2,$2,-65
	b	$L15
	nop

$L14:
	lw	$2,8($fp)
	slt	$2,$2,97
	bne	$2,$0,$L16
	nop

	lw	$2,8($fp)
	slt	$2,$2,123
	beq	$2,$0,$L16
	nop

	lw	$2,8($fp)
	addiu	$2,$2,-71
	b	$L15
	nop

$L16:
	lw	$2,8($fp)
	slt	$2,$2,48
	bne	$2,$0,$L17
	nop

	lw	$2,8($fp)
	slt	$2,$2,58
	beq	$2,$0,$L17
	nop

	lw	$2,8($fp)
	addiu	$2,$2,4
	b	$L15
	nop

$L17:
	lb	$2,24($fp)
	li	$3,43			# 0x2b
	beq	$2,$3,$L19
	nop

	li	$3,47			# 0x2f
	beq	$2,$3,$L20
	nop

	b	$L21
	nop

$L19:
	li	$2,62			# 0x3e
	b	$L15
	nop

$L20:
	li	$2,63			# 0x3f
	b	$L15
	nop

$L21:
	li	$2,-1			# 0xffffffffffffffff
$L15:
	move	$sp,$fp
	lw	$fp,20($sp)
	addiu	$sp,$sp,24
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_decodeValueLetter
	.size	_decodeValueLetter, .-_decodeValueLetter
	.align	2
	.globl	encode64
	.set	nomips16
	.set	nomicromips
	.ent	encode64
	.type	encode64, @function
encode64:
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
	lw	$2,56($fp)
	beq	$2,$0,$L23
	nop

	lw	$2,64($fp)
	bne	$2,$0,$L24
	nop

$L23:
	li	$2,-1			# 0xffffffffffffffff
	b	$L25
	nop

$L24:
	lw	$5,60($fp)
	lw	$4,56($fp)
	lw	$2,%got(_generate_phrase)($28)
	addiu	$2,$2,%lo(_generate_phrase)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,_generate_phrase
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sw	$2,32($fp)
	sw	$0,24($fp)
	b	$L26
	nop

$L27:
	lw	$3,24($fp)
	move	$2,$3
	sll	$3,$3,2
	subu	$2,$2,$3
	sll	$2,$2,1
	addiu	$2,$2,18
	lw	$3,32($fp)
	sra	$2,$3,$2
	andi	$2,$2,0x3f
	sw	$2,36($fp)
	lw	$3,64($fp)
	lw	$2,24($fp)
	addu	$16,$3,$2
	lw	$4,36($fp)
	lw	$2,%got(_encodeValue)($28)
	addiu	$2,$2,%lo(_encodeValue)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,_encodeValue
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sb	$2,0($16)
	lw	$2,24($fp)
	addiu	$2,$2,1
	sw	$2,24($fp)
$L26:
	lw	$2,24($fp)
	sltu	$2,$2,4
	bne	$2,$0,$L27
	nop

	lw	$2,60($fp)
	addiu	$2,$2,1
	sw	$2,28($fp)
	b	$L28
	nop

$L29:
	lw	$3,64($fp)
	lw	$2,28($fp)
	addu	$2,$3,$2
	li	$3,61			# 0x3d
	sb	$3,0($2)
	lw	$2,28($fp)
	addiu	$2,$2,1
	sw	$2,28($fp)
$L28:
	lw	$2,28($fp)
	sltu	$2,$2,4
	bne	$2,$0,$L29
	nop

	move	$2,$0
$L25:
	move	$sp,$fp
	lw	$31,52($sp)
	lw	$fp,48($sp)
	lw	$16,44($sp)
	addiu	$sp,$sp,56
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	encode64
	.size	encode64, .-encode64
	.align	2
	.globl	decode64
	.set	nomips16
	.set	nomicromips
	.ent	decode64
	.type	decode64, @function
decode64:
	.frame	$fp,56,$31		# vars= 24, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-56
	sw	$31,52($sp)
	sw	$fp,48($sp)
	move	$fp,$sp
	.cprestore	16
	sw	$4,56($fp)
	sw	$5,60($fp)
	sw	$0,24($fp)
	sw	$0,28($fp)
	sw	$0,32($fp)
	b	$L31
	nop

$L34:
	lw	$3,56($fp)
	lw	$2,32($fp)
	addu	$2,$3,$2
	lb	$4,0($2)
	li	$3,3			# 0x3
	lw	$2,32($fp)
	subu	$2,$3,$2
	move	$5,$2
	lw	$2,%got(_decodeLetterAndShift)($28)
	addiu	$2,$2,%lo(_decodeLetterAndShift)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,_decodeLetterAndShift
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sw	$2,40($fp)
	lw	$3,40($fp)
	li	$2,-1			# 0xffffffffffffffff
	bne	$3,$2,$L32
	nop

	li	$2,-1			# 0xffffffffffffffff
	b	$L33
	nop

$L32:
	lw	$3,24($fp)
	lw	$2,40($fp)
	addu	$2,$3,$2
	sw	$2,24($fp)
	lw	$2,32($fp)
	addiu	$2,$2,1
	sw	$2,32($fp)
$L31:
	lw	$2,32($fp)
	sltu	$2,$2,4
	bne	$2,$0,$L34
	nop

	sw	$0,36($fp)
	b	$L35
	nop

$L37:
	lw	$3,36($fp)
	move	$2,$0
	subu	$2,$2,$3
	sll	$2,$2,3
	addiu	$2,$2,16
	lw	$3,24($fp)
	sra	$2,$3,$2
	andi	$2,$2,0xff
	sw	$2,44($fp)
	lw	$2,44($fp)
	beq	$2,$0,$L36
	nop

	lw	$2,28($fp)
	addiu	$2,$2,1
	sw	$2,28($fp)
$L36:
	lw	$3,60($fp)
	lw	$2,36($fp)
	addu	$2,$3,$2
	lw	$3,44($fp)
	seb	$3,$3
	sb	$3,0($2)
	lw	$2,36($fp)
	addiu	$2,$2,1
	sw	$2,36($fp)
$L35:
	lw	$2,36($fp)
	sltu	$2,$2,3
	bne	$2,$0,$L37
	nop

	lw	$2,28($fp)
$L33:
	move	$sp,$fp
	lw	$31,52($sp)
	lw	$fp,48($sp)
	addiu	$sp,$sp,56
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	decode64
	.size	decode64, .-decode64
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
