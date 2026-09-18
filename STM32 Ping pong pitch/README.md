# Ping Pong Pitch: STM32 Two Player Game

## About
I made this in 2025 as a part of a group project with my friends [Irfan Khan](https://www.linkedin.com/in/irfank06/) and [Robert Sabau Mance](https://www.linkedin.com/in/robertsabaumance) during my second year at TU Dublin.
It's a football themed based off of the two-player game Pong. It was built for the STM32F031x6 microcontroller a small, low-cost 32-bit microcontroller .

This project was quite big and was built upon numerous times in which we had to test for bugs and errors within the code.
Working on this project taught me how to control the hardware directly, create my own display driver, and use PWM to make sounds.
Creating new features for the game and completing it within a deadline taught me a huge amount.Fixing bugs and errors also helped me 
understand how to better manage and develop a project.



## What it does
- A two-player Pong game that runs on a TFT screen using SPI.
- Football pitch theme with goal lines and pitch markings drawn using custom shape drawing functions
- Start menu with a "Press any button to start" prompt
- Button input read directly from GPIO pins
- A short intro tune plays through the buzzer using timer generated tones
- Score tracking and ball movement for two players

## Tech used
- C
- STM32F031x6 microcontroller
- SPI TFT display
- PlatformIO

## Files
| File | Description |
|---|---|
| `src/main.c` | Game logic: menu, input handling, scoring, tune playback |
| `src/display.c` / `display.h` | Display driver: pixels, shapes, text, and sprite rendering |
| `src/sound.c` / `sound.h` | Timer based tone generation for the buzzer |
| `src/font5x7.h` | Bitmap font used for on-screen text |
| `src/musical_notes.h` | Note to frequency table used for the intro tune |
| `assets/` | Sprite BMPs and a Python script used to convert them into pixel arrays |
| `platformio.ini` | Project build configuration |

## What I learned
- Writing bare-metal embedded C, working directly with STM32 registers (GPIO, SPI, timers)
- Building a display driver from scratch, including SPI communication and bitmap text rendering
- Generating sound using timer PWM output, including playing a full sequence of notes
- Converting image assets into a hardware-specific pixel format using a custom Python script
- Working as part of a 3-person team on a shared embedded codebase

## Known limitations
These are things that would need to be addressed if this were developed further:
- No HAL/CMSIS abstraction — the code is tied directly to the STM32F031x6 register map so it won't run on other STM32 boards without changes so its not very accessible
- Requires the exact SPI display used in development; no fallback for other display drivers

## How to run
1. Install [PlatformIO](https://platformio.org/) (VS Code extension or CLI)
2. Open this folder as a PlatformIO project
3. Connect the STM32F031x6 board with the matching SPI display and buttons wired up
4. Build and upload via PlatformIO

note: this project requires the physical STM32 board and display to run. It can't be run directly on a laptop, since it's written for specific hardware
registers rather than a general-purpose computer but id like to revisit this and make a version for laptop at some point.
