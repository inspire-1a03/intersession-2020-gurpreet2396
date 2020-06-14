#include "pitches.h" 

// notes in the melody
int melody[]={NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int noteDurations[]={4, 8, 8, 4, 4, 4, 4, 4};

// LED Lights
const int greenLED = 4;
int blueLED = 5;

// RGB Lights4
int red_light_pin= 3;
int blue_light_pin = 5;
int green_light_pin = 12;

// Buzzer
int sound = 8;

// Button
int buttonPin = 12;
int buttonState = 0;

// Temperature
int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
// Light & Temp
const int hot = 14;

void setup()
{
// Buzzer 
  pinMode(sound, OUTPUT);
  pinMode(blueLED, OUTPUT);
// Button
  pinMode(buttonPin, INPUT);
// Temperature
  Serial.begin(9600);
  pinMode(greenLED, OUTPUT);
}

void loop()
{

// With Buzzer
  digitalWrite(blueLED, HIGH);
  tone(sound, 1000, 250);
  delay(2000);
  digitalWrite(blueLED, LOW);
  tone(sound, 6000, 250);
  delay(2000);
  
// Button
  int buttonState = digitalRead(buttonPin);
  if (buttonState == 1) {
    for(int thisNote=0; thisNote <8; thisNote++){
      int noteDuration = 1000 / noteDurations [thisNote];
      tone(8, melody [thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration *1.30;
      delay(pauseBetweenNotes);
      noTone(8);
   
  }
// Temperature
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: "); 
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C");  

 // Temp & Colour
 if (Tf >= hot) {
  digitalWrite(greenLED, HIGH);
  Serial.println(" It's Hot.");
 }

  delay(500);
  }
}
