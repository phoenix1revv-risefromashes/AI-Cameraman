#include <stdint.h>

extern int main(void);

void Reset_Handler(void);

__attribute__((section(".isr_vector")))
uint32_t vector_table[] = {
    0x20020000,
    (uint32_t)Reset_Handler
};

void Reset_Handler(void)
{
    main();

    while (1);
}

