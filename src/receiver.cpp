#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <avr/wdt.h>
#include <receiver.h>

#define TIMEOUT_TRANSMISSION 500

RF24 radio(9,10);

const byte address[6] = "00001";

Servo channel_1;
Servo channel_2;
Servo channel_3;
Servo channel_4;

unsigned long lastTransmissionTime = 0;
bool signalLost = false;

struct payload { 
	 byte aileron;
     byte elevator;
     byte thrust;
}; 

payload myPayload; 


void setup() {
    wdt_disable();
    Serial.begin(115200); 

    channel_1.attach(2);
    channel_2.attach(3);
    channel_3.attach(4);
    channel_4.attach(5, 1000, 2000);
    channel_4.write(0);

    radio.begin(); 
    radio.setAutoAck(false); 
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_HIGH); //REMETTRE HIGH
    radio.setPayloadSize(sizeof(myPayload)); 
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
        payload tempPayload;
        radio.read(&tempPayload, sizeof(tempPayload)); 

        //check if aileron data makes sense
        //TODO: ADD OTHER TESTS
        if (tempPayload.aileron >= 50 && tempPayload.aileron <= 130) {
            myPayload = tempPayload;
            lastTransmissionTime = millis();

            Serial.print("AILERON DATA:"); 
            Serial.print(tempPayload.aileron); 

            Serial.print(" ELEVATOR DATA:"); 
            Serial.print(tempPayload.elevator); 

            Serial.print(" THRUST DATA:"); 
            Serial.println(tempPayload.thrust); 
        }

        readCount++;
    }
}

void writeData()
{
    channel_1.write(myPayload.elevator);
    channel_2.write(myPayload.aileron);
    channel_3.write(myPayload.aileron);
    channel_4.write(myPayload.thrust);
}

void lostTransmissionHandler()
{
    Serial.println("LOST TRANSMISSION"); 
    
    myPayload.aileron = 90;
    myPayload.elevator = 90;
    myPayload.thrust = 0;

    writeData();
}
