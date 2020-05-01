#include "msp.h"


/**
 * main.c
 */
void main(void)
{
    Clock_Init48MHz();
     LaunchPad_Init();   // built-in switches and LEDs
     Bump_Init();        // bump switches
     Motor_InitSimple(); // initialization
     SysTick_Init();
     uint8_t isForward = 0;

     Motor_ForwardSimple(1000,1500);
//     Motor_LeftSimple(100,400);
//     Motor_RightSimple(100,400);
//     Motor_BackwardSimple(100,400);
//     while(1){
//         if(LaunchPad_Input()==0xED && isForward == 0){
//             Motor_ForwardSimple(5000,350);
//             P2->OUT |= 0x01;
//             isForward = 1;
//         }
//         else if (LaunchPad_Input()==0xEF){
//             Motor_LeftSimple(3000,200);
//             P2->OUT |= 0x03; //right switch, left motor, Turn right
//         }
//         else if(LaunchPad_Input()==0xFD){
//             Motor_RightSimple(3000,200);// left switch, right motor, turn left
//             P2->OUT &= ~0x07;
//         }
//         else if(LaunchPad_Input()==0xED && isForward == 1){
//             Motor_BackwardSimple(3000,200);
//             P2->OUT |= 0x02;
//             isForward = 0;
//         }
//     }
}
