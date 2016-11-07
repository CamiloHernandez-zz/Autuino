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
const int Pin_Motor_A1 = 6;
const int Pin_Motor_A2 = 5;
const int Pin_Motor_B1 = A0;
const int Pin_Motor_B2 = A1;


// Pines del sensor ultrasonido
const int trigPin = A4;
const int echoPin = A5;

// Variables del ultrasonido
unsigned int duracion, distancia_frontal, distancia_izq, distancia_der, distancia;

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
    servo.write(125);

    //Mensaje de bienvenida
    Serial.println("AOK");

}



void loop(){


  motor.writeMotor('B', 225, true);
  motor.writeMotor('A', 225, true);

    distancia_frontal = UltraSonido();

    if (distancia_frontal < 30){

    Serial.println ();
    Serial.println ( "-----------------------------------------------------");
     Serial.print ("Obstaculo detectedo a " );
     Serial.print (distancia_frontal);
     Serial.println ( " centimetros.");

     Serial.println ( "Deteniendo motores");

     motor.FrenoM();

     Serial.println ( "Revisando a que lado voy:");

     servo.write(70);

     delay(500);
     distancia_der = UltraSonido();

     servo.write(180);

    delay(500);
     distancia_izq = UltraSonido();

     delay(500);
     servo.write(125);

       if(distancia_der>distancia_izq){

           Serial.print ( "El lado derecho esta mas despejado, girando. (");
           Serial.print (distancia_der);
           Serial.println ( " centimetros).");


         motor.writeMotor('B',0,false);
         motor.writeMotor('A',255,false);

         delay(800);

         distancia_der = 0;
         distancia_izq = 0;
       }

       if(distancia_der<distancia_izq){

         Serial.print ( "El lado izquierdo esta mas despejado, girando. (");
         Serial.print (distancia_izq);
         Serial.println ( " centimetros).");

         motor.writeMotor('A',0,true);
         motor.writeMotor('B',255,false);

         delay(800);

         distancia_der = 0;
         distancia_izq = 0;
       }

       Serial.println ( "-----------------------------------------------------");


    }

}


//************************Fin codigo**************************//
