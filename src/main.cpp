//***********************Inicio codigo************************//

#include <Arduino.h>
#include <Servo.h>
#include <ConMotor.h>

using namespace std;

//*******************Inicio declaraciones*********************//

const int Pin_Motor_A1 = 10;
const int Pin_Motor_A2 = 9;
const int Pin_Motor_B1 = 6;
const int Pin_Motor_B2 = 5;

//*********************Fin declaraciones**********************//


//*******************************Setup********************************//

ConMotor motor(Pin_Motor_A1, Pin_Motor_A2, Pin_Motor_B1, Pin_Motor_B2);

void setup(){

    motor.writeMotor('B', 255, true);
    motor.writeMotor('A', 255, true);

}

void loop(){


}

//************************Fin codigo**************************//
