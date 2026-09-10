# ✈️ Arduino RC plane transmitter & receiver

A custom-build radio control system for RC planes, built from scratch using Arduino microcontrollers and other electronic components.

## What you need for this project

Before getting to the code, we need to build the transmitter, receiver and airplane. For that, you need several components & tools.

### Components:
- Arduino Nano (x2)
- nRF24L01 transceiver (x2)
- Perfboard 
  - 8*6cm perfboard for the transmitter (x2)
  - 7*5cm perfboard for the receiver
  - Header connectors & male connector strip
- 5 pin XY Joysticks (x2)
- On-off toggle switch
- Wires (x50)
- 9V Battery
- Lipo 11.1V 3S Battery with XT60 connector
- RC Plane components kit (on Amazon) with those components combined:
  - 2200KV Brushless motor with ESC
  - Servo motors (x3)
  - Propeller
  - Wheels
- Polystyrene foam board
- M3 screws & nuts
- Copper wire
 
### Tools:
- Soldering iron kit
  - Soldering iron
  - Solder wire
  - Solder wick
  - Flux
  - Safety glasses (!!)
- Wire cutter
- Cutter
- Hot glue gun
- Screwdriver

I recommend seeking kits on Amazon to get many of these components all in one go (example: the soldering kit, the RC plane component kits).
An Arduino starter kit can also get you many of these components (wires, battery, screws & nuts, etc...)

## 1: Build the transmitter

The transmitter is basically the controller of your aircraft. You send input from the joysticks to the airplane's receiver via radio frequency.
Follow the final result image below to build the transmitter, along with the steps.

- First, you can join 2 8*6 perfboard pieces together, with solder & copper wire.
- Then, solder some straight header connectors in the middle of the perfboard. This is where the Arduino Nano will sit.
- Solder 2 rows of 4 header connectors for the nRF24l01 module, above the Arduino Nano.
- Make 4 holes on each side of the perfboard, where you will screw in the 2 joysticks. But don't screw them in just yet.

Our components are now set. Now, it's time to connect all of them.

### First, we need to connect the nRF24l01 module to the Arduino Nano. 7 connections need to be made:
- GND to GND
- VCC to 3.3V
- CE to D9
- CSN to D10
- SCK to D13
- MOSI to D11
- MISO to D12

### Then, we connect our 2 joysticks to the Arduino Nano. 4 connections need to be made for each:
- GND to GND
- 5V to 5V
- VRX to A0 (right joystick), VRX to A2 (left joystick)
- VRY to A1 (right joystick), VRY to A3 (left joystick)

### Finally, we can connect a 9V battery clip connector. To improve user experience, we can add an ON/OFF switch.
- Connect the red wire of the battery clip connector to a wire of the ON/OFF switch
- Connect the other wire of the ON/OFF switch to the VIN pin of the Arduino Nano
- Connect the black wire of the battery clip connector to the GND pin of the Arduino Nano

And we're done! Since there is no receiver to connect to, we'll leave the coding part for later. We will build the receiver first

## 2: Build the receiver

## 3: Code the transmitter

## 4: Code the receiver

## 5: Build the airplane
