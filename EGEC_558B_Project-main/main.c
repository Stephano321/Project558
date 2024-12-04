/**
 * main.c
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "inc/tm4c123gh6pm.h"
#include "HC-SR04.h"
#include "DCMotor.h"
#include "ServoMotor.h"

uint32_t risingEdge=0;
uint32_t fallingEdge=0;
uint32_t PreScalar1 = 0;
uint32_t PreScalar2 = 0;
uint32_t period=0;
float distance = 0;

int main(void)
{
    HC_SR04_Init();
    DC_Motor_Init();
    Servo_Motor_Init();

    middlePosition();                               //Default middle position of servo motor
    Timer1_Delay_MilliSecond(5000);                 //Get everything ready for testing




    while(1){
        if(distance > .3)
            Forward();                              //Nothing close so go forward
        else
        {
            Stop();
            rightPosition();                        //Move servo to right position to scan
            Timer1_Delay_MilliSecond(50);
            if(distance > .3)
            {
                Turn_Right();                       //Right side scanned and there's room to travel
                Timer1_Delay_MilliSecond(500);      //Helps so car can turn right properly
                Stop()    ;                         //Stops the turning
                middlePosition();                   //Centers the servo motor so the sensor is in the middle position again
                Forward();                          //Start Driving since path is clear after it turned right
            }
            else
            {
                Stop();
                leftPosition();                     //Too close to the object on the right, now scanning left
                Timer1_Delay_MilliSecond(50);
                if(distance > .3)
                {
                    Turn_Left();                    //Left side scanned, there's room to travel
                    Timer1_Delay_MilliSecond(500);  //Helps so far can turn left properly
                    Stop();                         //Stops the turning
                    middlePosition();               //Centers the servo motor so the sensor is in the middle position again
                    Forward();                      //Start Driving since the path is clear after it turned left
                }
                else
                {
                    middlePosition();               //No path is clear in front, center the servo motor
                    Reverse();                      //Reverse to find a different route
                    Timer1_Delay_MilliSecond(2000); //Drives backwards for about 2 seconds
                    Stop();
                    int r = rand() % 20;            //Generate random number from 0-19 to pick which way to turn
                    if (r >= 10)
                        Turn_Right();               //Greater than or equal to 10, turn right
                    else
                        Turn_Left();                //Less than 10, turn left

                }
            }
        }
    }


}

