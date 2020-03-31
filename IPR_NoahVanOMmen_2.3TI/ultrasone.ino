
#include <pins.h>
#include <frequencies.h>
#include <hardware.h>
#include <Servo.h>

/*
This project is developed by Noah van Ommen. It's a simple game played with the arduino and a few other pieces of hardware. Move the ultrasone sensor until you hear the victory song.
You can play this game by looking at the screen to get hints, looking at the RGB led for hints or listen to the buzzer for the hints.
*/

//Variables
long duration, distance, ranNum;
int angle;
//Structs
Buzzer buzzer;
UltraSone ultraSone;
RGBled rgbled;
RLed ledLeft, ledRight;
Servo servoMotor;
//Prototypes
void RGB_color();
void ledsVictoryBlink();
void showOffBanner();
long ranNumGen();

/*
The setup method for the main application where all the sensors are set up
*/

void setup() {
  //Serial Port begin
  Serial.begin (9600);

  //Initiate RGBled
  strcpy(rgbled.name, "RGBled");
  rgbled.pinR = 4; //Set pin Red
  pinMode(rgbled.pinR, OUTPUT);
  rgbled.pinG = 3; //Set pin Green
  pinMode(rgbled.pinG, OUTPUT);
  rgbled.pinB = 2; //Set pin Blue
  pinMode(rgbled.pinB, OUTPUT);

  //Initiate buzzer
  strcpy(buzzer.name, "mainBuzzer");
  buzzer.pinMain = PIN9; //Set pin for the buzzer
  buzzer.defaultFrequency = LowFrequency; //Setting Default frequency
  pinMode(buzzer.pinMain, OUTPUT);

  //Initiate Ultrasone sensor
  strcpy(ultraSone.name, "mainUltraSoneSensor");
  ultraSone.pinTrigger = PIN11; //Set Trigger pin Ultrasone
  pinMode(ultraSone.pinTrigger, OUTPUT);
  ultraSone.pinEcho = PIN12; //Set Echo pin Ultrasone
  pinMode(ultraSone.pinEcho, INPUT);

  //Initiate left led light
  strcpy(ledLeft.name, "ledLeft");
  ledLeft.pinLed = PIN6;
  pinMode(ledLeft.pinLed, OUTPUT);

  //Initiate red led light
  strcpy(ledRight.name, "ledRight");
  ledLeft.pinLed = PIN5;
  pinMode(ledRight.pinLed, OUTPUT);

  //Attach the servo
  servoMotor.attach(PIN13);
  //Generate a random number
  ranNum = ranNumGen();
}

