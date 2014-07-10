#ifndef RAND_TOOLS_H
#define RAND_TOOLS_H

#include <math.h>
#include <sys/types.h>
#include <inttypes.h>

#ifdef USE_MTWIST
#include "mtwist.h"

#define SET_SRAND(seed) mt_seed32((uint32_t)(seed))
#define INIT_SRAND() mt_bestseed()
#define Uniform() mt_ldrand()

#define lrand() mt_lrand()

#else /* USE_MTWIST */
#include <stdlib.h>
#include <time.h>

#define lrand() rand()

#define SET_SRAND(seed) srand((unsigned int)(seed))

static inline void INIT_SRAND(void) {
  time_t now_time = 0;
  unsigned int *seed = (unsigned int *)&now_time;

  if(time(&now_time) < 0) now_time = 0;
  srand(*seed);

  return;
}

static inline double Uniform(void) {
  int64_t temp1 = 0, temp2 = 0;

  temp1 = (int64_t)rand() + (int64_t)1;
  temp2 = (int64_t)RAND_MAX + (int64_t)2;

  return ((double)temp1) / ((double)temp2);
}

#endif /* USE_MTWIST */

/*
 * Exponential Distribution
 */
static inline double rand_exp(double lambda) {
  return -log(Uniform() / lambda);
}

/*
 * Standard Normal Distribution () (Central limit)
 */
static inline double rand_norm_cl(void) {
  double result = 0.0;
  int i = 0;

  for (i = 0; i < 12; i++) {
    result += Uniform();
  }

  return result - 6.0;
}

/*
 * Standard Normal Distribution (Box-Muller transform: use only sin())
 *
 * retuens random number from N(0, 1)
 */
static inline double rand_gauss(void) {
  return sqrt(-2.0 * log(Uniform())) * sin(2.0 * M_PI *Uniform());
}

/*
 * Normal Distribution
 *
 * returns random number from N(averagem, variance^2)
 */
static inline double rand_norm_bm(double average, double variance) {
  return variance * rand_gauss() + average;
}


static inline uint32_t lrand_exp(double l, uint32_t min, uint32_t max) {
  uint32_t result = 0;

  do {
    result = (uint32_t)(round(abs(rand_exp(l) * max))) + min;
  } while (result < min || max < result);

  return result;
}

#endif /* RAND_TOOLS_H */
