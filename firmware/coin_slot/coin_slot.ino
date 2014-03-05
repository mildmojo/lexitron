/*
 * lex_coin_key.ino
 *
 * One-key USB keyboard.
 *
 * Designed to report key insertion events on Run Jump Dev's Lexitron
 * arcade cabinet.
 *
 * Adafruit Trinket settings:
 *   Board Type: Adafruit Trinket 16MHz
 *   Programmer: USBtinyISP
 *   
 */

#include <Bounce.h>
#include <TrinketKeyboard.h>

// Magic numbers
#define LED_PIN     1
#define SWITCH_PIN  0
#define DEBOUNCE_MS 10
#define COIN_KEY    KEYCODE_EQUAL

// Globals
Bounce coin_switch = Bounce(SWITCH_PIN, DEBOUNCE_MS);

void setup() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  TrinketKeyboard.begin();
}

void loop() {
  TrinketKeyboard.poll();

  if (coin_switch.update()) {
    if (coin_switch.fallingEdge()) {
      //TrinketKeyboard.typeChar(COIN_KEY);
      TrinketKeyboard.pressKey(0, COIN_KEY);
      led_on();
    } else if (coin_switch.risingEdge()) {
      TrinketKeyboard.pressKey(0, 0);
      led_off();
    }
  }
}

void led_on() {
  digitalWrite(LED_PIN, HIGH);
}

void led_off() {
  digitalWrite(LED_PIN, LOW);
}

