#ifndef _OPERATIONAL_H_
#define _OPERATIONAL_H_

#include <stdint.h>

void PIN_SETUP(void);
void BEEP(uint8_t reps);
void LED(uint8_t reps);
void OPEN(void);
void CLOSE(void);
char GET_KEY(void);
float GET_BATTERY(void);


#endif