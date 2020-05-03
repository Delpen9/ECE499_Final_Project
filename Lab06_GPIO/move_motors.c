#include "msp.h"

uint8_t bumpVal;
uint8_t launchIn;

void Motor_InitSimple(void);
void Motor_StopSimple(void);
void Motor_ForwardSimple(uint16_t duty, uint32_t period, uint32_t time);
void Motor_BackwardSimple(uint16_t duty, uint32_t period, uint32_t time);
void Motor_LeftSimple(uint16_t duty, uint32_t period, uint32_t time);
void Motor_RightSimple(uint16_t duty, uint32_t period, uint32_t time);
void Clock_Delay1ms(uint32_t n);
void SysTick_Wait10ms(uint32_t delay);
uint8_t Bump_Read(void);
uint8_t Bump_Read_Right(void);
uint8_t Bump_Read_Left(void);


/*************************************
 *  Launchpad init
 ************************************/
void LaunchPad_Init(void){
  P5->SEL0 &= ~0x13;
  P5->SEL1 &= ~0x13;    // 1) configure P1.4 and P1.1 as GPIO
  P5->DIR &= ~0x12;     // 2) make P1.4 and P1.1 in
  P5->DIR |= 0x01;      //    make P1.0 out
  P5->REN |= 0x12;      // 3) enable pull resistors on P1.4 and P1.1
  P5->OUT |= 0x12;      //    P1.4 and P1.1 are pull-up
  P2->SEL0 &= ~0x07;
  P2->SEL1 &= ~0x07;    // 1) configure P2.2-P2.0 as GPIO
  P2->DIR |= 0x07;      // 2) make P2.2-P2.0 out
  P2->DS |= 0x07;       // 3) activate increased drive strength
  P2->OUT &= ~0x07;     //    all LEDs off
}

void Motor_InitSimple(void){
// Initializes the 6 GPIO lines and puts driver to sleep
// Returns right away
// initialize P1.6 and P1.7 and make them outputs

    P5->SEL0 &= ~0x30; // Set P5.4, and P5.5 as GPIO
    P5->SEL1 &= ~0x30; // DIR
    //P1->DIR &= ~0x12;  // Set P1.1 and P1.4 as input
    P5->DIR |= 0x30;   // Set P5.4 and P5.5 as output
    P5->REN |= 0x30;   // Set resistor

    P2->SEL0 &= ~0xC0; // Set P2.6 and P2.7 as GPIO
    P2->SEL1 &= ~0xC0; // PWM
    P2->DIR |= 0xC0;   // Set P2.6 and P2.7 as output
    P2->REN |= 0xC0;  // Set resistor

    P3->SEL0 &= ~0xC0; // Set P3.6 and P3.7 as GPIO
    P3->SEL1 &= ~0xC0; // SLP
    P3->DIR |= 0xC0;   // Set P3.6 and P3.7 as output
    P3->OUT &= ~0xC0;  // Put drivers to sleep
    P3->REN |= 0xC0;  // Set resistor

}

void Motor_StopSimple(void){
// Stops both motors, puts driver to sleep
// Returns right away
  P5->OUT &= ~0x30;   //0xC0 ===> 0x30
  P2->OUT &= ~0xC0;   // off
  P3->OUT &= ~0xC0;   // low current sleep mode
}

void Motor_ForwardSimple(uint16_t duty, uint32_t period, uint32_t time){
    // Drives just the right motor forward at duty (100 to 9900)
    // Left motor is stopped (sleeping)
    // Runs for time duration (units=10ms), and then stops
    // Stop the motor and return if any bumper switch is active
    // Returns after time*10ms or if a bumper switch is hit
        P5->OUT &= ~0x30; //PH(0 forward)
        P3->OUT |= 0xC0;  //wake right, SLP left
        uint16_t duty1=period-duty;
        do{
            time  -= period;
            P2->OUT |= 0xC0;//EN
            SysTick_Wait10ms(duty);
            /*
            if(Bump_Read() == 1){
                P2->OUT &= ~0xC0;
                Motor_StopSimple();
                return;
            }
            */
            P2->OUT &= ~0xC0;
            SysTick_Wait10ms(duty1);
            /*
            if(Bump_Read() == 1){
                P2->OUT &= ~0xC0;
                Motor_StopSimple();
                return;
            }
            */
        }while( (time > 0) );
        Motor_StopSimple();
        SysTick_Wait10ms(time);
}

void Motor_BackwardSimple(uint16_t duty, uint32_t period, uint32_t time){
    // Drives just the right motor forward at duty (100 to 9900)
    // Left motor is stopped (sleeping)
    // Runs for time duration (units=10ms), and then stops
    // Stop the motor and return if any bumper switch is active
    // Returns after time*10ms or if a bumper switch is hit
        P5->OUT |= 0x30; //PH(0 forward)
        P3->OUT |= 0xC0;  //wake right, SLP left
        uint16_t duty1=period-duty;
        do{
            time  -= period;
            P2->OUT |= 0xC0;//EN
            SysTick_Wait10ms(duty);
            /*
            if(Bump_Read() == 1){
                P2->OUT &= ~0xC0;
                Motor_StopSimple();
                return;
            }
            */
            P2->OUT &= ~0xC0;
            SysTick_Wait10ms(duty1);
            /*
            if(Bump_Read() == 1){
                P2->OUT &= ~0xC0;
                Motor_StopSimple();
                return;
            }
            */
        }while( (time > 0) );
        Motor_StopSimple();
        SysTick_Wait10ms(time);
}

