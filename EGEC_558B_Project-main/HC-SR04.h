#ifndef HC_SR04_C_
#define HC_SR04_C_


void HC_SR04_Init(void);

void TIMER0A_Handler(void);

void measurePulseWidth(void);

float getDistance(uint32_t time);


#endif
