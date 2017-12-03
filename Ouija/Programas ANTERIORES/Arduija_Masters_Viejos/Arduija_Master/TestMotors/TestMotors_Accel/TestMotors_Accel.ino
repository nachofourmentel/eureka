
#include <AccelStepper.h>

// Define some steppers and the pins the will use
//AccelStepper stepper1; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
//AccelStepper stepper2(AccelStepper::FULL4WIRE, 6, 7, 8, 9);
//AccelStepper stepper3(AccelStepper::FULL2WIRE, 10, 11);

AccelStepper stepperX(1, 2, 3);     //X axis
AccelStepper stepperY(1, 9, 8);     //Y axis   //(driver=true, step, dir)
int enableX = 7;  //Enables de los motores (Cambiar)
int enableY = 12;

//Se ve afectada por la velocidad del procesador y el clock (( 1000/500  es 10000pap por extremo)
//unsigned int velocidad = 1500.0;
//unsigned int aceleracion = 3500.0;

unsigned int velocidadX = 5000.0;
unsigned int aceleracionX = 6000.0;

unsigned int velocidadY = 4000.0;
unsigned int aceleracionY = 6000.0;

//Punteros
long posX = 0; 
long posY = 0;
void setup()
{  
    //Pinmodes
     pinMode(enableX, OUTPUT);
     pinMode(enableY, OUTPUT);
    //Seriales
    Serial.begin(115200);   //Serial print for debug
    Serial.println("Control de los motores.");
    Serial.println();
    Serial.println("Controle dirección con el teclado:");
    Serial.println();
    Serial.println("W A S D  para control a 100 pasos.");
    Serial.println("J K I L  para control a 10000 pasos");
    Serial.println();

      //Velocidades
    stepperX.setMaxSpeed(velocidadX);
    stepperX.setAcceleration(aceleracionX);
        
    stepperY.setMaxSpeed(velocidadY);
    stepperY.setAcceleration(aceleracionY);

    }

void loop()
{
  moveWithKeyboard();
 }

void enableMotors()
{
  //Enable the motors 
  digitalWrite(enableX, LOW);
  digitalWrite(enableY, LOW);
}
//------------------------------------------------------------------------------
void disableMotors()
{
  //Disable the motors 
  digitalWrite(enableX, HIGH);
  digitalWrite(enableY, HIGH);
}

void moveWithKeyboard()
{
  enableMotors();
  
  if(Serial.available() > 0)
  {
    int temp = Serial.read();
    
    if(temp == 119 || temp == 87)       //dec for 'w'
    {
      stepperY.moveTo(stepperY.currentPosition() - 100);
      stepperY.setSpeed(8000);
      while(stepperY.distanceToGo() != 0)
      {
        stepperY.runSpeed();
        
      }
      
      Serial.println("   ");
      Serial.print(stepperX.currentPosition());
      Serial.print("   ");
      Serial.println(stepperY.currentPosition());
    }
    if(temp == 115 || temp == 83)//dec for 's'
    {
      stepperY.moveTo(stepperY.currentPosition() + 100);
      //stepperY.setSpeed(2000);
      while(stepperY.distanceToGo() != 0)
      {
        stepperY.run();
      } 
      Serial.print(stepperX.currentPosition());
      Serial.print("   ");
      Serial.println(stepperY.currentPosition());
    }
    if(temp == 97 || temp == 65)//dec for 'a'
    {
      
      stepperX.moveTo(stepperX.currentPosition() - 100);
      //stepperX.setSpeed(3000);
      while(stepperX.distanceToGo() != 0)
      {
        stepperX.run();
      }
        
      Serial.print(stepperX.currentPosition());
      Serial.print("   ");
      Serial.println(stepperY.currentPosition());
    }
    if(temp == 100 || temp == 68)//dec for 'd'
    {
      stepperX.moveTo(stepperX.currentPosition() + 100.00);
      //stepperX.setSpeed(3000);
      while(stepperX.distanceToGo() != 0)
      {
        stepperX.run();
      }
      Serial.print(stepperX.currentPosition());
      Serial.print("   ");
      Serial.println(stepperY.currentPosition());
    }
    
    //Moviendose de 10000 pasos
    if(temp == 105 || temp == 73)//dec for 'i'
    {
      stepperY.moveTo(stepperY.currentPosition() - 10000);
      while(stepperY.distanceToGo() != 0)
      {
        stepperY.run();
      }
      Serial.print(stepperX.currentPosition()); Serial.print("   "); Serial.println(stepperY.currentPosition());
    }
    if(temp == 107 || temp == 75)//dec for 'k'
    {
      stepperY.moveTo(stepperY.currentPosition() + 10000);
      //stepperY.setSpeed(2000);
      while(stepperY.distanceToGo() != 0)
      {
        stepperY.run();
      } 
      Serial.print(stepperX.currentPosition()); Serial.print("   "); Serial.println(stepperY.currentPosition());
    }
    if(temp == 106 || temp == 74)//dec for 'j'
    {
      stepperX.moveTo(stepperX.currentPosition() - 10000);
      //stepperX.setSpeed(3000);
      while(stepperX.distanceToGo() != 0)
      {
        stepperX.run();
      }  
      Serial.print(stepperX.currentPosition()); Serial.print("   "); Serial.println(stepperY.currentPosition());
    }
    if(temp == 108 || temp == 76)//dec for 'l'
    {
      stepperX.moveTo(stepperX.currentPosition() + 10000);
      while(stepperX.distanceToGo() != 0)
      {
        stepperX.run();
      }
      Serial.print(stepperX.currentPosition()); Serial.print("   "); Serial.println(stepperY.currentPosition());
    }
  
  }
  disableMotors();
}
