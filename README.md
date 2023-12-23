# Arduino Morse Code Translator
This is Arduino code (.ino) written in C++ that controls a circuit for a morse code translator!

## Images
![Circuit Image](https://i.ibb.co/rvR1Qc7/IMG20231222180508.jpg)
![Arduino Port Wiring Image](https://i.ibb.co/hKT4BWJ/IMG20231223165003.jpg)

## Components Used
1. Arduino UNO
2. 3 Small Buttons
3. 3 1k Ohm Resistors
4. Jumper Wires (Male and Female)
5. LCD I2C

## Features
- **LCD display**
  - Displays the morse code itself
  - Also displays the translated text
- **Morse code button**
  - Inputs the actual desired morse code to be translated into the arduino
    - _To input a dit (.), press for 200ms - 600ms_
    - _To input a dah (-), press for longer than 600ms (3x the length of a dit)_
  - Any input shorter than 200ms will be considered an extranneous input and will not be registered.
- **Backspace button**
  - When pressed, will remove the most recently added character
- **Spacebar button**
  - When pressed, will add a '/' to the morse code, which is interpreted as a whitespace character in English.

## How to Use
Use the **Morse Code Button** to input anything you like in morse code.

> [!IMPORTANT]
> _To input a dit (.), press for 200ms - 600ms._
> 
> _To input a dah (-), press for longer than 600ms (3x the length of a dit)._

For the program to recognize that you are finished writing a single letter, wait for at least _1.5 seconds_. After this time frame, the program will interpret the current 'letter' that has not been interpreted yet.

If you made a mistake, or if the program interpreted a letter when you have not finished writing it fully yet, press the **Backspace Button** to undo the most recent change.

If you are finished writing an entire word, use the **Spacebar Button** to display a whitespace character.

## Morse Code to English Chart
![Morse Code to English Chart](https://cdn.shopify.com/s/files/1/2223/4507/files/morse-chart_grande.png?v=1501447409)

### Additional Characters
|**_Character_**|**_Morse Code_**|
|---------------|---------|
|**Exclamation Point (!)**|```-.-.--```|
|**Question Mark (?)**|```..--..```|
|**Dot (.)**|```.-.-.-```|
|**Comma (,)**|```--..--```|
|**Plus (+)**|```.-.-.```|
|**Minus or Hyphen (-)**|```-....-```|
|**Slash (/)**|```-..-.```|
|**Equal Sign (=)**|```-...-```|
|**Heart**|```---...```|

## Arduino Port Guide

|**_Component_**|**_Pin_**|
|---------------|---------|
|**Morse Code Button**|3|
|**Spacebar Button**|2|
|**Backspace Button**|4|
|**SDA**|A4|
|**SCL**|A5|
