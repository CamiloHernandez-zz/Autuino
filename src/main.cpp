//***********************Inicio codigo************************//

#include <Arduino.h>
#include <Servo.h>
#include <ConMotor.h>

using namespace std;

#define trigPin A4 // pins del sensor ultrasonido
#define echoPin A5

//*******************Inicio declaraciones*********************//

const int Pin_Motor_A1 = 10;
const int Pin_Motor_A2 = 9;
const int Pin_Motor_B1 = 6;
const int Pin_Motor_B2 = 5;

//*********************Fin declaraciones**********************//


//*******************************Setup********************************//

ConMotor motor(Pin_Motor_A1, Pin_Motor_A2, Pin_Motor_B1, Pin_Motor_B2);

void setup(){
    Serial.begin(9600); // begin serial communitication
    Serial.println("Motor test!");
    pinMode(trigPin, OUTPUT);// set the trig pin to output (Send sound waves)
    pinMode(echoPin, INPUT);// set the echo pin to input (recieve sound waves)
    motor.writeMotor('B', 200, true);
    motor.writeMotor('A', 200, true);

}

void loop(){

    long duration, distance; // start the scan

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // delays are required for a succesful sensor operation.
    digitalWrite(trigPin, HIGH);

    delayMicroseconds(10); //this delay is required as well!
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;// convert the distance to centimeters.
    if (distance < 25)/*if there's an obstacle 25 centimers, ahead, do the following: */ {
     Serial.println ("Close Obstacle detected!" );
    Serial.println ("Obstacle Details:");
    Serial.print ("Distance From Robot is " );
    Serial.print ( distance);
    Serial.print ( " CM!");// print out the distance in centimeters.

    Serial.println (" The obstacle is declared a threat due to close distance. ");
    Serial.println (" Turning !");
}

}


//************************Fin codigo**************************//
