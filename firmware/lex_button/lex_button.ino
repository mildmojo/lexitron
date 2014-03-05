/*
 * lex_key.ino
 *
 * One-key keyboard that sends an additional keystroke if the key is
 * held down too long.
 *
 * Designed to be connected to the LEX button on Run Jump Dev's Lexitron
 * arcade cabinet. Tap to start a game, long press to quit back to the
 * launcher.
 *
 * Teensy 2.0 settings:
 *   USB Type: Keyboard + Mouse + Joystick
 *   CPU Speed: 1MHz
 *   Keyboard Layout: US English
 *   
 */

// Magic numbers
const int ledPin = 11;
const int switchPin = 3;
const int LOOP_DELAY = 50;

// Configuration
const int LONGPRESS_TIME = 2000;
const char SHORT_KEY = '[';
const char LONG_KEY = ']';

// Globals
int short_down = 0;
int short_down_last = 0;
int long_down = 0;
int long_down_last = 0;
int timer = 0;

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  if (digitalRead(switchPin) == LOW)
    buttonDown();
  else
    buttonUp();

  // Update history for next loop.
  short_down_last = short_down;
  long_down_last = long_down;
  delay(LOOP_DELAY);
}

void buttonDown() {
  // Debounce button; make sure it's held down for at least LOOP_DELAY.
  short_down = timer >= LOOP_DELAY;
  long_down = timer >= LONGPRESS_TIME;
  
  if (long_down && !long_down_last) {
    ledOn();
    // On long button down, tap long-press key.
    Keyboard.press(LONG_KEY);
  } else {
    // Flash LED when first pressed.
    if (timer == 0) {
      ledOn();
    } else {
      ledOff();
    }
    // On button down, depress short-press key. 
    if (short_down != short_down_last) {
      Keyboard.press(SHORT_KEY);
    }
    // Count time elapsed to see if short press becomes a long press.
    timer += LOOP_DELAY;
  }
}

void buttonUp() {
  // Reset all state, wait for next press.
  short_down = 0;
  long_down = 0;
  timer = 0;
  ledOff();
  // On button up, release short-press key.
  if (short_down != short_down_last) {
    Keyboard.release(SHORT_KEY);
  }
  if (long_down != long_down_last) {
    Keyboard.release(LONG_KEY);
  }
}

void ledOn() {
  digitalWrite(ledPin, HIGH);
}

void ledOff() {
  digitalWrite(ledPin, LOW);
}

