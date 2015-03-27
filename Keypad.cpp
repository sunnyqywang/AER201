//
//  Keypad.cpp
//  
//
//  Created by Qingyi Wang on 2015-03-13.
//
//

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
        
        if(key)  // Check for a valid key.
        {
            if (key == '#')
                Serial.println(
                break;
            if (key == '*') {
                hopper1 = hopper1 / 10;
            } else {
                switch (key) {
                    case '1':
                        hopper1 = hopper1 * 10 + 1;
                    case '2':
                        hopper1 = hopper1 * 10 + 2;
                    case '3':
                        hopper1 = hopper1 * 10 + 3;
                    case '4':
                        hopper1 = hopper1 * 10 + 4;
                    case '5':
                        hopper1 = hopper1 * 10 + 5;
                    case '6':
                        hopper1 = hopper1 * 10 + 6;
                    case '7':
                        hopper1 = hopper1 * 10 + 7;
                    case '8':
                        hopper1 = hopper1 * 10 + 8;
                    case '9':
                        hopper1 = hopper1 * 10 + 9;
                    case '0':
                        hopper1 = hopper1 * 10;
                    break;
                        
                    default:
                        break;
                }
            }
        }
    }
    
    while (true) {
        
        char key = kpd.getKey();
        
        if(key)  // Check for a valid key.
        {
            if (key == '#')
                break;
            if (key == '*') {
                hopper2 = hopper2 / 10;
            } else {
                switch (key) {
                    case '1':
                        hopper2 = hopper2 * 10 + 1;
                    case '2':
                        hopper2 = hopper2 * 10 + 2;
                    case '3':
                        hopper2 = hopper2 * 10 + 3;
                    case '4':
                        hopper2 = hopper2 * 10 + 4;
                    case '5':
                        hopper2 = hopper2 * 10 + 5;
                    case '6':
                        hopper2 = hopper2 * 10 + 6;
                    case '7':
                        hopper2 = hopper2 * 10 + 7;
                    case '8':
                        hopper2 = hopper2 * 10 + 8;
                    case '9':
                        hopper2 = hopper2 * 10 + 9;
                    case '0':
                        hopper2 = hopper2 * 10;
                        break;
                        
                    default:
                        break;
                }
            }
        }
    }
    
    Serial.print("The central hoppers are:");
    Serial.print(hopper1);
    Serial.print(" and ");
    Serial.println(hopper2);
}