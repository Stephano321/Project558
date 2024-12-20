#include <stdint.h>
#include <stdio.h>
#include "HC-SR04.h"
#include "inc/tm4c123gh6pm.h"

extern uint32_t risingEdge;
extern uint32_t fallingEdge;
extern uint32_t PreScalar1;
extern uint32_t PreScalar2;
extern uint32_t period;
extern float distance;

void HC_SR04_Init(void)
{
    /* Enable clock to GPIOB at clock gating control register */
    SYSCTL_RCGCGPIO_R |= 0x02;
    // Enable TIMER0
    SYSCTL_RCGCTIMER_R |= 0x01;
    // Enable PWM0
    SYSCTL_RCGC0_R |= SYSCTL_RCGC0_PWM0;
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
    SYSCTL_RCGCPWM_R |= 0x01;

    SYSCTL_RCC_R &= ~(0x7 << 17);
    // Enable PWMDIV
    SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV;
    SYSCTL_RCC_R |= SYSCTL_RCC_PWMDIV_64;

    //
    // GPIO Setup
    //
    /* Enable GPIO PB6 as input and enable PB4 as output*/
    GPIO_PORTB_DEN_R |= 0x50;                               // 0101 0000
    GPIO_PORTB_DIR_R |= 0x10;                               // 0001 0000
    // GPIO_PORTB_AFSEL_R &= ~0x000F0000;
    GPIO_PORTB_AFSEL_R |= 0x50;
    GPIO_PORTB_PCTL_R &= ~0x0F0F0000;
    GPIO_PORTB_PCTL_R |= 0x07040000;
    //
    // GPIO Setup
    //

    // NVIC_PRI0_R |= 0x6000;
    // NVIC_EN0_R |= 0x02;
    // Enable interrupt for PB6 and PB4

    //
    // Timer setup
    //
    TIMER0_CTL_R &= ~0x01;
    TIMER0_CFG_R = 0x04;
    TIMER0_TAMR_R = 0x0017;
    // PreScalar to let the timer reach 30ms
    // At 16 MHz
    // MAX = 4.096ms * (PreScalar - 1)
    // MAX = 4.096ms * (10 - 1) =
    TIMER0_TAPR_R = 9;
    TIMER0_CTL_R |= 0x0C;
    // Clear TIMER0A capture flag
    TIMER0_ICR_R = 0x04;
    //TIMER0_
    // Enable TIMER0A capture interrupt
    TIMER0_IMR_R |= 0x04;
    // Enable IRQ 19 in NVIC for TIMER0A
    NVIC_EN0_R |= (1 << 19);
    TIMER0_CTL_R |= 0x02;
    TIMER0_CTL_R |= 0x01;
    //
    // Timer Setup
    //

    //
    // PWM Setup
    //
    // the PWM1 block produces the MnPWM2 and MnPWM3 outputs
    // Disable PWM0 generator 1
    PWM0_ENABLE_R &= ~0x04;
    PWM0_CTL_R = 0;
    // Down count
    PWM0_1_CTL_R &= ~0x03;

    // Set PWM output when counter reloaded and clear when matches PWMCMPA
    PWM0_1_GENA_R = 0x0000008C;
    PWM0_1_GENB_R = 0;
    // Set PWM load register for 100ms period
    PWM0_1_LOAD_R = 25000 - 1;
    // Set comparator value for 10us
    // Load value - (clock freq - on time)
    PWM0_1_CMPA_R = (25000 - 3) - 1;
    // Enable PWM0 Generator 1
    PWM0_CTL_R |= 0x02;
    PWM0_1_CTL_R |= 0x01;
    // Enable M0PWM2 Output
    PWM0_ENABLE_R |= 0x04;
    //
    // PWM Setup
    ///

}

void TIMER0A_Handler(void)
{
    uint8_t PB6 = GPIO_PORTB_DATA_R && 0x40;
    if (TIMER0_RIS_R & 0x04)
    {
        TIMER0_ICR_R = 0x04;
        if ((PB6 && 0x40) == 1)
        {
            risingEdge = TIMER0_TAR_R & 0xFFFF;
            PreScalar1 = (TIMER0_TAR_R & 0xFF0000) >> 16;
        }
        else if ((PB6 && 0x40) == 0)
        {
            fallingEdge = TIMER0_TAR_R & 0xFFFF;
            PreScalar2 = (TIMER0_TAR_R & 0xFF0000) >> 16;
            measurePulseWidth();
            distance = getDistance(period);
        }
    }
}

void measurePulseWidth(void)
{
    if ((fallingEdge >= risingEdge) && (PreScalar1 == PreScalar2))
        period = fallingEdge - risingEdge;
    else
    {
        // get the difference in prescalar and multiply by 0xFFFF
        period = (0xFFFF*(PreScalar2-PreScalar1) + fallingEdge) - risingEdge;
    }
}


float getDistance(uint32_t time)
{
    float temp = 0.0;
    // time = clocks/frequency
    // time = clocks/16000000
    // period = 1/16000000 = 62.5ns or .0000000625s or .0000625ms
    temp = time/16000000.0;
    // Distance = (speed * time)/2
    // Distance = (340m/s * time)/2
    temp = (340*(temp))/2.0;
    return temp;
}

