# Design-of-a-Digital-Clock-Based-on-MCU

## Introduction

This project, developed in my sophomore year, is based on the TI LaunchPad experimentation board and a microcontroller (MCU) expansion board. The objective was to design a program capable of implementing a digital clock system. This system makes use of the internal functionalities of the MCU along with the peripherals provided by the expansion board.

## Functions

1. Second Timing Function
   - Implements a 1-second timing function using a timer interrupt.
   - Activates an LED to blink with each second.

2. 24-Hour Clock Function
   - Displays the current time (hours, minutes, seconds) on an OLED screen.
   - Accurately maintains time and carries over to the next day.
   - Includes a 12-hour format option with AM/PM display, switchable using a button.

3. Perpetual Calendar Function
   - Shows the current date on the OLED screen.

4. Time and Date Setting Function
   - Enables setting the current time and date using a matrix keypad.
   - Offers real-time synchronization with a computer's time.

5. System Power-Off Memory Function
   - Maintains time and date settings even after power loss.

6. Additional Features
   - Allows for the setting of three independent alarm clocks.
   - Includes a timer function with start, pause, stop, and reset capabilities.

## Result
