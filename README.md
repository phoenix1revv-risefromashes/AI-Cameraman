# AI Cameraman

## Overview
AI Cameraman is a voice-controlled autonomous robotic system designed to track a human subject and capture photos/videos from dynamic angles.

The system integrates computer vision, embedded control, and real-time motor actuation using a distributed architecture.

---

## System Architecture

Raspberry Pi (High-Level Control)
- Voice processing
- Decision-making
- Vision (planned)

ESP32 (Real-Time Control)
- Motor actuation
- PWM control
- Low-latency execution

Flow:
Voice → Decision → Communication → ESP32 → Motors

---

## Current Development Stage

The project is currently in the hardware integration and motor control validation phase.

---

## Progress So Far

### Completed
- ESP32 motor control via USB serial
- BTS7960 motor driver testing
- Individual motor movement verification
- Basic 4-motor wiring setup
- Power system design with buck converter

### In Progress
- UART communication (Raspberry Pi ↔ ESP32)
- Multi-motor coordination

### Next Steps
- Stabilize UART communication
- Implement command protocol
- Integrate voice command system
- Add human tracking using camera

---

## Repository Structure

- system/ → high-level control (Pi)
- firmware/ → ESP32 motor control
- tests/ → validation and experiments
- hardware/ → wiring and power system
- docs/ → architecture and design
- logs/ → development journal

---

## Author
Phoenix
