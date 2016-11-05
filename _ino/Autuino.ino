/* ATENCION!: Esta es la versión no apta para Platformio, las
              librerias incluidas en la carpeta "lib" deben
              ser manualmente agregadas
*/



//***********************Inicio codigo************************//

#include <Arduino.h>
#include <Servo.h>
#include <ConMotor.h>

using namespace std;

//*******************Inicio declaraciones*********************//

// Pines de los motores
const int Pin_Motor_A1 = 10;
const int Pin_Motor_A2 = 9;
const int Pin_Motor_B1 = 6;
const int Pin_Motor_B2 = 5;

// Pines del sensor ultrasonido
const int trigPin = A4;
const int echoPin = A5;

// Variables del ultrasonido
    long duracion, distancia;

//*********************Fin declaraciones**********************//


//*******************************Setup********************************//


// Iniciando la librería
ConMotor motor(Pin_Motor_A1, Pin_Motor_A2, Pin_Motor_B1, Pin_Motor_B2);

void setup(){

     // Iniciando serial
    Serial.begin(9600);

    motor.writeMotor('B', 200, true);
    motor.writeMotor('A', 200, true);

    // Declaración sobre E/S de los pines
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    //Mensaje de bienvenida
    Serial.println("AOK");

}

void loop(){

    digitalWrite(trigPin, LOW);

    // Se detiene el sensor por 0.002 segundos
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);

    // Se detiene el sensor por 0.01 segundos
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    duracion = pulseIn(echoPin, HIGH);

    //Ecuación para calcular la distáncia en centimetros
    distancia = (duracion/2) / 29.1;

    if (distancia < 25){
     Serial.print ("Obstaculo detectedo a " );
     Serial.print (distancia);
     Serial.println ( " centimetros.");
    }

}


//************************Fin codigo**************************//
