
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

unsigned int mcm(unsigned int m, unsigned int n) {
  return ((m * n) / mcd(m, n));
}

int main() {
  printf("%i\n", mcd(247, 221));
  printf("%i\n", mcm(247, 221));
  return 0;
}
