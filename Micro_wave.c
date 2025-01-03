#include "main.h"

extern unsigned char half_sec;

unsigned char res = 0;

int micro(unsigned char key)
{
    
    static unsigned char mode = DEFAULT;
    
    if(mode == DEFAULT)
    {
        clcd_clear();
        clcd_print("POWER = 900W", LINE2(2));
        __delay_ms(500);
        clcd_clear();
        mode = SET_TIME;
        
    }
    if(mode == SET_TIME)
    {
        res = set_time(key, MICRO);
        if(res == MENU_CHANGE)
        {
            mode = DEFAULT;
             
        }  
        return res;  
    }
    
    
    
}

int grill(unsigned char key) 
{
    static unsigned char mode = GRILL_MODE;
    if (mode == GRILL_MODE) 
    {
        mode = SET_TIME_GRILL;
    }
    if(mode == SET_TIME_GRILL)
    {
        res = set_time(key, GRILL);
        if(res == MENU_CHANGE_GRILL)
        {
            mode = GRILL_MODE;
        }
        return res;
        
    }
    
    
    

}

int convection(unsigned char key)
{
    static unsigned char mode = CONVECTION_MODE;
    static unsigned int edit = 0;
    static unsigned char temp[3] = {'0', '0', '0'};
    static unsigned int sec = 180;
    static unsigned int flag = 0;
    static unsigned int delay_1 = 0;
    static unsigned int delay_2 = 0;
    static unsigned int delay_3 = 0;
    static unsigned char once = 0;
    
    if(key == 2)
    {
        if(++edit > 2)
        {
            edit = 0;
        }
    }
    
    if(key == 1)
    {
        if(edit == 0)
        {
            if(++temp[2] < 9)
            {
                temp[2] = '0';
            }
        }
        if(edit == 1)
        {
            if(++temp[1] < 9)
            {
                temp[1] = '0';
            }
        }
        if(edit == 2)
        {
            if(++temp[0] < 9)
            {
                temp[0] = '0';
            }
        }
    }
    if(mode == CONVECTION_MODE)
    {
        if (flag == 0) 
        {
            clcd_print("SET_TEMP", LINE1(0));
            clcd_print("(", LINE1(10));
            clcd_putch(0xDF, LINE1(11));
            clcd_putch(0x43, LINE1(12));
            clcd_print(")", LINE1(13));
            clcd_print("TEMP: ", LINE2(0));
            clcd_print(temp, LINE2(6));
            if (edit == 0) 
            {
                if (delay_1 == 2) 
                {
                    clcd_putch(temp[2], LINE2(8));
                }
                if (delay_1 == 5) 
                {
                    delay_1 = 0;
                    clcd_putch(' ', LINE2(8));
                }
                delay_1++;
            }
            if (edit == 1) 
            {
                if (delay_2 == 2) 
                {
                    clcd_putch(temp[1], LINE2(7));
                }
                if (delay_2 == 5) 
                {
                    delay_2 = 0;
                    clcd_putch(' ', LINE2(7));
                }
                delay_2++;
            }
            if (edit == 2) 
            {
                if (delay_3 == 2) 
                {
                    clcd_putch(temp[0], LINE2(6));
                }
                if (delay_3 == 5) 
                {
                    delay_3 = 0;
                    clcd_putch(' ', LINE2(6));
                }
                delay_3++;
            }
            clcd_print("*:CLEAR  #:ENTER", LINE4(0));

            if (key == '*') 
            {
                for (int i = 0; i < 3; i++) 
                {
                    temp[i] = '0';
                }
            }

            if (key == '#') 
            {
                if (!once) 
                {
                    flag = 1;
                    clcd_clear();
                    TMR2ON = 0; // Stop Timer 2
                    half_sec = 0;
                    TMR2ON = 1; // Start Timer 2
                    once = 1;
                } 
                else if (once == 1) 
                {
                    flag = 1;
                    clcd_clear();
                    TMR2ON = 0; // Stop Timer 2
                    half_sec = 0;
                    TMR2ON = 1; // Start Timer 2
                    once = 1;
                }
            }
        }
        
        
        if(flag == 1)
        {
            if (half_sec == 2) 
            {
                FAN = 1;
                half_sec = 0;

                // Decrement the seconds or minutes as needed
                if (sec > 0) 
                {
                    sec--;
                } 
                if (sec == 0) 
                {
                    mode = SET_TIME_CONVECTION;
                    TMR2ON = 0;
                    FAN = 0;
                    flag = 2;
                }

            }
            clcd_print("PRE_HEATING", LINE1(0));
            clcd_print("TIME_LEFT: ", LINE2(0));
            clcd_putch((sec / 100) + '0', LINE2(12)); // Hundreds place
            clcd_putch((sec / 10) % 10 + '0', LINE2(13)); // Tens place
            clcd_putch((sec % 10) + '0', LINE2(14)); // Ones place
            clcd_putch('s', LINE2(15));
        }
    }
    
    if (flag == 2) 
    {
        res = set_time(key, CONVECTION);
        if(res == MENU_CHANGE_CONVECTION)
        {
            flag = 0;  
        }
        return res;
    }
}

