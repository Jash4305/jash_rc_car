#include <Arduino.h>
#include <ESP32Servo.h>

// ==========================================
// PIN DEFINITIONS
// ==========================================

// Servos
const int STEERING_SERVO_PIN = 18;
const int DOOR_SERVO_PIN     = 19;

// Lights
const int FRONT_LIGHT_PIN    = 25;
const int BRAKE_LIGHT_PIN    = 27;

// Inputs
const int STEERING_POT_PIN   = 34;
const int HEADLIGHT_BUTTON   = 23;
const int DOOR_BUTTON        = 33;


// ==========================================
// SERVO OBJECTS
// ==========================================

Servo steeringServo;
Servo doorServo;


// ==========================================
// STATE VARIABLES
// ==========================================

bool headlightsState = false;
bool brakeLightState  = false;
bool doorOpenState   = false;


// ==========================================
// BUTTON STATE
// ==========================================

bool lastHeadlightButton = HIGH;
bool lastDoorButton      = HIGH;


// ==========================================
// SETUP
// ==========================================

void setup()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("================================");
    Serial.println("       JASH RC CAR - STAGE 4: Steering, Headlights, and Door Control");
    Serial.println("================================");


    // --------------------------------------
    // LIGHT OUTPUTS
    // --------------------------------------

    pinMode(FRONT_LIGHT_PIN, OUTPUT);
    pinMode(BRAKE_LIGHT_PIN, OUTPUT);

    digitalWrite(FRONT_LIGHT_PIN, LOW);
    digitalWrite(BRAKE_LIGHT_PIN, LOW);


    // --------------------------------------
    // BUTTON INPUTS
    // --------------------------------------

    pinMode(HEADLIGHT_BUTTON, INPUT_PULLUP);
    pinMode(DOOR_BUTTON, INPUT_PULLUP);


    // --------------------------------------
    // STEERING SERVO
    // --------------------------------------

    steeringServo.setPeriodHertz(50);

    steeringServo.attach(
        STEERING_SERVO_PIN,
        1000,
        2000
    );


    // --------------------------------------
    // DOOR SERVO
    // --------------------------------------

    doorServo.setPeriodHertz(50);

    doorServo.attach(
        DOOR_SERVO_PIN,
        1000,
        2000
    );


    // --------------------------------------
    // INITIAL POSITION
    // --------------------------------------

    steeringServo.write(90);
    doorServo.write(0);


    Serial.println("Steering: CENTER");
    Serial.println("Door: CLOSED");
    Serial.println("Headlights: OFF");
    Serial.println();

    Serial.println("Controls:");
    Serial.println("  POTENTIOMETER -> STEERING");
    Serial.println("  H -> HEADLIGHTS");
    Serial.println("  D -> DOOR");
    Serial.println();
}


// ==========================================
// HEADLIGHT CONTROL
// ==========================================

void toggleHeadlights()
{
    headlightsState = !headlightsState;
    brakeLightState = !brakeLightState;

    digitalWrite(
        FRONT_LIGHT_PIN,
        headlightsState ? HIGH : LOW
    );
    digitalWrite(
        BRAKE_LIGHT_PIN,
        brakeLightState ? HIGH : LOW
    );

    Serial.print("Headlights: ");

    if (headlightsState)
    {
        Serial.println("ON");
    }
    else
    {
        Serial.println("OFF");
    }

    Serial.print("Brakelights: ");

    if (brakeLightState)
    {
        Serial.println("ON");
    }
    else
    {
        Serial.println("OFF");
    }
}


// ==========================================
// DOOR CONTROL
// ==========================================

void toggleDoor()
{
    doorOpenState = !doorOpenState;

    if (doorOpenState)
    {
        doorServo.write(90);

        Serial.println("Door: OPEN");
    }
    else
    {
        doorServo.write(0);

        Serial.println("Door: CLOSED");
    }
}


// ==========================================
// STEERING CONTROL
// ==========================================

void updateSteering()
{
    int potValue = analogRead(STEERING_POT_PIN);

    // ESP32 ADC = 0 to 4095
    int steeringAngle = map(
        potValue,
        0,
        4095,
        45,
        135
    );

    steeringAngle = constrain(
        steeringAngle,
        45,
        135
    );

    steeringServo.write(steeringAngle);

    // Print occasionally so terminal doesn't flood
    static int lastPrintedAngle = -1;

    if (abs(steeringAngle - lastPrintedAngle) >= 5)
    {
        Serial.print("Steering angle: ");
        Serial.print(steeringAngle);
        Serial.print("° | ADC: ");
        Serial.println(potValue);

        lastPrintedAngle = steeringAngle;
    }
}


// ==========================================
// MAIN LOOP
// ==========================================

void loop()
{
    // --------------------------------------
    // READ STEERING
    // --------------------------------------

    updateSteering();


    // --------------------------------------
    // HEADLIGHT BUTTON
    // --------------------------------------

    bool currentHeadlightButton =
        digitalRead(HEADLIGHT_BUTTON);

    if (
        lastHeadlightButton == HIGH &&
        currentHeadlightButton == LOW
    )
    {
        toggleHeadlights();
    }

    lastHeadlightButton =
        currentHeadlightButton;


    // --------------------------------------
    // DOOR BUTTON
    // --------------------------------------

    bool currentDoorButton =
        digitalRead(DOOR_BUTTON);

    if (
        lastDoorButton == HIGH &&
        currentDoorButton == LOW
    )
    {
        toggleDoor();
    }

    lastDoorButton =
        currentDoorButton;


    delay(20);
}