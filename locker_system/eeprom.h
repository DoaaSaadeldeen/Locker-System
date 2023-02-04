/*
 * eeprom.h
 *
 * Created: 11/18/2022 11:25:17 AM
 *  Author: safifi
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "std_macros.h"


void eerpom_write (uint16_t add, uint32_t data);
uint32_t eeprom_read(uint16_t add);
 

#endif /* EEPROM_H_ */