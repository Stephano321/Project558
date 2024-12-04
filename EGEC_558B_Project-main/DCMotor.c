#include <stdint.h>
#include <stdio.h>
#include "DCMotor.h"
#include "inc/tm4c123gh6pm.h"

void DC_Motor_Init(void)
{
    //Port D Initialization Motor 1 (Top Left Motor)
    SYSCTL_RCGCGPIO_R |= 0x08;       // Enable Port D
    GPIO_PORTD_DIR_R |= 0x0C;   // Set PD2 and PD3 as output
    GPIO_PORTD_DEN_R |= 0x0C;   // Enable Digital for PD2 and PD3

    //Port E Initialization Motor 2 (Top Right Motor)
    SYSCTL_RCGCGPIO_R |= 0x10;
    GPIO_PORTE_DIR_R |= 0x30;   // Set PE4 and PE5 as output
    GPIO_PORTE_DEN_R |= 0x30;   // Enable Digital for PE4 and PE5

    /* Broken pins?
    GPIO_PORTD_DIR_R |= 0xC0;   // Set PD6 and PD7 as output
    GPIO_PORTD_DEN_R |= 0xC0;   // Enable Digital for PD6 and PD7

    //Port C Initialization Motor 3 (Bottom left Motor)
    SYSCTL_RCGCGPIO_R |= 0x04;
    GPIO_PORTC_DIR_R |= 0xC0;   // Set PC6 and PC7 as output
    GPIO_PORTC_DEN_R |= 0xC0;   // Enable Digital for PC6 and PC7
    */


    //PWM Initialization
    SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R0;  // Enable Clock for PWM0
    SYSCTL_RCC_R &= ~0x00100000;           // Use System Clock
    GPIO_PORTD_DIR_R |= 0x03;               // Set PD0 and PD1 as output
    GPIO_PORTD_DEN_R |= 0x03;               // Enable Digital for PD0 and PD1

    GPIO_PORTD_AFSEL_R |= 0x03; // Alternate Functions for PD0 and PD1
    GPIO_PORTD_PCTL_R |= 0x44;

    //Disable Generators
    PWM0_ENABLE_R &= ~0x03;
    PWM0_CTL_R &= ~0x05;    // 0 1 0 1
    PWM0_0_CTL_R = 0;
    PWM0_2_CTL_R = 0;

    //Down Count for Generator 0
    PWM0_0_CTL_R &= ~0x03;
    PWM0_0_GENA_R = 0x8C;
    PWM0_0_GENB_R = 0;

    //Down Count for Generator 2
    PWM0_2_CTL_R &= ~0x03;
    PWM0_2_GENA_R = 0x8C;
    PWM0_2_GENB_R = 0;

    // 16,000,000 / 2500
    //Set PWM load Register for 2.5Khz
    PWM0_0_LOAD_R = 6400 - 1;

    //Set PWM load Register for 2.5Khz
    PWM0_2_LOAD_R = 6400 - 1;

    // Duty Cycle, change here (Just need to modify this to change speed)
    PWM0_0_CMPA_R = 6400 - 1;   // Initial Duty Cycle PWM0 Generator 0
    PWM0_2_CMPA_R = 6400 - 1;   // Initial Duty Cycle PWM0 Generator 2

    //Enable Generators
    PWM0_CTL_R |= 0x5;    // Enables Gen 0 and 2
    PWM0_0_CTL_R = 1;
    PWM0_2_CTL_R = 1;

    //Enable PWM Output for PD0 and PD1
    PWM0_ENABLE_R |= 0x3;
}

void Forward(void)
{
    // Top Right Motor(Forward)
    GPIO_PORTD_DATA_R |= 0x04;   // Set PD2 high
    GPIO_PORTD_DATA_R &= ~0x08;  // Set PD3 low

    // Top Left Motor(Forward)
    GPIO_PORTE_DATA_R |= 0x10;   // Set PE4 high
    GPIO_PORTE_DATA_R &= ~0x20;  // Set PE5 low

    /* Unused Motors
    // Bottom Right Motor(Forward)
    GPIO_PORTD_DATA_R |= 0x40;   // Set PD6 high
    GPIO_PORTD_DATA_R &= ~0x80;  // Set PD7 low

    // Bottom Left Motor(Forward)
    GPIO_PORTC_DATA_R |= 0x40;   // Set PC6 high
    GPIO_PORTC_DATA_R &= ~0x80;  // Set PC7 low
    */
}

