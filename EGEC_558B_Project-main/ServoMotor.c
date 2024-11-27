#include <stdint.h>
#include <stdio.h>
#include "ServoMotor.h"
#include "inc/tm4c123gh6pm.h"


void Servo_Motor_Init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x04;    //Enable Port C
    GPIO_PORTC_DIR_R |= 0x10;    //Set PC4 as output
    GPIO_PORTC_DEN_R |= 0x10;    //Enable Digital for PC4

    //PWM Init
    GPIO_PORTC_AFSEL_R |= 0x10;
    GPIO_PORTC_PCTL_R |= 0x00040000;

    //Disable PWM Generator 3
    PWM0_ENABLE_R &= ~0x40;
    PWM0_CTL_R &= ~0x08;

    //Down Count
    PWM0_3_CTL_R &= ~0x03;
    PWM0_3_GENA_R = 0x8C;
    PWM0_3_GENB_R = 0;

    //Set PWM load Register for 20ms Period
    PWM0_3_LOAD_R = 5000 - 1;

    //Set Default Comparator Value for the middle position
    PWM0_3_CMPA_R = (5000 - 350) - 1;
    PWM0_CTL_R |= 0x08;
    PWM0_3_CTL_R |= 0x01;

    //Enable M0PWMB output
    PWM0_ENABLE_R |= 0x40;
}


void leftPosition(void)
{
    PWM0_3_CMPA_R = (5000 - 552) - 1;
    // Theoretical Value for other Servo
    //PWM0_3_CMPA_R = (5000-434) - 1;

    /*int i = 0;
    for(i = 0; i < 100; i++)
    {
    GPIO_PORTC_DATA_R |= 0x10;
    Timer1_Delay_MicroSecond(1735);
    GPIO_PORTC_DATA_R &= ~0x10;
    Timer1_Delay_MicroSecond(18265); //Finish Period of 20ms
    }*/
}


void middlePosition(void)
{
    PWM0_3_CMPA_R = (5000-350) - 1;
    // Theoretical Value for other Servo
    //PWM0_3_CMPA_R = (5000-231) - 1;

    /*
    int i = 0;
    for(i = 0; i < 100; i++)
    {
    GPIO_PORTC_DATA_R |= 0x10;
    Timer1_Delay_MicroSecond(925);
    GPIO_PORTC_DATA_R &= ~0x10;
    Timer1_Delay_MicroSecond(19075); //Finish Period of 20ms
    }
    */
}


void rightPosition(void)
{
    PWM0_3_CMPA_R = (5000 - 147) - 1;
    // Theoretical Value for other Servo
    //PWM0_3_CMPA_R = (5000-65) - 1;

    /*
    int i = 0;
    for(i = 0; i < 100; i++)
    {
    GPIO_PORTC_DATA_R |= 0x10;
    Timer1_Delay_MicroSecond(260);
    GPIO_PORTC_DATA_R &= ~0x10;
    Timer1_Delay_MicroSecond(19740); //Finish Period of 20ms
    }
    */
}

void Timer1_Delay_MicroSecond(int ttime)
{
    int i;
    SYSCTL_RCGCTIMER_R |= 2;        // Enable clock to Timer Block 1
    TIMER1_CTL_R = 0;               // Disable Timer1 before initialization
    TIMER1_CFG_R = 0x04;            // Configure for 16-bit mode
    TIMER1_TAMR_R = 0x02;           // Configure for periodic mode and down-counter
    TIMER1_TAILR_R = 16 - 1; // Load TimerA interval value (16 cycles per microsecond)
    TIMER1_ICR_R = 0x1;             // Clear the TimerA timeout flag
    TIMER1_CTL_R |= 0x01;           // Enable Timer1A after initialization

    for (i = 0; i < ttime; i++)
    {
        while ((TIMER1_RIS_R & 0x1) == 0); // Wait for TimerA timeout flag
        TIMER1_ICR_R = 0x1;                // Clear the TimerA timeout flag
    }
}
