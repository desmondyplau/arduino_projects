const int DEBOUNCE_DELAY = 50;

const int BUTTON_PIN = 8;
const int LED_1    = 12;
const int LED_2    = 13;

  
int ledState = LOW;
int lastSteadyState = LOW;
int lastMovingState = LOW;
int currentState = LOW;

unsigned long lastDebounceTime = 0;
  
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
}
  
void loop() {
  currentState = digitalRead(BUTTON_PIN);
  if (currentState != lastMovingState) {
    lastDebounceTime = millis();
    lastMovingState = currentState;
  }
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if(lastSteadyState == HIGH && currentState == LOW) {
      Serial.print("The device is tilted ");
    
      ledState = !ledState;
   
      digitalWrite(LED_1, ledState);
      digitalWrite(LED_2, ledState);

    }
    lastSteadyState    = currentState;
  }
}
