/*
 * KPD_Interface.h
 *
 * Created: 7/11/2023 4:31:23 PM
 *  Author: Abdallah Medhat
 */ 


#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_


#define NOTPRESSED 0xff

void KPD_Init(void);
u8   KPD_GetPressed( void );



#endif /* KPD_INTERFACE_H_ */