#ifndef MCAL_DIO_DIO_CFG_H_
#define MCAL_DIO_DIO_CFG_H_

// ---------------------------------------- Options ---------------------------------------- //

// Pin Mode Options
#define DIO_OUTPUT_LOW 0
#define DIO_OUTPUT_HIGH 1
#define DIO_INPUT_FLOATING 2
#define DIO_INPUT_PULLUP 3

// ---------------------------------------- Configurations ---------------------------------------- //

// PORTB Pins
#define DIO_PORTB_PIN0_MODE         DIO_OUTPUT_LOW
#define DIO_PORTB_PIN1_MODE         DIO_OUTPUT_LOW
#define DIO_PORTB_PIN2_MODE         DIO_OUTPUT_LOW
#define DIO_PORTB_PIN3_MODE         DIO_OUTPUT_LOW
#define DIO_PORTB_PIN4_MODE         DIO_OUTPUT_LOW
#define DIO_PORTB_PIN5_MODE         DIO_OUTPUT_LOW
#define DIO_PORTB_PIN6_MODE         DIO_OUTPUT_LOW
#define DIO_PORTB_PIN7_MODE         DIO_OUTPUT_LOW
        
// PORTC Pins       
#define DIO_PORTC_PIN0_MODE         DIO_OUTPUT_LOW
#define DIO_PORTC_PIN1_MODE         DIO_OUTPUT_LOW
#define DIO_PORTC_PIN2_MODE         DIO_OUTPUT_LOW
#define DIO_PORTC_PIN3_MODE         DIO_OUTPUT_LOW
#define DIO_PORTC_PIN4_MODE         DIO_OUTPUT_LOW
#define DIO_PORTC_PIN5_MODE         DIO_OUTPUT_LOW
#define DIO_PORTC_PIN6_MODE         DIO_OUTPUT_LOW
#define DIO_PORTC_PIN7_MODE         DIO_OUTPUT_LOW
        
// PORTD Pins       
#define DIO_PORTD_PIN0_MODE         DIO_INPUT_FLOATING  // Rx
#define DIO_PORTD_PIN1_MODE         DIO_INPUT_FLOATING  // Tx
#define DIO_PORTD_PIN2_MODE         DIO_INPUT_PULLUP    // Mode
#define DIO_PORTD_PIN3_MODE         DIO_INPUT_FLOATING  // Echo
#define DIO_PORTD_PIN4_MODE         DIO_OUTPUT_LOW      // Trigger
#define DIO_PORTD_PIN5_MODE         DIO_OUTPUT_LOW      // OC0B
#define DIO_PORTD_PIN6_MODE         DIO_OUTPUT_LOW      // OC0A
#define DIO_PORTD_PIN7_MODE         DIO_OUTPUT_LOW

#endif
