/*
 * main.c
 *
 *  Created on: Aug 18, 2023
 *      Author: user
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"



#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"

#include <avr/delay.h>

int main(void)

{
	CLCD_voidInitialization();
	u8 LOC_u8Iterator=0;
	u8 LOC_u8col=1;
	u8 *ptr="ALIAA ESLAM ";


	while(1)
	{
		while(ptr[LOC_u8Iterator] != '/0')
		{
			LOC_u8col++;
			CLCD_voidSendData(ptr[LOC_u8Iterator]);
			CLCD_voidSetPosition(CLCD_ROW_2,LOC_u8col);
			LOC_u8Iterator++;
			if(ptr[LOC_u8Iterator]== '/0')  break;
			CLCD_voidSendData(ptr[LOC_u8Iterator]);
			LOC_u8col++;
			CLCD_voidSetPosition(CLCD_ROW_1,LOC_u8col);
			LOC_u8Iterator++;
		}
		_delay_ms(50);


			/*

		CLCD_voidSendData('A');
		CLCD_voidSetPosition(2,2);
		CLCD_voidSendData('L');
		CLCD_voidSetPosition(1,3);
		CLCD_voidSendData('I');
		CLCD_voidSetPosition(2,4);
		CLCD_voidSendData('A');
		CLCD_voidSetPosition(1,5);
		CLCD_voidSendData('A');
		CLCD_voidSetPosition(2,6);

		CLCD_voidSetPosition(2,8);
		CLCD_voidSendData('E');
		CLCD_voidSetPosition(1,9);
		CLCD_voidSendData('S');
		CLCD_voidSetPosition(2,10);
		CLCD_voidSendData('L');
		CLCD_voidSetPosition(1,11);
		CLCD_voidSendData('A');
		CLCD_voidSetPosition(2,12);
		CLCD_voidSendData('M');
		_delay_ms(50);
		CLCD_voidClearScreen();
		*/
	}
	return 0;
}
