/*
 * main.c
 *
 * Created: 7/11/2023 6:45:06 PM
 *  Author: Abdallah Medhat
 */ 

 /*
         for KPD 
		 
#define KPD_PORT      DIO_PORTD		 
#define KPD_ROW_INIT  DIO_PIN0
#define KPD_ROW_END   DIO_PIN3

#define KPD_COL_INIT  DIO_PIN4
#define KPD_COL_END   DIO_PIN7

*/

/*
      for LCD 
	  
	  
#define CLCD_DATA_PORT      DIO_PORTA
 RS,RW,EN 
#define CLCD_CONTROL_PORT   DIO_PORTB
 
#define CLCD_RS             DIO_PIN1
#define CLCD_RW             DIO_PIN2
#define CLCD_EN             DIO_PIN3

*/



#include "LCD_Interface.h"
#include "KPD_Interface.h"
#include <util/delay.h>

int main(void)
{
	u8 read_data=0;
	
	LCD_Init();
	
	KPD_Init();
	
	LCD_SendNumber(KPD_GetPressed());
	

	


}