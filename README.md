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

### Setup the perfboard
- First, you can join 2 8*6 perfboard pieces together, with solder & copper wire.
- Then, solder some single row female header connectors in the middle of the perfboard (enough for all the pins of the Nano board). This is where the Arduino Nano will sit.
- Solder 2 rows of 4 single row female header connectors for the nRF24l01 module, above the Arduino Nano.
- Make 4 holes on each side of the perfboard, where you will screw in the 2 joysticks. But don't screw them in just yet.

Our components are now set. Now, it's time to connect all of them.

### Connect the nRF24l01 Module
Then, we need to connect the nRF24l01 module to the Arduino Nano. 7 connections need to be made:
- GND to GND
- VCC to 3.3V
- CE to D9
- CSN to D10
- SCK to D13
- MOSI to D11
- MISO to D12

### Connect the joysticks
Then, we connect our 2 joysticks to the Arduino Nano. 4 connections need to be made for each:
- GND to GND
- 5V to 5V
- VRX to A0 (right joystick), VRX to A2 (left joystick)
- VRY to A1 (right joystick), VRY to A3 (left joystick)

### Connect the power
Finally, we can connect a 9V battery clip connector. To improve user experience, we can add an ON/OFF switch.

- Connect the red wire of the battery clip connector to a wire of the ON/OFF switch
- Connect the other wire of the ON/OFF switch to the VIN pin of the Arduino Nano
- Connect the black wire of the battery clip connector to the GND pin of the Arduino Nano
- Plug in a 9V battery to the clip connector.

And we're done! Since there is no receiver to connect to, we'll leave the coding part for later. We will build the receiver first

## 2: Build the receiver

The receiver receives data from the input you make on the joysticks connected to your transmitter. It then interprets that data and sends it accordingly to the servos & brushless motor connected to the receiver itself.
Follow the final result image below to build the receiver, along with the steps.

### Setup the perfboard
- First, get a 7*5cm perfboard.
- Then, as for the transmitter, solder in some single row female header connectors (enough for all the pins of the Nano board).
- As for the transmitter, solder 2 rows of 4 single row female header connectors, for the nRF24l01 module.
- Solder in 3 rows of male pin headers.

Our components are now set. Now, it's time to make the connections.

### Connect the nRF24l01 Module
As for the transmitter, we need to connect the nRF24l01 module to the Arduino Nano. 7 connections need to be made:
- GND to GND
- VCC to 3.3V
- CE to D9
- CSN to D10
- SCK to D13
- MOSI to D11
- MISO to D12

### Connect the rows of pins
We have 3 rows of pins. One will be for connecting ground wires, one for power wires and one for signal wires. This is where we will easily connect our servos and brushless motors with their 3-pin connectors.

- With solder and copper wire, connect the upper row to the GND pin of the Arduino Nano
- With solder and copper wire, connect the middle row to the 5V pin of the Arduino Nano
- Do NOT solder together the pins of the last row. Those will be connected individually like so:
  - Connect each pin separately to the pins from D2 to D5 of the Arduino Nano.

 ### Connect the servos/motors
Now we only need to connect each motor to their respective pins
- Plug in the 3 servos wires to the pins connected to D2, D3 and D4.
- Plug in the 3 wires of the ESC to the D5 pins of your transmitter.
- Plug in the ESC to the brushless motor.
- Plug in the Lipo 3S battery to the ESC. This battery will power up the brushless motor, but it will also power up the Arduino Nano.

 And we're done! Our transmitter and receivers are built. Now, we can get to programming them.

## 3: Code the transmitter

You will find the [code for the transmitter here.](https://github.com/Martinrolo/Arduino-RC-Plane/blob/main/src/transmitter.cpp). 

You can upload it right away to your transmitter's Arduino Nano in 2 ways: Arduino IDE or VS Code

### Uploading code through Arduino IDE
- Connect your Arduino Nano to your laptop with an USB cable.
- Open the Arduino IDE.
- Click on File -> New Sketch, and paste the code inside the file.
- Select your board (Arduino Nano).
- Click on Sketch -> Upload, or on the "->" icon.

### Uploading code through VSCode 
- Install the PlatformIO extension.
- Download the ZIP file of this repository and extract it.
- Click on "Open Project" and open the extracted file of the project (in the folder where the "platformio.ini" file is located).
- On the terminal type the following command: ```pio device list```
  -  Make sure your transmitter is connected to your laptop. This command will return you which port corresponds to your Arduino Nano.
  -  Copy the result of this command in the "upload_port" field of the [env.transmitter] section.
- Click on the "->" icon in the lower part of the VS Code window to upload the code.

## 4: Code the receiver

You will find the [code for the transmitter here.](https://github.com/Martinrolo/Arduino-RC-Plane/blob/main/src/receiver.cpp). 

The steps for uploading the receiver code are the same as for the transmitter, except that you need to select a different board:

### Uploading code through Arduino IDE
- You simply select another board as "Arduino Nano", which will be on a different port.

### Uploading code through VSCode 
- In the [platformio.ini file](https://github.com/Martinrolo/Arduino-RC-Plane/blob/main/platformio.ini), change the ```upload_port``` field for the result of the ```pio device list``` command.

The rest of the procedures are the same.

## 5: Build the controller 

## 6: Build the airplane
