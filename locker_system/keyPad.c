/*
 * keyPad.c
 *
 * Created: 11/20/2022 10:41:19 PM
 *  Author: Dell_G3
 */ 
#include "keyPadCfg.h"
#include "keyPad.h"
int8_t const KP_matrix[]={
	'7','8','9','/',
	'4','5','6','*',
	'1','2','3','-',
	'c','0','=','+'
};

void initKeyPad(void){
	init_keypad();
}
int8_t readKeyPad(void){
	K4(0);K5(1);K6(1);K7(1);
	if(K0()==0) return KP_matrix[0];
	if(K1()==0) return KP_matrix[1];
	if(K2()==0) return KP_matrix[2];
	if(K3()==0) return KP_matrix[3];
	_delay_ms(5);

	K4(1);K5(0);K6(1);K7(1);
	if(K0()==0) return KP_matrix[4];
	if(K1()==0) return KP_matrix[5];
	if(K2()==0) return KP_matrix[6];
	if(K3()==0) return KP_matrix[7];
	_delay_ms(5);
	
	K4(1);K5(1);K6(0);K7(1);
	if(K0()==0) return KP_matrix[8];
	if(K1()==0) return KP_matrix[9];
	if(K2()==0) return KP_matrix[10];
	if(K3()==0) return KP_matrix[11];
	_delay_ms(5);
	
	K4(1);K5(1);K6(1);K7(0);
	if(K0()==0) return KP_matrix[12];
	if(K1()==0) return KP_matrix[13];
	if(K2()==0) return KP_matrix[14];
	if(K3()==0) return KP_matrix[15];
	_delay_ms(5);
	
	return -1;
}