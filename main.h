/* 
 * File:   main.h
 * Author: magdu
 *
 * Created on 22 November, 2024, 7:05 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"
#include "timers.h"
#include "Micro_wave.h"

#define BUZZER_DDR             TRISC1
#define FAN_DDR                TRISC2


#define BUZZER                 RC1
#define FAN                    RC2
        
        
#define POWER_ON_SCREEN        0x01
#define MENU_SCREEN            0x02
#define MICRO                  0x03
#define GRILL                  0x04
#define CONVECTION             0x05
#define START                  0x06
#define DEFAULT                0x07
#define SET_TIME               0x08
#define MENU_CHANGE            0x09
#define MENU_CHANGE_START      0x10
#define MENU_CHANGE_GRILL      0x11
#define MENU_CHANGE_CONVECTION 0x12
#define SET_TIME_GRILL         0x13


#define GRILL_MODE             0x13

#define CONVECTION_MODE        0x14

#define START_MODE             0x16

#define SET_TIME_CONVECTION    0x15

#endif	/* MAIN_H */

