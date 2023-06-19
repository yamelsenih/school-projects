#define A 2
#define B 3
#define C 4
#define D 5
 
#define NUMBER_OF_STEPS_PER_REV 1024
#define NUMBER_OF_STEPS_FOR_OPEN_DOOR 128
#define DELAY_BY_STEP 2
#define PIN_BUZZER 6
#define FREQUENCY 850


const int trigPin = 9;
const int echoPin = 10;

int LEDpin = 11;          // connect Red LED to pin 11 (PWM pin)
int LEDbrightness;

long duration;
int distance;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  Serial.begin(9600); 
}

void write(int a,int b,int c,int d){
  digitalWrite(A,a);
  digitalWrite(B,b);
  digitalWrite(C,c);
  digitalWrite(D,d);
}

void forwardStep(){
  write(1,0,0,0);
  delay(DELAY_BY_STEP);
  write(1,1,0,0);
  delay(DELAY_BY_STEP);
  write(0,1,0,0);
  delay(DELAY_BY_STEP);
  write(0,1,1,0);
  delay(DELAY_BY_STEP);
  write(0,0,1,0);
  delay(DELAY_BY_STEP);
  write(0,0,1,1);
  delay(DELAY_BY_STEP);
  write(0,0,0,1);
  delay(DELAY_BY_STEP);
  write(1,0,0,1);
  delay(DELAY_BY_STEP);
}

void reverseStep(){
  write(1,0,0,1);
  delay(DELAY_BY_STEP);
  write(0,0,0,1);
  delay(DELAY_BY_STEP);
  write(0,0,1,1);
  delay(DELAY_BY_STEP);
  write(0,0,1,0);
  delay(DELAY_BY_STEP);
  write(0,1,1,0);
  delay(DELAY_BY_STEP);
  write(0,1,0,0);
  delay(DELAY_BY_STEP);
  write(1,1,0,0);
  delay(DELAY_BY_STEP);
  write(1,0,0,0);
  delay(DELAY_BY_STEP);
}

void openDoor() {
  for(int step = 0; step < NUMBER_OF_STEPS_FOR_OPEN_DOOR; step ++) {
    forwardStep();
  }
}

void closeDoor() {
  for(int step = 0; step < NUMBER_OF_STEPS_FOR_OPEN_DOOR; step ++) {
    reverseStep();
  }
}

boolean readSendor() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  boolean openDoor = false;
  if(distance > 20 && distance <= 30) {
    Serial.println("Carro en la Entrada...");
  } else if(distance > 10 && distance <= 20) {
    openDoor = true;
  } else {
    Serial.println("Nada por Hacer");
  }
  return openDoor;
}

void loop() {
  boolean isOpenDoor = readSendor();
  if(isOpenDoor) {
    Serial.println("Abriendo Puerta...");
    // tone(PIN_BUZZER, FREQUENCY, 100);
    playSound();
    openDoor();
    delay(5000);
    Serial.println("Cerrando Puerta...");
    playSound();
    closeDoor();
    // delay(1000);
  }
}

void playSound() {
  tone(PIN_BUZZER, FREQUENCY, 500);
  delay(1000);
  tone(PIN_BUZZER, FREQUENCY * 2, 500);
  delay(1000);
  tone(PIN_BUZZER, FREQUENCY * 3, 500);
}