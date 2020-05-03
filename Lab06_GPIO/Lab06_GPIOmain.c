/* This example accompanies the book
   "Embedded Systems: Introduction to Robotics,
   Jonathan W. Valvano, ISBN: 9781074544300, copyright (c) 2019
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2019, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/

#include <stdint.h>
#include "msp.h"
#include "..\inc\Reflectance.h"
#include "..\inc\Clock.h"
#include "..\inc\TExaS.h"

/*
int main(void){
    Clock_Init48MHz();
    Reflectance_Init();
    TExaS_Init(LOGICANALYZER_P7);
    Clock_Init48MHz();
    LaunchPad_Init();   // built-in switches and LEDs
    Bump_Init();        // bump switches
    Motor_InitSimple(); // initialization
    SysTick_Init();

    uint8_t scale = 1;
    uint8_t duty = 1*scale;
    uint8_t period = 10000*scale;
    uint8_t time = 10000*scale;

    while(1){
        Data = Reflectance_Read(1000);
        Position = Reflectance_Position(Data);
        if(Position>30 && Position<300){
            Motor_LeftSimple(duty, period, time);
            Clock_Delay1ms(100);
        }else if (Position<-30){
            Motor_RightSimple(duty, period, time);
            Clock_Delay1ms(100);
        }else if (Position<30 && Position>-30){
            Motor_ForwardSimple(duty, period, time);
            Clock_Delay1ms(100);
        }
        else{
            Motor_StopSimple();
            Clock_Delay1ms(100);
        }
    }
}
*/

int main(void){
    Clock_Init48MHz();
    Reflectance_Init();
    TExaS_Init(LOGICANALYZER_P7);
    Clock_Init48MHz();
    LaunchPad_Init();   // built-in switches and LEDs
    Bump_Init();        // bump switches
    Motor_InitSimple(); // initialization
    SysTick_Init();

    uint8_t scale = 5;
    uint8_t duty = 5*scale;
    uint8_t period = 10*scale;
    uint8_t time = 10*scale;

    while(1){
        Motor_ForwardSimple(duty, period, time);
        Clock_Delay1ms(1);
        /*
        Motor_ForwardSimple(duty, period, time);
        Clock_Delay1ms(10);
        if(Bump_Read_Left() == 1 && Bump_Read_Right() == 0){
            Motor_StopSimple(duty, period, time);
            Clock_Delay1ms(10);
            Motor_BackwardSimple(duty, period, time);
            Clock_Delay1ms(10);
            Motor_LeftSimple(duty, period, time);
            Clock_Delay1ms(10);
        }
        if(Bump_Read_Right() == 1 && Bump_Read_Left() == 0){
            Motor_StopSimple(duty, period, time);
            Clock_Delay1ms(10);
            Motor_BackwardSimple(duty, period, time);
            Clock_Delay1ms(10);
            Motor_RightSimple(duty, period, time);
            Clock_Delay1ms(10);
        }
         */
        if (Bump_Read() == 1){
            /*
            Motor_StopSimple(duty, period, time);
            Clock_Delay1ms(1000);
            */
            Motor_BackwardSimple(duty, period, time);
            Clock_Delay1ms(1000);
            Motor_RightSimple(duty, period, time);
            Clock_Delay1ms(1000);
        }
    }
}
