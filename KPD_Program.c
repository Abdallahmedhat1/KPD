/*
 * KPD_Program.c
 *
 * Created: 7/11/2023 4:32:17 PM
 *  Author: Abdallah Medhat
 */ 
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_INTERFACE.h"

#include "KPD_Interface.h"
#include "KPD_Private.h"
#include "KPD_Config.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function initialize the pin which connected to KPD as input pins
 * Parameters : Nothing
 * return : Nothing
 */
void KPD_Init(void){

	/*                    Connect Internal pull up for the pins of the rows                             */

	Dio_SetPinDirection     ( KPD_PORT , KPD_R0 , DIO_PIN_INPUT );
	Dio_SetPinDirection     ( KPD_PORT , KPD_R1 , DIO_PIN_INPUT );
	Dio_SetPinDirection     ( KPD_PORT , KPD_R2 , DIO_PIN_INPUT );
	Dio_SetPinDirection     ( KPD_PORT , KPD_R3 , DIO_PIN_INPUT );
	
	
	Dio_SetPinValue         ( KPD_PORT , KPD_R0 , DIO_PIN_HIGH );
	Dio_SetPinValue         ( KPD_PORT , KPD_R1 , DIO_PIN_HIGH );
	Dio_SetPinValue         ( KPD_PORT , KPD_R2 , DIO_PIN_HIGH );
	Dio_SetPinValue         ( KPD_PORT , KPD_R3 , DIO_PIN_HIGH );
	
	
	



	Dio_SetPinDirection( KPD_PORT , KPD_C0 , DIO_PIN_OUTPUT );
	Dio_SetPinDirection( KPD_PORT , KPD_C1 , DIO_PIN_OUTPUT );
	Dio_SetPinDirection( KPD_PORT , KPD_C2 , DIO_PIN_OUTPUT );
	Dio_SetPinDirection( KPD_PORT , KPD_C3 , DIO_PIN_OUTPUT );

	Dio_SetPinValue    ( KPD_PORT , KPD_C0 , DIO_PIN_HIGH );
	Dio_SetPinValue    ( KPD_PORT , KPD_C1 , DIO_PIN_HIGH );
	Dio_SetPinValue    ( KPD_PORT , KPD_C2 , DIO_PIN_HIGH );
	Dio_SetPinValue    ( KPD_PORT , KPD_C3 , DIO_PIN_HIGH );

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function used to get the pressed button of the kpd
 * Parameters : Nothing
 * return : the pressed button
 */
u8   KPD_GetPressed( void ){

	u8 LOC_ReturnData = NOTPRESSED ;
	
	
	/* iterators  */
	u8 LOC_Row ;
	
	u8 LOC_Col ;
	
  u8 read_value=0; // retun the row value
			 

	for( LOC_Col = 0 + KPD_COL_INIT ; LOC_Col < KPD_COL_END + 1 ; LOC_Col++ ){

		Dio_SetPinValue  ( KPD_PORT , LOC_Col , DIO_PIN_LOW );   // Low on the columns

		for( LOC_Row = 0 +KPD_ROW_INIT ; LOC_Row < KPD_ROW_END + 1 ; LOC_Row++ ){

			 read_value=Dio_GetPinValue  ( KPD_PORT , LOC_Row  ); // retun the row value
			/* 
			if the row is high ....there is no pressed buttons
			if the row is low ....there is pressed button ===>> I will check on this
			 */
			if( read_value == 0 )
			{

				_delay_ms(50);   // delay for bouncing

				read_value= Dio_GetPinValue( KPD_PORT , LOC_Row );   // to make sure that the button is pressed & check again

				if( read_value == 0 )

				{
					/*      # Important Note #

					the button will khnow by the row and the column (ASCII Code)
					==> Hint1 : I already defined The ASCII Codes in 2D array at --> "KPD_config.h"
					==> Hint2 : if there is no pressed buttons , it will retured NOTPRESSED (0xff) and there is not any button has this ASCII (0xff)
					*/

					LOC_ReturnData = KPD_u8Buttons[ LOC_Row - KPD_ROW_INIT ][ LOC_Col - KPD_COL_INIT ];

				}

				// stay here if the button is pressed   # we could put delay 200 ms instead of that
			read_value=	Dio_GetPinValue( KPD_PORT ,LOC_Row );
			
				while( DIO_PIN_LOW == read_value ) /*  This cond for safty instead of (LOC_u8GetPressed == DIO_PIN_LOW) if i foget = */
				{

				read_value=	Dio_GetPinValue( KPD_PORT , LOC_Row  );

				}

				break ;

			}

		}

		// return this column’s pin to high
		
		Dio_SetPinValue    ( KPD_PORT , LOC_Col , DIO_PIN_HIGH );

	}

	return LOC_ReturnData ;

}