#include <CapacitiveSensor.h>

CapacitiveSensor   cs_12_3 = CapacitiveSensor(12,3);       
CapacitiveSensor   cs_12_4 = CapacitiveSensor(12,4);        
CapacitiveSensor   cs_12_5 = CapacitiveSensor(12,5);    
CapacitiveSensor   cs_12_6 = CapacitiveSensor(12,6);   

void setup() {
  // put your setup code here, to run once:
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
  
  if (touch1>1000){
      Serial.println("greenIn touched");
    }

  if (touch2 > 1000){
      Serial.println("yelloIn touched");
    }

  if (touch3 > 1000){
      Serial.println("blueIn touched");
    }
  if (touch4 > 1000){
      Serial.println("redIn touched");
  }

  if (touch1<=1000  &  touch2<=1000  &  touch3<=1000 & touch4<=1000){
    delay(10);
  }
}
