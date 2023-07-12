/*
 * DIO_program.c
 *
 * Created: 6/30/2023 11:55:02 PM
 *  Author: Abdallah Medhat
 */
#include "DIO_interface.h"
#include "BIT_MATH.h" 
#include "DIO_PRIVATE.h"

void Dio_SetPinDirection(u8 port,u8 pin,u8 Direction)
{
	if(Direction==DIO_PIN_OUTPUT)
	{
		switch(port)
		{
		 case DIO_PORTA:
		  SET_BIT(DDRA,pin);
		     break;
	      case DIO_PORTB:
			SET_BIT(DDRB,pin);
			break;
				case DIO_PORTC:
				SET_BIT(DDRC,pin);
				break;
					case DIO_PORTD:
					SET_BIT(DDRD,pin);
					break;
		}
	}
	else if(Direction==DIO_PIN_INPUT)
	{
		switch(port)
		{
			  case DIO_PORTA:
		      	CLR_BIT(DDRA,pin);
		     	break;
			    case DIO_PORTB:
			      CLR_BIT(DDRB,pin);
			        break;
			         case DIO_PORTC:
			           CLR_BIT(DDRC,pin);
			           break;
			             case DIO_PORTD:
			                CLR_BIT(DDRD,pin);
			                  break;
		}
	}
	
}
void Dio_SetPinValue(u8 port,u8 pin,u8 value)
{
	if(value==DIO_PIN_HIGH)
	{
		switch(port)
		{
			     case DIO_PORTA:
			           SET_BIT(PORTA,pin);
			             break;
			              case DIO_PORTB:
			                 SET_BIT(PORTB,pin);
			                     break;
			                        case DIO_PORTC:
			                            SET_BIT(PORTC,pin);
			                                   break;
			                            case DIO_PORTD:
			                               SET_BIT(PORTD,pin);
			                                      break;
		}
	}
	else if(value==DIO_PIN_LOW)
	{
		switch(port)
		{
			                    case DIO_PORTA:
			                      CLR_BIT(PORTA,pin);
			                          break;
			                         case DIO_PORTB:
			                          CLR_BIT(PORTB,pin);
			                             break;
			                              case DIO_PORTC:
			                                 CLR_BIT(PORTC,pin);
			                                      break;
			                                    case DIO_PORTD:
			                                        CLR_BIT(PORTD,pin);
			                                              break;
		}
	}
	
}
u8 Dio_GetPinValue(u8 port,u8 pin)
{
	u8 loc_status=0;
		switch(port)
		{
			         case DIO_PORTA:
			              loc_status= GET_BIT(PINA,pin);
			                    break;
			                       case DIO_PORTB:
			                          loc_status= GET_BIT(PINB,pin);
			                                  break;
			                                   case DIO_PORTC:
			                                   loc_status=  GET_BIT(PINC,pin);
			                                          break;
			                                            case DIO_PORTD:
														loc_status=  GET_BIT(PIND,pin);
			                                                  break;
		}
	                                                          return loc_status;
}

void Dio_TogglePin(u8 port,u8 pin)
{
	switch(port)
	{
		case DIO_PORTA:
		TOG_BIT(PORTA,pin);
		break;
		case DIO_PORTB:
		TOG_BIT(PORTB,pin);
		break;
		case DIO_PORTC:
		TOG_BIT(PORTC,pin);
		break;
		case DIO_PORTD:
		TOG_BIT(PORTD,pin);
		break;
	}
}

void Dio_SetPortDirection(u8 port,u8 Direction)
{
	switch(port)
	{
		case DIO_PORTA:
		DDRA=Direction;
		break;
		case DIO_PORTB:
		DDRB=Direction;
		break;
		case DIO_PORTC:
		DDRC=Direction;
		break;
		case DIO_PORTD:
		DDRD=Direction;
		break;
	}
}
void Dio_SetPortValue(u8 port,u8 value)
{
		switch(port)
		{
			case DIO_PORTA:
			PORTA=value;
			break;
			case DIO_PORTB:
			PORTB=value;
			break;
			case DIO_PORTC:
			PORTC=value;
			break;
			case DIO_PORTD:
			PORTD=value;
			break;
		}
}
u8 Dio_TogglePortValue(u8 port)
{
		switch(port)
		{
			case DIO_PORTA:
			PORTA=~PORTA;
			break;
			case DIO_PORTB:
			PORTB=~PORTB;
			break;
			case DIO_PORTC:
			PORTC=~PORTC;
			break;
			case DIO_PORTD:
			PORTD=~PORTD;
			break;
		}
	
}
u8 Dio_GetPortValue(u8 port,u8*ptr_value)
{
	switch(port)
	{
			case DIO_PORTA:
			*ptr_value=PINA;
			break;
			case DIO_PORTB:
		     *ptr_value=PINB;
			 break;
			 case DIO_PORTC:
			  *ptr_value=PINC;
			 break;
			 case DIO_PORTD:
			  *ptr_value=PIND;
			  break;
	}
	return *ptr_value;
}