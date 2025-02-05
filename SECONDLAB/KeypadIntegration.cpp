#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
// Try 0x27 or 0x3F based on your module
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

LiquidCrystal_I2C lcd(0x27, 16, 2); // use the addresss from the first code
byte rowPins[ROWS] = {9, 8, 7, 6}; // Rows
byte colPins[COLS] = {5, 4, 3, 2}; // Columns

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
String inputStr = "";

void setup() {
  lcd.init();      // Initialize the LCD
  lcd.backlight(); // Turn on backlight
  lcd.setCursor(0, 0);
  lcd.print("I2C LCD Working!");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {  // Clear screen on #
      inputStr = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter Text:");
    } else if (key == '*') {  // Confirm input on *
      lcd.setCursor(0, 1);
      lcd.print(inputStr);
    } else if (inputStr.length() < 16) {  // Append characters
      inputStr += key;
      lcd.setCursor(0, 1);
      lcd.print(inputStr);
    }
  }
}
