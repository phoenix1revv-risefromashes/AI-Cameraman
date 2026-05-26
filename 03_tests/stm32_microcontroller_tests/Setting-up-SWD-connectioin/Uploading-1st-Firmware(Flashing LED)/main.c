#include <stdint.h>

#define GPIOA_BASE 0x40020000UL
#define RCC_BASE 0x40023800UL

#define OFFSET_RCC_AHB1ENR 0x30
#define OFFSET_GPIOA_MODER 0x00
#define OFFSET_GPIOA_ODR 0x14

#define GPIOA_MODER_STATE (*(volatile uint32_t *) (GPIOA_BASE + OFFSET_GPIOA_MODER))
#define GPIOA_ODR_STATE (*(volatile uint32_t *) (GPIOA_BASE + OFFSET_GPIOA_ODR))
#define RCC_AHB1ENR_STATE (*(volatile uint32_t *)(RCC_BASE + OFFSET_RCC_AHB1ENR))



void delay7(void) {
    for (volatile uint32_t i=0; i<700000;i++);
}

void delay5(void) {
    for (volatile uint32_t i=0; i<500000;i++);
}

void delay3(void) {
    for (volatile uint32_t i=0; i<300000;i++);
}


int main () {
    RCC_AHB1ENR_STATE |=(1U << 0); //enabled clock cycle for gpioa peripheral block
    GPIOA_MODER_STATE &= ~(3U<<10); //TURNED OFF THE BIT 10, 11
    GPIOA_MODER_STATE |= (1U << 10); //MADE 01 STATE WHICH IS OUTPUT

    while(1){
        GPIOA_ODR_STATE |= (1U<<5);
        delay7();

        GPIOA_ODR_STATE &= ~(1U<<5);
        delay7();

        GPIOA_ODR_STATE |= (1U<<5);
        delay5();

        GPIOA_ODR_STATE &= ~(1U<<5);
        delay5();


        GPIOA_ODR_STATE |= (1U<<5);
        delay3();

        GPIOA_ODR_STATE &= ~(1U<<5);
        delay3();


    }
}
