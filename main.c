/*
 * File:   main.c
 * Author: magdu
 *
 * Created on 22 November, 2024, 7:05 AM
 */



#include "main.h"
#pragma config WDTE = OFF

extern unsigned char half_sec;
extern  unsigned char res;



static void init_config(void) 
{
     //Buzzer and Fan initializations
    BUZZER_DDR = 0;
    FAN_DDR = 0;
    BUZZER = 0;
    FAN = 0;
    
    //clcd_initializations
     init_clcd();
     
     //matrix_keypad_initializations
     init_matrix_keypad();
     
     //timer2_initializations
     init_timer2();
     
     
     GIE = 1;//Global Interrupt bit enable
     PEIE = 1; //Peripheral Interrupt bit enable
     

}

void main(void) 
{
    unsigned char control_flag = POWER_ON_SCREEN;
    unsigned char key;
    static unsigned char display = 0;
    init_config();
    while (1) 
    {
        key = read_matrix_keypad(STATE);
        
        if(key == 1 && control_flag != GRILL && control_flag !=  CONVECTION && control_flag != START)
        {
            clcd_clear();
            control_flag = MICRO;
        }
        if(key == 2 && control_flag != MICRO && control_flag != CONVECTION && control_flag != START)
        {
            clcd_clear();
            control_flag = GRILL;
        }
        if(key == 3 && control_flag != MICRO && control_flag != GRILL && control_flag != START)
        {
            clcd_clear();
            control_flag = CONVECTION;
        }
        if(key == 4 && control_flag != MICRO && control_flag != CONVECTION && control_flag != GRILL)
        {
            clcd_clear();
            control_flag = START;
        }
        switch(control_flag)
        {
            case POWER_ON_SCREEN:
            {
                for(int i = 0; i < 16; i++)
                {
                    clcd_putch(0xFF, LINE1(i));
                    __delay_ms(100);
                }
                clcd_print("POWER ON", LINE2(0));
                clcd_print("MICROWAVE OVEN", LINE3(0));
                for(int i = 0; i < 16; i++)
                {
                    clcd_putch(0xFF, LINE4(i));
                    __delay_ms(100);
                }
                __delay_ms(5000);
                clcd_clear();
                control_flag = MENU_SCREEN;
            }
            break;
            
            case MENU_SCREEN:
            {
                
                if (display == 0) 
                {
                    clcd_print("1.Micro", LINE1(0));
                    clcd_print("2.Grill", LINE2(0));
                    clcd_print("3.Convection", LINE3(0));
                    clcd_print("4.Start", LINE4(0));
                    display = 1;
  
                }
                
            }
            break;
            
            case MICRO:
            {
                res = micro(key);
                if(res == MENU_CHANGE)
                {
                    clcd_clear();
                    control_flag = MENU_SCREEN;
                    display = 0;
                    res = 0;
                }
            }
            break;
            
            case GRILL:
            {
                res = grill(key);
                if(res == MENU_CHANGE_GRILL)
                {
                    clcd_clear();
                    control_flag = MENU_SCREEN;
                    display = 0;
                    res = 0;
   
                }
            }
            break;
            
            case CONVECTION:
            {
                res = convection(key);
                if(res == MENU_CHANGE_CONVECTION)
                {
                    clcd_clear();
                    control_flag = MENU_SCREEN;
                    display = 0;
                    res = 0;
                }
            }
            break;
            
            case START:
            {
          
                res = start(key);
                if(res == MENU_CHANGE_START)
                {
                    clcd_clear();
                    control_flag = MENU_SCREEN;
                    display = 0;
                    res = 0;
   
                }
            }
            break;
        }
        
        
    }
    return;
}