/*
The loop that constantly runs on this application. This takes care of the game knowledge and everything else related to the main application
*/
void loop() {
  
  delay(1000);
  digitalWrite(ultraSone.pinTrigger, LOW);
  delayMicroseconds(5);
  digitalWrite(ultraSone.pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraSone.pinTrigger, LOW);
 
  duration = pulseIn(ultraSone.pinEcho, HIGH);
  distance = (duration / 2) / 29.1;
  //If loops that check which state the ultrasone is in and handle the rules attaches to those states
  //Victory condition
  if(distance <= ranNum + 5 && distance >= ranNum - 5)
  {
    Serial.println("Victory royale!");//Victory Message
    RGB_color(255, 0, 0);
    showOffBanner(); 
    for (size_t i = 0; i < 3t; i++)
    {
      ledsVictoryBlink();
    }
    RGB_color(0, 0, 255);
    playWinSound(buzzer.pinMain); 
    ranNum = ranNumGen(); 
  }
   //Really close condition
  else if(distance <= ranNum + 15 && distance >= ranNum - 15 && distance >= ranNum + 5 || distance <= ranNum + 15 && distance >= ranNum - 15 && distance <= ranNum - 5){
    Serial.println("Boiling hot!"); //Hint
    RGB_color(200, 0, 0);
    tone(buzzer.pinMain, NOTE_D8);
    delay(50);
    noTone(buzzer.pinMain);
  }
  //Close condition
  else if(distance <= ranNum + 30 && distance >= ranNum - 30 && distance >= ranNum + 15 || distance <= ranNum + 15 && distance >= ranNum - 15 && distance <= ranNum - 15){
    Serial.println("Very hot!");//Hint
    RGB_color(150, 0, 0);
    tone(buzzer.pinMain, NOTE_D6);
    delay(200);
    noTone(buzzer.pinMain);
  }
  //Decently close condition
  else if(distance <= ranNum + 45 && distance >= ranNum - 45 && distance >= ranNum + 30 || distance <= ranNum + 15 && distance >= ranNum - 15 && distance <= ranNum - 30){
    Serial.println("Hot!");//Hint
    RGB_color(100, 0, 0);
    tone(buzzer.pinMain, NOTE_D4);
    delay(200);
    noTone(buzzer.pinMain);
  }
  //A little far condition
  else if(distance <= ranNum + 60 && distance >= ranNum - 60 && distance >= ranNum + 45 || distance <= ranNum + 15 && distance >= ranNum - 15 && distance <= ranNum - 45){
    Serial.println("Warm");//Hint
    RGB_color(50, 0, 0);
    tone(buzzer.pinMain, NOTE_D2);
    delay(200);
    noTone(buzzer.pinMain);
  }
  //Far condtion
  else if(distance <= ranNum + 75 && distance >= ranNum - 75 && distance >= ranNum + 60 || distance <= ranNum + 15 && distance >= ranNum - 15 && distance <= ranNum - 60){
    Serial.println("Still a bit cold");//Hint
    RGB_color(0, 250, 0);
    noTone(buzzer.pinMain);
    delay(200);
  }
  //Really far away condition
  else
  {
    //The RGBled blinks blue
    RGB_color(0, 255, 0); 
    delay(50);
     RGB_color(0, 0, 0);
    delay(50);
    RGB_color(0, 255, 0);
    delay(50);
    RGB_color(0, 0, 0);
  }
  //Checks if the ultrasone is before the goal and turns on the correct led
  if(distance < ranNum)
  {
   digitalWrite(ledRight.pinLed, LOW);
   digitalWrite(ledLeft.pinLed, HIGH);
  }
  //Checks if the ultrasone is after the goal and turns on the correct led
  else if(distance > ranNum)
  {
   digitalWrite(ledLeft.pinLed, LOW);
   digitalWrite(ledRight.pinLed, HIGH);
  }
  //General data
  Serial.println(ranNum);
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  
  
  delay(250);
}
/*
Generates a random number as a long object
 @return long A random number between 6 and 50
*/
long ranNumGen()
{
  long randomNum;
  randomSeed(analogRead(0));
  randomNum = random(6, 50);
  return randomNum;
}
/*
Lets the left right simple leds to blink
*/
void ledsVictoryBlink(){
    digitalWrite(ledRight.pinLed, HIGH);
    digitalWrite(ledLeft.pinLed, HIGH);
    delay(200);
    digitalWrite(ledRight.pinLed, LOW);
    digitalWrite(ledLeft.pinLed, LOW);
    delay(200);
}
/*
Method to let the RGBled switch colors easily
  @param red_light_value The value which will be written to the red light
  @param green_light_value The value which will be written to the green light
  @param blue_light_value The value which will be written to the blue light
*/
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(rgbled.pinR, red_light_value);
  analogWrite(rgbled.pinG, green_light_value);
  analogWrite(rgbled.pinB, blue_light_value);
}
/*
Waves the banner using the Servo for the victory condition
*/
void showOffBanner()
{
    for ( angle = 10; angle < 180; angle++)
    {
        servoMotor.write(angle);
        delay(15);
    }
    for(angle = 180; angle > 10; angle--)    
    {                                
        servoMotor.write(angle);           
        delay(15);       
    }
    
}