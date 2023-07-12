/*
 * LCD_Program.c
 *
 * Created: 7/7/2023 7:43:41 PM
 *  Author: Abdallah Medhat
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_INTERFACE.h"

#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"


/***************************************************************************************/

/*

###########  8 Bits Mode
 -----------                   ----------
 | ATmega32  |                 |   LCD    |
 |           |                 |          |
 |        PA7|---------------->|D7        |
 |        PA6|---------------->|D6        |
 |        PA5|---------------->|D5        |
 |        PA4|---------------->|D4        |
 |        PA3|---------------->|D3        |
 |        PA2|---------------->|D2        |
 |        PA1|---------------->|D1        |
 |        PA0|---------------->|D0        |
 |           |                 |          |
 |        PC2|---------------->|E         |
 |        PC1|---------------->|RW        |
 |        PC0|---------------->|RS        |
 -----------                   ----------
 */
/***************************************************************************************/


//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function Apply initialization sequence for LCD module
* Parameters : nothing
* return : nothing
*/
void LCD_Init        ( void ){



	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      8 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	#if   CLCD_MODE == 8

	// 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
	_delay_ms(50);

	// All Pins as OutPut pins
	Dio_SetPortDirection ( CLCD_DATA_PORT    , DIO_PORT_OUTPUT           );
	Dio_SetPinDirection ( CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_OUTPUT  );
	Dio_SetPinDirection  ( CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_OUTPUT  );
	Dio_SetPinDirection  ( CLCD_CONTROL_PORT , CLCD_EN , DIO_PIN_OUTPUT  );

	/* Return cursor to the first position on the first line  */
	LCD_SendCommand(lcd_Home);
	_delay_ms(1);

	/*FUNCTION SET Command : 2 lines , 5*8 font size */
	LCD_SendCommand( EIGHT_BITS ); // 8 Bit Mode ==> 0x38
	_delay_ms(1); // wait more than 39 Ms

	/* DISPLAY & Cursor (ON / OFF) Control */
	LCD_SendCommand( lcd_DisplayOn_CursorOff );
	_delay_ms(1);

	/* DISPLAY CLEAR */
	LCD_ClearScreen();

	/* ENTRY MODE  SET*/
	LCD_SendCommand( lcd_EntryMode );
	_delay_ms(1);



	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*
	#elif   CLCD_MODE == 4

	// 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
	_delay_ms(50);
	    Dio_SetPinDirection     (CLCD_DATA_PORT,DIO_PIN4,DIO_PIN_OUTPUT);
		Dio_SetPinDirection     (CLCD_DATA_PORT,DIO_PIN5,DIO_PIN_OUTPUT);
		Dio_SetPinDirection     (CLCD_DATA_PORT,DIO_PIN6,DIO_PIN_OUTPUT);
		Dio_SetPinDirection     (CLCD_DATA_PORT,DIO_PIN7,DIO_PIN_OUTPUT);
		Dio_SetPinDirection     ( CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_OUTPUT );
		Dio_SetPinDirection     ( CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_OUTPUT );
		Dio_SetPinDirection     ( CLCD_CONTROL_PORT , CLCD_EN , DIO_PIN_OUTPUT );

*/

	/*return home*/
	//LCD_SendCommand( lcd_Home );
	//_delay_ms(30);

	/*FUNCTION SET Command*/
//	LCD_SendCommand( FOUR_BITS ); // 4 Bit Mode
//	_delay_ms(1);

	/* DISPLAY & Cursor (ON / OFF) Control */
	//LCD_SendCommand( lcd_DisplayOn_CursorOff );
	//_delay_ms(1);

	/* DISPLAY CLEAR */
	//LCD_ClearScreen();

	/* ENTRY MODE  Set*/
	//LCD_SendCommand( lcd_EntryMode );
	//_delay_ms(1);


	#endif




}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send data to the port which is defined in config.h
* Parameters :
            => Copy_u8Data --> Data that you want to display (for every pixel )
* return : nothing
*/
void LCD_SendData    ( u8 Data ){

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      8 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	if  ( CLCD_MODE == 8)
{
	Dio_SetPortValue ( CLCD_DATA_PORT    , Data        );
	Dio_SetPinValue  ( CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_HIGH );
	Dio_SetPinValue  ( CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_LOW  );
	LCD_SendFallingEdge();
}
else
{
	
}

}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*	#elif   CLCD_MODE == 4

	Dio_SetPinValue  ( CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_HIGH );
	Dio_SetPinValue  ( CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_LOW  );
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,(Copy_u8Data>>4));            // send the most 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,Copy_u8Data);               // send the least 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();

	#endif

	_delay_ms(1);

}
*/
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function Interface to send the configuration commands to the LCD Driver
* Parameters :
            => Copy_u8Command --> Command number
* return : nothing
*Hint : RS pin Mode is the difference between this function and the previous (CLCD_voidSendData)
*/
void LCD_SendCommand ( u8 Command ){

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      8 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	if ( CLCD_MODE == 8)

	Dio_SetPortValue ( CLCD_DATA_PORT    , Command     );
	Dio_SetPinValue  ( CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_LOW  );
	// RW always connect to GND to Write
	Dio_SetPinValue          (CLCD_CONTROL_PORT,CLCD_RW , DIO_PIN_LOW    );
	LCD_SendFallingEdge();
}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	/*
	#elif   CLCD_MODE == 4

	DIO_enumSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_LOW  );
	DIO_enumSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_LOW  );
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,Copy_u8Command>>4);             // send the most 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,Copy_u8Command);                // send the least 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();

	#endif

	_delay_ms(1);

}
*/

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send string to the port which is defined in config.h
* Parameters :
            => * Copy_u8ptrString  --> Pointer to the string
