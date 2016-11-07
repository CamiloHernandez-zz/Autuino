//***********************Inicio codigo************************//

#include <Arduino.h>
#include <ConMotor.h>

//Iniciamos la clase principal de la libreria
ConMotor::ConMotor(int Pin_Motor_A1, int Pin_Motor_A2,  int Pin_Motor_B1, int Pin_Motor_B2):

//Remplazamos los valores globales por los privados (Inicialización de lista)
_Pin_Motor_A1(Pin_Motor_A1),
_Pin_Motor_A2(Pin_Motor_A2),
_Pin_Motor_B1(Pin_Motor_B1),
_Pin_Motor_B2(Pin_Motor_B2)

{
  //Iniciamos los pines por si todavía no se hace en main
  pinMode(_Pin_Motor_A1, OUTPUT);
  pinMode(_Pin_Motor_A2, OUTPUT);
  pinMode(_Pin_Motor_B1, OUTPUT);
  pinMode(_Pin_Motor_B2, OUTPUT);

  }

void ConMotor::writeMotor(char Motor, int Velocidad, bool Sentido){
  if(Motor == 'A'){
    if(Sentido == true){
      _PinSalida = _Pin_Motor_A1;
      _PinApagado = _Pin_Motor_A2;
    }
    if(Sentido == false){
      _PinSalida = _Pin_Motor_A2;
      _PinApagado = _Pin_Motor_A1;
    }
  }
  if(Motor == 'B'){
    if(Sentido == true){
      _PinSalida = _Pin_Motor_B1;
      _PinApagado = _Pin_Motor_B2;
    }
    if(Sentido == false){
      _PinSalida = _Pin_Motor_B2;
      _PinApagado = _Pin_Motor_B1;
    }
  }

  analogWrite(_PinSalida,Velocidad);
  analogWrite(_PinApagado,0);
}
void ConMotor::FrenoM(){
 analogWrite(_Pin_Motor_A1,255);
 analogWrite(_Pin_Motor_A2,255);
 analogWrite(_Pin_Motor_B1,255);
 analogWrite(_Pin_Motor_B2,255);
}
