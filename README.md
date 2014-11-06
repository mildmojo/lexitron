lexitron
========

Plans, models, firmware associated with RunJumpDev's arcade cabinet, the [Lexitron](http://runjumpdev.org/lexitron).

## Microcontrollers

At launch, the Lexitron used two Arduino-compnatible microcontrollers to drive
the LEX button and sense coin insertions. The LEX button is a SUZO-HAPP
[large green illuminated pushbutton](http://na.suzohapp.com/all_catalogs/pushbuttons/D54-0004-13)
connected to a [Teensy 2.0](http://pjrc.com/store/teensy_pins.html) board that's
programmed to act like a USB keyboard. The coin door switches are wired to an
[Adafruit Trinket](http://www.adafruit.com/products/1501) that's also programmed
to act like a USB keyboard.

We've had some reliability issues with the Trinket. It's emulating USB in
software, and that's pretty taxing for its ATtiny85 chip. Occasionally it
doesn't send a keystroke, sometimes it sends the keystroke several seconds (!!)
late. We're looking at replacing it with a [Pro Trinket](http://www.adafruit.com/products/2000)
(with an ATmega328 chip) or a Digispark Pro (ATtiny167 w/external crystal).
These physically-small boards let us mount the controller on the coin
mechanism itself.

The Teensy continues to be rock-solid. It scoffs at the menial task of reading
a switch and sending keystrokes. It's got a closed-source bootloader, is way
overpowered for the job, and costs much more than you need to pay for this
functionality, but it's still cheap and provides peace of mind.

## Adafruit Trinket in Windows

Setting up the Arduino IDE for the Trinket in Windows was kind of
a bear.

- Download the [Arduino IDE v1.0x](http://arduino.cc/en/Main/Software)
  & install. (Adafruit doesn't yet support v1.5.x)
- Follow Adafruit's ["slow way" instructions](http://learn.adafruit.com/introducing-trinket/setting-up-with-arduino-ide#the-slow-way)
  for setting up the Trinket with the Arduino IDE.
- Download Adafruit's [Windows driver](http://learn.adafruit.com/usbtinyisp/download)
  for the USBtinyISP and unzip it somewhere.
- In Device Manager, right-click the Trinket, update driver, and
  point to the place where you unzipped the Windows driver.
- Grab the [Bounce2](https://github.com/thomasfredericks/Bounce-Arduino-Wiring)
  and [TrinketKeyboard](https://github.com/adafruit/Adafruit-Trinket-USB)
  libraries and put them in folders in 
  C:\Users\<user>\Documents\Arduino\libraries.
- Start the Arduino IDE.
- Make sure Tools => Board is set to "Adafruit Trinket 16MHz".
- Make sure Tools => Programmer is set to "USBtinyISP".
- Verify (compile) the sketch.
- Press the Trinket's reset button.
- While the Trinket is flashing red, hit the Arduino IDE upload button.
