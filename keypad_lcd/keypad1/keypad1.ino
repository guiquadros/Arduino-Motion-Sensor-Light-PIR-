#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]=
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {9,8,7,6}; //Rows 0 to 3
byte colPins[numCols]= {5,4,3,2}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

//initializes the display at address 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

String _lcdText = "";

void setup()
{
  Serial.begin(9600);
  lcd.begin (16,2);
}

//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
//If key is '*' the screen is cleaned and the backlight is set to LOW
void loop()
{
  char keypressed = myKeypad.getKey();
  
  if (keypressed == '*')
  {
    _lcdText = "";
    lcd.setBacklight(LOW);
    lcd.setCursor(0,0);
    lcd.clear();
    return;
  }
  
  if (keypressed != NO_KEY)
  {
    Serial.print(keypressed);

    lcd.setBacklight(HIGH);
    lcd.setCursor(0,0);
    _lcdText += keypressed;
    lcd.print(_lcdText);
  }
}
