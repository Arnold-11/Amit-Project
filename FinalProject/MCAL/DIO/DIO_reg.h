#ifndef DIO_REG_H_
#define DIO_REG_H_

#define PINA		*((volatile uint8*)0x39)
#define PORTA		*((volatile uint8*)0x3B)

#define PINB		*((volatile uint8*)0x36)
#define PORTB		*((volatile uint8*)0x38)

#define PINC		*((volatile uint8*)0x33)
#define PORTC		*((volatile uint8*)0x35)

#define PIND		*((volatile uint8*)0x30)
#define PORTD		*((volatile uint8*)0x32)


#endif
