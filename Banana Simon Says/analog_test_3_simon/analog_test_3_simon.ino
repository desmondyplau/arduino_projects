#include <CapacitiveSensor.h>
#include <Servo.h>
Servo myServo;
const int nowPlayingAngle = 90;
const int youLoseAngle = 0;
const int youWinAngle = 180;

CapacitiveSensor cs_12_3 = CapacitiveSensor(12, 3);
CapacitiveSensor cs_12_4 = CapacitiveSensor(12, 4);
CapacitiveSensor cs_12_5 = CapacitiveSensor(12, 5);
CapacitiveSensor cs_12_6 = CapacitiveSensor(12, 6);

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

int ledLightTime = 400;

// Max of 20 rounds can be run
int gameRounds[20];
// GameRoundCount = 5 * Difficulty
int difficulty = 1;

void setup()
{
    // put your setup code here, to run once:
    myServo.attach(13);
    
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

void loop()
{
    // put your main code here, to run repeatedly:
    // Game Start State
    myServo.write(nowPlayingAngle);
    setUpGame();
}

void setUpGame()
{
    difficulty = getTouchedValue();
    Serial.print("difficulty chosen by user: ");
    Serial.println(difficulty);
    delay(100);
    createRounds();
    gameStartFlash();
    delay(1000);
    playGame();
}

void createRounds()
{
    randomSeed(analogRead(1));
    for (int i = 0; i < (5 * difficulty); i++)
    {
        gameRounds[i] = random(1, 5);
    }
}

void gameStartFlash(){
  for (int i = 0; i < difficulty; i++){
    lightLED(green);
    lightLED(yellow);
    lightLED(blue);
    lightLED(red);
   }
}

void playGame()
{
    for (int userRound = 0; userRound < (5 * difficulty); userRound++)
    {
        Serial.print("userRound: ");
        Serial.println(userRound);
        // disply value(s) from gameRounds 0 to userRound
        for (int ledToDisplay = 0; ledToDisplay < userRound + 1; ledToDisplay++)
        {
            switch (gameRounds[ledToDisplay])
            {
            case 1:
                // green
                lightLED(green);
                delay(ledLightTime);
                break;
            case 2:
                // yellow
                lightLED(yellow);
                delay(ledLightTime);
                break;
            case 3:
                // blue
                lightLED(blue);
                delay(ledLightTime);
                break;
            case 4:
                // red
                lightLED(red);
                delay(ledLightTime);
                break;
            default:
                Serial.println("game broken stop");
                break;
            }
        }
        // get user input(as many as userRound + 1)
        int userInputArray[20];
        for (int loc = 0; loc < userRound + 1; loc++)
        {
            userInputArray[loc] = getTouchedValue();
        }

        Serial.print("userInputArray: [");
        for (int i = 0; i < userRound + 1; i++)
        {
            Serial.print(userInputArray[i]);
            Serial.print(", ");
            if (userInputArray[i] != gameRounds[i])
            {
                Serial.println("MISMATCH");
                youLose();
                return;
            }
        }
        Serial.println("]");
        // wait for user to move away
        delay(ledLightTime * 2);
    }
    // run end game (win)
    Serial.println("You Win");
    youWin();
}

void lightLED(int pinNumber)
{
    digitalWrite(pinNumber, HIGH);
    delay(ledLightTime);
    digitalWrite(pinNumber, LOW);
    
}

void youWin(){
   myServo.write(youWinAngle);
   for (int i = 0; i < 3; i++){
    lightLED(green);
    lightLED(yellow);
    lightLED(blue);
    lightLED(red);
   }
}

void youLose(){
  myServo.write(youLoseAngle);
  for (int i = 0; i < 3; i++){
    lightLED(red);
    lightLED(blue);
    lightLED(yellow);
    lightLED(green);;
   }
}

int getTouchedValue()
{
    bool hasTouched = false;
    int touchValue;
    while (1 == 1)
    {
        long touch1 = cs_12_3.capacitiveSensor(1000);
        long touch2 = cs_12_4.capacitiveSensor(1000);
        long touch3 = cs_12_5.capacitiveSensor(1000);
        long touch4 = cs_12_6.capacitiveSensor(1000);

        if (touch1 > 1000 && touch2 < 1000 && touch3 < 1000 && touch4 < 1000)
        {
            // If red line is touched
            // Serial.println("yellowIn touched");
            if (prevGreenState == LOW)
            {
                // If state changed
                greenState = HIGH;
            }
        }
        else
        {
            // If blue line is not touched
            if (prevGreenState == HIGH)
            {
                // If state changed
                greenState = LOW;
                hasTouched = true;
                touchValue = 1;
            }
        }

        if (touch2 > 1000 && touch1 < 1000 && touch3 < 1000 && touch4 < 1000)
        {
            // If yellow line is touched
            // Serial.println("yellowIn touched");
            if (prevYellowState == LOW)
            {
                // If state changed
                yellowState = HIGH;
            }
        }
        else
        {
            // If blue line is not touched
            if (prevYellowState == HIGH)
            {
                // If state changed
                yellowState = LOW;
                hasTouched = true;
                touchValue = 2;
            }
        }

        if (touch3 > 1000 && touch2 < 1000 && touch1 < 1000 && touch4 < 1000)
        {
            // If blue line is touched
            // Serial.println("redIn touched");
            if (prevBlueState == LOW)
            {
                // If state changed
                blueState = HIGH;
            }
        }
        else
        {
            // If blue line is not touched
            if (prevBlueState == HIGH)
            {
                // If state changed
                blueState = LOW;
                hasTouched = true;
                touchValue = 3;
            }
        }

        if (touch4 > 1000 && touch2 < 1000 && touch3 < 1000 && touch1 < 1000)
        {
            // If red line is touched
            // Serial.println("redIn touched");
            if (prevRedState == LOW)
            {
                // If state changed
                redState = HIGH;
            }
        }
        else
        {
            // If red line is not touched
            if (prevRedState == HIGH)
            {
                // If state changed
                redState = LOW;
                hasTouched = true;
                touchValue = 4;
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
        if (hasTouched)
        {
            return touchValue;
        }
    }
}
