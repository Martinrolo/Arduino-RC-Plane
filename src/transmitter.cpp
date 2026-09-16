#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <controlsData.h> 

RF24 radio(9,10);

const byte address[6] = "00001";

struct controlsData payload; 

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
    radio.setPALevel(RF24_PA_HIGH);
    radio.setDataRate(RF24_250KBPS);
    radio.setPayloadSize(sizeof(payload)); 
    radio.stopListening();
}

void loop() {  
    //get thrust data from right joystick
    joystickThrust = analogRead(thrustJoyPinY);  
    joystickThrust = constrain(joystickThrust, 550, 1023); 
    thrust = map(joystickThrust, 550, 1023, 0, 180);
    payload.thrust = thrust;

    //Get controls data from left joystick
    controlsY = analogRead(controlsJoyPinY);  
    controlsY = map(controlsY, 0, 1023, 120, 0);
    payload.elevator = controlsY;
    controlsX = analogRead(controlsJoyPinX);  
    controlsX = map(controlsX, 0, 1023, 0, 120);
    payload.aileron = controlsX;
    payload.rudder = controlsX;

    radio.write(&payload, sizeof(payload)); 

    //Printing data
    Serial.print(" Data Elevator:"); 
    Serial.print(payload.elevator); 
    Serial.print(" Data Rudder:"); 
    Serial.println(payload.rudder); 
    Serial.print(" Data Aileron:"); 
    Serial.println(payload.aileron); 
    Serial.print("Data thrust:"); 
    Serial.print(payload.thrust); 
    
    delay(20); 
}
