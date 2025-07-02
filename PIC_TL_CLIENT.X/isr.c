
#include <xc.h>
#include "main.h"
extern char operation_mode;
void __interrupt()isr(void)
{
    if(INT0IF)
    {
        operation_mode=1;
        INT0IF=0;
    }
}