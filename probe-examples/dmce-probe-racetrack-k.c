#ifndef __DMCE_PROBE_FUNCTION_BODY__
#define __DMCE_PROBE_FUNCTION_BODY__


/* read the cpu timestamp counter */
static unsigned long dmce_rdtsc(void)
{
#if defined(__x86_64__)
    unsigned long hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi) : : "memory");
    return ((hi << 32) | lo);

#elif defined(__x86__)
    unsigned int hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi) : : "memory");
    return lo;

#else
#error Architecture not supported!
#endif
}

/* spins t number timestamp counter ticks */
static void spin_tsc(unsigned long t)
{
    unsigned long later = dmce_rdtsc() + t;
    while(dmce_rdtsc() < later);
}


static void dmce_probe_body(unsigned int probenbr, unsigned long delay)
{
    (void)probenbr;
    spin_tsc(delay);
}


#endif