# STM32 SWD Debugging via Raspberry Pi 5

## Overview

This documentation describes a low-level embedded debugging experiment where a Raspberry Pi 5 was successfully used as a GPIO-based SWD (Serial Wire Debug) debugger for an STM32 Nucleo-F446RE development board.

The goal of this experiment was to understand and manually build a complete ARM Cortex-M debug pipeline without relying on the onboard ST-LINK USB debugger.

This setup demonstrated:

* SWD protocol communication
* OpenOCD configuration and usage
* Raspberry Pi 5 GPIO-based debugging
* ARM Cortex-M4 CPU register inspection
* Flash memory inspection
* Direct CPU halt and reset control
* Vector table inspection
* Low-level embedded systems debugging

---

# System Architecture

The final architecture looked like this:

```text
Raspberry Pi 5
    ↓
OpenOCD
    ↓
Linux GPIOD GPIO Control
    ↓
GPIO Bit-Banged SWD
    ↓
SWDIO / SWCLK Physical Wiring
    ↓
STM32 SWD Debug Hardware
    ↓
ARM Cortex-M4 CPU
```

---

# Hardware Used

## Main Devices

* Raspberry Pi 5
* STM32 Nucleo-F446RE
* Dupont jumper wires

---

# Understanding SWD

SWD stands for:

```text
Serial Wire Debug
```

It is a low-level ARM debugging protocol used for:

* flashing firmware
* halting CPUs
* reading memory
* inspecting registers
* stepping through instructions
* setting breakpoints

SWD typically uses two main signals:

| Signal | Purpose          |
| ------ | ---------------- |
| SWDIO  | Debug data line  |
| SWCLK  | Debug clock line |

# Wiring Used

## Raspberry Pi 5 → STM32 Nucleo-F446RE

| Raspberry Pi 5           | STM32 Nucleo-F446RE |
| ------------------------ | ------------------- |
| GPIO24 / physical pin 18 | SWDIO               |
| GPIO25 / physical pin 22 | CLK / SWCLK         |
| GND                      | GND                 |
| 3.3V                     | 3.3V reference      |

Important:

```text
Only 3.3V logic was used.
5V was NOT connected.
```

---

# Important Raspberry Pi 5 Discovery

Older OpenOCD tutorials commonly use:

```text
bcm2835gpio
```

However, Raspberry Pi 5 uses a newer GPIO architecture.

Initial attempts failed with:

```text
Error: open /dev/gpiomem: No such file or directory
```

The successful solution was switching to:

```text
linuxgpiod
```

and explicitly specifying:

```text
-chip 4
```

for Raspberry Pi 5 GPIO access.

---

# Installing OpenOCD

OpenOCD stands for:

```text
Open On-Chip Debugger
```

It acts as the bridge between:

* the Raspberry Pi GPIO pins
* the SWD protocol
* the STM32 ARM debug hardware

Install OpenOCD:

```bash
sudo apt update
sudo apt install openocd -y
```

---

# Final OpenOCD Config Used

File name:

```text
stm32-pi.cfg
```

Config contents:

```text
adapter driver linuxgpiod

transport select swd

adapter gpio swclk -chip 4 25
adapter gpio swdio -chip 4 24

adapter speed 10

source [find target/stm32f4x.cfg]
```

---

# Engineering Meaning of the Config

## adapter driver linuxgpiod

Tells OpenOCD:

```text
Use Linux GPIOD interface to access Raspberry Pi GPIO pins.
```

This was required for Raspberry Pi 5 compatibility.

---

## transport select swd

Tells OpenOCD:

```text
Use SWD protocol instead of JTAG.
```

---

## adapter gpio swclk -chip 4 25

Assigns:

```text
GPIO25 = SWCLK
```

This pin generates SWD clock timing.

---

## adapter gpio swdio -chip 4 24

Assigns:

```text
GPIO24 = SWDIO
```

This pin carries SWD data.

---

## adapter speed 10

Attempts to configure debug speed.

For linuxgpiod on Raspberry Pi 5, OpenOCD reported:

```text
adapter speed not implemented
```

but communication still worked successfully.

---

## source [find target/stm32f4x.cfg]

Loads STM32F4-specific ARM target definitions.

This gives OpenOCD knowledge about:

* STM32F4 flash layout
* Cortex-M4 architecture
* breakpoints
* memory maps
* debug behavior

---

# Starting OpenOCD

Command used:

```bash
sudo openocd -f stm32-pi.cfg
```

Engineering meaning:

| Part         | Meaning                        |
| ------------ | ------------------------------ |
| sudo         | Run with root privileges       |
| openocd      | Launch OpenOCD debugger server |
| -f           | Load config file               |
| stm32-pi.cfg | Hardware/debug configuration   |

---

# Successful Detection Output

The successful SWD connection produced:

