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
    resetData();       


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
        if (tempPayload.aileron >= 0 && tempPayload.aileron <= 120) {
            payload = tempPayload;
            lastTransmissionTime = millis();

            int16_t elevatorRead = channel_1.read();
            int16_t rudderRead = channel_2.read();
            int16_t aileronRead = channel_3.read();
            int16_t thrustRead = channel_5.read();

            payload.elevator = setNextServoValue(tempPayload.elevator, elevatorRead, 4);
            payload.rudder = setNextServoValue(tempPayload.rudder, rudderRead, 4);
            payload.aileron = setNextServoValue(tempPayload.aileron, aileronRead, 4);
            payload.thrust = setNextServoValue(tempPayload.thrust, thrustRead, 10);

            Serial.print("AILERON:"); 
            Serial.print(payload.aileron); 
            Serial.print(" RUDDER:"); 
            Serial.print(payload.rudder); 
            Serial.print(" ELEVATOR:"); 
            Serial.print(payload.elevator); 
            Serial.print(" THRUST:"); 
            Serial.println(payload.thrust); 
        }

        readCount++;
    }
}

int16_t setNextServoValue(int16_t target, int16_t current, int16_t step)
{
    if(abs(target - current) < step) 
    {
        return target; //If the difference is less than the step, just put the difference
    }


    if(target > current) return current + step;
    if(target < current) return current - step;

    return current;
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
    resetData();       
    writeData();
}

void resetData()
{
    payload.elevator = 60;
    payload.aileron = 60;
    payload.rudder = 60;
    payload.thrust = 0;
}
