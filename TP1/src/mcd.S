#include <sys/regdef.h>

#define SS 24 #stack size multiplo de 8
#SRA
#define O_FP 20
#define O_GP 16

#LTA
#define O_R0 0
#define O_R1 4
#define O_AUX 8

#define O_A0 (SS)
#define O_A1 (O_A0 + 4)

.text
.align 2
.globl mcd
.ent mcd

mcd:

  subu sp,sp,SS
  sw fp, O_FP(sp)
  sw gp, O_GP(gp)
  move fp, sp


  sw a0, O_A0(fp)
  sw a1, O_A1(fp)
#-------LTA-------#
  lw t0, O_A0(fp)
  sw t0, O_R0(fp)

  lw t0, O_A1(fp)
  sw t0, O_R1(fp)

  lw t0, O_R0(fp) #obtengo r0 en t0
  lw t1, O_R1(fp) #obtengo r1 en t1
  lw t2, O_AUX(fp) #obtengo aux en t2
while:
  beqz t1 return
  move t2, t0   # aux = r0
  move t0, t1   # r0  = r1
  #.......         # r1  = aux % r1
  j while

return:
  li v0,r0 #devuelvo r0 No se si esta bien asi
  
#----Stack unwinding----#
  lw fp, O_FP(sp)
  lw gp, O_GP(sp)
  addiu sp,sp,SS
  jr ra

.end mcd