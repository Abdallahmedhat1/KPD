/*
 * LCD_Config.h
 *
 * Created: 7/7/2023 7:42:17 PM
 *  Author: Abdallah Medhat
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#define CLCD_MODE  8


/***************************************************************************************/


/* D0 ------> D7 */

/*

  Options:-
 	 1-DIO_PORTA
 	 2-DIO_PORTB
 	 3-DIO_PORTC
 	 4-DIO_PORTD

 */
/***************************************************************************************/


#define CLCD_DATA_PORT      DIO_PORTA
/* RS,RW,EN */
#define CLCD_CONTROL_PORT   DIO_PORTB




/*

 Options:-
 	 1-DIO_PIN0
 	 2-DIO_PIN1
 	 3-DIO_PIN2
 	 4-DIO_PIN3
 	 5-DIO_PIN4
 	 6-DIO_PIN5
 	 7-DIO_PIN6
 	 8-DIO_PIN7

 */
#define CLCD_RS             DIO_PIN1
#define CLCD_RW             DIO_PIN2
#define CLCD_EN             DIO_PIN3






#endif /* LCD_CONFIG_H_ */