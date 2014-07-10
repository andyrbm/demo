#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>
#include <time.h>

#include "rand_tools.h"

#include "demo_limits.h"

int main(int argc, char *argv[]) {
  register int iter = 0;
  int iter2 = 0, res = 0;
  uint32_t count = 0, store = 0, member = 0, item = 0, item_count = 0, item_total = 0;
  char *temp = NULL, buf[100] = { (char)0 };
  time_t now_time = 0, iter_time = 0;
  struct tm *ts = NULL;
  FILE *fp_sales = NULL, *fp_detail = NULL;

  uint32_t store_count[STORE_MAX + 1] = { 0U };
  uint32_t product_no[STORE_MAX + 1][PRODUCTS_MAX + 1] = { 0U };
  char used_product[PRODUCTS_MAX + 1] = { '\0' };
  uint32_t product_count[PRODUCTS_MAX + 1] = { 0U };

  if (argc < 4 || 4 < argc) {
    fprintf(stderr,
            "Create data to import to pgsql\n"
            "Usage: %s count sales.tsv detail.tsv\n"
            "count      : Number of rows(data) to create\n"
            "sales.tsv  : Output Sales TSV to this file\n"
            "detail.tsv : Output Detail TSV to this file\n",
            argv[0]);
    return 1;
  }

  count = strtoul(argv[1], &temp, 10);
  if (*temp != '\0') {
    fprintf(stderr, "Invalid Argument\n");
    return 1;
  }

  fp_sales = fopen(argv[2], "w");
  fp_detail = fopen(argv[3], "w");
  if (!fp_sales || !fp_detail) {
    fprintf(stderr, "Can't open output file(s)\n");
    res = 2;
    goto failed;
  }

  INIT_SRAND();

  (void) time(&now_time);

  /* Stir product no */
  for (iter = 1; iter <= STORE_MAX; iter++) {
    memset(used_product, '\0', sizeof(used_product));

    for (iter2 = 1; iter2 <= PRODUCTS_MAX; iter2++) {
      do {
        item = (lrand() % PRODUCTS_MAX) + 1;
      } while (used_product[item] == 'X');

      used_product[item] = 'X';
      product_no[iter][iter2] = item;
    }
  }

  /* Make test data */
  for (iter = 0, iter_time = now_time; iter < count; iter++, iter_time += (lrand() % 30)) {
    store = lrand_exp((double)1.0, 1, 15);
    member = (uint32_t)(lrand() % (CUSTOMER_MAX * 3));
    memset(buf, '\0', sizeof(buf));

    ts = localtime(&iter_time);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ts);

    /* We want to create NON member customers twice as members */
    if (0 < member && member <= CUSTOMER_MAX) {
      fprintf(fp_sales, "%d\t%s\t%u\t%u\n", iter, buf, member, store);
    } else {
      fprintf(fp_sales, "%d\t%s\t\\N\t%u\n", iter, buf, store);
    }

    item_total = (lrand() % TOTAL_MAX) + 1;
    memset(used_product, '\0', sizeof(used_product));
    for (iter2 = 0; iter2 < item_total; iter2++) {
      do {
        item = lrand_exp((double)1.0, 1, PRODUCTS_MAX);
      } while (used_product[item] == 'X');
      item_count = (lrand() % COUNT_MAX) + 1;

      fprintf(fp_detail, "%d\t%u\t%u\n",
        iter, product_no[store][item], item_count);

      product_count[product_no[store][item]] += item_count;
      used_product[item] = 'X';
    }

    store_count[store]++;
  }

  for (iter = 0; iter <= STORE_MAX; iter++) {
    printf("Store [%d] : %u\n", iter, store_count[iter]);
  }
  printf("\n");
  for (iter = 0; iter <= PRODUCTS_MAX; iter++ ) {
    printf("Products [%d] : %u\n", iter, product_count[iter]);
  }


failed :
  if (fp_detail != NULL) fclose(fp_detail);
  if (fp_sales != NULL)  fclose(fp_sales);

  return res;
}
