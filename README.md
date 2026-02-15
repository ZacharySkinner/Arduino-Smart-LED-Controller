# Arduino Smart LED Control System (WS2812 + IR Remote)

## Overview
This project implements a timing-sensitive LED control system using an Arduino and a large WS2812B LED strip, controlled via an IR remote.  
During initial bring-up, the LED strip exhibited dimming and intermittent flickering due to voltage drop and current spikes along the strip when powered from a single injection point.  

To resolve this, the system was redesigned with three separate 5V power injection points distributed along the strip. Each injection point includes a bulk decoupling capacitor to locally buffer current draw and reduce transient voltage dips caused by rapid LED switching. This eliminated visible flicker and improved stability at higher brightness levels.  

The final system combines embedded firmware with practical power distribution, signal integrity, and hardware debugging considerations typical of large LED installations.


## Hardware
- Arduino Mega (DATA_PIN = 31)
- WS2812B addressable LED strip (~900 LEDs)
- IR Receiver (NEC protocol remote)
- External 5V power supply (required for LED current draw)
- Common ground between Arduino and LED power supply

## Electrical & System Considerations
- WS2812B LEDs draw significant current; external 5V power is required.
- Ground must be shared between the Arduino and LED power supply.
- Power injection is recommended every ~100 LEDs to avoid voltage drop.
- A series resistor (220–470Ω) on the data line is recommended for signal integrity.
- LED current spikes required validation of wiring gauge and power distribution.

## Features
- Solid color modes (white, red, green, blue, cyan, yellow, purple)
- IR remote control for mode switching
- Brightness control with bounds checking
- Animated BPM-based color pattern using FastLED palettes
- Non-blocking animation timing

## Software
- Platform: Arduino (Mega-class board)
- Language: Embedded C/C++
- Libraries:
  - FastLED
  - IRremote

## How to Run
1. Install dependencies:
   - FastLED
   - IRremote  
   (via Arduino Library Manager)

2. Wire the system:
   - Connect WS2812 data line to pin 31
   - Power LEDs from an external 5V supply
   - Share ground between Arduino and LED power
   - Connect IR receiver output to pin 2

3. Flash the sketch to the Arduino.

4. Use the IR remote to:
   - Change colors
   - Adjust brightness
   - Toggle animation modes

## Project Structure
```text
arduino-smart-led-controller/
├─ led_controller.ino
├─ README.md
<!--
└─ wiring_diagram.png   # optional
-->

## What This Demonstrates
- Timing-critical LED control (WS2812 protocol)
- Embedded firmware for hardware peripherals
- IR protocol decoding and event handling
- Power distribution and signal integrity considerations
- HW/SW integration in an embedded system

## Future Improvements
- Add configuration storage (EEPROM)
- Add multiple animation modes
- Add brightness memory on power toggle
- Add button debounce / IR code mapping table
