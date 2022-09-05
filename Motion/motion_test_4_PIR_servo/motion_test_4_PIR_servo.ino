#include <Servo.h>
Servo myServo;
#define maxSwing 3
int sensorPin = 4;
int calibrationTime = 30;        
int angle = 0;
int swingCount = 0;
int servoDirection = 1;
int currentMotionState; // the current state of motion sensor

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);    // initialize sensor as an input
  myServo.attach(9);
  Serial.begin(9600);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}

void loop() {
  currentMotionState = digitalRead(sensorPin);     // Read Sensor
  if (currentMotionState == HIGH){
    Serial.println("Senor Triggered");
    while (swingCount < maxSwing){
      if (servoDirection == 1){
        if (angle < 180){
          angle = angle + 3;
        }
      }else{
        if (angle > 0){
          angle = angle - 3;
        }
      }
      myServo.write(angle);
      delay(35);
      if (angle == 180){
        servoDirection = !servoDirection;
      }
      else if(angle == 0){
        servoDirection = !servoDirection;
        swingCount = swingCount + 1;
      }
      Serial.println(swingCount);
    }
    swingCount = 0;
  }
}
