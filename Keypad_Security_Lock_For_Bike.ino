 // Include Arduino Wire library for I2C
#include <Wire.h>
// Include LCD display library for I2C
#include <LiquidCrystal_I2C.h>
// Include Keypad library
#include <Keypad.h>
// Include Servo Motor library
#include <Servo.h>

// create servo object to control a servo
Servo myservo;
// Length of password + 1 for null character
#define Password_Length 5
// Character to hold password input
char Data[Password_Length];
// Password
char Master[Password_Length] = "1256";
 
// variable to store the servo position
int pos = 0; 
 
// Counter for character entries
byte data_count = 0;
 
// Character to hold key input
char customKey;
 
// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 3;
 
// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
 
// Connections to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};
 
// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
 
// Create LCD object
LiquidCrystal_I2C lcd(0x3F, 16, 2);
 
void setup() {
  // Setup LCD with backlight and initialize
  lcd.backlight();
  lcd.init();
  lcd.print("Bike Rentals");
  lcd.setCursor(0, 1);
  lcd.print("Security Lock");
  delay(5000);
  lcd.clear();
  // Initialize the Buzzer Pin
  pinMode(11, OUTPUT);
  
 // attaches the servo on pin 13 to the servo object
   myservo.attach(13);
}
void ServoOpen() {
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}

void ServoClose() {
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
    }
}

 
void loop() {
 
  // Initialize LCD and print
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
 
  // Look for keypress
  customKey = customKeypad.getKey();
  if (customKey) {
    // Enter keypress into array and increment counter
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }
 
  // See if we have reached the password length
  if (data_count == Password_Length - 1) {
    lcd.clear();
 
    if (!strcmp(Data, Master)) {
      // Password is correct
      lcd.print("Correct!!");
      lcd.setCursor(0, 1);
      lcd.print("Bike Unlocked");
      // Turn on Buzzer for 1 second.
      digitalWrite(11, HIGH);
      delay(500);
      digitalWrite(11,LOW);
      delay(1000);
      // Turn on Servo for 10 seconds
      ServoOpen();  // Signals the Servor to open
      delay(10000);
      ServoClose();
    }
    else {
      // Password is incorrect
      lcd.print("Incorrect!!");
      delay(5000);
    }
 
    // Clear data and LCD display
    lcd.clear();
    clearData();
  }
}
 
void clearData() {
  // Go through array and clear data
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}
