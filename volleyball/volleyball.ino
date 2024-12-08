#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ezButton.h>

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin
#define SW_PIN   2  // Arduino pin connected to SW  pin

ezButton button(SW_PIN);

LiquidCrystal_I2C lcd(0x27,  16, 2);

int failValue = 0;
int scoreValue = 0;
int buttonValue = 0;
bool playing = false;
int localScore = 0;
int guestScore = 0;
int localFails = 0;
int guestFails = 0;

void setup() {
  //initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();
  button.setDebounceTime(50);
  lcd.setCursor(3, 0);
  lcd.print("Bienvenido!");
  lcd.setCursor(0, 1);
  lcd.print("Presiona y Juega");
}
void loop() {
  button.loop();
  //  Get Data from Joystick
  failValue = analogRead(VRX_PIN);
  scoreValue = analogRead(VRY_PIN);
  buttonValue = button.getState();
  if (!playing) {
    if(button.isReleased()) {
      play();   
    }
  } else {
    refreshScore();
    if (button.isReleased()) {
      showResult();
    }
  }
}

void showResult() {
  playing = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("*** GANADOR ***");
  lcd.setCursor(0, 1);
  if(localScore > guestScore) {
    lcd.print("**** Local ****");
  } else if(guestScore > localScore) {
    lcd.print("** Visitante **");
  } else {
    lcd.print("*** Empate ***");
  }
  localScore = 0;
  guestScore = 0;
  localFails = 0;
  guestFails = 0;
  delay(1000);
}

void play() {
  playing = true;
  localScore = 0;
  guestScore = 0;
  lcd.clear();
  lcd.setCursor(16, 0);
  lcd.print("A Jugar con el Humboldt");
  for(int i = 0; i <= 28; i++) {
    delay(200);
    lcd.scrollDisplayLeft();
  }
  lcd.clear();
  //  Points
  lcd.setCursor(0, 0);
  lcd.print("L: 0");
  lcd.setCursor(12, 0);
  lcd.print("V: 0");
  lcd.setCursor(5, 0);
  lcd.print("Puntos");
  //  Fails
  lcd.setCursor(0, 1);
  lcd.print("L: 0");
  lcd.setCursor(12, 1);
  lcd.print("V: 0");
  lcd.setCursor(5, 1);
  lcd.print("Faltas");
}

void refreshScore() {
  if(scoreValue <= 400) {
    localScore ++;
  } else if(scoreValue >= 600) {
    guestScore ++;
  }
  if(failValue <= 400) {
    localFails ++;
  } else if(failValue >= 600) {
    guestFails ++;
  }
  //  Score
  if(localScore < 10) {
    lcd.setCursor(3, 0); 
  } else {
    lcd.setCursor(2, 0); 
  }
  lcd.print(localScore);
  if(guestScore < 10) {
    lcd.setCursor(15, 0);
  } else {
    lcd.setCursor(14, 0);
  }
  lcd.print(guestScore);
  //  Fails
  if(localFails < 10) {
    lcd.setCursor(3, 1); 
  } else {
    lcd.setCursor(2, 1); 
  }
  lcd.print(localFails);
  if(guestFails < 10) {
    lcd.setCursor(15, 1);
  } else {
    lcd.setCursor(14, 1);
  }
  lcd.print(guestFails);
  delay(200);
}
