#include <xc.h>
#include "uart.h"
#include "can.h"
#include "clcd.h"
extern unsigned char can_payload[13];
void init_config()
{
    init_can();
     init_uart();
    init_clcd();
}
void main(void) {
    init_config();
    char stock[4]={0};
    char id[4]={0};
    clcd_print("SERVER  ",LINE1(0));
    while(1)
    {
        if(can_receive())
        {
            clcd_print("Received",LINE2(0));
            puts("\n\r P_ID : ");
            for(int i=0;i<4;i++)
            {
                putch(can_payload[i+5]+'0');
            }
            puts("\n\r STOCK : ");
            for(int i=0;i<4;i++)
            {
                putch(can_payload[i+9]+'0');
            }
            puts("\n\r Enter The Details:\n\rP_ID : ");
            for(int i=0;i<4;i++)
            {
                id[i]=getche()-'0';
            }
            puts("\n\r STOCK : ");
            for(int i=0;i<4;i++)
            {
                stock[i]=getche()-'0';
            }
            can_transmit(id,stock);
            
        }
    }
    return;
}
