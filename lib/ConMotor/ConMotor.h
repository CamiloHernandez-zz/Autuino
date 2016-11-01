#ifndef ConMotor_h
#define ConMotor_h

#include "Arduino.h"

class ConMotor
{
  public:
    ConMotor(int Pin_Motor_A1, int Pin_Motor_A2,  int Pin_Motor_B1, int Pin_Motor_B2);
    void writeMotor(char Motor, int Velocidad, bool Sentido);
    void FrenoM();
  private:
     int _Pin_Motor_A1;
     int _Pin_Motor_A2;
     int _Pin_Motor_B1;
     int _Pin_Motor_B2;
     char _Motor;
     int _Velocidad;
     bool _Sentido;
     int _PinSalida;

};


#endif
