#include <sys/regdef.h>

#define SS 24 //stack size multiplo de 8
//SRA
#define O_FP 20
#define O_GP 16

//LTA
#define O_A0 (SS)
#define O_A1 (O_A0 + 4)

.text
.align 2
.globl mcm
.ent mcm

mcm:

  subu sp,sp,SS
  sw fp, O_FP(sp)
  sw gp, O_GP(sp)
  move fp, sp


  sw a0, O_A0(fp)     //m
  sw a1, O_A1(fp)     //n


#IMPLEMENTACION
#
#

return:
  li v0,r0 //devuelvo r0 No se si esta bien asi

/*----Stack unwinding----*/
  lw fp, O_FP(sp)
  lw gp, O_GP(sp)
  addiu sp,sp,SS
  jr ra

.end mcm