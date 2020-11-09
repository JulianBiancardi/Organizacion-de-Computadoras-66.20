
#include "stddef.h"
#include "stdio.h"

// Manera recursiva
unsigned int mcd_rec(unsigned int m, unsigned int n) {
  if (n = 0) {
    return m;
  }
  return mcd_rec(n, m % n);
}

// Manera iterativa
unsigned int mcd(unsigned int m, unsigned int n) {
  unsigned int r0 = m;
  unsigned int r1 = n;
  unsigned int aux;
  while (r1 != 0) {
    aux = r0;
    r0 = r1;
    r1 = aux % r1;
  }
  return r0;
}

/*
unsigned int mcd(unsigned int m, unsigned int n)

-- Funcion que recibe dos parametros, devuleve un valor y es una funicion no
hoja
-- gp no se necesita ya que no hay variables globales pero hay que tenerlo

#include <sys/regdef.h>

#define SS 24 //stack size multiplo de 8
//SRA
#define O_FP 20
#define O_GP 16

//LTA
#define O_R0 0
#define O_R1 4
#define O_AUX 8

#define O_A0 (SS)
#define O_A1 (O_A0 + 4)

.tex
.aling 2
.global mcd
.ent mcd

mcd:

  subu sp,sp,SS
  sw fp, O_FP(sp)
  sw gp, O_GP(gp)
  move fp, sp


  sw a0, O_A0(fp)
  sw a1, O_A1(fp)
//-------LTA-------//
  lw t0, O_A0(fp)
  sw t0, O_R0(fp)

  lw t0, O_A1(fp)
  sw t0, O_R1(fp)

  lw t0, O_R0(fp) //obtengo r0 en t0
  lw t1, O_R1(fp) //obtengo r1 en t1
  lw t2, O_AUX(fp) //obtengo aux en t1
while:
  bez $t1 return
  add $t2, $t0, $zero // aux = r0
  add $t0, $t1, $zero // r0  = r1
  ....... // r1  = aux % r1
  ba while

return:
  li v0,r0 //devuelvo r0 No se si esta bien asi

//----Stack unwinding----//
  lw fp, O_FP(sp)
  lw gp, O_GP(sp)
  addiu sp,sp,SS
  jr ra

.end mcd
*/

unsigned int mcm(unsigned int m, unsigned int n) {
  return ((m * n) / mcd(m, n));
}

int main() {
  printf("%i\n", mcd(247, 221));
  printf("%i\n", mcm(247, 221));
  return 0;
}
