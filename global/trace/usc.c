/*$Id: usc.c,v 1.2 1995-02-02 23:14:40 d3g681 Exp $*/
/*
 * USC.C  (Source file for the Microsecond Clock package)
 *
 * Written by:  Arun Nanda    (07/17/91)
 */

#include "usc_main.h"


VOID usc_init()
{

#if defined(MULTIMAX)

	usc_multimax_timer = timer_init();
	usc_MD_rollover_val = (usc_time_t) ((1<<usc_MD_timer_size)-1);

#endif


#if (defined(BALANCE) || defined(SYMMETRY))

	unsigned long roll;

	usclk_init();

	roll = 1 << (usc_MD_timer_size-1);
	usc_MD_rollover_val = (usc_time_t) (roll + roll - 1);

#endif


#if (defined(BFLY2) || defined(BFLY2_TCMP))

	unsigned long roll;

	roll = 1 << (usc_MD_timer_size-1);
	usc_MD_rollover_val = (usc_time_t) (roll + roll - 1);

#endif


#if (defined(IPSC860_NODE) || defined(IPSC860_NODE_PGI) || defined(DELTA))

	esize_t hwtime;
	double ustime;

	hwtime.shigh = hwtime.slow = ~0x0;
        hwtime.shigh = (hwtime.shigh & 0x7) << (sizeof(long)*8-3);
        hwtime.slow = ((hwtime.slow >> 3) & ~(0x7 << (sizeof(long)*8-3)))
				| hwtime.shigh;
        ustime = (unsigned long)hwtime.slow * 0.8;
	usc_MD_rollover_val = (usc_time_t) ustime; 

#endif


#if (defined(ATT_3B2) || defined(SUN) || defined(IBM_RS6000) \
    || defined(NEXT) || defined(TITAN) || defined(BFLY1) || defined(KSR) \
    || defined(SGI) || defined(IPSC860_HOST) || defined(ALLIANT))

	struct timeval tp;
	struct timezone tzp;
	unsigned long roll;

	gettimeofday(&tp,&tzp);
	usc_MD_reference_time = (usc_time_t) tp.tv_sec;

	roll = (unsigned long)1 << ((sizeof(usc_time_t)*8)-1);
	roll = roll + roll - 1;
	usc_MD_rollover_val = (usc_time_t) (roll / 1000000);

#endif

}



usc_time_t usc_MD_clock()
{

#if (defined(BFLY2) || defined(BFLY2_TCMP))

	struct {
	    unsigned long hi;
	    unsigned long low;
	} usclock;

	get64bitclock(&usclock);
	return((usc_time_t)usclock.low);

#endif


#if (defined(IPSC860_NODE) || defined(IPSC860_NODE_PGI) || defined(DELTA))

	esize_t hwtime;
	double ustime;

	hwclock(&hwtime);
        hwtime.shigh = (hwtime.shigh & 0x7) << (sizeof(long)*8-3);
        hwtime.slow = ((hwtime.slow >> 3) & ~(0x7 << (sizeof(long)*8-3)))
				| hwtime.shigh;
        ustime = (unsigned long)hwtime.slow * 0.8;
	return((usc_time_t)ustime);

#endif


#if (defined(ATT_3B2) || defined(SUN) || defined(IBM_RS6000) \
    || defined(NEXT) || defined(TITAN) || defined(BFLY1) || defined(KSR) \
    || defined(SGI) || defined(IPSC860_HOST) || defined(ALLIANT))

	unsigned long ustime;
	struct timeval tp;
	struct timezone tzp;

	gettimeofday(&tp,&tzp);
	ustime = (unsigned long) (tp.tv_sec - usc_MD_reference_time);
	ustime = ustime % usc_MD_rollover_val;
	ustime = (ustime * 1000000) + (unsigned long) tp.tv_usec;

	return((usc_time_t) ustime);

#endif

}
