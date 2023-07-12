/*
 * DIO_INTERFACE.h
 *
 * Created: 6/30/2023 11:54:19 PM
 *  Author: Abdallah Medhat
 */ 
#include "STD_TYPES.h"

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


#define DIO_PIN_OUTPUT  1
#define DIO_PIN_INPUT   0

#define DIO_PORT_OUTPUT  1
#define DIO_PORT_INPUT   0

#define DIO_PORT_HIGH   1
#define DIO_PORT_LAW    0
 
#define DIO_PIN_HIGH   1
#define DIO_PIN_LOW    0

#define DIO_PIN0      0
#define DIO_PIN1      1
#define DIO_PIN2      2
#define DIO_PIN3      3
#define DIO_PIN4      4
#define DIO_PIN5      5
#define DIO_PIN6      6
#define DIO_PIN7      7

#define DIO_PORTA      0
#define DIO_PORTB      1
#define DIO_PORTC      2
#define DIO_PORTD      3

         //func to pins
void Dio_SetPinDirection(u8 port,u8 pin,u8 Direction);   
void Dio_SetPinValue(u8 port,u8 pin,u8 value);
u8 Dio_GetPinValue(u8 port,u8 pin);
void Dio_TogglePin(u8 port,u8 pin);
         //func to ports
void Dio_SetPortDirection(u8 port,u8 Direction);
void Dio_SetPortValue(u8 port,u8 value);
u8 Dio_TogglePortValue(u8 port);
u8 Dio_GetPortValue(u8 port,u8*ptr_value);

#endif /* DIO_INTERFACE_H_ */