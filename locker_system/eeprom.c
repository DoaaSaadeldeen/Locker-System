/*
 * eeprom.c
 *
 * Created: 11/18/2022 11:24:59 AM
 *  Author: safifi
 */ 
#include "eeprom.h"
#include "std_macros.h"

void eerpom_write (uint16_t add, uint32_t data){
	while(READBIT(EECR, EEWE) != 0); //writting operation is already on 
	EEAR = add;
	EEDR = data;
	SETBIT(EECR, EEMWE);
	SETBIT(EECR, EEWE);
}
uint32_t eeprom_read(uint16_t add){
	while(READBIT(EECR, EEWE) != 0); //writting operation is already on 
	EEAR = add;
	SETBIT(EECR, EERE);
	return EEDR;
}