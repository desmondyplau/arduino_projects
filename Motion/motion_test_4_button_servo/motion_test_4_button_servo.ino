#include <Servo.h>
Servo myServo;

const int servoDirectionPin = 4;

int angle = 0;
int directionSwitchState = 0;
int prevDirectionSwitchState = 0;

int servoDirection = 0;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(9);
  pinMode(servoDirectionPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  directionSwitchState = digitalRead(servoDirectionPin);
  if (directionSwitchState != prevDirectionSwitchState) {
    if (directionSwitchState == HIGH) {
      servoDirection = !servoDirection;
    }
  }
  if (servoDirection == 1){
      if (angle < 180){
        angle = angle + 2;
      }
    } else{
      if (angle > 0){
        angle = angle - 3;
      }
    }
  Serial.print("direction switch state: ");
  Serial.print(directionSwitchState);

  Serial.print(", angle: ");
  Serial.println(angle);

  myServo.write(angle);
  prevDirectionSwitchState = directionSwitchState;
}
