# Bare-Metal STM32 LED Blink Test

## Objective

Develop and flash a bare-metal STM32 program that directly controls the onboard LD2 LED through memory-mapped register manipulation without using HAL libraries or STM32CubeMX.

---

# Hardware Used

- STM32 Nucleo Board
- Raspberry Pi 5
- SWD debugger/programmer
- OpenOCD
- 

---

# GPIO Architecture Understanding

The onboard LD2 LED is connected to:

```text
PA5
```

Meaning:

- Port: GPIOA
- Pin: 5

GPIOA contains:
- PA0 → PA15

Each GPIO port contains:
- registers
- pin configuration logic
- output/input circuitry

---

# Important Registers Used

| Register | Purpose |
|---|---|
| RCC_AHB1ENR | Enable GPIOA peripheral clock |
| GPIOA_MODER | Configure PA5 mode |
| GPIOA_ODR | Control PA5 output voltage |

---

# Base Addresses

```c
#define GPIOA_BASE 0x40020000UL
#define RCC_BASE   0x40023800UL
```

---

# Register Offsets

```c
#define OFFSET_RCC_AHB1ENR 0x30
#define OFFSET_GPIOA_MODER 0x00
#define OFFSET_GPIOA_ODR   0x14
```

---

# Register Access Definitions

```c
#define GPIOA_MODER_STATE (*(volatile uint32_t *)(GPIOA_BASE + OFFSET_GPIOA_MODER))
#define GPIOA_ODR_STATE   (*(volatile uint32_t *)(GPIOA_BASE + OFFSET_GPIOA_ODR))
#define RCC_AHB1ENR_STATE (*(volatile uint32_t *)(RCC_BASE + OFFSET_RCC_AHB1ENR))
```

---

# Procedure

## 1. Enable GPIOA Peripheral Clock

```c
RCC_AHB1ENR_STATE |= (1U << 0);
```

This enables the GPIOA hardware block through the RCC peripheral.

---

## 2. Configure PA5 as Output

PA5 mode bits are:
- bit 10
- bit 11

Inside:
- GPIOA_MODER register

### Clear Existing Mode Bits

```c
GPIOA_MODER_STATE &= ~(3U << 10);
```

### Set Output Mode (`01`)

```c
GPIOA_MODER_STATE |= (1U << 10);
```

---

# LED Control

## Turn LED ON

```c
GPIOA_ODR_STATE |= (1U << 5);
```

Sets:
- ODR bit 5 = 1

Which drives:
- PA5 HIGH (~3.3V)

---

## Turn LED OFF

```c
GPIOA_ODR_STATE &= ~(1U << 5);
```

Clears:
- ODR bit 5

Which drives:
- PA5 LOW

---

# Delay Implementation

```c
void delay(void) {
    for (volatile uint32_t i = 0; i < 500000; i++);
}
```

Used to create visible LED blinking timing.

---

# Main Loop

```c
while(1){
    GPIOA_ODR_STATE |= (1U << 5);
    delay();

    GPIOA_ODR_STATE &= ~(1U << 5);
    delay();
}
```

Creates continuous LED blinking behavior.

---

# Startup File

A minimal startup file was created containing:

- vector table
- initial stack pointer
- Reset_Handler
- main() entry jump

---

# Linker Script

Custom linker script created to define:

- FLASH memory region
- RAM memory region
- section placement
- firmware entry point

---

# Compilation

```bash
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -g -O0 -nostdlib -T linker.ld startup.c main.c -o main.elf
```

---

# Flashing Procedure

## Start OpenOCD

```bash
openocd -f stm32-pi.cfg
```

---

## Open Telnet Interface

```bash
telnet localhost 4444
```

---

## Flash Firmware

```text
program main.elf verify reset
```

---

# Result

Successfully:
- configured STM32 GPIO registers manually
- compiled ARM Cortex-M4 firmware
- established bare-metal startup pipeline
- flashed firmware through OpenOCD
- controlled onboard LD2 LED through direct register manipulation
```
