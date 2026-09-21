## Circuit Diagram 

```text
                         ┌───────────────┐
                         │     ESP32     │
                         │               │
                GPIO18 ──┤               ├── GPIO25 → FRONT
                GPIO19 ──┤               ├── GPIO27 → BRAKE
                GPIO34 ──┤               │
                GPIO23 ──┤               │
                GPIO33 ──┤               │
                         └───────────────┘
                             │
                             │
       ┌──────────────┐      │      ┌──────────────┐
       │ POTENTIOMETER│──────┘      │   BUTTON H   │
       │   STEERING   │             │  HEADLIGHT   │
       └──────────────┘             └──────────────┘

                                      ┌──────────────┐
                                      │   BUTTON D   │
                                      │     DOOR     │
                                      └──────────────┘

```

## Control Architecture

```text
                                  ESP32
                                    │
      ┌───────────────┬─────────────┼─────────────┬──────────────┐
      │               │             │             │              │
   GPIO34          GPIO23        GPIO33        GPIO18         GPIO19
      │               │             │             │              │
      ▼               ▼             ▼             │              │
POTENTIOMETER     BUTTON 1      BUTTON 2          │              │
      │               │             │             │              │
      ▼               │             │             │              │
  STEERING            ▼             ▼             ▼              ▼
   SERVO         HEADLIGHTS        DOOR        STEERING         DOOR
   (INPUT)        CONTROL        CONTROL        SERVO          SERVO
                  (INPUT)        (INPUT)       (OUTPUT)       (OUTPUT)
                     │
                     │ (Controls Data)
                     ▼
             GHT SYSTEM (GPIO25/27)
                     │
                     ├─── Common GND
                     │
                ┌────┴────┐
                ↓         ↓
              FRONT      REAR
            HEADLIGHT    BRAKE
            (GPIO25)   (GPIO27)
```

## Current pin map 🔒

|   GPIO | Function               | Status |
| -----: | ---------------------- | ------ |
| **18** | Steering servo         | ✅      |
| **19** | Door servo             | ✅      |
| **25** | Front lights           | ✅      |
| **27** | Brake/rear lights      | ✅      |
| **34** | Steering potentiometer | ✅      |
| **23** | Headlight button       | ✅      |
| **33** | Door button            | ✅      |

