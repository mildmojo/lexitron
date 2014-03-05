/*
 * coin_slot.ino
 *
 * One-key USB keyboard using the Adafruit Trinket microcontroller.
 *
 * Designed to report coin insertion events on Run Jump Dev's Lexitron
 * arcade cabinet. Sends a '=' keydown/keyup each time the coin switch
 * is tripped. Wire SWITCH_PIN -> switch -> ground.
 *
 * Part of the Lexitron project:
 *   https://github.com/runjumpdev/lexitron
 *
 * Adafruit Trinket settings:
 *   Board Type: Adafruit Trinket 16MHz
 *   Programmer: USBtinyISP
 *
 * Dependencies:
 *   Bounce2: https://github.com/thomasfredericks/Bounce-Arduino-Wiring
 *   TrinketKeyboard: https://github.com/adafruit/Adafruit-Trinket-USB
 *
 */

#include <Bounce2.h>
#include <TrinketKeyboard.h>

// Magic numbers
#define SWITCH_PIN  0
#define LED_PIN     1
#define DEBOUNCE_MS 10
#define COIN_KEY    KEYCODE_EQUAL // '=' key

// Globals
Bounce coin_switch = Bounce();

void setup() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  coin_switch.attach(SWITCH_PIN);
  coin_switch.interval(DEBOUNCE_MS);
  TrinketKeyboard.begin();
}

void loop() {
  TrinketKeyboard.poll();

  if (coin_switch.update()) {
    // Switch pin goes high to low when closed.
    if (coin_switch.read()) {
      key_up();
      led_off();
    } else {
      key_down();
      led_on();
    }
  }
}

void key_down() {
  //TrinketKeyboard.typeChar(COIN_KEY);
  TrinketKeyboard.pressKey(0, COIN_KEY);
}

void key_up() {
  TrinketKeyboard.pressKey(0, 0);
}

void led_on() {
  digitalWrite(LED_PIN, HIGH);
}

void led_off() {
  digitalWrite(LED_PIN, LOW);
}
