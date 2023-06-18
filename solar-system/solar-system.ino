#define A 2
#define B 3
#define C 4
#define D 5
 
#define NUMBER_OF_STEPS_PER_REV 1024

/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground
 
For more information see http://learn.adafruit.com/photocells */
 
int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the analog resistor divider
int LEDpin = 11;          // connect Red LED to pin 11 (PWM pin)
int LEDbrightness;

void setup(){
  Serial.begin(9600); 
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
}

void write(int a,int b,int c,int d){
  digitalWrite(A,a);
  digitalWrite(B,b);
  digitalWrite(C,c);
  digitalWrite(D,d);
}

void oneStep(){
  write(1,0,0,0);
  delay(2);
  write(1,1,0,0);
  delay(2);
  write(0,1,0,0);
  delay(2);
  write(0,1,1,0);
  delay(2);
  write(0,0,1,0);
  delay(2);
  write(0,0,1,1);
  delay(2);
  write(0,0,0,1);
  delay(2);
  write(1,0,0,1);
  delay(2);
}

void handleLight() {
  photocellReading = analogRead(photocellPin);  
 
  Serial.print("Analog reading = ");
  Serial.print(photocellReading);     // the raw analog reading
 
  // We'll have a few threshholds, qualitatively determined
  if (photocellReading < 10) {
    photocellReading = 1023;
    Serial.println(" - Dark");
  } else if (photocellReading < 200) {
    photocellReading = 1023 - photocellReading;
    Serial.println(" - Dim");
  } else if (photocellReading < 500) {
    photocellReading = 0;
    Serial.println(" - Light");
  } else if (photocellReading < 800) {
    photocellReading = 0;
    Serial.println(" - Bright");
  } else {
    photocellReading = 0;
    Serial.println(" - Very bright");
  }
  LEDbrightness = map(photocellReading, 0, 1023, 0, 255);
  analogWrite(LEDpin, LEDbrightness);
}

void loop(){
  int i;
  i=0;
  while(i < NUMBER_OF_STEPS_PER_REV){
    oneStep();
    handleLight();
    i++;
  }
}
