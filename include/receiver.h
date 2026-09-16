#ifndef RECEIVER_H
#define RECEIVER_H

void receiveData();
void resetData();
void writeData();
uint8_t setNextServoValue(uint8_t target, uint8_t current, int16_t step);
void lostTransmissionHandler();

#endif