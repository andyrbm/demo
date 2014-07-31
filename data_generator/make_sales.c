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
  char *temp = NULL, buf[100] = { '\0' };
  time_t now_time = 0, iter_time = 0, campaign_end_time = 0;
  struct tm *ts = NULL;
  FILE *fp_sales = NULL, *fp_detail = NULL, *fp_campaign = NULL;

  uint32_t store_count[STORE_MAX + 1] = { 0U };
  uint32_t product_no[STORE_MAX + 1][PRODUCTS_MAX + 1] = { 0U };
  char used_product[PRODUCTS_MAX + 1] = { '\0' };
  uint32_t product_count[PRODUCTS_MAX + 1] = { 0U };

  uint32_t sales_interval = INTERVAL_STD, campaign_code = 0U, discount_rate = 0U;
  char cp_str[100] = { '\0' };

  if (argc < 5 || 5 < argc) {
    fprintf(stderr,
            "Create data to import to pgsql\n"
            "Usage: %s count sales.tsv detail.tsv campaign.tsv\n"
            "count        : Number of rows(data) to create\n"
            "sales.tsv    : Output Sales TSV to this file\n"
            "detail.tsv   : Output Detail TSV to this file\n"
            "campaign.tsv : Output campaign infomation TSV to this file\n",
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
  fp_campaign = fopen(argv[4], "w");
  if (!fp_sales || !fp_detail || !fp_campaign) {
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
  for (iter = 0, iter_time = now_time; iter < count; iter++, iter_time += (lrand() % sales_interval)) {
    store = lrand_exp((double)1.0, 1, 15);
    member = (uint32_t)(lrand() % (CUSTOMER_MAX * 3));
    memset(buf, '\0', sizeof(buf));

    ts = localtime(&iter_time);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ts);

    if (campaign_end_time < iter_time) {
      memset(cp_str, '\0', sizeof(cp_str));
      if (lrand_exp((double)1.0, 1, 10) >= 7) {
        campaign_code++;
        campaign_end_time =
          iter_time + lrand_exp((double)1.0, 4, 14) * (60 * 60 * 24);
        sales_interval = INTERVAL_STD / 2;
        discount_rate = lrand_exp((double)1.0, 1, 10) * 5;  // between 5% and 50%, step 5%
        snprintf(cp_str, sizeof(cp_str), "%u", campaign_code);
        fprintf(fp_campaign, "%u\t%u%% OFF Sale! (%ld)\t%u\n",
          campaign_code, discount_rate, campaign_end_time, discount_rate);
      } else {
        sales_interval = INTERVAL_STD;
        snprintf(cp_str, sizeof(cp_str), "\\N");
      }
    }

    /* We want to create NON member customers twice as members */
    if (0 < member && member <= CUSTOMER_MAX) {
      fprintf(fp_sales, "%d\t%s\t%u\t%u\t%s\n", iter, buf, member, store, cp_str);
    } else {
      fprintf(fp_sales, "%d\t%s\t\\N\t%u\t%s\n", iter, buf, store, cp_str);
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
  if (fp_campaign != NULL)  fclose(fp_campaign);

  return res;
}
