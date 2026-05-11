# AI Cameraman

## Overview

AI Cameraman is an autonomous robotics and embedded systems project focused on building a voice-interactive robotic cameraman capable of:

- tracking a human subject
- following the subject dynamically
- responding to voice commands
- capturing photos/videos from multiple cinematic angles
- performing real-time robotic movement and decision-making

The system combines robotics, embedded systems, real-time motor control, voice interaction, computer vision, autonomous navigation, and distributed system architecture.

The long-term goal is to develop a fully autonomous robotic cinematography platform capable of intelligent movement, subject awareness, and voice-guided camera behavior.

---

## Current Prototype Stage

[![Robot Prototype Stage](05_assets/robot_build_photos/current-progress.png)](https://sofiauniversity-my.sharepoint.com/:f:/g/personal/santosh_bogati_sofia_edu/IgA31v3vTGQQS7aVL7Cg1fQVARlYgo7sM40RWyne4M3HtHk?e=OIZYYl)
Click in the picture to see the video demos: 


Current development stage focuses on:

- hardware integration
- power distribution
- ESP32 communication
- motor driver validation
- movement testing
- system architecture development

---

## Core System Objectives

The robot is being designed to:

- Identify and lock the human subject
- autonomously follow the locked-subject avoiding obstacles
- listen for voice commands especially during photo sessions and photograph accordingly (such as take portrait, take cinematic,..) 


---

## System Architecture

```text

Voice Commands
       ↓
Raspberry Pi 5
(High-Level Intelligence/RL)
       ↓
Decision Layer
       ↓
Communication Layer
       ↓
STM32F446RE MCU NUCLEO-F446RE (Upgraded from esp32 due to limitation)
(Real-Time Embedded Control)
       ↓
BTS7960 Motor Drivers
       ↓
Mecanum Wheel Drive System
```

---

## Distributed Control Architecture

### Raspberry Pi 5 — High-Level System

Responsibilities:

- voice command processing
- future computer vision pipeline
- human tracking logic
- decision-making
- command generation
- system coordination

Hardware:

- Raspberry Pi 5
- 8GB RAM
- 500GB NVMe SSD

### STM32F446RE MCU NUCLEO-F446RE — Real-Time Embedded Controller

Responsibilities:

- PWM motor control
- real-time command execution
- low-latency motor response
- motor driver actuation
- future encoder processing

Communication:

- pi -- STM32 comms successful through SWD system

---

# Embedded System Architecture Evolution

The project expanded into low-level ARM Cortex-M embedded debugging using a Raspberry Pi 5 configured as a GPIO-based SWD debugger for an STM32 Nucleo-F446RE.

This experimentation involved:

- OpenOCD configuration
- Linux GPIOD GPIO debugging
- GPIO-based SWD communication
- Cortex-M4 CPU detection
- CPU halt/reset control
- register inspection
- flash memory inspection
- vector table analysis
- low-level embedded debugging workflows

One important engineering discovery during development was that older Raspberry Pi OpenOCD configurations using:

```text
bcm2835gpio



## Hardware Stack

### Core Components

- Raspberry Pi 5, 8GB
- 500GB NVMe SSD
- STM32F446RE MCU NUCLEO-F446RE (upgraded from esp32 due to its limitation)
- 4 × BTS7960 motor drivers
- 4 × 12V DC motors with encoders
- Mecanum chassis
- 12V LiFePO4 battery
- Buck converter, 12V to 5V
- Logitech C270 camera
- Movo USB-1 microphone

### Additional Hardware

- XT60 connectors
- jumper wires
- breadboards
- acrylic mounting plates
- standoffs
- mounting tape
- motor wiring adapters

---

## Software Stack

### Raspberry Pi Side

- Python
- serial communication
- future voice processing
- future computer vision
- future autonomous behavior logic

### ESP32 Side

- Arduino C/C++
- PWM motor control
- serial command handling
- BTS7960 driver control

---

## Repository Structure

```text
AI-Cameraman/
│
├── 01_system/
│   ├── main.py
│   ├── voice/
│   │   ├── speech_listener.py
│   │   ├── command_parser.py
│   │   └── wake_word.py
│   ├── vision/
│   │   ├── camera_stream.py
│   │   ├── human_tracker.py
│   │   └── shot_framing.py
│   ├── decision/
│   │   ├── behavior_manager.py
│   │   ├── motion_planner.py
│   │   └── safety_rules.py
│   └── communication/
│       ├── serial_link.py
│       └── protocol.py
│
├── 02_firmware/
│   └── esp32_motor_controller/
│
├── 03_tests/
│   ├── motor_tests/
│   ├── uart_tests/
│   ├── voice_tests/
│   └── camera_tests/
│
├── 04_hardware/
│   ├── components.md
│   ├── wiring.md
│   ├── pinout.md
│   └── power_system.md
│
├── 05_assets/
│   └── robot_build_photos/
│
├── 06_logs/
│
├── 07_docs/
│   ├── architecture/
│   ├── troubleshooting/
│   └── development_notes/
│
├── README.md
├── LICENSE
└── requirements.txt
```

---

## Current Working Capabilities

Completed:

- STM32 -- Rasp-pi communication
- single motor text-command testing
- BTS7960 motor driver validation
- forward/backward/stop motor control
- initial 4-motor wiring setup
- power distribution design
- buck converter integration
- hardware documentation
- repository architecture organization

---

## Current Engineering Challenges

### Grounding Stability

A grounding instability issue was identified during motor testing.

Observed behavior:

- motors stopped unexpectedly when sharing certain ground paths
- grounding layout requires redesign and validation

Detailed investigation is documented in:

```text
04_hardware/wiring.md
04_hardware/pinout.md
```


---

## Development Progress

### Completed

- repository architecture designed
- hardware stack assembled
- power system integrated
- motor driver testing completed
- single motor movement testing completed
- initial communication testing completed
- current prototype documented

### In Progress

- stable grounding layout
- coordinated 4-motor movement
- cleaner power distribution

### Planned

- voice command integration
- human detection and tracking
- autonomous follow behavior
- camera-based shot framing
- encoder feedback integration
- AI-assisted movement behavior

---

## Development Roadmap

```text
1. Stabilize grounding and power distribution
2. Smooth motors moverment control
3. Enable coordinated 4-motor movement
4. Implement voice command pipeline
5. Integrate camera stream processing
6. Add human detection and tracking
7. Implement autonomous follow behavior
8. Add cinematic movement modes
9. Add encoder feedback and closed-loop control
10. Build full autonomous robotic cameraman system
```

---

## Hardware Notes

### Motor Orientation Adjustment

Because motors are mounted in mirrored orientation on the chassis, some motors initially rotated in opposite directions despite identical wiring.

This was corrected by reversing motor polarity on affected motors:

```text
OUT+ ↔ OUT-
```

This ensured consistent movement behavior across all wheels.

Detailed explanation available in:

```text
04_hardware/wiring.md
```

---

## Project Vision

The long-term vision of AI Cameraman is to create a fully autonomous robotic cinematography platform capable of:

- intelligent subject tracking
- voice interaction
- autonomous movement
- cinematic shot positioning
- AI-assisted camera behavior
- real-time robotic decision-making

---

## Author

Phoenix
