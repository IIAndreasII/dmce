#ifndef __DMCE_PROBE_FUNCTION_BODY__
#define __DMCE_PROBE_FUNCTION_BODY__

#include <linux/slab.h>
#include <linux/atomic.h>
#include <linux/printk.h>
#include <linux/panic.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <asm/page.h>

#define DMCE_BUF_SIZE (8 * DMCE_NBR_OF_PROBES)
#if (DMCE_BUF_SIZE < PAGE_SIZE)
#define DMCE_ALLOC() kmalloc(DMCE_BUF_SIZE, GFP_KERNEL)
#else
#define DMCE_ALLOC() vmalloc(DMCE_BUF_SIZE)
#endif

atomic64_t __attribute__((common)) *dmce_buffer;
atomic_t __attribute__((common)) dmce_buffer_allocated;
int __attribute__((common)) nbr_probes;


static void dmce_probe_body(unsigned int probenbr)
{
    if (atomic_fetch_inc(&dmce_buffer_allocated) == 0)
    {
        dmce_buffer = DMCE_ALLOC();
        memset(dmce_buffer, 0, DMCE_BUF_SIZE);
        printk("dmce_probe: dmce_buffer allocated %lu bytes at 0x%px", (long unsigned)DMCE_BUF_SIZE, dmce_buffer);
    }

    // Ugly way to propagate to dmce kernel module
    nbr_probes = DMCE_NBR_OF_PROBES;
    atomic64_fetch_inc(&dmce_magic[probenbr]);
}

#endif
