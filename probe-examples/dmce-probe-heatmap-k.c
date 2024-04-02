#ifndef __DMCE_PROBE_FUNCTION_BODY__
#define __DMCE_PROBE_FUNCTION_BODY__

#include <linux/slab.h>
#include <linux/atomic.h>
#include <linux/printk.h>


atomic64_t __attribute__((common)) *dmce_magic;

atomic_t __attribute__((common)) alloced;

int __attribute__((common)) nbr_probes;


static void dmce_probe_body(unsigned int probenbr) {

    if (atomic_fetch_inc(&alloced) == 0)
    {
        unsigned long num_bytes = sizeof(atomic_t) * DMCE_NBR_OF_PROBES;
        dmce_magic = kmalloc(num_bytes, GFP_KERNEL);
        printk("dmce_probe: dmce_magic allocated %lu bytes at 0x%px", num_bytes, dmce_magic);
    }

    // Ugly way to propagate to dmce kernel module
    nbr_probes = DMCE_NBR_OF_PROBES;
    atomic_fetch_inc(&dmce_magic[probenbr]);
}

#endif
