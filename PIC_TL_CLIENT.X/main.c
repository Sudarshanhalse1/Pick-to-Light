
#include <xc.h>
#include"can.h"
#include"main.h"
#include"eeprom.h"
#include"ssd_display.h"
#include <stdint.h>
//#include"digital_keypad.h"

extern unsigned char can_payload[13];
void init_config()
{
    PEIE=1;
    GIE=1;
    INT0IE=1;
    INT0=1;
    INT0IF=0;
    TRISB7=0;
    TRISB6=0;
            RB6=0;
    RB7=0;
    init_digital_keypad();
    TRISC|=0x0F;
    init_ssd_control();
    init_can();
}
                         // 0      1    2    3     4      5     6     7     8     9     10            11       12        13        14          15        16    
unsigned char display[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, UNDERSCORE, LETTER_U, LETTER_t, LETTER_P, LETTER_d, LETTER_I, BLANK};
char operation_mode=0;
char check_flag=1;
void main(void) {
    init_config();
    char mode_flag=1;          
    char ssd[4];
    unsigned char key;
    char select_mode=0;
    char change_flag=0;
   // char check_flag=1;
    char stock[4]={0};
    char id[4]={0};
    while(1)
    {
        key=read_digital_keypad(STATE_CHANGE);
        
        if(operation_mode)
        {
            if(key==SWITCH4)
            {
              operation_mode=0;
              check_flag=0;
            }
            if(key==SWITCH3)
            {
               // RB6=1;
                mode_flag=!mode_flag;
            }
            else if(key==SWITCH2)
            {
                select_mode=!select_mode;
                
            }
            
            if(mode_flag)
            {
                if(select_mode==0)
                {
                ssd[0]=display[11];
                ssd[1]=display[10];
                ssd[2]=display[6];
                ssd[3]=display[12];
                }
                else
                {
                    data_setup(change_flag,stock);
                    select_mode=0;
                }
            }
            else
            {
                if(select_mode==0)
                {
                ssd[0]=display[13];
                ssd[1]=display[10];
                ssd[2]=display[15];
                ssd[3]=display[14];
                }
                else
                {
                    data_setup(change_flag,id);
                    select_mode=0;
                }
            }
            display_ssd(ssd);
        }
        else
        {
            PORTD=0x00;
            PORTA=0x00;
            if(check_flag==0)
            {
              write(stock,id);
              can_transmit(id,stock);
              change_flag=1;
              check_flag=1;
            }
            //while(!can_receive() && operation_mode==0);
            if(can_receive())
            {
              int i;
              RB6=RB7=0;
              for(i=0;i<4;i++)
            {
                if(read_internal_eeprom(i)!=can_payload[i+5])
                {
                    RB6=1;
                    can_transmit(id,stock);
                    break;
                }
            }
            if(i==4)
            {
                for(int j=0;j<4;j++)
                {
                    stock[j]=can_payload[j+9];
                }
                operation_mode=1;
                check_flag=0;
                key=0;
                select_mode=0;
            }
            }
            
            
            
        }
    }
    return;
}
void write(char *stock,char *id)
{
    for(int i=0;i<8;i++)
    {
        if(i<4)
        {
            write_internal_eeprom(i,id[i]);
        }
        else
        {
            write_internal_eeprom(i,stock[i-4]);
        }
    }
}

int data_setup(char flag,signed char *data)
{
    char key;
    char field_flag=0;
    char ssd[4];
    while(1)
    {
        key=read_digital_keypad(STATE_CHANGE);
        if(key==SWITCH3)
        {
            break;
        }
        else if(key==SWITCH4)
        {
            operation_mode=0;
            check_flag=0;
            RB6=RB7=1;
            break;
        }
        if(flag)
        {
          if(key==SWITCH1)
          {
              data[3]++;
              if(data[3]>9)
              {
                  data[3]=0;
                  data[2]++;
                  if(data[2]>9)
                  {
                      data[2]=0;
                      data[1]++;
                      if(data[1]>9)
                      {
                          data[1]=0;
                          data[0]++;
                          if(data[0]>9)
                              data[0]=0;
                      }
                  }
              }
          }
          else if(key==SWITCH2)
          {
              data[3]--;
              if(data[3]<0)
              {
                  data[3]=9;
                  data[2]--;
                  if(data[2]<0)
                  {
                      data[2]=9;
                      data[1]--;
                      if(data[1]<0)
                      {
                          data[1]=9;
                          data[0]--;
                          if(data[0]<0)
                              data[0]=9;
                      }
                  }
              }
          }
          ssd[0]=display[data[0]];
            ssd[1]=display[data[1]];
            ssd[2]=display[data[2]];
            ssd[3]=display[data[3]];
        }
        else
        {
            if(key==SWITCH1)
            {
                data[field_flag]++;
                if(data[field_flag]>9)
                {
                    data[field_flag]=0;
                }
            }
            else if(key==SWITCH2)
            {
                field_flag++;
                if(field_flag==4)
                {
                    field_flag=0;
                }
            }
            ssd[0]=display[data[0]];
            ssd[1]=display[data[1]];
            ssd[2]=display[data[2]];
            ssd[3]=display[data[3]];
            ssd[field_flag]|=0x10;
                
        }
        display_ssd(ssd);
        
        
    }
    
}
