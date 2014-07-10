#include <stdio.h>
#include <limits.h>

#include "rand_tools.h"

void main(void) {
  register int i = 0;
  register int j = 0;

  int c[10] = { 0 };

  INIT_SRAND();

  for(i = 0; i < 10000; i++) {
    j = (int)(round(abs(rand_exp(0.3))));
    if (j > 9) j = 9;
    c[j]++;
  }

  for(i = 0; i < 10; i++) {
    printf("%d : %d\n", i, c[i]);
  }
}

