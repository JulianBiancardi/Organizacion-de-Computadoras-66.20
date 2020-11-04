
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

#define SS 24 //stack size multiplo de 8
//SRA
#define O_FP 20
#define O_GP 16

//LTA  4*4 = 16 bytes multiplo de 8
#define O_A0 12
#define O_A1 8
#define O_R0 4
#define O_R1 0

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

  lw t0, O_A0(fp)
  sw t0, O_R0(fp)

  lw t0, O_A1(fp)
  sw t0, O_R1(fp)

while:


end_while:


retur:

  li v0,0

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
