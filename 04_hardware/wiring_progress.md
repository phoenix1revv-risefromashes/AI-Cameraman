# Wiring Configuration

## Overview

This document describes the **physical and electrical wiring implementation** of the AI Cameraman system.

The wiring is divided into:

1. High-current motor power path
2. Low-voltage logic/control path
3. Signal wiring (ESP32 → drivers)
4. Grounding strategy

This stage focuses on **single-motor and initial multi-motor testing using ESP32 via USB serial control**.

---

# 1. System Wiring Architecture

## Functional Flow

```text
ESP32 GPIO → Control Signals → BTS7960 → Motor
                               ↑
                         12V Battery
                               ↓
                     Buck Converter → 5V Logic
                     
                     
                     
                     
                     
                     
#Pinmapping:


# 🔌 Pin Mapping & Wiring Reference

## Overview

This document defines the complete pin mapping between:

- ESP32 (controller)
- BTS7960 motor drivers
- Power system (battery + buck converter)

Each motor is controlled using one BTS7960 driver.

---

#  BTS7960 Pin Roles

| Pin | Type | Purpose |
|-----|------|--------|
| RPWM | Input | Forward PWM control |
| LPWM | Input | Reverse PWM control |
| R_EN | Input | Enable forward channel |
| L_EN | Input | Enable reverse channel |
| VCC | Power | 5V logic power |
| GND | Power | Ground reference |
| VM / B+ | Power | 12V motor power |
| B- | Power | Battery ground |
| OUT+ | Output | Motor terminal |
| OUT- | Output | Motor terminal |

---

# ESP32 → BTS7960 Mapping (FULL)

## 🔹 Motor 1 (Front Left)

| Function | BTS7960 Pin | ESP32 / Source |
|----------|------------|----------------|
| Forward PWM | RPWM | GPIO 14 |
| Reverse PWM | LPWM | GPIO 15 |
| Enable Right | R_EN | 5V rail |
| Enable Left | L_EN | 5V rail |
| Logic Power | VCC | 5V rail (buck converter) |
| Ground | GND | System ground |
| Motor Power | VM | 12V battery |
| Motor Output | OUT+/OUT- | Motor wires |

---

## 🔹 Motor 2 (Front Right)

| Function | BTS7960 Pin | ESP32 / Source |
|----------|------------|----------------|
| Forward PWM | RPWM | GPIO 16 |
| Reverse PWM | LPWM | GPIO 17 |
| Enable Right | R_EN | 5V rail |
| Enable Left | L_EN | 5V rail |
| Logic Power | VCC | 5V rail |
| Ground | GND | System ground |
| Motor Power | VM | 12V battery |
| Motor Output | OUT+/OUT- | Motor wires |

---

## 🔹 Motor 3 (Rear Left)

| Function | BTS7960 Pin | ESP32 / Source |
|----------|------------|----------------|
| Forward PWM | RPWM | GPIO 18 |
| Reverse PWM | LPWM | GPIO 19 |
| Enable Right | R_EN | 5V rail |
| Enable Left | L_EN | 5V rail |
| Logic Power | VCC | 5V rail |
| Ground | GND | System ground |
| Motor Power | VM | 12V battery |
| Motor Output | OUT+/OUT- | Motor wires |

---

## 🔹 Motor 4 (Rear Right)

| Function | BTS7960 Pin | ESP32 / Source |
|----------|------------|----------------|
| Forward PWM | RPWM | GPIO 25 |
| Reverse PWM | LPWM | GPIO 26 |
| Enable Right | R_EN | 5V rail |
| Enable Left | L_EN | 5V rail |
| Logic Power | VCC | 5V rail |
| Ground | GND | System ground |
| Motor Power | VM | 12V battery |
| Motor Output | OUT+/OUT- | Motor wires |

---

#  Power Connections (Global)

## High Power (Motor Side)

```text
12V Battery (+) → BTS7960 VM
12V Battery (–) → BTS7960 GND