```text
Info : SWD DPIDR 0x2ba01477 DPv1
Info : [stm32f4x.cpu] Cortex-M4 r0p1 processor detected
Info : [stm32f4x.cpu] target has 6 breakpoints, 4 watchpoints
Info : [stm32f4x.cpu] Examination succeed
Info : [stm32f4x.cpu] starting gdb server on 3333
```

---

# Engineering Meaning of the Successful Output

## SWD DPIDR

This confirmed:

```text
ARM debug hardware handshake succeeded.
```

---

## Cortex-M4 processor detected

This confirmed:

```text
OpenOCD successfully identified the STM32 CPU.
```

---

## hardware has 6 breakpoints, 4 watchpoints

This confirmed:

```text
ARM hardware debugging features are accessible.
```

---

## Examination succeed

This confirmed:

```text
The target MCU was successfully initialized and inspected.
```

---

# Connecting to OpenOCD

OpenOCD exposes a telnet command interface on port 4444.

Install telnet:

```bash
sudo apt install telnet -y
```

Connect to OpenOCD:

```bash
telnet localhost 4444
```

---

# Engineering Meaning of Telnet Connection

Architecture:

```text
Terminal
    ↓
Telnet Client
    ↓
TCP Socket Connection
    ↓
OpenOCD Command Server
    ↓
SWD Protocol
    ↓
STM32 Cortex-M4
```

OpenOCD acts as a debug server.

Telnet acts as a client used to send debugging commands.

---

# Testing the Connection

## Command

```text
targets
```

Meaning:

```text
Display connected debug targets.
```

Output:

```text
0* stm32f4x.cpu cortex_m little stm32f4x.cpu running
```

This confirmed:

```text
STM32 Cortex-M4 target is actively connected.
```

---

# Reset and Halt Test

## Command

```text
reset halt
```

Meaning:

```text
1. Reset STM32
2. Immediately halt CPU execution
3. Give debugger control over the processor
```

Output:

```text
[stm32f4x.cpu] halted due to debug-request, current mode: Thread
xPSR: 0x01000000 pc: 0x080025a4 msp: 0x200004b8
```

---

# Engineering Meaning of the Halt Output

## xPSR

CPU status register.

Contains:

* execution state
* condition flags
* interrupt state

---

## PC (Program Counter)

```text
pc: 0x080025a4
```

This is:

```text
address of next instruction being executed
```

The address is inside STM32 flash memory.

---

## MSP (Main Stack Pointer)

```text
msp: 0x200004b8
```

This points into STM32 SRAM.

It stores:

* function stack frames
* temporary execution data
* local variables
* return addresses

---

# Register Inspection

## Command

```text
reg
```

Meaning:

```text
Display ARM Cortex-M4 CPU registers.
```

Important registers observed:

```text
sp: 0x200004b8
pc: 0x080025a4
xpsr: 0x01000000
```

---

# Engineering Meaning of Registers

Registers are:

```text
tiny ultra-fast storage locations inside the CPU core
```

They are used for:

* temporary computation
* memory addresses
* arithmetic
* execution control
* stack management

Examples:

| Register | Purpose                           |
| -------- | --------------------------------- |
| r0-r12   | General purpose working registers |
| sp       | Stack pointer                     |
| lr       | Link register / return address    |
| pc       | Program counter                   |
| xPSR     | CPU status register               |

---

# Reading Flash Memory

## Command

```text
mdw 0x08000000 8
```

Meaning:

| Part       | Meaning                  |
| ---------- | ------------------------ |
| m          | memory                   |
| d          | display                  |
| w          | 32-bit word              |
| 0x08000000 | STM32 flash base address |
| 8          | Display 8 words          |

---

# Flash Memory Output

```text
0x08000000: 200004b8 080025a5 08002311 08002313 08002315 08002317 08002319 00000000
```

---

# Engineering Meaning of Flash Output

## First Word

```text
200004b8
```

Initial stack pointer value.

Matches:

```text
msp: 0x200004b8
```

---

## Second Word

```text
080025a5
```

Reset handler address.

This is where CPU jumps after reset.

Matches observed:

```text
pc: 0x080025a4
```

The +1 is due to ARM Thumb mode encoding.

---

## Remaining Words

These are interrupt and exception vector addresses.

The vector table tells the CPU where to jump when:

* reset occurs
* interrupts happen
* faults occur

---

# What This Experiment Confirmed

This experiment successfully demonstrated:

* Raspberry Pi 5 GPIO-based SWD debugging
* OpenOCD communication with STM32
* ARM Cortex-M4 CPU detection
* direct CPU halt capability
* register inspection
* flash memory inspection
* vector table inspection
* live low-level embedded debugging

---

# Engineering Significance

This experiment provided hands-on experience with:

* ARM Cortex-M architecture
* SWD protocol
* OpenOCD
* Linux GPIO interfaces
* Cortex-M debug hardware
* CPU registers
* flash memory layout
* embedded debugging workflows
* low-level hardware/software interaction

This represents an important step toward building a more professional embedded robotics control architecture for the AI Cameraman system.