void Motor_LeftSimple(uint16_t duty, uint32_t period, uint32_t time){
    // Drives just the right motor forward at duty (100 to 9900)
    // Left motor is stopped (sleeping)
    // Runs for time duration (units=10ms), and then stops
    // Stop the motor and return if any bumper switch is active
    // Returns after time*10ms or if a bumper switch is hit
        P5->OUT &= ~0x80; //PH(0 forward)
        P3->OUT |= 0x80;  //wake right, SLP left
        uint16_t duty1=period-duty;
        do{
            time  -= period;
            P2->OUT |= 0x80;//EN
            SysTick_Wait10ms(duty);
            /*
            if(Bump_Read() == 1){
                P2->OUT &= ~0x80;
                Motor_StopSimple();
                return;
            }
            */
            P2->OUT &= ~0x80;
            SysTick_Wait10ms(duty1);
            /*
            if(Bump_Read() == 1){
                P2->OUT &= ~0x80;
                Motor_StopSimple();
                return;
            }
            */
        }while( (time > 0) );
        Motor_StopSimple();
        SysTick_Wait10ms(time);
}

void Motor_RightSimple(uint16_t duty, uint32_t period, uint32_t time){
// Drives just the right motor forward at duty (100 to 9900)
// Left motor is stopped (sleeping)
// Runs for time duration (units=10ms), and then stops
// Stop the motor and return if any bumper switch is active
// Returns after time*10ms or if a bumper switch is hit
    P5->OUT &= ~0x40; //PH(0 forward)
    P3->OUT |= 0x40;  //wake right, SLP left
    uint16_t duty1=period-duty;
    do{
        time  -= period;
        P2->OUT |= 0x40;//EN
        SysTick_Wait10ms(duty);
        /*
        if(Bump_Read() == 1){
            P2->OUT &= ~0x40;
            Motor_StopSimple();
            return;
        }
        */
        P2->OUT &= ~0x40;
        SysTick_Wait10ms(duty1);
        /*
        if(Bump_Read() == 1){
            P2->OUT &= ~0x40;
            Motor_StopSimple();
            return;
        }
        */
    }while( (time > 0) );
    Motor_StopSimple();
    SysTick_Wait10ms(time);
}



//------------LaunchPad_Input------------
// Input from Switches
// Input: none
// Output: 0x00 none
//         0x01 Button1
//         0x02 Button2
//         0x03 both Button1 and Button2
uint8_t LaunchPad_Input(void){
  //return ((((~(P1->IN))&0x10)>>3)|(((~(P1->IN))&0x02)>>1));   // read P1.4,P1.1
  Clock_Delay1ms(50);
  return (P5->IN | 0xED);
}

//------------LaunchPad_Output------------
// Output to LaunchPad LEDs
// Input: 0 off, bit0=red,bit1=green,bit2=blue
// Output: none
void LaunchPad_Output(uint8_t data){  // write three outputs bits of P2
  P2->OUT = (P2->OUT&0xF8)|data;
}

// Driver test
void Pause(void){
  while(LaunchPad_Input()==0);  // wait for touch
  while(LaunchPad_Input());     // wait for release
}

//--------------------------
// Initialize Bump sensors
// Make six Port 4 pins inputs
// Activate interface pullup
// pins 7,6,5,3,2,0
void Bump_Init(void){
    P4->SEL0 &= ~0xED;  // Configure P4.0, P4.2, P4.3, P4.5, P4.6, and P4.7 as GPIO
    P4->SEL1 &= ~0xED;
    P4->DIR &= ~0xED;   // Input
    P4->REN |= 0xED;    // Internal resistor
}

// Read current state of 6 switches
// Returns a 6-bit positive logic result (0 to 63)
// bit 7 Bump5
// bit 6 Bump4
// bit 5 Bump3
// bit 3 Bump2
// bit 2 Bump1
// bit 0 Bump0
uint8_t Bump_Read(void){
    uint8_t value = P4->IN|0x12;
    printf("Value is: %d\n", value);
    if (value == 127 || value == 126){
        return 0;
    }
    return 1;
}

uint8_t Bump_Read_Right(void){ /*Works*/
    uint8_t value = P4->IN|0xF2;
    if (value == 255){
        return 0;
    }
    return 1;
}

uint8_t Bump_Read_Left(void){
    uint8_t value = P4->IN|0x1F;
    if (value == 127){
        return 0;
    }
    return 1;
}

/***************************
 * main.c
 ***************************/


/****************************************
 *  SysTick Timer Init
 ***************************************/
void SysTick_Init(void){
  SysTick->LOAD = 0x00FFFFFF;           // maximum reload value
  SysTick->CTRL = 0x00000005;           // enable SysTick with no interrupts
}

void SysTick_Wait(uint32_t delay){
  SysTick->LOAD = (delay - 1);// count down to zero
  SysTick->VAL = 0;          // any write to CVR clears it and COUNTFLAG in CSR
  while(( SysTick->CTRL&0x00010000) == 0){};

}
// Time delay using busy wait.
// assumes 48 MHz bus clock
void SysTick_Wait10ms(uint32_t delay){
  uint32_t i;
  for(i=0; i<delay; i++){
    SysTick_Wait(480000);  // wait 10ms (assumes 48 MHz clock)
  }
}
