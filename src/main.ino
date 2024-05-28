#include <AccelStepper.h>

// for the Arduino Uno + CNC shield V3

#define home_switch_B 10
#define home_switch_C 9

#define MOTOR_A_ENABLE_PIN 8
#define MOTOR_A_STEP_PIN 2
#define MOTOR_A_DIR_PIN 5

#define MOTOR_B_ENABLE_PIN 8
#define MOTOR_B_STEP_PIN 3
#define MOTOR_B_DIR_PIN 6

#define MOTOR_C_ENABLE_PIN 8
#define MOTOR_C_STEP_PIN 4
#define MOTOR_C_DIR_PIN 7


AccelStepper motorA(1, MOTOR_A_STEP_PIN, MOTOR_A_DIR_PIN);
AccelStepper motorB(1, MOTOR_B_STEP_PIN, MOTOR_B_DIR_PIN);
AccelStepper motorC(1, MOTOR_C_STEP_PIN, MOTOR_C_DIR_PIN);

const long deplacementB = 80;
const long deplacementC = 60;
long posB = deplacementB;
long posC = deplacementC;

long initial_homing=-1;

void homingSteppers() {
  Serial.println("Stepper is Homing . . . . . . . . . . . ");

  // homing B
  motorB.setMaxSpeed(100.0);
  motorB.setAcceleration(1000);
  motorB.enableOutputs();

  while (digitalRead(home_switch_B)) {  // Make the Stepper move CCW until the switch is activated   
    motorB.moveTo(initial_homing);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
    motorB.run();  // Start moving the stepper
    delay(5);
  }

  motorB.setCurrentPosition(0);
  motorB.setMaxSpeed(100.0);
  motorB.setAcceleration(1000);
  initial_homing=1;

  while (!digitalRead(home_switch_B)) { // Make the Stepper move CW until the switch is deactivated
    motorB.moveTo(initial_homing);  
    motorB.run();
    initial_homing++;
    delay(5);
  }

  motorB.setCurrentPosition(0);

  // homing C
  motorC.setMaxSpeed(100.0);
  motorC.setAcceleration(1000);
  motorC.enableOutputs();

  initial_homing=-1;
  while (digitalRead(home_switch_C)) {  // Make the Stepper move CCW until the switch is activated   
    motorC.moveTo(initial_homing);  // Set the position to move to
    Serial.println(digitalRead(home_switch_C));
    initial_homing--;  // Decrease by 1 for next move if needed
    motorC.run();  // Start moving the stepper
    delay(5);
  }

  motorC.setCurrentPosition(0);
  motorC.setMaxSpeed(100.0);
  motorC.setAcceleration(1000);
  initial_homing=1;

  while (!digitalRead(home_switch_C)) { // Make the Stepper move CW until the switch is deactivated
    motorC.moveTo(initial_homing);  
    motorC.run();
    initial_homing++;
    delay(5);
  }

  motorC.setCurrentPosition(0);

  Serial.println(("Homing Completed"));
}

void setup()
{
  Serial.begin(9600);

  // overriding homing
  // pinMode(MOTOR_B_ENABLE_PIN, OUTPUT);
  // pinMode(home_switch_B, INPUT_PULLUP);
  // pinMode(MOTOR_C_ENABLE_PIN, OUTPUT);
  // pinMode(home_switch_C, INPUT_PULLUP);
  delay(5);

  motorA.setEnablePin(MOTOR_A_ENABLE_PIN);
  motorA.setPinsInverted(false, false, true);
  motorB.setEnablePin(MOTOR_B_ENABLE_PIN);
  motorB.setPinsInverted(false, false, true);
  motorC.setEnablePin(MOTOR_C_ENABLE_PIN);
  motorC.setPinsInverted(false, false, true);

  // homingSteppers();

  // overriding homing
  // motorA.enableOutputs();
  motorB.enableOutputs();
  motorC.enableOutputs();


  motorA.setMaxSpeed(1000);
  motorA.setAcceleration(400);
  motorB.setMaxSpeed(1000);
  motorB.setAcceleration(400);
  motorC.setMaxSpeed(1000);
  motorC.setAcceleration(100);

  delay(2000);

  motorA.moveTo(posC/2);
  motorB.moveTo(posB);
  motorC.moveTo(posC);
}

void loop()
{
  Serial.print("Positions: B: ");
  Serial.print(motorB.currentPosition());
  Serial.print(" C: ");
  Serial.println(motorC.currentPosition());
  

  if (motorB.currentPosition() != posB) {
    motorB.run();
  }

  if (motorC.currentPosition() != posC) {
    motorC.run();
    motorA.run();
  }

  if (motorB.currentPosition() == posB && motorC.currentPosition() == posC) {
    if (posB == deplacementB) {
      posB = 0;
    } else {
      posB = deplacementB;
    }

    if (posC == deplacementC) {
      posC = 0;
    } else {
      posC = deplacementC;
    }

    motorA.moveTo(posC/2);
    motorB.moveTo(posB);
    motorC.moveTo(posC);
    delay(1000);
  }
}