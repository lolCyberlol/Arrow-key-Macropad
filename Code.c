#include <Keyboard.h>

// Pin assignments
const int rightPin = 7;
const int leftPin  = 14;  // <-- updated
const int downPin  = 5;
const int upPin    = 6;

struct KeySwitch {
  int pin;
  uint8_t keycode;
  bool wasDown;
  unsigned long lastChange;
};

KeySwitch keys[] = {
  { rightPin, KEY_RIGHT_ARROW, false, 0 },
  { leftPin,  KEY_LEFT_ARROW,  false, 0 },
  { downPin,  KEY_DOWN_ARROW,  false, 0 },
  { upPin,    KEY_UP_ARROW,    false, 0 }
};

const int debounce = 20; // milliseconds

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(keys[i].pin, INPUT_PULLUP); // internal pull-ups
  }
  Keyboard.begin();
}

void loop() {
  unsigned long now = millis();
  for (int i = 0; i < 4; i++) {
    bool down = (digitalRead(keys[i].pin) == LOW); // pressed = LOW
    if (down != keys[i].wasDown && (now - keys[i].lastChange) > debounce) {
      if (down) {
        Keyboard.press(keys[i].keycode);
      } else {
        Keyboard.release(keys[i].keycode);
      }
      keys[i].wasDown = down;
      keys[i].lastChange = now;
    }
  }
}
