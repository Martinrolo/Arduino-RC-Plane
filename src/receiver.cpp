#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <avr/wdt.h>
#include <receiver.h>
#include <controlsData.h>

#define TIMEOUT_TRANSMISSION 500

RF24 radio(9,10);

const byte address[6] = "00001";

Servo channel_1;
Servo channel_2;
Servo channel_3;
Servo channel_4;
Servo channel_5;

unsigned long lastTransmissionTime = 0;
bool signalLost = false;

struct controlsData payload; 

void setup() {
    wdt_disable();
    Serial.begin(115200); 

    //Set servos at 0



    channel_1.attach(2);
    channel_2.attach(3);
    channel_3.attach(4);
    channel_4.attach(5);
    channel_5.attach(6, 1000, 2000);
    channel_5.write(0);

    radio.begin(); 
    radio.setAutoAck(false); 
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_HIGH);
    radio.setPayloadSize(sizeof(payload)); 
    radio.openReadingPipe(0, address); 
    radio.startListening(); 
    wdt_enable(WDTO_250MS);
}

void loop() {
    wdt_reset();
    receiveData();

    //Signal is lost if it's been more than 500ms since last transmission
    int timeDifference = millis() - lastTransmissionTime;
    signalLost = timeDifference > TIMEOUT_TRANSMISSION;

    if (signalLost) lostTransmissionHandler();
    writeData();
}

void receiveData()
{
    byte readCount = 0;
    while (radio.available() && readCount < 5)
    {
        struct controlsData tempPayload;
        radio.read(&tempPayload, sizeof(tempPayload)); 

        //check if aileron data makes sense
        if (tempPayload.aileron >= 70 && tempPayload.aileron <= 110) {
            payload = tempPayload;
            lastTransmissionTime = millis();

            Serial.print("AILERON:"); 
            Serial.print(tempPayload.aileron); 

            Serial.print(" RUDDER:"); 
            Serial.print(tempPayload.rudder); 

            Serial.print(" ELEVATOR:"); 
            Serial.print(tempPayload.elevator); 

            Serial.print(" THRUST:"); 
            Serial.println(tempPayload.thrust); 
        }

        readCount++;
    }
}

void writeData()
{
    channel_1.write(payload.elevator);
    channel_2.write(payload.rudder);
    channel_3.write(payload.aileron);
    channel_4.write(payload.aileron);
    channel_5.write(payload.thrust);
}

void lostTransmissionHandler()
{
    Serial.println("LOST TRANSMISSION"); 
    
    payload.elevator = 30;
    payload.aileron = 30;
    payload.rudder = 30;
    payload.thrust = 0;

    writeData();
}
