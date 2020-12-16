#include <sys/regdef.h>

#define SS 32 //stack size multiplo de 8
//SRA
#define O_RA 28
#define O_FP 24
#define O_GP 20
#define O_S0 16

//CalleeABA 16 bytes

//Callers ABA
#define O_A0 (SS)
#define O_A1 (O_A0 + 4)

.text
.align 2
.globl mcm
.ent mcm

mcm:

  subu  sp,sp,SS
  sw		ra, O_RA(sp)		// guardo RA
  
  sw    fp, O_FP(sp)
  sw    gp, O_GP(sp)
  move  fp, sp

  sw    s0, O_S0(sp)     // Save s0 for use

  sw    a0, O_A0(fp)     // m
  sw    a1, O_A1(fp)     // n


  //unsigned int a = m * n;
  mul   s0,a0,a1			 // m * n
  
  jal mcd

  div s0, v0      // a / b
  mflo v0
  

  //return c;
return:
/*----Stack unwinding----*/
  lw ra, O_RA(sp)
  lw fp, O_FP(sp)
  lw gp, O_GP(sp)
  lw s0, O_S0(sp)
  addiu sp,sp,SS
  jr ra

.end mcm