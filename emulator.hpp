#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <stdlib.h>
#include <stdint.h>

enum { HIGH, LOW };
enum { INPUT, OUTPUT, INPUT_PULLUP };

extern void setup(void);
extern void loop(void);

extern void digitalWrite(int pin, int state);
extern void pinMode(int pin, int mode);

unsigned long micros(void);
unsigned long millis(void);

#endif
