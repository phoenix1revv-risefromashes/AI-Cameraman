# System Overview

AI Cameraman is a voice-controlled autonomous robotic camera platform designed to follow a human subject and capture photos/videos from dynamic angles.

The project is built as a distributed robotics system. Instead of making one board handle everything, the architecture separates high-level intelligence from real-time execution.

## Core System Idea

The robot receives a human command through voice, interprets the intent, decides the correct behavior, sends a structured movement command to the ESP32, and the ESP32 executes the motion through motor drivers.

## Main Pipeline

```text
Voice Command
    ↓
Raspberry Pi 5
    ↓
Decision System
    ↓
Serial/UART Command
    ↓
ESP32
    ↓
BTS7960 Motor Drivers
    ↓
4 DC Motors
    ↓
Robot Motion
