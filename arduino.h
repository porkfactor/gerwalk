#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <stdlib.h>
#include <stdint.h>

extern void setup(void);
extern void loop(void);

unsigned long micros(void);
unsigned long millis(void);

#endif
