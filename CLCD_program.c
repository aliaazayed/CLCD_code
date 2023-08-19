/*
 *
 *<<<<<<<<<<<<<<<<<<<<<CLCD_PROGRAM.c>>>>>>>>>>>>>>>>>>>>>
 * Author : ALIAA ESLAM ZAYED
 * Created: 18 /8/2023
 * Layer  : HAL
 * SWC    : CLCD
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"


#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"
#include "CLCD_extraChar.h"


#include <avr/delay.h>

void CLCD_voidInitialization(void)
{
	#if CLCD_MODE ==EIGHT_BIT_MODE
	MDIO_voidSetPortDirection( CLCD_DATA_PORT, DIO_PORT_OUTPUT);
	MDIO_voidSetPinDirection( CLCD_CONTROL_PORT, CLCD_RS_PIN,DIO_PIN_OUTPUT);
	MDIO_voidSetPinDirection( CLCD_CONTROL_PORT, CLCD_RW_PIN,DIO_PIN_OUTPUT);
	MDIO_voidSetPinDirection( CLCD_CONTROL_PORT, CLCD_EN_PIN,DIO_PIN_OUTPUT);

	_delay_ms(50);
	CLCD_voidClearScreen();
	CLCD_voidSendCommand(CLCD_RETURN_HOME);
	_delay_ms(50);
	CLCD_voidSendCommand(FUNCTION_SET_TWO_LINE );
	_delay_ms(1);
	CLCD_voidSendCommand(LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF  );
	_delay_ms(1);
	CLCD_voidClearScreen();
	CLCD_voidSendCommand(LCD_ENTRY_MODE_SHIFT_LEFT );
	
	#elif CLCD_MODE == FOUR_BIT_MODE
	MDIO_voidSetPinDirection( CLCD_DATA_PORT, CLCD_PIN4, DIO_PIN_OUTPUT);
	MDIO_voidSetPinDirection( CLCD_DATA_PORT, CLCD_PIN5, DIO_PIN_OUTPUT);
	MDIO_voidSetPinDirection( CLCD_DATA_PORT, CLCD_PIN6, DIO_PIN_OUTPUT);
	MDIO_voidSetPinDirection( CLCD_DATA_PORT, CLCD_PIN7, DIO_PIN_OUTPUT);
	MDIO_voidSetPinDirection( CLCD_CONTROL_PORT, CLCD_RS_PIN, DIO_PIN_OUTPUT);
	MDIO_voidSetPinDirection( CLCD_CONTROL_PORT, CLCD_RW_PIN, DIO_PIN_OUTPUT);
	MDIO_voidSetPinDirection( CLCD_CONTROL_PORT, CLCD_EN_PIN, DIO_PIN_OUTPUT);
	
	CLCD_voidSendCommand(CLCD_RETURN_HOME);
	_delay_ms(50);

	CLCD_voidSendCommand(FUNCTION_SET_FOUR_BIT );
	_delay_ms(1);
	CLCD_voidSendCommand(LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF  );
	_delay_ms(1);
	CLCD_voidClearScreen();
	CLCD_voidSendCommand(LCD_ENTRY_MODE_SHIFT_LEFT );
	#endif
	
}
	
 void CLCD_voidSendData( u8 copy_u8Data)
 {
	 #if CLCD_MODE == EIGHT_BIT_MODE
	 MDIO_voidSetPortValue(CLCD_DATA_PORT, copy_u8Data);
	 MDIO_voidSetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,DIO_PIN_HIGH);
	 MDIO_voidSetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,DIO_PIN_LOW);
	 CLCD_voidSendFallingEdge ();
	 #elif CLCD_MODE == FOUR_BIT_MODE
	MDIO_voidSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RS_PIN , DIO_PIN_HIGH );
	MDIO_voidSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RW_PIN , DIO_PIN_LOW  );
	MDIO_voidWriteHighNibbles (CLCD_DATA_PORT ,(copy_u8Data>>FOUR_BIT_MODE));            // send the most 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();
	MDIO_voidWriteHighNibbles (CLCD_DATA_PORT ,copy_u8Data);               // send the least 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();

	#endif

	_delay_ms(1);
	  
	  
 }
	 
void CLCD_voidSendCommand( u8 copy_u8Command)
{
	 #if CLCD_MODE == EIGHT_BIT_MODE
	 MDIO_voidSetPortValue(CLCD_DATA_PORT,copy_u8Command);
	 MDIO_voidSetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,DIO_PIN_LOW);
	 MDIO_voidSetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,DIO_PIN_LOW);
	 CLCD_voidSendFallingEdge ();
	  #elif CLCD_MODE == FOUR_BIT_MODE
	MDIO_voidSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RS_PIN , DIO_PIN_LOW );
	MDIO_voidSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RW_PIN , DIO_PIN_LOW  );
	MDIO_voidWriteHighNibbles (CLCD_DATA_PORT ,(copy_u8Command>>FOUR_BIT_MODE));            // send the most 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();
	MDIO_voidWriteHighNibbles (CLCD_DATA_PORT ,copy_u8Command);               // send the least 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();

	#endif

	_delay_ms(1);
	 
}
void CLCD_voidClearScreen(void)
{
	CLCD_voidSendCommand( LCD_DISPLAY_CLEAR);
	_delay_ms(10);
}
 void CLCD_voidSendString( u8* copy_u8ptrString)
 {
	 u8 LOC_u8Itrator=0;
	 while(copy_u8ptrString[ LOC_u8Itrator] != '/0')
	 {
		CLCD_voidSendData(copy_u8ptrString[ LOC_u8Itrator]);
		 LOC_u8Itrator++;
	 }
 }	 

 void CLCD_voidSetPosition ( u8 copy_u8Row, u8 copy_u8Column)
 {
	 u8 LOC_u8Data;
	 if( (copy_u8Row>2)||(copy_u8Row<1) ||(copy_u8Column>16)||(copy_u8Column<1))
	 {
		 LOC_u8Data=LCD_SET_CURSOR_FIRST_LINE;
	 }
	 else if(copy_u8Row==CLCD_ROW_1)
	 {
		 LOC_u8Data=LCD_SET_CURSOR_FIRST_LINE+(copy_u8Column-1);
	 }
     else if(copy_u8Row==CLCD_ROW_2)
	 {
		 LOC_u8Data=LCD_SET_CURSOR_SECOND_LINE +(copy_u8Column-1);
	 }	
    CLCD_voidSendCommand(LOC_u8Data);
	_delay_ms(1);
 }	




 void CLCD_voidSendFallingEdge (void)
 {
	MDIO_voidSetPinValue(CLCD_CONTROL_PORT, CLCD_EN_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	MDIO_voidSetPinValue(CLCD_CONTROL_PORT, CLCD_EN_PIN, DIO_PIN_LOW);
    _delay_ms(1);
 }
