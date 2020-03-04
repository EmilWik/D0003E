#pragma once

#include <stdint.h>		// uint8_t


void openSerialPort(void);

void writeToAVR(uint8_t instruction);

void* getLights(void* arg);

