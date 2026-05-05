
---

# 📄 `06_power_architecture.md`

```markdown
# Power Architecture

## Overview

The system uses a dual-voltage power architecture to separate high-power and low-power components.

---

## Power Flow

```text
12V Battery
    ├── Motors (12V)
    └── Buck Converter → 5V
                    ├── ESP32
                    └── Rasp pi 5
