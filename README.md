---

# Pick to Light (Warehouse Simulation)

## Description
This project simulates a pick-to-light system used in warehouses.  
It uses a client-server model where a PC sends commands via UART, and microcontrollers communicate using CAN to confirm item picking.

## Features
- Simulates warehouse item picking
- Multi-protocol system (UART + CAN)
- LED indicators for pick confirmations
- Helps reduce picking errors in warehouse systems

## Tech Stack
- Embedded C
- PIC18F4580
- CAN Protocol
- UART
- MPLAB IDE

## How to Run
1. Open MPLAB and compile the code.
2. Flash microcontroller using Tiny Bootloader.
3. Use Tera Term to send commands over UART.
4. Observe LEDs light up as items are picked.

---
