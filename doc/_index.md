---
title: "IO: Sensor Unit"
---

# IO: Sensor Unit

[![view - Documentation](https://img.shields.io/badge/Source%20Code-GitHub-blue)](https://github.com/Zakhar-the-Robot/io_sensors "Go to Repository")

A module collecting data from sensors. Periodically sends the data to the network.

The unit consists of:

- 1x - Nucleo F411RE
- 3x - HC-SR04 module
- 1x - KY-018 photoresistor module
- 1x - MCP2515 CAN bus module

## Schematic

<img src="index_schematic.svg" alt="platform_schematic" width="1000">

## Communication

**CAN bus**

- Protocol: [**qCAN**](https://zakhar-the-robot.github.io/doc/docs/communication-protocols/canbus/) **0.2.0**, standard CAN frame
- Address: **0x4**

**Serial**

- Speed: **115200** BPS

## Data Message

The unit sends a data message with sensor data every 100 ms.

- Message Type: **0x1** (Data Message)

Message content:

|Field   |Value                                |
|--------|-------------------------------------|
| MSG ID |0x401                                |
| DATA0  |HC-SR04 Left: distance - 0..200 cm   |
| DATA1  |HC-SR04 Center: distance - 0..200 cm |
| DATA2  |HC-SR04 Right: distance - 0..200 cm  |
| DATA3  |KY-018: Light value - High 4 bits    |
| DATA4  |KY-018: Light value - Low 8 bits     |
