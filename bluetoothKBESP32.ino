/*
 * Modified white cane attachment code for VMobi
 * 
 */

#define USE_NIMBLE
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

#define QUERY 16 // CHANGE THESE
#define TEXT 17 //CHANGE THESE

bool keyStates[2] = {false, false};
int keyPins[2] = {QUERY, TEXT};
uint8_t keyCodes[2] = {'q', 't'};


void setup() {
  Serial.begin(115200);
  Serial.println("Code running...");
  setInputs();
  bleKeyboard.begin();
}

bool connectNotificationSent = false;

void loop() {
  int counter;
  if(bleKeyboard.isConnected()) {
    if (!connectNotificationSent) {
      Serial.println("Code connected...");
      connectNotificationSent = true;
    }
    for(counter = 0; counter < 2; counter ++){
      handleButton(counter);
    }
  }
}

void setInputs() {
  pinMode(QUERY, INPUT_PULLUP);
  pinMode(TEXT, INPUT_PULLUP);
}

void handleButton(int keyIndex){
  // handle the button press
  if (!digitalRead(keyPins[keyIndex])){
    // button pressed
    if (!keyStates[keyIndex]){
      // key not currently pressed
      keyStates[keyIndex] = true;
      bleKeyboard.press(keyCodes[keyIndex]);
    }
  }
  else {
    // button not pressed
    if (keyStates[keyIndex]){
      // key currently pressed
      keyStates[keyIndex] = false;
      bleKeyboard.release(keyCodes[keyIndex]);
    }
  }
}
