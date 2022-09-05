#include <CapacitiveSensor.h>

CapacitiveSensor   cs_12_3 = CapacitiveSensor(12,3);       
CapacitiveSensor   cs_12_4 = CapacitiveSensor(12,4);        
CapacitiveSensor   cs_12_5 = CapacitiveSensor(12,5);    
CapacitiveSensor   cs_12_6 = CapacitiveSensor(12,6);

const int red = 11;
const int blue = 10;
const int yellow = 9;
const int green = 8;

int greenState = LOW;
int yellowState = LOW;
int blueState = LOW;
int redState = LOW;

int prevGreenState = LOW;
int prevYellowState = LOW;
int prevBlueState = LOW;
int prevRedState = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  cs_12_3.set_CS_AutocaL_Millis(0xFFFFFFFF); 
  cs_12_4.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_12_5.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_12_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);
}

void loop() {
  long touch1 =  cs_12_3.capacitiveSensor(1000);
  long touch2 =  cs_12_4.capacitiveSensor(1000);
  long touch3 =  cs_12_5.capacitiveSensor(1000);
  long touch4 =  cs_12_6.capacitiveSensor(1000);
  
  
  if (touch1 > 1000){
      // If red line is touched
      //Serial.println("yellowIn touched");
      if (prevGreenState == LOW){
        // If state changed
        greenState = HIGH;
      }
  }else{
    // If blue line is not touched
    if (prevGreenState == HIGH){
        // If state changed
        greenState = LOW;
      }
  }

  if (touch2 > 1000){
      // If yellow line is touched
      //Serial.println("yellowIn touched");
      if (prevYellowState == LOW){
        // If state changed
        yellowState = HIGH;
      }
  }else{
    // If blue line is not touched
    if (prevYellowState == HIGH){
        // If state changed
        yellowState = LOW;
      }
  }

  if (touch3 > 1000){
      // If blue line is touched
      //Serial.println("redIn touched");
      if (prevBlueState == LOW){
        // If state changed
        blueState = HIGH;
      }
  }else{
    // If blue line is not touched
    if (prevBlueState == HIGH){
        // If state changed
        blueState = LOW;
      }
  }

  if (touch4 > 1000){
      // If red line is touched
      //Serial.println("redIn touched");
      if (prevRedState == LOW){
        // If state changed
        redState = HIGH;
      }
  }else{
    // If red line is not touched
    if (prevRedState == HIGH){
        // If state changed
        redState = LOW;
      }
  }

  // Write states to LED, and update prev states
  digitalWrite(red, redState);
  digitalWrite(blue, blueState);
  digitalWrite(yellow, yellowState);
  digitalWrite(green, greenState);

  prevRedState = redState;
  prevBlueState = blueState;
  prevYellowState = yellowState;
  prevGreenState = greenState;

}
