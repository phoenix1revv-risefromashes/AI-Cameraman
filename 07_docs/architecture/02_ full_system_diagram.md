
---

## `docs/architecture/02_full_system_diagram.md`

```markdown
# Full System Diagram

This document shows the full AI Cameraman architecture from user input to physical robot motion.

## Complete System View

```text
┌────────────────────────────────────────────────────────────────────┐
│                              USER                                  │
│                                                                    │
│  Gives voice command:                                              │
│  "follow me", "stop", "move forward", "take picture"             │
└───────────────────────────────┬────────────────────────────────────┘
                                │
                                ▼
┌────────────────────────────────────────────────────────────────────┐
│                      VOICE INPUT LAYER                             │
│                                                                    │
│  Purpose: capture spoken input and convert it into text/intent      │
│                                                                    │
│  Future modules:                                                   │
│  - wake_word.py                                                    │
│  - speech_listener.py                                              │
│  - command_parser.py                                               │
└───────────────────────────────┬────────────────────────────────────┘
                                │
                                ▼
┌────────────────────────────────────────────────────────────────────┐
│                    RASPBERRY PI 5                                  │
│                    8GB RAM + 500GB NVMe SSD                        │
│                                                                    │
│  Role: High-level robot brain                                      │
│                                                                    │
│  Responsibilities:                                                 │
│  - voice command processing                                        │
│  - behavior selection                                              │
│  - future computer vision                                          │
│  - camera stream handling                                          │
│  - decision-making                                                 │
│  - serial command generation                                       │
└───────────────────────────────┬────────────────────────────────────┘
                                │
                                ▼
┌────────────────────────────────────────────────────────────────────┐
│                       DECISION LAYER                               │
│                                                                    │
│  Converts user intent into robot behavior.                         │
│                                                                    │
│  Example:                                                          │
│  "follow me" does not directly mean FORWARD.                       │
│  It means:                                                         │
│  - detect subject                                                  │
│  - estimate position                                               │
│  - maintain distance                                               │
│  - keep subject centered                                           │
│  - move only when safe                                             │
│                                                                    │
│  Planned modules:                                                  │
│  - behavior_manager.py                                             │
│  - motion_planner.py                                               │
│  - safety_rules.py                                                 │
└───────────────────────────────┬────────────────────────────────────┘
                                │
                                ▼
┌────────────────────────────────────────────────────────────────────┐
│                    COMMUNICATION LAYER                             │
│                                                                    │
│  Converts robot decisions into structured serial commands.          │
│                                                                    │
│  Example commands:                                                 │
│  - FORWARD:120                                                     │
│  - BACKWARD:100                                                    │
│  - LEFT:90                                                         │
│  - RIGHT:90                                                        │
│  - STOP                                                            │
│                                                                    │
│  Planned modules:                                                  │
│  - serial_link.py                                                  │
│  - protocol.py                                                     │
└───────────────────────────────┬────────────────────────────────────┘
                                │
                                │ UART / USB Serial
                                ▼
┌────────────────────────────────────────────────────────────────────┐
│                              ESP32                                 │
│                                                                    │
│  Role: real-time motor execution controller                        │
│                                                                    │
│  Responsibilities:                                                 │
│  - receive serial commands                                         │
│  - parse movement instructions                                     │
│  - generate PWM signals                                            │
│  - control motor direction                                         │
│  - execute emergency stop quickly                                  │
└───────────────────────────────┬────────────────────────────────────┘
                                │
                                │ PWM + direction signals
                                ▼
┌────────────────────────────────────────────────────────────────────┐
│                       BTS7960 MOTOR DRIVERS                        │
│                                                                    │
│  Role: high-current motor power stage                              │
│                                                                    │
│  The ESP32 cannot power motors directly.                           │
│  The BTS7960 modules act as power switches between the battery      │
│  and motors while being controlled by low-power ESP32 signals.      │
└───────────────────────────────┬────────────────────────────────────┘
                                │
                                ▼
┌────────────────────────────────────────────────────────────────────┐
│                         MOTION SYSTEM                              │
│                                                                    │
│  - 4 DC motors                                                     │
│  - Mecanum movement planned                                        │
│  - Forward/backward movement tested                                │
│  - Lateral and rotational movement planned                         │
└────────────────────────────────────────────────────────────────────┘
