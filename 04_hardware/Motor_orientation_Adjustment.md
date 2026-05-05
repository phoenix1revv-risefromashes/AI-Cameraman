---

## 🔄 Motor Orientation Adjustment (Physical Wiring)

### Overview

During initial testing, motors that were wired identically produced **opposite rotation directions**.

This was not a wiring mistake, but a result of **motor orientation on the chassis**.

---

### Observed Behavior

```text
Same wiring + same command → different wheel rotation


therefore, for motors on the left side, the -ve and +ve connections from motors going to the Bts7960 driver module were reversed. This fixed the same spin direction.


