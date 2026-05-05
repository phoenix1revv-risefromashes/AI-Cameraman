# Power System Design

## Overview
The AI Cameraman system uses a distributed power architecture to safely and efficiently supply different voltage levels required by motors and control electronics.

The system is powered by a 12V battery, with voltage regulation handled using a buck converter for lower-voltage components.

---

## Power Architecture

### Primary Source
- Battery Type: 12V rechargeable battery (LiFePO4)
- Nominal Voltage: 12V
- Purpose:
  - Directly powers high-current components (motors via drivers)

---

### Voltage Regulation (Buck Converter)

A DC-DC buck converter is used to step down voltage from 12V to 5V.

#### Function
- Converts high input voltage (12V) to stable lower voltage (5V)
- Maintains efficiency while reducing heat losses compared to linear regulators

#### Input
- Source: 12V battery
- Input Voltage Range: ~10V–14V

#### Output
- Regulated Voltage: 5V
- Used for:
  - ESP32
  - Logic-side inputs of motor drivers (BTS7960)
  - Future Raspberry Pi supply (if required)

---

## Component Power Distribution

| Component        | Voltage | Source                  |
|-----------------|--------|--------------------------|
| Motors (DC)      | 12V    | Direct from battery      |
| BTS7960 (VM)     | 12V    | Direct from battery      |
| BTS7960 (VCC)    | 5V     | Buck converter           |
| ESP32            | 5V     | Buck converter           |
| Raspberry Pi     | 5V     | (Planned via regulator)  |

---

## Wiring Strategy

### High-Power Path
- Battery → Motor Drivers → Motors
- Uses thicker wires to handle current spikes

### Low-Power Path
- Battery → Buck Converter → 5V Rail
- Supplies control electronics

---

## Observations and Issues

### Grounding Behavior
- Connecting ESP32 GND to common rail caused unexpected motor shutdown
- Indicates improper grounding or reference mismatch

### Hypothesis
- Potential ground loop or incorrect shared reference
- Possible noise or current interference affecting logic signals

---

## Safety Considerations

- Ensure common ground between all components (with proper layout)
- Avoid thin wires for high-current paths
- Use proper connectors (XT60 recommended)
- Verify polarity before powering system
- Monitor voltage output from buck converter before connecting sensitive components

---

## Future Improvements

- Add dedicated voltage regulator for Raspberry Pi
- Introduce fuse protection for safety
- Implement current monitoring
- Improve grounding layout (star grounding approach)

---

## Summary

The system uses a dual-voltage architecture:
- 12V for motors (high power)
- 5V regulated for control electronics

The buck converter is critical in ensuring stable operation of low-voltage components while maintaining efficiency and preventing damage.
