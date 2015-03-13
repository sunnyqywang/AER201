#include <Keypad.h>


const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 11, 10, 9, 8 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 7, 6, 5 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

byte hopper1 = 0;
byte hopper2 = 0;

void setup()
{
  
  Serial.begin(9600);
}

void loop()
{
  while (true) {
    
    char key = kpd.getKey();
    Serial.println(key);
    if(key)  // Check for a valid key.
    {
      if (key == '#')
        break;
      if (key == '*') {
          hopper1 = hopper1 / 10;
      } else {
          hopper1 = hopper1 * 10 + (key-48);
      }
    }
  }
  
  while (true) {
    
    char key = kpd.getKey();
  
    if(key)  // Check for a valid key.
    {
      if (key == '#')   // Finish input
        break;
      if (key == '*') {  // Backspace
          hopper2 = hopper2 / 10;
      } else {  // Record digit
          hopper2 = hopper2 * 10 + (key-48);
      }
    }
  }
  
  Serial.print("The central hoppers are:");
  Serial.print(hopper1);
  Serial.print(" and ");
  Serial.println(hopper2);
}
