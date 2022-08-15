# Zakhar Sensor Platform

Sensors implementation for the Zakhar Project

Part of the [Zakhar: A robotics UX project](https://github.com/an-dr/zakhar)

Components:

- 1x - Nucleo F411RE
- 3x - HC-SR04 module
- 1x - KY-018 photoresistor module
- 1x - MCP2515 CAN bus module

## Schematic

<img src="index_schematic.svg" alt="platform_schematic" width="1000">

## Data Message

- Message Type: 0x1 (Data 0x1)
- Device ID: 0x4

Message content:

- DATA0: Distance Left in cm (0-200)
- DATA1: Distance Center in cm (0-200)
- DATA2: Distance Right in cm (0-200)
- DATA3: Light sensor value (High 4 bits)
- DATA4: Light sensor value (Low 8 bits)
