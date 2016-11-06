//***********************Inicio codigo************************//

#include <Arduino.h>
#include <Servo.h>
#include <ConMotor.h>

using namespace std;

//*******************Inicio declaraciones*********************//

// Pines de los motores
const int Pin_Motor_A1 = A0;
const int Pin_Motor_A2 = A1;
const int Pin_Motor_B1 = 6;
const int Pin_Motor_B2 = 5;

// Pines del sensor ultrasonido
const int trigPin = A4;
const int echoPin = A5;

// Variables del ultrasonido
int duracion, distancia;

//*********************Fin declaraciones**********************//


//*******************************Setup********************************//


// Iniciando la librería ConMotor
ConMotor motor(Pin_Motor_A1, Pin_Motor_A2, Pin_Motor_B1, Pin_Motor_B2);

// Iniciando la librería Servo
Servo servo;

int UltraSonido(){

  digitalWrite(trigPin, LOW);

  // Se detiene el sensor por 0.002 segundos
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);

  // Se detiene el sensor por 0.01 segundos
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH);

  //Ecuación para calcular la distancia en centimetros
  distancia = (duracion/2) / 29.1;

  return distancia;
}

void setup(){

     //Se agrega el Servo
     servo.attach(3);

     // Iniciando serial
    Serial.begin(9600);

    motor.writeMotor('B', 225, true);
    motor.writeMotor('A', 225, true);

    // Declaración sobre E/S de los pines
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    //Moviendo el Servo a la posición inicial
    servo.write(180);

    //Mensaje de bienvenida
    Serial.println("AOK");

}



void loop(){

    distancia = UltraSonido();

    if (distancia < 25){
     Serial.print ("Obstaculo detectedo a " );
     Serial.print (distancia);
     Serial.println ( " centimetros.");
     Serial.println ( " Revisando a que lado ir.");

     servo.write(180);


    }

}


//************************Fin codigo**************************//
