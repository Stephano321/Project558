#include <stdint.h>
#include <stdio.h>
#include "DCMotor.h"
#include "inc/tm4c123gh6pm.h"

void DC_Motor_Init(void)
{
    //Port D Initialization Motor 1 (Front Left wheel)
    SYSCTL_RCGCGPIO_R |= 0x08;       // Enable Port D
    GPIO_PORTD_DIR_R |= 0x0C;   // Set PD2 and PD3 as output
    GPIO_PORTD_DEN_R |= 0x0C;   // Enable Digital for PD2 and PD3

    //Port E Initialization Motor 2 (Front Right Wheel)
    SYSCTL_RCGCGPIO_R |= 0x10;
    GPIO_PORTE_DIR_R |= 0x30;   // Set PE4 and PE5 as output
    GPIO_PORTE_DEN_R |= 0x30;   // Enable Digital for PE4 and PE5

    /* Broken pins?
    GPIO_PORTD_DIR_R |= 0xC0;   // Set PD6 and PD7 as output
    GPIO_PORTD_DEN_R |= 0xC0;   // Enable Digital for PD6 and PD7
    */

    /*
    //Port C Initialization Motor 3 (Back left Wheel)
    SYSCTL_RCGCGPIO_R |= 0x04;
    GPIO_PORTC_DIR_R |= 0xC0;   // Set PC6 and PC7 as output
    GPIO_PORTC_DEN_R |= 0xC0;   // Enable Digital for PC6 and PC7
    */


    //Port F Initialization for PWM

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
    // Top Left Motor(Forward)
    GPIO_PORTD_DATA_R |= 0x04;   // Set PD2 high
    GPIO_PORTD_DATA_R &= ~0x08;  // Set PD3 low

    /*
    // Top Right Motor(Forward)
    GPIO_PORTD_DATA_R |= 0x40;   // Set PD6 high
    GPIO_PORTD_DATA_R &= ~0x80;  // Set PD7 low

    // Bottom Left Motor(Forward)
    GPIO_PORTC_DATA_R |= 0x40;   // Set PC6 high
    GPIO_PORTC_DATA_R &= ~0x80;  // Set PC7 low
    */

    // Top Right Motor(Forward)
    GPIO_PORTE_DATA_R |= 0x10;   // Set PE4 high
    GPIO_PORTE_DATA_R &= ~0x20;  // Set PE5 low
}

void Reverse(void)
{
    // Top Left Motor(Backwards)
    GPIO_PORTD_DATA_R &= ~0x04;  // Set PD2 low
    GPIO_PORTD_DATA_R |= 0x08;   // Set PD3 high

    /*
    // Top Right Motor(Backwards)
    GPIO_PORTD_DATA_R &= ~0x40;  // Set PD6 low
    GPIO_PORTD_DATA_R |= 0x80;   // Set PD7 high

    GPIO_PORTD_DATA_R = 0x88;

    // Bottom Left Motor(Backwards)
    GPIO_PORTC_DATA_R &= ~0x40;   // Set PC6 low
    GPIO_PORTC_DATA_R |= 0x80;  // Set PC7 high
    */

    // Top Right Motor(Backwards)
    GPIO_PORTE_DATA_R &= ~0x10;   // Set PE4 low
    GPIO_PORTE_DATA_R |= 0x20;  // Set PE5 high
}

void Turn_Left(void)
{
    // Top Left Motor (Backwards)
    GPIO_PORTD_DATA_R &= ~0x04;  // Set PD2 low
    GPIO_PORTD_DATA_R |= 0x08;   // Set PD3 high

    /*
    // Top Right Motor (Forward)
    GPIO_PORTD_DATA_R |= 0x40;   // Set PD6 high
    GPIO_PORTD_DATA_R &= ~0x80;  // Set PD7 low

    // Bottom Left Motor(Backwards)
    GPIO_PORTC_DATA_R &= ~0x40;   // Set PC6 low
    GPIO_PORTC_DATA_R |= 0x80;  // Set PC7 high
    */

    // Top Right Motor(Forward)
    GPIO_PORTE_DATA_R |= 0x10;   // Set PE4 high
    GPIO_PORTE_DATA_R &= ~0x20;  // Set PE5 low
}

void Turn_Right(void)
{
    // Top Left Motor (Forward)
    GPIO_PORTD_DATA_R |= 0x04;   // Set PD2 high
    GPIO_PORTD_DATA_R &= ~0x08;  // Set PD3 low

    /*
    // Top Right Motor (Backwards)
    GPIO_PORTD_DATA_R &= ~0x40;  // Set PD6 low
    GPIO_PORTD_DATA_R |= 0x80;   // Set PD7 high

    // Bottom Left Motor(Forward)
    GPIO_PORTC_DATA_R |= 0x40;   // Set PC6 high
    GPIO_PORTC_DATA_R &= ~0x80;  // Set PC7 low
    */

    // Top Right Motor(Backwards)
    GPIO_PORTE_DATA_R &= ~0x10;   // Set PE4 low
    GPIO_PORTE_DATA_R |= 0x20;  // Set PE5 high
}

void Stop(void)
{
    // Top Left Motor (Stop)
    GPIO_PORTD_DATA_R &= ~0x04;   // Set PD2 low
    GPIO_PORTD_DATA_R &= ~0x08;  // Set PD3 low

    /*
    // Top Right Motor (Stop)
    GPIO_PORTD_DATA_R &= ~0x40;  // Set PD6 low
    GPIO_PORTD_DATA_R &= ~0x80;   // Set PD7 low

    // Bottom Left Motor(Stop)
    GPIO_PORTC_DATA_R &= ~0x40;   // Set PC6 low
    GPIO_PORTC_DATA_R &= ~0x80;  // Set PC7 low
    */

    // Top Right Motor(Stop)
    GPIO_PORTE_DATA_R &= ~0x10;   // Set PE4 low
    GPIO_PORTE_DATA_R &= ~0x20;  // Set PE5 low
}


