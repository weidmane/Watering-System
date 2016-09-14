/*
###############################
# Tali & Elad Watering System #
#          2016               #
###############################
*/
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

// frequency musical notes
#define NOTE_C6  1047
#define NOTE_C3  131
#define NOTE_G3  196

// pins definition
int MoistureSensorPin1 = A0;
int MoistureSensorPin2 = A1;
int AudioPin = 2;
int RelayPin = 3;

// variables
int MoistureSensorValue1;    // stores the moisture sensor 1 values
int MoistureSensorValue2;    // stores the moisture sensor 2 values

void setup() {
  // serial initialization
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Tali & Elad");
  lcd.setCursor(0, 1);
  lcd.print("Watering System");

  // Arduino pins initalization
  pinMode(AudioPin, OUTPUT);
  pinMode(RelayPin, OUTPUT);
  pinMode(MoistureSensorPin1, INPUT);
  pinMode(MoistureSensorPin2, INPUT);
  //start sound
  tone(AudioPin, NOTE_G3, 200);
  delay(200);
  tone(AudioPin, NOTE_C3, 200);
  delay(200);
  noTone(AudioPin);
  lcd.clear();
}

void loop() {
  // reads the sensor
  MoistureSensorValue1 = analogRead(MoistureSensorPin1);
  // MoistureSensorValue2 = analogRead(MoistureSensorPin2);
  MoistureSensorValue2 = 1024; // to be used when 2nd snsor is not connected
  Serial.println(MoistureSensorValue1, MoistureSensorValue2 );
  lcd.setCursor(0, 0);
  lcd.print("Sensor1|Sensor2");
  lcd.setCursor(0, 1);
  lcd.print(MoistureSensorValue1, MoistureSensorValue2);

  if ((MoistureSensorValue1 > 700) && (MoistureSensorValue2 > 700))  {
    tone(AudioPin, NOTE_C6, 200);
    delay(100);
    tone(AudioPin, NOTE_C6, 200);
    delay(100);
    noTone(AudioPin);
    lcd.clear();
    lcd.print("Water On");
    digitalWrite(RelayPin, HIGH); // start watering
    delay(120000); //minimum watering time
    while ((MoistureSensorValue1 > 700) && (MoistureSensorValue2 > 700)) {
      MoistureSensorValue1 = analogRead(MoistureSensorPin1);
      // MoistureSensorValue2 = analogRead(MoistureSensorPin2);
      MoistureSensorValue2 = 1024; // to be used when 2nd snsor is not connected
      Serial.println(MoistureSensorValue1, MoistureSensorValue2 );
      delay(5000); //
    }
    digitalWrite(RelayPin, LOW);
    tone(AudioPin, NOTE_G3, 200);
    delay(100);
    tone(AudioPin, NOTE_C3, 200);
    delay(100);
    noTone(AudioPin);
    lcd.clear();
    lcd.print("Water Off");
  }
  delay(120000); // time between sensor reading

}

