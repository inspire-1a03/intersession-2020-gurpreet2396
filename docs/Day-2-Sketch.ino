// Temperature Info
#include <math.h>

#define ThermistorPIN 0                 // Analog Pin 0

float vcc = 4.91;                       // only used for display purposes, if used
                                       // set to the measured Vcc.
float pad = 9850;                       // balance/pad resistor value, set this to
                                       // the measured resistance of your pad resistor
float thermr = 10000;                   // thermistor nominal resistance

float Thermistor(int RawADC) {
 long Resistance;  
 float Temp;  // Dual-Purpose variable to save space.

 Resistance=pad*((1024.0 / RawADC) - 1);
 Temp = log(Resistance); // Saving the Log(resistance) so not to calculate  it 4 times later
 Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
 Temp = Temp - 273.15;  // Convert Kelvin to Celsius                      

 return Temp;                                      // Return the Temperature
}

// LED Info

int redPin = 11;
int greenPin = 10;
int bluePin = 9;


void setup()
{
 pinMode(redPin, OUTPUT);
 pinMode(greenPin, OUTPUT);
 pinMode(bluePin, OUTPUT);  
 Serial.begin(115200); // Temp
}

void loop(){
 // Temp
 float temp;
 temp=Thermistor(analogRead(ThermistorPIN));       // read ADC and  convert it to Celsius
 Serial.print("Celsius: ");
 Serial.print(temp,1);                             // display Celsius
 //temp = (temp * 9.0)/ 5.0 + 32.0;                  // converts to  Fahrenheit
 //Serial.print(", Fahrenheit: ");
 //Serial.print(temp,1);                             // display  Fahrenheit
 Serial.println("");                                  
 delay(5000);                                      // Delay a bit...

 // Colour Changing
 if(temp<5){
 setColor(0, 255, 255);  // aqua
 }
 else if(temp>6){
 setColor(0, 255, 0);  // green
 }
 else if(temp>=15) {
 setColor(0, 0, 255);  // blue
 }
 else if(temp>=20) {
 setColor(255, 255, 0);  // yellow  
 }
 else if(temp=25){
 setColor(80, 0, 80);  // purple
 }
 else if (temp>25) {
 setColor(255, 0, 0);  // red
 }
}

void setColor(int red, int green, int blue)
{
 #ifdef COMMON_ANODE
   red = 255 - red;
   green = 255 - green;
   blue = 255 - blue;
 #endif
 analogWrite(redPin, red);
 analogWrite(greenPin, green);
 analogWrite(bluePin, blue);  
}
