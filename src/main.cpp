#include <Arduino.h>
#include <ESP32Servo.h>

// ==========================================
// PIN DEFINITIONS
// ==========================================

// Servos
const int STEERING_SERVO_PIN = 18;
const int DOOR_SERVO_PIN = 19;

// Lights
const int FRONT_LIGHT_PIN = 25;
const int BRAKE_LIGHT_PIN = 27;

// ==========================================
// SERVO OBJECTS
// ==========================================

Servo steeringServo;
Servo doorServo;

// ==========================================
// LIGHT FUNCTIONS
// ==========================================

void setHeadlights(bool state)
{
  digitalWrite(FRONT_LIGHT_PIN, state ? HIGH : LOW);

  Serial.print("Headlights: ");
  Serial.println(state ? "ON" : "OFF");
}

void setBrakeLights(bool state)
{
  digitalWrite(BRAKE_LIGHT_PIN, state ? HIGH : LOW);

  Serial.print("Brake lights: ");
  Serial.println(state ? "ON" : "OFF");
}

// ==========================================
// SETUP
// ==========================================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("================================");
  Serial.println("       JASH RC CAR - STAGE 3");
  Serial.println("================================");

  // -------------------------------
  // Configure lights
  // -------------------------------

  pinMode(FRONT_LIGHT_PIN, OUTPUT);
  pinMode(BRAKE_LIGHT_PIN, OUTPUT);

  // Start with lights OFF
  setHeadlights(false);
  setBrakeLights(false);

  // -------------------------------
  // Configure steering servo
  // -------------------------------

  steeringServo.setPeriodHertz(50);
  steeringServo.attach(
      STEERING_SERVO_PIN,
      1000,
      2000);

  // -------------------------------
  // Configure door servo
  // -------------------------------

  doorServo.setPeriodHertz(50);
  doorServo.attach(
      DOOR_SERVO_PIN,
      1000,
      2000);

  // -------------------------------
  // Initial positions
  // -------------------------------

  steeringServo.write(90);
  doorServo.write(0);

  Serial.println("Steering: CENTER");
  Serial.println("Door: CLOSED");

  Serial.println("Lights initialized.");
}

// ==========================================
// LOOP
// ==========================================

void loop()
{
  // ======================================
  // HEADLIGHT TEST
  // ======================================

  Serial.println();
  Serial.println("---- HEADLIGHT TEST ----");

  setHeadlights(true);
  delay(2000);

  setHeadlights(false);
  delay(1000);

  // ======================================
  // BRAKE LIGHT TEST
  // ======================================

  Serial.println();
  Serial.println("---- BRAKE LIGHT TEST ----");

  setBrakeLights(true);
  delay(2000);

  setBrakeLights(false);
  delay(1000);

  // ======================================
  // BOTH LIGHTS
  // ======================================

  Serial.println();
  Serial.println("---- ALL LIGHTS ON ----");

  setHeadlights(true);
  setBrakeLights(true);

  delay(2000);

  // ======================================
  // ALL LIGHTS OFF
  // ======================================

  Serial.println();
  Serial.println("---- ALL LIGHTS OFF ----");

  setHeadlights(false);
  setBrakeLights(false);

  delay(2000);
}