# Voice Control Architecture

## Overview

The voice control system serves as the primary human–robot interaction interface.

It is designed to convert natural language commands into structured robot actions through a multi-stage processing pipeline.

---

## Voice Processing Pipeline

```text
User Speech
    ↓
Audio Capture
    ↓
Speech Recognition
    ↓
Command Parsing
    ↓
Intent Extraction
    ↓
Decision Layer
