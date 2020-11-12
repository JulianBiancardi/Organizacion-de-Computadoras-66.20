#include <sys/regdef.h>

#define SS 24 //stack size multiplo de 8
//SRA
#define O_FP 20
#define O_GP 16

//LTA
#define O_A0 (SS)
#define O_A1 (O_A0 + 4)

.extern mcd
.text
.align 2
.globl mcm
.ent mcm

mcm:

  subu  sp,sp,SS
  sw    fp, O_FP(sp)
  sw    gp, O_GP(sp)
  move  fp, sp

  sw    a0, O_A0(fp)     # m
  sw    a1, O_A1(fp)     # /n


  //unsigned int a = m * n;
  mul   $t0,$a0,$a1			 # m * n

  jal mcd

  div $t0, $v0      # a / b
  mflo $v0
  

  //return c;
return:
/*----Stack unwinding----*/
  lw fp, O_FP(sp)
  lw gp, O_GP(sp)
  addiu sp,sp,SS
  jr ra

.end mcm