void Reverse(void)
{
    // Top Right Motor(Backwards)
    GPIO_PORTD_DATA_R &= ~0x04;  // Set PD2 low
    GPIO_PORTD_DATA_R |= 0x08;   // Set PD3 high

    // Top Left Motor(Backwards)
    GPIO_PORTE_DATA_R &= ~0x10;   // Set PE4 low
    GPIO_PORTE_DATA_R |= 0x20;  // Set PE5 high

    /*
    // Bottom Right Motor(Backwards)
    GPIO_PORTD_DATA_R &= ~0x40;  // Set PD6 low
    GPIO_PORTD_DATA_R |= 0x80;   // Set PD7 high

    GPIO_PORTD_DATA_R = 0x88;

    // Bottom Left Motor(Backwards)
    GPIO_PORTC_DATA_R &= ~0x40;   // Set PC6 low
    GPIO_PORTC_DATA_R |= 0x80;  // Set PC7 high
    */
}

void Turn_Left(void)
{
    // Top Right Motor (Forward)
    GPIO_PORTD_DATA_R |= 0x04;  // Set PD2 high
    GPIO_PORTD_DATA_R &= ~0x08;   // Set PD3 low

    // Top Left Motor(Backwards)
    GPIO_PORTE_DATA_R &= ~0x10;   // Set PE4 low
    GPIO_PORTE_DATA_R |= 0x20;  // Set PE5 high

    /* Unused Motors
    // Top Right Motor (Forward)
    GPIO_PORTD_DATA_R |= 0x40;   // Set PD6 high
    GPIO_PORTD_DATA_R &= ~0x80;  // Set PD7 low

    // Bottom Left Motor(Backwards)
    GPIO_PORTC_DATA_R &= ~0x40;   // Set PC6 low
    GPIO_PORTC_DATA_R |= 0x80;  // Set PC7 high
    */
}

void Turn_Right(void)
{
    // Top Right Motor (Backwards)
    GPIO_PORTD_DATA_R &= ~0x04;   // Set PD2 low
    GPIO_PORTD_DATA_R |= 0x08;  // Set PD3 high

    // Top Left Motor(Forwards)
    GPIO_PORTE_DATA_R |= 0x10;   // Set PE4 high
    GPIO_PORTE_DATA_R &= ~0x20;  // Set PE5 low

    /* Unused Motors
    // Bottom Right Motor (Backwards)
    GPIO_PORTD_DATA_R &= ~0x40;  // Set PD6 low
    GPIO_PORTD_DATA_R |= 0x80;   // Set PD7 high

    // Bottom Left Motor(Forward)
    GPIO_PORTC_DATA_R |= 0x40;   // Set PC6 high
    GPIO_PORTC_DATA_R &= ~0x80;  // Set PC7 low
    */
}

void Stop(void)
{
    // Top Left Motor (Stop)
    GPIO_PORTD_DATA_R &= ~0x04;   // Set PD2 low
    GPIO_PORTD_DATA_R &= ~0x08;  // Set PD3 low

    // Top Right Motor(Stop)
    GPIO_PORTE_DATA_R &= ~0x10;   // Set PE4 low
    GPIO_PORTE_DATA_R &= ~0x20;  // Set PE5 low

    /* Unused Motors
    // Top Right Motor (Stop)
    GPIO_PORTD_DATA_R &= ~0x40;  // Set PD6 low
    GPIO_PORTD_DATA_R &= ~0x80;   // Set PD7 low

    // Bottom Left Motor(Stop)
    GPIO_PORTC_DATA_R &= ~0x40;   // Set PC6 low
    GPIO_PORTC_DATA_R &= ~0x80;  // Set PC7 low
    */
}