int set_time(unsigned char key, unsigned char org_mode) 
{
    static unsigned char first_key1_press = 1;
    static unsigned char first_key2_press = 1;
    static unsigned int sec = 0;
    static unsigned int min = 0;
    static unsigned char mode = 1;
    static unsigned int delay_1 = 0;
    static unsigned int delay_2 = 0;
    static unsigned char flag = 0;
    static unsigned char pause_start = 0;
    static unsigned char once = 0;

    // Toggle between modes on key 2
    if (key == 2) 
    {
        if(first_key2_press)
        {
            first_key2_press = 0;
        }
        else
        {
             mode = !mode;
        }
       
    }

    // Start the timer on key '#'
    if (key == '#') 
    {
        if (!once) 
        {
            flag = 1;
            clcd_clear();
            TMR2ON = 0; // Stop Timer 2
            half_sec = 0;
            TMR2ON = 1; // Start Timer 2
            once = 1;
        }
        else if (once == 1) 
        {
            flag = 1;
            clcd_clear();
            TMR2ON = 0; // Stop Timer 2
            half_sec = 0;
            TMR2ON = 1; // Start Timer 2
            once = 1;
        }
    }

    // Increment sec or min depending on the mode
    if (key == 1) 
    {
        if(first_key1_press)
        {
            first_key1_press = 0;
        }
        else 
        {
            if (mode) 
            {
                if (++sec >= 60) 
                {
                    sec = 0;
                }
            }
            else 
            {
                if (++min >= 60) 
                {
                    min = 0;
                }
            }
        }
        
    }

    // Reset sec or min when '*' is pressed
    if (key == '*') 
    {
        if (mode) 
        {
            sec = 0;
        } 
        else 
        {
            min = 0;
        }
    }

    // Handle other actions when flag is set (i.e., when the timer is running)
    if (flag) 
    {
        // Menu navigation or actions on key press
        if (key == 6) 
        {
            if(org_mode == MICRO)
            {
                return MENU_CHANGE;
            }
            else if(org_mode == GRILL)
            {
                return MENU_CHANGE_GRILL;
            }
            else if(org_mode == CONVECTION)
            {
                return MENU_CHANGE_CONVECTION;
            }
            
        }

        // Pause the timer
        if (key == 5) 
        {
            pause_start = 1;
            FAN = 0;
            TMR2ON = 0;
        }

        // Add 30 seconds or resume
        if (key == 4)
        {
            if (!pause_start) 
            {
                // Add 30 seconds to the timer
                sec += 30;
                if (sec >= 60) 
                {
                    sec -= 60;
                    min++;
                }

                // Resume countdown
                pause_start = 0; 
                TMR2ON = 1;
            } 
            else 
            {
                // Resume countdown if paused
                pause_start = 0;
                TMR2ON = 1;
            }
            FAN = 1;
        }

        // Decrement the timer
        if (!pause_start) 
        {
            if (half_sec == 2) 
            {
                FAN = 1;
                half_sec = 0;

                // Decrement sec and min
                if (sec > 0) 
                {
                    sec--;
                } 
                else if (min > 0) 
                {
                    sec = 59;
                    min--;
                }

                // Handle timer expiry
                if (min == 0 && sec == 0) 
                {
                    clcd_clear();
                    clcd_print("TIME_UP", LINE2(4));
                    clcd_print("ENJOY YOUR MEAL", LINE3(1));
                    FAN = 0;
                    BUZZER = 1;
                    __delay_ms(5000);
                    BUZZER = 0;
                    flag = 0;
                    if (org_mode == MICRO) 
                    {
                        return MENU_CHANGE;
                    } 
                    else if (org_mode == GRILL) 
                    {
                        return MENU_CHANGE_GRILL;
                    } 
                    else if (org_mode == CONVECTION) 
                    {
                        return MENU_CHANGE_CONVECTION;
                    }
                }
            }
        }

        // Update display
        clcd_print("TIME:", LINE1(0));
        clcd_putch((min / 10) + '0', LINE1(6));
        clcd_putch((min % 10) + '0', LINE1(7));
        clcd_putch(':', LINE1(8));
        clcd_putch((sec / 10) + '0', LINE1(9));
        clcd_putch((sec % 10) + '0', LINE1(10));
        clcd_print("4.START/RESUME", LINE2(0));
        clcd_print("5.PAUSE", LINE3(0));
        clcd_print("6.STOP", LINE4(0));

        // Small delay to avoid constant refresh
        __delay_ms(100);
    }

    // When flag is not set (timer is stopped), allow for time setting
    if (!flag) 
    {
        clcd_print("SET_TIME <MM:SS>", LINE1(0));
        clcd_print("TIME:", LINE2(0));
        clcd_putch(' ', LINE2(5));
        clcd_putch((min / 10) + '0', LINE2(6));
        clcd_putch((min % 10) + '0', LINE2(7));
        clcd_putch(':', LINE2(8));
        clcd_putch((sec / 10) + '0', LINE2(9));
        clcd_putch((sec % 10) + '0', LINE2(10));
        clcd_print("     ", LINE2(11));
        if (mode) 
        {
            if (delay_1 == 2) 
            {
                clcd_putch((sec / 10) + '0', LINE2(9));
                clcd_putch((sec % 10) + '0', LINE2(10));
            }
            if (delay_1 == 5) 
            {
                delay_1 = 0;
                clcd_putch(' ', LINE2(9));
                clcd_putch(' ', LINE2(10));
            }
            delay_1++;
        }
        if (!mode) 
        {
            if (delay_2 == 2) 
            {
                clcd_putch((min / 10) + '0', LINE2(6));
                clcd_putch((min % 10) + '0', LINE2(7));
            }
            if (delay_2 == 5) 
            {
                delay_2 = 0;
                clcd_putch(' ', LINE2(6));
                clcd_putch(' ', LINE2(7));
            }
            delay_2++;
        }
        clcd_print("*:CLEAR  #:ENTER", LINE4(0));
    }
}


