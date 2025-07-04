#ifndef SSD_DISPLAY_H  
#define SSD_DISPLAY_H  

#define MAX_SSD_CNT			4

#define HIGH				1
#define LOW				0
#define MAX_SSD_CNT			4



#define SSD_DATA_PORT			PORTD
#define SSD_CNT_PORT			PORTA

/* This values are for common cathode display */
#define ZERO				0xE7
#define ONE                	0x21
#define TWO         		0xCB
#define THREE				0x6B
#define FOUR				0x2D
#define FIVE				0x6E
#define SIX             	0xEE
#define SEVEN				0x23
#define EIGHT				0xEF
#define NINE				0x6F
#define DOT                 0x10
#define BLANK				0x00
#define UNDERSCORE          0x40
#define LETTER_U            0xE5
#define LETTER_t            0xCC
#define LETTER_P            0x8F
#define LETTER_d            0xE9
#define LETTER_I            0x84
/* Need to fill All others */
#define M_ONE				0x9D
#define MINUS				0xFD

void init_ssd_control(void);
void display_ssd(unsigned char data[]);

#endif