* return : nothing
*/
void LCD_SendString  ( const u8 * Copy_u8ptrString ){

	u8 LOC_u8Iterator = 0 ;

	while( Copy_u8ptrString[LOC_u8Iterator] != '\0' ) 
	
	{

		LCD_SendData( Copy_u8ptrString[LOC_u8Iterator] );
		LOC_u8Iterator++ ;

	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send number to the port which is defined in config.h
* Parameters :
            => Copy_u64Number --> number that you want to display
* return : nothing
*/
void LCD_SendNumber   ( u64 Copy_u64Number    ){

	u64 LOC_u64Reversed = 1 ;

	if( Copy_u64Number == 0 )
	{
		 LCD_SendData('0');
		 
		  }

	else{

		while( Copy_u64Number != 0 ){

			LOC_u64Reversed = ( LOC_u64Reversed * 10 ) + ( Copy_u64Number % 10 );
			Copy_u64Number /= 10 ;

		}
		while( LOC_u64Reversed != 1 ){

			LCD_SendData( ( LOC_u64Reversed % 10 ) + 48 );
			LOC_u64Reversed /= 10 ;

		}

	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function set the curser position
* Parameters :
            => Copy_u8Row --> row number (CLCD_ROW_1 or CLCD_ROW_2)
			=> Copy_u8Col --> column number (CLCD_COL_1 ... CLCD_COL_16)
* return : nothing
*Hint :-
   In This function we send a command which =0b1xxxxxxx
   MSB = 1  ===> refers that it is command to set cursor
   xxxxxxx  ===> refers to AC ( Address Counter 7Bits / DDRAM Locations 128Location )
*/
void LCD_SetPosition ( u8 Copy_u8Row , u8 Copy_u8Col ){

	u8 LOC_u8data ;

	/* In These cases will set at (0,0) ==> if the user enter invalid location */
	if(Copy_u8Row>2||Copy_u8Row<1||Copy_u8Col>16||Copy_u8Col<1)  //check
	{
		LOC_u8data = lcd_SetCursor ;   // first location 
	}

	else if( Copy_u8Row == CLCD_ROW_1 ){

		LOC_u8data = ( ( lcd_SetCursor ) + ( Copy_u8Col - 1 ) );              //Row1 -> 0x80+col-1

	}

	else if( Copy_u8Row == CLCD_ROW_2 ){

		LOC_u8data = ( ( lcd_SetCursor ) + (64) + ( Copy_u8Col - 1 ) );       //Row2 -> 0xc0+col-1

	}
	LCD_SendCommand ( LOC_u8data );
	_delay_ms(1);

}


//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send extra char
* Parameters :
            => Copy_u8Row --> row number (CLCD_ROW_1 or CLCD_ROW_2)
			=> Copy_u8Col --> column number (CLCD_COL_1 ... CLCD_COL_16)
* return : nothing
* Hint :-
	Address Counter can refer to CGRAM and DDRAM
*/
/*
void CLCD_voidSendExtraChar( u8 Copy_u8Row , u8 Copy_u8Col ){

	u8 LOC_u8Iterator = 0 ;
	/* 1- Go To CGRAM            */
	// CLCD_voidSendCommand( lcd_CGRAM );  // Make AC refers to the first Place/Address at CGRAM


	/* 2- Draw Character in CGRAM        */
	/* Hint : it will be copied to DDRAM automatically */
	//for( LOC_u8Iterator = 0 ; LOC_u8Iterator < sizeof(CLCD_u8ExtraChar) / sizeof(CLCD_u8ExtraChar[0]) ; LOC_u8Iterator++){

	//	CLCD_voidSendData( CLCD_u8ExtraChar[LOC_u8Iterator] );

	// }


	/* 3- Back (AC) To DDRAM          */
	
	/*
	CLCD_voidSetPosition(Copy_u8Row,Copy_u8Col);


	4- Send Character Address 
	for( LOC_u8Iterator = 0 ; LOC_u8Iterator < 8 ; LOC_u8Iterator++ ){

		CLCD_voidSendData( LOC_u8Iterator );

	}

}
*/

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function clear LCD
* Parameters : nothing
* return : nothing
*/
void LCD_ClearScreen(void)
{
	LCD_SendCommand(lcd_Clear);
	_delay_ms(10); //wait more than 1.53 ms
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send a pulse (falling edge ) to Enable Pin
* Parameters : nothing
* return : nothing
*
* Hint : static Function to forbid calling it out this file
*
*/
  void  LCD_SendFallingEdge    (void)
{
	Dio_SetPinValue ( CLCD_CONTROL_PORT , CLCD_EN , DIO_PIN_HIGH);
	
	_delay_ms(1);
	
	 Dio_SetPinValue ( CLCD_CONTROL_PORT , CLCD_EN , DIO_PIN_LOW  );
	
	_delay_ms(1);
	


}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    END    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
