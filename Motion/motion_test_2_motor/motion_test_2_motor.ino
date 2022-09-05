const int controlPin1 = 2;
const int controlPin2 = 3;
const int motorPowerPin = 5;
const int motorDirectionPin = 4;
const int enablePin = 9;
const int motorSpeedPin = A0;

int onOffSwitchState = 0;
int prevOnOffSwitchState = 0;
int directionSwitchState = 0;
int prevDirectionSwitchState = 0;

int motorEnable = 0;
int motorSpeed = 0;
int motorDirection = 0;

void setup() {
  pinMode(motorDirectionPin, INPUT);
  pinMode(motorPowerPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  onOffSwitchState = digitalRead(motorPowerPin);
  delay(1);
  directionSwitchState = digitalRead(motorDirectionPin);
  motorSpeed = analogRead(motorSpeedPin)/4;

  if(onOffSwitchState != prevOnOffSwitchState){
    if(onOffSwitchState == HIGH){
      motorEnable = !motorEnable;
      }
    }
  if (directionSwitchState != prevDirectionSwitchState) {
    if (directionSwitchState == HIGH) {
      motorDirection = !motorDirection;
    }
  }

  if (motorDirection == 1){
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  }else{
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }
  if (motorEnable == 1) {
    analogWrite(enablePin, motorSpeed);
  }else{
    analogWrite(enablePin, 0);
  }

  prevDirectionSwitchState = directionSwitchState;
  prevDirectionSwitchState = onOffSwitchState;
}
