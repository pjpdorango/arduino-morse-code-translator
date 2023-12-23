#include <LiquidCrystal_PCF8574.h>

// Pin for the morse code button is set to 3
byte pinButton = 3;
// Pin for the '/' button is set to 2
byte pinSlash = 2;
// Pin for the spacebar button is set to 4
byte pinBackspace = 4;

bool isButtonPressed;
bool isBackspacePressed;
bool backspaceOn = false;
bool waiting = true;

// Custom heart character
byte heartChar[] = {
  0b00000, 0b01010, 0b10101, 0b10001,
  0b01010, 0b00100, 0b00000, 0b00000
};

String currentMessage = "";

unsigned long now;
unsigned long timeSincePrint = 0;
unsigned long timeSincePressed = 0;

// LCD Display Setup
// SDA to A4
// SCL to A5
LiquidCrystal_PCF8574 lcd(0x27);

void setup() {
  // pinButton detects whether or not button is on, therefore it is an input
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(pinSlash, INPUT_PULLUP);

  // LCD setup
  lcd.begin(16, 2);

  Serial.begin(9600);

  lcd.createChar(1, heartChar);

  attachInterrupt(digitalPinToInterrupt(pinButton), addMorseCode, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinSlash), addSlash, FALLING);
}

void loop() {
  // VARIABLE ASSIGNMENTS
  isButtonPressed = !digitalRead(pinButton);
  now = millis();
  isBackspacePressed = !digitalRead(pinBackspace);

  lcd.setBacklight(255);

  // If more than 10ms has passed, print the message
  // To ensure that the LCD prints constantly but not too fast
  if (now - timeSincePrint >= 100) {
    printCurrentMessage();
  }

  if (isBackspacePressed && !backspaceOn) {
    backSpace();
    backspaceOn = true;
  } else if (!isBackspacePressed && backspaceOn) {
    backspaceOn = false;
    timeSincePressed = now;
  }

  // If not waiting for an input and it has been longer than 2 seconds
  if (!waiting && now - timeSincePressed >= 2000 && currentMessage != "") {
    currentMessage += " ";

    // The time has been registered as a pause, you are now waiting for an input
    // To ensure a case where multiple spaces appear in a row doesn't happen
    waiting = true;
  }
}

void addMorseCode() {
  // When the button has just been pressed (FALLING STATE)
  if (!isButtonPressed) {
    // Start the timer on how long the press is
    timeSincePressed = now;

    // You are now waiting for an input (when the button is let go)
    waiting = true;
  // When the button has just been let go (RISING STATE)
  } else {
    // If pressed for more than 200ms (to filter accidental clicking or hardware malfunction),
    if (now - timeSincePressed >= 200) {
      // If pressed for 200ms to 600ms, message is a dot
      if (now - timeSincePressed <= 600) {
        currentMessage += ".";
      } else {
      // Otherwise, it is a dash (3x longer than dot)
        currentMessage += "-";
      }
    }

    timeSincePressed = now;
    waiting = false;
  }
}

void printCurrentMessage() {
  lcd.home();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(currentMessage);
  lcd.setCursor(0, 1);
  lcd.cursor();
  lcd.print(convertToEnglish(currentMessage));
  timeSincePrint = now;
}

void addSlash() {
  currentMessage += "/";
}

void backSpace() {
  currentMessage.remove(currentMessage.length() - 1);
  waiting = false;
  timeSincePressed = now;
}

String convertToEnglish(String morseCode) {
  String englishString = "";
  String currentWord = "";

  for (int i = 0; i < morseCode.length(); i++) {
    char currentLetter = morseCode[i];
    if (currentLetter == ' ') {
      // Word is complete, now all that is left to do is convert it
      englishString += wordToEnglish(currentWord);

      currentWord = "";
    } else if (currentLetter == '/') {
      if (currentWord != "") {
        englishString += wordToEnglish(currentWord);
      }

      englishString += " ";
      currentWord = "";
    } else {
      currentWord += currentLetter;
    }
  }

  // At the end of all of this, add the leftover currentWord to english
  englishString += currentWord;

  return englishString;
}

String wordToEnglish(String morseCode) {
  if (morseCode == ".-") {
    return "A";
  } else if (morseCode == "-...") {
    return "B";
  } else if (morseCode == "-.-.") {
    return "C";
  } else if (morseCode == "-..") {
    return "D";
  } else if (morseCode == ".") {
    return "E";
  } else if (morseCode == "..-.") {
    return "F";
  } else if (morseCode == "--.") {
    return "G";
  } else if (morseCode == "....") {
    return "H";
  } else if (morseCode == "..") {
    return "I";
  } else if (morseCode == ".---") {
    return "J";
  } else if (morseCode == "-.-") {
    return "K";
  } else if (morseCode == ".-..") {
    return "L";
  } else if (morseCode == "--") {
    return "M";
  } else if (morseCode == "-.") {
    return "N";
  } else if (morseCode == "---") {
    return "O";
  } else if (morseCode == ".--.") {
    return "P";
  } else if (morseCode == "--.-") {
    return "Q";
  } else if (morseCode == ".-.") {
    return "R";
  } else if (morseCode == "...") {
    return "S";
  } else if (morseCode == "-") {
    return "T";
  } else if (morseCode == "..-") {
    return "U";
  } else if (morseCode == "...-") {
    return "V";
  } else if (morseCode == ".--") {
    return "W";
  } else if (morseCode == "-..-") {
    return "X";
  } else if (morseCode == "-.--") {
    return "Y";
  } else if (morseCode == "--..") {
    return "Z";
  } else if (morseCode == ".----") {
    return "1";
  } else if (morseCode == "..---") {
    return "2";
  } else if (morseCode == "...--") {
    return "3";
  } else if (morseCode == "....-") {
    return "4";
  } else if (morseCode == ".....") {
    return "5";
  } else if (morseCode == "-....") {
    return "6";
  } else if (morseCode == "--...") {
    return "7";
  } else if (morseCode == "---..") {
    return "8";
  } else if (morseCode == "----.") {
    return "9";
  } else if (morseCode == "-----") {
    return "0";
  } else if (morseCode == "..--..") {
    return "?";
  } else if (morseCode == "-.-.--") {
    return "!";
  } else if (morseCode == ".-.-.-") {
    return ".";
  } else if (morseCode == "--..--") {
    return ",";
  } else if (morseCode == ".-.-.") {
    return "+";
  } else if (morseCode == "-....-") {
    return "-";
  } else if (morseCode == "-..-.") {
    return "/";
  } else if (morseCode == "-...-") {
    return "=";
  } else if (morseCode == "---...") {
    return "\01"; // Custom Heart Character
  } else if (morseCode == "") {
    return "";
  }
  
  return "?";
  
}
