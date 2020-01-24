#ifndef PART1_H_
#define PART1_H_

#include <stdbool.h>

void initLCD(void);
void writeChar(char c, int pos);
void writeLong(long i);
void primes(void);
bool is_prime(long i);


// void clearLCD(void);


#endif /* PART1_H_ */