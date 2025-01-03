#include <xc.h>
#include "main.h"

unsigned char half_sec = 0;

void __interrupt() isr(void)
{
    static unsigned int count = 0;
    
    if (TMR2IF == 1)
    {
        if (++count == 625)
        {
            count = 0;
            half_sec++; 
        }
        
        TMR2IF = 0;
    }
}