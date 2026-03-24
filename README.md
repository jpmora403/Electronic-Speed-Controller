# BLDC Electronic Speed Controller
20A Brushless DC Motor Driver

## Overview
This esc takes a 1ms - 2ms period PWM signal as input and drives
a triple phase motor for up to 20A draw. This was initially designed for an autonomous quadcopter, utilizing a 3300KV motor.
With the implementation of adaptive startup, it should be able to startup and drive heavier loads than propellors as well.
This project utilizes the many peripherals on the AVR MCU such as the Timer B, Timer E, Wave Extension (WEX), for wave capture
and PWM generation with inversion + deadtime, to drive a triple half-bridge. 

## Components
- AVR16EB32 MCU
- DRV8320H MOSFET driver
- Tiple H-Bridge
- 0805 smd resistors and capacitors
- 470 uF electrolytic capacitor
- Testpoint layouts for oscilloscope hooks
- 6 IRF540N mosfets

## Features
- Sensorless BLDC control
- Back-EMF zero crossing detection
- Adaptive startup
- 24kHz PWM frequency
- Deadtime insertion via WEX


## Software

### Toolchain
- Utilizes the gcc-avr toolchain

### Make and Flash
- make all
- The Makefile provided makes use of an arduino sketch make by ElTangas, which when uploaded to an arduino, allows it to act as programmer
and can be selected in the avrdude command with -c jtag2updi. More information is available at https://github.com/ElTangas/jtag2updi, 
but essentially the arduino programs the AVR onboard using the UPDI test point by running make flash.

## Status
The project is still ongoing with hope of creating an entirely open-source drone design. The provided code is currently missing a start-up
sequence, but most main loop logic is present along with initialization. Updates are coming to the PCB design soon, like a mosfet footprint
that exposes copper for the drain, and most likely a section of vias around the battery ground input. Also, a different configuration on the IDRIVE
pin of the DRV8320H for a higher source/sink current.
