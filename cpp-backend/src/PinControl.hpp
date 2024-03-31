#ifndef _PIN_CONTROL_HPP
#define _PIN_CONTROL_HPP

void StartSerial(const char* port);
void StopSerial();

void WritePin(int pin, bool value);
bool ReadPin(int pin);

// false for input, true for output
void ConfigPinMode(int pin, bool mode);

#endif /* _PIN_CONTROL_HPP */