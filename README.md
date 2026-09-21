# ESP32 Vehicle Control System

An ESP32-based embedded project designed to control a vehicle's steering, automated doors, headlights, and brake/rear lights using analog inputs and tactile buttons.

## 🛠️ Circuit Diagram

Refer to the realistic breadboard layout below when wiring your hardware components[cite: 2]:

![Breadboard Circuit Diagram](/images/title_photo.png)

---

## 🏗️ Control Architecture

```text
                        ESP32
                          │
        ┌───────────────┬─────────────┬─────────────┬──────────────┐
        │               │             │             │              │
       GPIO34          GPIO23        GPIO33        GPIO18         GPIO19
        │               │             │             │              │
        ▼               ▼             ▼             │              │
    POTENTIOMETER     BUTTON 1      BUTTON 2        │              │
        │               │             │             │              │
        ▼               │             │             │              │
      STEERING          ▼             ▼             ▼              ▼
       SERVO       HEADLIGHTS      DOOR         STEERING         DOOR
      (INPUT)       CONTROL       CONTROL        SERVO          SERVO
                    (INPUT)       (INPUT)       (OUTPUT)       (OUTPUT)
                        │
                        │ (Controls Data)
                        ▼
           GHT SYSTEM (GPIO25/27)
                        │
                        ├─── Common GND
                        │
                   ┌────┴────┐
                   ↓         ↓
                 FRONT     REAR
               HEADLIGHT  BRAKE
               (GPIO25)   (GPIO27)
```

## 📌 Current Pin Map
|   GPIO | Function               | Status |
| -----: | ---------------------- | ------ |
| **18** | Steering servo         | ✅      |
| **19** | Door servo             | ✅      |
| **25** | Front lights           | ✅      |
| **27** | Brake/rear lights      | ✅      |
| **34** | Steering potentiometer | ✅      |
| **23** | Headlight button       | ✅      |
| **33** | Door button            | ✅      |
