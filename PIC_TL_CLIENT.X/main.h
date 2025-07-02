#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

void write(char *stock,char *id);
int data_setup(char flag,signed char *data);
#define LEVEL					     	0
#define STATE_CHANGE			       	1

#define KEY_PORT					PORTC

#define SWITCH1					0x0E
#define SWITCH2					0x0D
#define SWITCH3					0x0B
#define SWITCH4					0x07
#define ALL_RELEASED					0x0F

#define INPUT_PINS					0x0F

void init_digital_keypad(void);
unsigned char read_digital_keypad(unsigned char detection_type);

void __interrupt()isr(void);
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

