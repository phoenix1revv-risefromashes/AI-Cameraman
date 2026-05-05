
---

# 📄 `05_motion_control_architecture.md`

```markdown
# Motion Control Architecture

## Overview

The motion control system translates high-level commands into physical robot movement.

---

## Motion Pipeline

```text
Decision Layer
    ↓
Command Generation
    ↓
ESP32 Execution
    ↓
PWM Signals
    ↓
Motor Drivers
    ↓
Physical Movement
