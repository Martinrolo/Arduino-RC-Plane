#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// RF24 radio(7,8);
RF24 radio(9,10);

const byte address[6] = "00001";

struct payload { 
	 byte aileron;
     byte elevator;
     byte thrust;
}; 

payload myPayload; 

//Thrust data
int thrustJoyPinY = A0;                
int thrustJoyPinX = A1;                
int joystickThrust = 0;                  
int thrust = 0;

//Aileron/elevator data
int controlsJoyPinY = A2;
int controlsJoyPinX = A3;
int controlsY = 0;                  
int controlsX = 0;

void setup() {
    Serial.begin(115200);
    radio.begin();
    radio.setAutoAck(false);
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_HIGH); //REMETTRE HIGH
    radio.setDataRate(RF24_250KBPS);
    radio.setPayloadSize(sizeof(payload)); 
    radio.stopListening();
}

void loop() {  
    //get thrust data from right joystick
    joystickThrust = analogRead(thrustJoyPinY);  
    joystickThrust = constrain(joystickThrust, 550, 1023); 
    thrust = map(joystickThrust, 550, 1023, 0, 180);
    myPayload.thrust = thrust;

    //Get controls data from left joystick
    controlsY = analogRead(controlsJoyPinY);  
    controlsY = map(controlsY, 0, 1023, 110, 70);
    myPayload.elevator = controlsY;
    controlsX = analogRead(controlsJoyPinX);  
    controlsX = map(controlsX, 0, 1023, 110, 70);
    myPayload.aileron = controlsX;

    radio.write(&myPayload, sizeof(myPayload)); 

    //Printing data
    Serial.print("Data thrust:"); 
    Serial.print(myPayload.thrust); 
    Serial.print(" Data Elevator:"); 
    Serial.print(myPayload.elevator); 
    Serial.print(" Data Aileron:"); 
    Serial.println(myPayload.aileron); 
    
    delay(20); 
}
