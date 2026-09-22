#ifndef RECEIVER_H
#define RECEIVER_H

void receiveData();
void resetData();
void writeData();
int16_t setNextServoValue(int16_t target, int16_t current, int16_t step);
void lostTransmissionHandler();

#endif