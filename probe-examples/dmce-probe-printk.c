#ifndef __DMCE_PROBE_FUNCTION_BODY__
#define __DMCE_PROBE_FUNCTION_BODY__

#include <linux/atomic.h>


extern atomic_t counter;

// dumb probe that prints its number
static void dmce_probe_body(unsigned int probenbr) {

    int a = atomic_add_return(1, &counter);

    printk("Probe counter: %u - (%u)", a, probenbr);


}


#endif