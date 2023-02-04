/*
 * keyPadCfg.h
 *
 * Created: 11/20/2022 10:42:03 PM
 *  Author: Dell_G3
 */ 


#ifndef KEYPADCFG_H_
#define KEYPADCFG_H_
#include "std_macros.h"
/*
c0 ->
c1 ->
c2 ->
*/
#define init_keypad() DDRC = 0b11110000; PORTC = 0b11111111;//output input
//input pins
#define K0() READBIT(PINC,0)///////////////////////////////*****
#define K1() READBIT(PINC,1)
#define K2() READBIT(PINC,2)
#define K3() READBIT(PINC,3)

//output pins
#define K4(x) if(x==1){SETBIT(PORTC,4);} else {CLRBIT(PORTC,4);}
#define K5(x) if(x==1){SETBIT(PORTC,5);} else {CLRBIT(PORTC,5);}
#define K6(x) if(x==1){SETBIT(PORTC,6);} else {CLRBIT(PORTC,6);}
#define K7(x) if(x==1){SETBIT(PORTC,7);} else {CLRBIT(PORTC,7);}




#endif /* KEYPADCFG_H_ */