# ✈️ Arduino RC plane transmitter & receiver

A custom-build radio control system for RC planes, built from scratch using Arduino microcontrollers and other cheap electronic components.

## What you need for this project

Before getting to the code, we need to build the transmitter and receiver. For that, you need several components and tools.

### 🛒 Components:
- Arduino Nano (x2)
- nRF24L01 transceiver (x2)
- Perfboard 
  - 8*6cm perfboard for the transmitter (x2)
  - 7*5cm perfboard for the receiver
  - Female & male header connectors strips
- 5-pin XY Joysticks (x2)
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
 
### 🛠️ Tools:
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

I recommend looking for kits on Amazon to get several of these components in one go (e.g. the soldering kit and the RC plane components kit). An Arduino starter kit can also get you many of these components (wires, battery, screws & nuts, etc.).

## 1: 📡🎮 Build the transmitter

The transmitter is essentially the controller for your aircraft. It sends joystick input to the airplane's receiver via radio frequency. Follow the final result image below to build the transmitter, along with the steps.

### Setup the perfboard
- First, join two 8x6cm perfboard pieces together with solder and copper wire.
- Solder single-row female header connectors in the middle of the perfboard (enough for all the pins of the Nano board). This is where the Arduino Nano will sit.
- Solder two rows of four single-row female header connectors for the nRF24L01 module, above the Arduino Nano.
- Make four holes on each side of the perfboard, where you'll screw in the two joysticks. But don't screw them in just yet.

Our components are now in place. Now it's time to connect them.

### Connect the nRF24l01 Module
Next, connect the nRF24L01 module to the Arduino Nano. Seven connections need to be made:
- GND to GND
- VCC to 3.3V
- CE to D9
- CSN to D10
- SCK to D13
- MOSI to D11
- MISO to D12

### Connect the joysticks
Next, connect the two joysticks to the Arduino Nano. Four connections need to be made for each:
- GND to GND
- 5V to 5V
- VRX to A0 (right joystick), VRX to A2 (left joystick)
- VRY to A1 (right joystick), VRY to A3 (left joystick)

### Connect the power
Finally, connect a 9V battery clip connector. To improve the user experience, add an on/off switch.

- Connect the red wire of the battery clip connector to a wire of the on/off switch.
- Connect the other wire of the on/off switch to the VIN pin of the Arduino Nano.
- Connect the black wire of the battery clip connector to the GND pin of the Arduino Nano.
- Plug in a 9V battery to the clip connector.

And we're done! Since there is no receiver to connect to, we'll leave the coding part for later. We will build the receiver first.

## 2: 📡 Build the receiver

The receiver receives data from the joysticks connected to your transmitter, interprets it, and sends it accordingly to the servos and brushless motor connected to the receiver itself. Follow the final result image below to build the receiver, along with the steps.

### Setup the perfboard
- First, get a 7x5cm perfboard.
- As with the transmitter, solder in single-row female header connectors (enough for all the pins of the Nano board).
- As with the transmitter, solder two rows of four single-row female header connectors for the nRF24L01 module.
- Solder in three rows of male pin headers.

Our components are now in place. Now it's time to make the connections.

### Connect the nRF24l01 Module
As with the transmitter, connect the nRF24L01 module to the Arduino Nano. Seven connections need to be made:
- GND to GND
- VCC to 3.3V
- CE to D9
- CSN to D10
- SCK to D13
- MOSI to D11
- MISO to D12

### Connect the rows of pins
We have three rows of male header pins: one for ground wires, one for power wires, and one for signal wires. This is where we'll connect our servos and brushless motor via their 3-pin connectors.
This part can be easily confusing, so look at the final result image to better visualize where and how to connect the pins to the Arduino Nano.

- With solder and copper wire, connect the upper row to the GND pin of the Arduino Nano
- With solder and copper wire, connect the middle row to the 5V pin of the Arduino Nano
- Do NOT solder together the pins of the last row. Those will be connected individually like so:
  - Connect each pin separately to the pins from D2 to D5 of the Arduino Nano. (Example: the right-most pin to D2, the pin next to it to D3, etc...

 ### Connect the servos/motors
Now we only need to connect each motor to their respective pins
- Plug the three servo wires into the pins connected to D2, D3, and D4.
- Plug the three ESC wires into the pin connected to D5.
- Plug the ESC into the brushless motor.
- Plug the LiPo 3S battery into the ESC. This battery powers the brushless motor, and it also powers the Arduino Nano.

 And we're done! Our transmitter and receivers are built. Now, we can get to programming them.

## 3: 📡💻 Code the transmitter

You will find the [code for the transmitter here.](https://github.com/Martinrolo/Arduino-RC-Plane/blob/main/src/transmitter.cpp). 

You can upload it right away to your transmitter's Arduino Nano in 2 ways: Arduino IDE or VS Code

### Uploading code through Arduino IDE
- Connect your Arduino Nano to your laptop with an USB cable.
- Open the Arduino IDE.
- Click on File -> New Sketch, and paste the code inside the file.
- Select your board (Arduino Nano).
- Click on Sketch -> Upload, or on the ***->*** icon.

### Uploading code through VSCode 
- Install the ***PlatformIO*** extension.
- Download the ZIP file of this repository and extract it.
- Click on ***Open Project*** and open the extracted file of the project (in the folder where the ***platformio.ini*** file is located).
- On the terminal type the following command: ```pio device list```
  -  Make sure your transmitter is connected to your laptop. This command will return you which port corresponds to your Arduino Nano.
  -  Copy the result of this command in the ```upload_port``` field (line 10) of the ```[env.transmitter]``` section. 
- Click on the *->* icon in the lower part of the VS Code window to upload the code.

## 4: 📡💻 Code the receiver

You will find the [code for the transmitter here.](https://github.com/Martinrolo/Arduino-RC-Plane/blob/main/src/receiver.cpp). 

The steps for uploading the receiver code are the same as for the transmitter, except that you need to select a different board:

### Uploading code through Arduino IDE
- You simply select another board as ***Arduino Nano***, which will be on a different port.

### Uploading code through VSCode 
- In the [***platformio.ini*** file](https://github.com/Martinrolo/Arduino-RC-Plane/blob/main/platformio.ini), change the ```upload_port``` field (line 21) for the result of the ```pio device list``` command. 

The rest of the procedures are the same.

## 5: 🎮 Build the controller 

## 6: ✈︎ Build the airplane
