//------------------------------------------------------------------------------
//Funcion para mover el sistema con el teclado y poder determinar la posicion en PASOS de las letras.
//  WASD  100 pasos
//  TFGH  1000 pasos
//  IJKL  10000 pasos.
// ##CUIDADO## siempre probar la direccion primero con 100 pasos, para evitar choques.

void moveWithKeyboard()
{
  enableMotors();
  if(Serial.available() > 0)
  {
    int temp = Serial.read();
    
    if(temp == 119 || temp == 87)       //dec for 'w'
    {
      stepperY.moveTo(stepperY.currentPosition() - 100);
      //stepperY.setSpeed(2000);
      while(stepperY.distanceToGo() != 0)
      {
        stepperY.run();
      }
      Serial.print(stepperX.currentPosition());
      Serial.print("   ");
      Serial.println(stepperY.currentPosition());
    }
    if(temp == 115 || temp == 83)     //dec for 's'
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
    if(temp == 97 || temp == 65)  //dec for 'a'
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
    if(temp == 100 || temp == 68) //dec for 'd'
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

    
   
    //Moviendose de 1000 pasos
    if(temp == 116 || temp == 84)  //dec for 't'
    {
      stepperY.moveTo(stepperY.currentPosition() - 1000);
      while(stepperY.distanceToGo() != 0)
      {
        stepperY.run();
      }
      Serial.print(stepperX.currentPosition()); Serial.print("   "); Serial.println(stepperY.currentPosition());
    }
    if(temp == 71 || temp == 103)//dec for 'g'
    {
      stepperY.moveTo(stepperY.currentPosition() + 1000);
      //stepperY.setSpeed(2000);
      while(stepperY.distanceToGo() != 0)
      {
        stepperY.run();
      } 
      Serial.print(stepperX.currentPosition()); Serial.print("   "); Serial.println(stepperY.currentPosition());
    }
    if(temp == 70 || temp == 102)//dec for 'f'
    {
      stepperX.moveTo(stepperX.currentPosition() - 1000);
      //stepperX.setSpeed(3000);
      while(stepperX.distanceToGo() != 0)
      {
        stepperX.run();
      }  
      Serial.print(stepperX.currentPosition()); Serial.print("   "); Serial.println(stepperY.currentPosition());
    }
    if(temp == 72 || temp == 104 )//dec for 'h'
    {
      stepperX.moveTo(stepperX.currentPosition() + 1000);
      while(stepperX.distanceToGo() != 0)
      {
        stepperX.run();
      }
      Serial.print(stepperX.currentPosition()); Serial.print("   "); Serial.println(stepperY.currentPosition());
    }
  
  }
  disableMotors();
}

