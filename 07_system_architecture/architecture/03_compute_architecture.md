# Compute Architecture

## Overview

The AI Cameraman system is designed using a **distributed compute architecture**, separating high-level intelligence from real-time execution.

This separation ensures:
- deterministic motor control
- scalability for AI and vision workloads
- modular system design
- easier debugging and fault isolation

---

## Compute Topology

```text
                HIGH-LEVEL COMPUTE (Decision Layer)

        ┌──────────────────────────────────────────┐
        │          Raspberry Pi 5                  │
        │        8GB RAM + 500GB NVMe SSD          │
        │------------------------------------------│
        │ Voice Processing                         │
        │ Decision Making                          │
        │ Vision (future)                          │
        │ Communication (UART/USB)                 │
        └───────────────┬──────────────────────────┘
                        │
                        │ Serial Communication
                        ▼
                REAL-TIME EXECUTION (Control Layer)

        ┌──────────────────────────────────────────┐
        │               STM32 Nucleo-F446RE                      │
        │------------------------------------------│
        │ Command Parsing                          │
        │ PWM Generation                           │
        │ Motor Control Logic                      │
        │ Deterministic Execution                  │
        └──────────────────────────────────────────┘
