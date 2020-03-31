#ifndef CUSTOMHARDWARE_H
#define CUSTOMHARDWARE_H

//STRUCT FOR THE RGB LED
typedef struct
{
  char name[20];
  int pinR;
  int pinG;
  int pinB;
} RGBled;
//STRUCT FOR THE BUZZER
typedef struct
{
  char name[20];
  int pinMain;
  int defaultFrequency;
} Buzzer;
//STRUCT FOR THE ULTRASONE
typedef struct
{
  char name[20];
  int pinTrigger;
  int pinEcho;
} UltraSone;
//STRUCT FOR THE NORMAL LEDS
typedef struct 
{
  char name[20];
  int pinLed;
} RLed;




#endif