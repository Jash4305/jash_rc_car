## Control Architecture

```text
                 ESP32
                   │
       ┌───────────┼──────────────┐
       │           │              │
     GPIO18      GPIO19       GPIO25/27
       │           │              │
   Steering       Door       LIGHT SYSTEM
    Servo         Servo           │
                                 GND.3
                              ┌───┴────┐
                              ↓        ↓
                           FRONT     REAR
                         HEADLIGHT   BRAKE
                           (25)       (27)
```