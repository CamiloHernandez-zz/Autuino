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

// Movimientos
const int Tiempo_de_giro = 600; //ms
const int Angulo_izq = 180; //grados
const int Angulo_der = 70;  //grados
const int Angulo_cen = 125;  //grados
const int distancia_para_giro = 15; //cm

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
    servo.write(Angulo_cen);

    //Mensaje de bienvenida
    Serial.println("AOK");

}



void loop(){

  //Iniciamos por defecto los motores en la velocidad maxima y dirección frontal
  motor.writeMotor('B', 225, true);
  motor.writeMotor('A', 225, true);

  // Medimos que tan lejos esta el auto de llegar a un objeto
  distancia_frontal = UltraSonido();


     // Cuando el auto se acerque a un objeto:
    if (distancia_frontal < distancia_para_giro){

     // Anunciamos por serial la proximidad
     Serial.println ();
     Serial.println ( "-----------------------------------------------------");
     Serial.print ("Obstaculo detectedo a " );
     Serial.print (distancia_frontal);
     Serial.println ( " centimetros.");
     Serial.println ( "Deteniendo motores");

     motor.FrenoM();

     Serial.println ( "Revisando a que lado voy:");


    // Giramos el servo del ultrasonido hacia la derecha para medir la distancia
     servo.write(Angulo_der);
     delay(500);
     distancia_der = UltraSonido();


    // Giramos el servo del ultrasonido hacia la izquierda para medir la distancia
     servo.write(Angulo_izq);
     delay(500);
     distancia_izq = UltraSonido();


    // Devolvemos el servo al centro
     delay(500);
     servo.write(Angulo_cen);

       if(distancia_der>distancia_izq){

           Serial.print ( "El lado derecho esta mas despejado, girando. (");
           Serial.print (distancia_der);
           Serial.println ( " centimetros).");

           // Hacemos funcionar solo uno de los motores para girar
           motor.writeMotor('B',0,false);
           motor.writeMotor('A',255,false);

           // Le damos tiempo para que gire
           delay(Tiempo_de_giro);

           // Reiniciamos los valores
           distancia_der = 0;
           distancia_izq = 0;
       }

       if(distancia_der<distancia_izq){

         Serial.print ( "El lado izquierdo esta mas despejado, girando. (");
         Serial.print (distancia_izq);
         Serial.println ( " centimetros).");

         // Hacemos funcionar solo uno de los motores para girar
         motor.writeMotor('A',0,true);
         motor.writeMotor('B',255,false);

         // Le damos tiempo para que gire
         delay(Tiempo_de_giro);

         // Reiniciamos los valores
         distancia_der = 0;
         distancia_izq = 0;
       }

       Serial.println ( "-----------------------------------------------------");

    }

}


//************************Fin codigo**************************//
