/*$Id: usc_main.h,v 1.2 1995-02-02 23:14:42 d3g681 Exp $*/
/*
 * USC_MAIN.H  (Private header file for the Microsecond Clock package)
 *
 * Written by:  Arun Nanda    (07/17/91)
 *
 * The following machine-specific libraries need to be linked in
 * with the application using the UST functions:
 *
 *      MULTIMAX      -lpp
 *      BALANCE       -lseq
 *      SYMMETRY      -lseq
 */


#include "usc.h"


#if defined(MULTIMAX)

#    include <parallel.h>
#    define usc_MD_timer_size  (sizeof(unsigned)*8)
     unsigned *usc_multimax_timer;

#endif


#if (defined(BALANCE) || defined(SYMMETRY))

#    define usc_MD_timer_size  (sizeof(usclk_t)*8)

#endif


#if (defined(BFLY2) || defined(BFLY2_TCMP))

#    define usc_MD_timer_size  (sizeof(unsigned long)*8)

#endif


#if (defined(IPSC860_NODE) || defined(IPSC860_NODE_PGI) || defined(DELTA))

#    if (defined (DELTA))
#        include <mesh.h>
#    else
#        include <cube.h>
#    endif
#    define usc_MD_timer_size ((sizeof(long)*8)+3)
#    define usc_MD_ticks_per_usec (HWHZ/1000000)

#endif


#if (defined(ATT_3B2) || defined(SUN) || defined(IBM_RS6000) \
    || defined(NEXT) || defined(TITAN) || defined(BFLY1) || defined(KSR) \
    || defined(SGI) || defined(IPSC860_HOST) || defined(ALLIANT))

#	include <sys/time.h>
	usc_time_t usc_MD_reference_time = 0;

#endif


usc_time_t usc_MD_rollover_val = 0;

