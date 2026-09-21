#include <Arduino.h>
#include <ESP32Servo.h>

// ===============================
// SERVO PINS
// ===============================

const int STEERING_SERVO_PIN = 18;
const int DOOR_SERVO_PIN = 19;

// ===============================
// SERVO OBJECTS
// ===============================

Servo steeringServo;
Servo doorServo;

// ===============================
// SETUP
// ===============================

void setup() {

    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("================================");
    Serial.println("       JASH RC CAR - STAGE 2");
    Serial.println("================================");

    // Attach steering servo
    steeringServo.setPeriodHertz(50);
    steeringServo.attach(STEERING_SERVO_PIN, 1000, 2000);

    // Attach door servo
    doorServo.setPeriodHertz(50);
    doorServo.attach(DOOR_SERVO_PIN, 1000, 2000);

    Serial.println("Steering servo attached.");
    Serial.println("Door servo attached.");

    // Initial positions
    steeringServo.write(90);
    doorServo.write(0);

    Serial.println("Steering: CENTER");
    Serial.println("Door: CLOSED");

    delay(1000);
}

// ===============================
// LOOP
// ===============================

void loop() {

    // -------------------------------
    // STEERING TEST
    // -------------------------------

    Serial.println("Steering -> LEFT");
    steeringServo.write(45);
    delay(1000);

    Serial.println("Steering -> CENTER");
    steeringServo.write(90);
    delay(1000);

    Serial.println("Steering -> RIGHT");
    steeringServo.write(135);
    delay(1000);

    Serial.println("Steering -> CENTER");
    steeringServo.write(90);
    delay(1000);


    // -------------------------------
    // DOOR TEST
    // -------------------------------

    Serial.println("Door -> OPEN");
    doorServo.write(90);
    delay(1500);

    Serial.println("Door -> CLOSED");
    doorServo.write(0);
    delay(1500);
}