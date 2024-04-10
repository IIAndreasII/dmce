#ifndef __DMCE_PROBE_FUNCTION_BODY__
#define __DMCE_PROBE_FUNCTION_BODY__

#include <linux/slab.h>
#include <linux/atomic.h>
#include <linux/printk.h>
#include <linux/panic.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <linux/syscalls.h>
#include <asm/page.h>

#define DMCE_BUF_SIZE (sizeof(atomic_t) * DMCE_NBR_OF_PROBES)
#define DMCE_MAX_NUM_KTHREADS_HOPEFULLY (1024 * 16)

#define DMCE_NO_RECURSE 1

atomic_t __attribute__((common)) dmce_buffer[DMCE_NBR_OF_PROBES];
atomic_t __attribute__((common)) dmce_buffer_allocated;
int __attribute__((common)) nbr_probes;
static int done_init = 0;

int __attribute__((common)) dmce_anti_recurse_check[DMCE_MAX_NUM_KTHREADS_HOPEFULLY];

static void dmce_probe_body(unsigned int probenbr)
{
#if DMCE_NO_RECURSE
    pid_t kthread_id = current->pid;
    if (unlikely(dmce_anti_recurse_check[kthread_id]))
    {
        printk("dmce_porbe: probe recursion detected!");
        return;
    }
#endif

    if (unlikely(!done_init))
    {
        if (!atomic_fetch_inc(&dmce_buffer_allocated))
        {
            // Ugly way to propagate to dmce kernel module
            nbr_probes = DMCE_NBR_OF_PROBES;
            for (size_t i = 0; i < DMCE_NBR_OF_PROBES; i++)
            {
                atomic_set(&dmce_buffer[i], 0);
            }
            printk("dmce_probe: dmce_buffer allocated at address with size: 0x%px %lu", &dmce_buffer, (long unsigned)DMCE_BUF_SIZE);
        }
        done_init = 1;
    }

#if DMCE_NO_RECURSE
    dmce_anti_recurse_check[kthread_id] = 1;
#endif
    atomic_fetch_inc(&dmce_buffer[probenbr]);
#if DMCE_NO_RECURSE
    dmce_anti_recurse_check[kthread_id] = 0;
#endif
}

#endif