int start(unsigned char key)
{
    static unsigned char mode = START_MODE;
    static unsigned int sec = 30;
    static unsigned int min = 0;
    static unsigned char pause_start = 0;
    static unsigned char first_key_4_press = 1;
    if (mode == START_MODE) 
    {
        if (key == 6) 
        {
            return MENU_CHANGE_START;
        }
        if (key == 5) 
        {
            pause_start = 1;
            FAN = 0;
            TMR2ON = 0;
        }
        if (key == 4) 
        {
            if (first_key_4_press)
            {
                TMR2ON = 1;
                half_sec = 0;
                first_key_4_press = 0;
            }
            else 
            {
                if (!pause_start) 
                {
                    // Add 30 seconds
                    sec += 30;
                    if (sec >= 60) 
                    {
                        sec -= 60; // Wrap seconds
                        min++; // Increment minutes
                    }

                    // Resume countdown
                    pause_start = 0; // Ensure not paused
                    TMR2ON = 1;
                } 
                else if (pause_start) 
                {
                    // Resume countdown if paused
                    pause_start = 0;
                    TMR2ON = 1;
                }
            }

            FAN = 1;

        }

        if (!pause_start) 
        {
            if (half_sec == 2) 
            {
                FAN = 1;
                half_sec = 0;

                // Decrement the seconds or minutes as needed
                if (sec > 0) 
                {
                    sec--;
                }
                else if (min > 0) 
                {
                    sec = 59; // Reset seconds to 59
                    min--; // Decrement minutes
                }
                if (min == 0 && sec == 0) 
                {
                    // Display "TIME_UP" message and stop the timer
                    clcd_clear(); // Only clear screen for "TIME_UP" message
                    clcd_print("TIME_UP", LINE2(4));
                    clcd_print("ENJOY YOUR MEAL", LINE3(1));
                    FAN = 0;
                    BUZZER = 1;
                    __delay_ms(5000);
                    TMR2ON = 0;
                    BUZZER = 0;
                    return MENU_CHANGE_START;
                }

            }
            // Only update display after time change
            clcd_print("TIME:", LINE1(0));
            clcd_putch((min / 10) + '0', LINE1(6));
            clcd_putch((min % 10) + '0', LINE1(7));
            clcd_putch(':', LINE1(8));
            clcd_putch((sec / 10) + '0', LINE1(9));
            clcd_putch((sec % 10) + '0', LINE1(10));
            // Update menu options
            clcd_print("4.START/RESUME", LINE2(0));
            clcd_print("5.PAUSE", LINE3(0));
            clcd_print("6.STOP", LINE4(0));



            // Small delay after each loop iteration to avoid constant refresh
            __delay_ms(100);
        }
}
}
    
            
   
void clcd_clear()
{
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_us(500);
}
