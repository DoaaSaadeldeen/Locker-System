/*
 * locker_system.c
 *
 * Created: 11/29/2022 2:09:16 PM
 * Author : Dell_G3
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "eeprom.h"
#include "LCD.h"
#include "keypad.h"
#include "std_macros.h"


void change(int32_t);
void open(int32_t);
void close(void);
void reset(void);
void read_num(void);
int32_t arr_sz = 0,opened=1,closed=0,deflt=0,state=0,saved_pass;
void save_pass(int32_t pass)//1234
{
	eerpom_write(0,pass%10);pass/=10;//4
	eerpom_write(1,pass%10);pass/=10;//3
	eerpom_write(2,pass%10);pass/=10;//2
	eerpom_write(3,pass%10);pass/=10;//1
}
int32_t read_pass()//1234
{
	int32_t pass=0;
	pass*=10;pass+=eeprom_read(3);//1
	pass*=10;pass+=eeprom_read(2);//2
	pass*=10;pass+=eeprom_read(1);//3
	pass*=10;pass+=eeprom_read(0);//4
	return pass;
}
int main(void)
{
	LCD_init();
	initKeyPad();
	state=0;
	//save_pass(0);
	saved_pass = read_pass();
    while (1) 
    {
		read_num();
    }
}
void read_num(void)
{
	int32_t key=-1,idx=0;
	int8_t  arr[12];
	arr_sz=0;
	while(1)
	{
		key=readKeyPad();//check if any key pressed
		while(key==-1){key=readKeyPad();}//not press any button
		if(key=='c'){ LCD_write_command(0x01);//clear
			idx=0;  continue;
		}
		while(readKeyPad()!=-1){}//still pressed
		LCD_write_char('*');
		if(key == '='){break;}
		if(key=='*' && idx==0){
			arr[idx]=key;idx++;break;
		}
		 if((key>='0' && key<='9') || key=='/' ){arr[idx]=key;idx++;}
		 else{
			LCD_write_command(0x01);//clear
			LCD_write_string("only digits allowed"); idx=0;
		}
		if(idx==10){break;}
	}
	
	arr_sz=idx;
	//****************************************************************************
	
		LCD_write_command(0x01);
		if(arr_sz==6 && arr[0]=='/' && arr[5]=='/')//change               / 4dig /
		{
			int32_t password=0;
			for(int i=1;i<=4;i++){
				password*=10;
				password+=(arr[i]-'0');
			}
			 change(password);
		}
		if(idx==10 && state == opened){//reset     0000000000
			int8_t flag=1;
			for(int8_t i=0;i<10;i++){
			if(arr[i]!='0') 
			 {
				 flag=0;
				 break;
			 }
			}
			if(flag==1) reset();
		}
		else if(arr_sz==1 && arr[0]=='*'  ){//close && state==opened              *
			close();
		}
		else if(arr_sz==4 && state == closed){//open                   4dig
			int32_t password=0;
			for(int i=0;i<arr_sz;i++){
				password*=10;
				password+=(arr[i]-'0');
			}

			//LCD_write_number(password);
			open(password);
		}

}
void change(int32_t newPass)
{
	LCD_write_string("changing...");
	saved_pass=newPass;
	save_pass(saved_pass);
}
void close(void)
{
	LCD_write_string("closing....");
	state=closed;
}
void reset(void)
{
	LCD_write_string("reseting....");
    saved_pass = 0; 
	save_pass(saved_pass);
	
}
void open(int32_t password)
{
		
	if(password == saved_pass)
	{
		state = opened;
		LCD_write_string("locker opened");
	}
	else{
		LCD_write_string("Try again");
	}
	//_delay_ms(3000);//wait 3 seconds
}

