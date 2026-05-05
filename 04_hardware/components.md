# Hardware Components

## Overview

This document lists the physical hardware components used in the AI Cameraman system.

AI Cameraman is built as a distributed robotic platform with:

- Raspberry Pi 5 as the high-level compute unit
- ESP32 as the real-time motor controller
- Mecanum chassis for omnidirectional movement
- BTS7960 motor drivers for high-current motor control
- Dedicated camera and microphone hardware for future vision and voice control

The hardware is organized into compute, motion, power, sensing, wiring, and mechanical subsystems.

---

# 1. Compute System

## Raspberry Pi 5

### Specifications
- Model: Raspberry Pi 5
- RAM: 8GB
- Storage: 500GB NVMe SSD
- Role: High-level robot brain

### Responsibilities
The Raspberry Pi handles the high-level intelligence of the robot.

Planned responsibilities include:

- voice command processing
- decision-making
- future computer vision
- camera stream handling
- system coordination
- communication with ESP32

### Why Raspberry Pi 5?
The Raspberry Pi 5 is used because it can run a full Linux-based environment and support Python, camera tools, audio tools, OpenCV, and future AI/vision workloads.

---

## NVMe SSD

### Specifications
- Capacity: 500GB
- Interface: NVMe SSD through Raspberry Pi 5 NVMe setup

### Role
The NVMe SSD provides fast and reliable storage for:

- project code
- system logs
- captured photos/videos
- future datasets
- future computer vision models
- testing and debugging files

### Why NVMe?
Compared to microSD storage, NVMe provides:

- faster read/write speeds
- better reliability
- more storage space
- better support for media-heavy workloads

---

## ESP32

### Role
The ESP32 is the real-time execution controller.

It receives commands from the Raspberry Pi and directly controls the motor drivers.

### Responsibilities
- receive serial commands
- parse movement commands
- generate PWM signals
- control motor direction
- execute stop commands quickly
- eventually handle encoder feedback

### Interfaces
- USB serial for current testing
- UART communication planned for Raspberry Pi ↔ ESP32 control

### Why ESP32?
The ESP32 is better suited for real-time motor control than the Raspberry Pi because it can generate stable PWM signals without relying on Linux timing.

---

# 2. Motion System

## Mecanum Chassis

### Type
- Four-wheel mecanum-drive mobile platform

### Role
The mecanum chassis allows the robot to support omnidirectional movement.

This is important for a camera robot because it can reposition itself without needing to turn like a normal car-style robot.

### Motion Capabilities
Planned movement types include:

- forward movement
- backward movement
- lateral left/right movement
- rotation in place
- diagonal movement
- smooth cinematic motion paths

### Why Mecanum?
Mecanum wheels are useful for AI Cameraman because they support dynamic camera positioning.

This allows the robot to perform movements such as:

- side tracking shots
- orbit-like movement
- repositioning while keeping the subject in frame
- smoother subject-following behavior

---

## DC Motors

### Quantity
- 4 DC motors

### Voltage
- 12V motors

### Encoder Support
- Motors include encoder wiring
- 6-wire configuration observed:
  - 2 wires for motor power
  - 4 wires for encoder signals

### Role
Each motor drives one wheel on the mecanum chassis.

### Current Status
- Individual motor movement has been tested
- Forward/backward behavior has been verified
- Full coordinated 4-motor movement is in progress

---

## Motor Drivers — BTS7960

### Quantity
- 4 BTS7960 motor driver modules

### Role
The BTS7960 drivers act as the power interface between the ESP32 and the motors.

The ESP32 cannot directly power motors, so the BTS7960 modules switch high-current motor power using low-power control signals from the ESP32.

### Responsibilities
- drive 12V DC motors
- control motor direction
- accept PWM speed control
- handle higher motor current than the ESP32 can provide

### Typical Control Signals
BTS7960 modules commonly use:

- RPWM
- LPWM
- R_EN
- L_EN
- VCC
- GND
- motor power input
- motor output terminals

### Current Status
- BTS7960 testing has started
- Motor control through ESP32 has been verified
- Grounding behavior requires further refinement

---

# 3. Power System

## Main Battery

### Type
- 12V LiFePO4 battery

### Capacity
- Approximately 10Ah

### Role
The battery is the main power source for the robot.

It powers:

- motor drivers
- DC motors
- buck converter input
- eventually the full robot power system

### Why 12V?
The motors are 12V motors, so a 12V battery provides the required motor voltage directly.

---

## Buck Converter

### Type
- DC-DC buck converter
- Adjustable voltage regulator

### Function
The buck converter steps down voltage from:

```text
12V → 5V
