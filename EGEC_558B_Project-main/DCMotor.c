#include <stdint.h>
#include <stdio.h>
#include "DCMotor.h"
#include "inc/tm4c123gh6pm.h"

void DC_Motor_Init(void)
{
    //Port D Initialization
    SYSCTL_RCGCGPIO_R |= 0x08;       // Enable Port D
    GPIO_PORTD_DIR_R |= 0x0C;   // Set PD2 and PD3 as output
    GPIO_PORTD_DEN_R |= 0x0C;   // Enable Digital for PD2 and PD3
    GPIO_PORTD_DIR_R |= 0xC0;   // Set PD6 and PD7 as output
    GPIO_PORTD_DEN_R |= 0xC0;   // Enable Digital for PD6 and PD7

    /*//PWM Initialization
    SYSCTL_RCGC0_R |= SYSCTL_RCGC0_PWM0;
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;
    SYSCTL_RCGCPWM_R |= 0x01;

    SYSCTL_RCC_R &= ~(0x7 << 17);
    SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV;
    SYSCTL_RCC_R |= SYSCTL_RCC_PWMDIV_64;

    GPIO_PORTD_AFSEL_R |= 0x03;  // Enable alternate function on PD0 and PD1
    GPIO_PORTD_PCTL_R &= ~0xFF;  // Clear PCTL for PD0 and PD1
    GPIO_PORTD_PCTL_R |= 0x44;   // Set PD0 and PD1 as PWM output
    GPIO_PORTD_DEN_R |= 0x03;    // Enable digital functionality for PD0 and PD1

    // Disable PWM0 generator 3
    PWM0_ENABLE_R |= ~0xC0;
    PWM0_3_CTL_R = 0;

    PWM0_3_GENA_R = 0x0000008C;
    PWM0_3_GENB_R = 0x0000080C;
    PWM0_3_LOAD_R = 25000 - 1;
    PWM0_3_CMPA_R = 25000 - 4;
    PWM0_3_CMPB_R = 25000 - 4;
    PWM0_3_CTL_R = 1;
    PWM0_ENABLE_R |= 0xC0;*/
}

void Forward(void)
{
    // Left Motor(Forward)
    GPIO_PORTD_DATA_R |= 0x04;   // Set PD2 high
    GPIO_PORTD_DATA_R &= ~0x08;  // Set PD3 low

    // Right Motor(Forward)
    GPIO_PORTD_DATA_R |= 0x40;   // Set PD6 high
    GPIO_PORTD_DATA_R &= ~0x80;  // Set PD7 low
}

void Reverse(void)
{
    // Left Motor(Backwards)
    GPIO_PORTD_DATA_R |= ~0x04;  // Set PD2 low
    GPIO_PORTD_DATA_R &= 0x08;   // Set PD3 high

    // Right Motor(Backwards)
    GPIO_PORTD_DATA_R |= ~0x40;  // Set PD6 low
    GPIO_PORTD_DATA_R &= 0x80;   // Set PD7 high
}

void Turn_Left(void)
{
    // Left Motor (Backwards)
    GPIO_PORTD_DATA_R |= ~0x04;  // Set PD2 low
    GPIO_PORTD_DATA_R &= 0x08;   // Set PD3 high

    // Right Motor (Forward)
    GPIO_PORTD_DATA_R |= 0x40;   // Set PD6 high
    GPIO_PORTD_DATA_R &= ~0x80;  // Set PD7 low
}

void Turn_Right(void)
{
    // Left Motor (Forward)
    GPIO_PORTD_DATA_R |= 0x04;   // Set PD2 high
    GPIO_PORTD_DATA_R &= ~0x08;  // Set PD3 low

    // Right Motor (Backwards)
    GPIO_PORTD_DATA_R |= ~0x40;  // Set PD6 low
    GPIO_PORTD_DATA_R &= 0x80;   // Set PD7 high
}

void Stop(void)
{
    // Left Motor (Stop)
    GPIO_PORTD_DATA_R |= ~0x04;   // Set PD2 low
    GPIO_PORTD_DATA_R &= ~0x08;  // Set PD3 low

    // Right Motor (Stop)
    GPIO_PORTD_DATA_R |= ~0x40;  // Set PD6 low
    GPIO_PORTD_DATA_R &= ~0x80;   // Set PD7 low
}


