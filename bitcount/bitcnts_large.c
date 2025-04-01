/* +++Date last modified: 05-Jul-1997 */

/*
**  BITCNTS.C - Test program for bit counting functions
**
**  public domain by Bob Stout & Auke Reitsma
*/

#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include <limits.h>
#include <time.h>
#include <float.h>
#include "bitops.h"
#include "pico/stdlib.h"
#include "hardware/structs/pio.h"
#include "hardware/structs/otp.h"
#include "power_functions.h"
#include "instruction_count.h"


#define FUNCS  7

static int bit_shifter(long int x);

int main(void) {
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

    stdio_init_all();
    printf("Starting Bitcounts Large");

    uint32_t archReg = otp_hw->archsel_status;
    bool arch = (archReg & 0x1); //0 is arm and 1 is risc-v

    if (arch) {
        printf("Hello from RISC-V!\n");
    } else {
        printf("Hello from ARM!\n");
    }

    initPowerTesting();
    enableClockCount();

    uint64_t start, stop;
    int argc = 2;
    const char* argv = "1125000";
  double ct, cmin = DBL_MAX, cmax = 0;
  int i, cminix, cmaxix;
  long j, n, seed;
  int iterations;
  static int (* CDECL pBitCntFunc[FUNCS])(long) = {
    bit_count,
    bitcount,
    ntbl_bitcnt,
    ntbl_bitcount,
    /*            btbl_bitcnt, DOESNT WORK*/
    BW_btbl_bitcount,
    AR_btbl_bitcount,
    bit_shifter
  };
  static char *text[FUNCS] = {
    "Optimized 1 bit/loop counter",
    "Ratko's mystery algorithm",
    "Recursive bit count by nybbles",
    "Non-recursive bit count by nybbles",
    /*            "Recursive bit count by bytes",*/
    "Non-recursive bit count by bytes (BW)",
    "Non-recursive bit count by bytes (AR)",
    "Shift and count bits"
  };
  if (argc<2) {
    fprintf(stderr,"Usage: bitcnts <iterations>\n");
    exit(-1);
	}
  iterations=atoi(argv);

  uint64_t time1, time2;
    uint64_t cycles1, cycles2;
    uint64_t instructions1, instructions2;

  puts("Bit counter algorithm benchmark\n");
  startBenchmark();
    sleep_ms(50);

    startPowerTesting();
time1 = time_us_64();
cycles1 = cycleCount();
instructions1 = numberInstructions();
  for (i = 0; i < FUNCS; i++) {
    start = time_us_64();

    for (j = n = 0, seed = rand(); j < iterations; j++, seed += 13)
	 n += pBitCntFunc[i](seed);

    stop = time_us_64();
    ct = (stop - start);
    if (ct < cmin) {
	 cmin = ct;
	 cminix = i;
    }
    if (ct > cmax) {
	 cmax = ct;
	 cmaxix = i;
    }

    //printf("%-38s> Time: %.0f sec.; Bits: %ld\n", text[i], ct, n);
  }
  //printf("\nBest  > %s\n", text[cminix]);
  //printf("Worst > %s\n", text[cmaxix]);

  time2 = time_us_64();
    cycles2 = cycleCount();
    instructions2 = numberInstructions();
    stopPowerTesting();

    printf("Time taken: %.4f ms\n", (float)(time2 - time1) / 1000);
    printf("Instructions executed: %llu\n", instructions2 - instructions1);
    printf("Clock cycles: %llu\n", cycles2 - cycles1);

    //Put this at the end of all benchmarks to help the data collector
    printf("\nEnd of benchmark\n");
    sleep_ms(50);
    stopBenchmark();
    //Put this at the end because picotool doesn't like connecting after main finishes
    while(true);
}

static int bit_shifter(long int x)
{
  int i, n;

  for (i = n = 0; x && (i < (sizeof(long) * CHAR_BIT)); ++i, x >>= 1)
    n += (int)(x & 1L);
  return n;
}
