/* REVISION 8/19   9:52 AM */
//Funcion que busca el punto 0-0 del sistema.

void homeing()
{
  //enableMotors(); //No me interesa que ambos esten prendidos, porque va de a 1.
 
  digitalWrite(enableY, LOW);
  //Primero se mueve eje Y
  if(digitalRead(switct_y_top) == HIGH)
  {
    while(digitalRead(switct_y_top) == HIGH)
    {
      stepperY.moveTo(posY);
      stepperY.run();
      //delayMicroseconds(20); //delay que evita que se trabe el motor, intenta procesar posiciones que no se calcularon todavia
      posY = posY - 1;    //Si suma o resta va a determinar el 0 del sistema.Por defecto resta.. Esto depende de donde queres que arranque
      }
    if(digitalRead(switct_y_top) == LOW)
      stepperY.stop();
      posY = 0;           //Una vez que llego, lo freno y le establezco este punto como el 0 absoluto
      stepperY.setCurrentPosition(0);
      digitalWrite(enableY, HIGH);
    }
  else
  {
  posY = 0;
  stepperY.setCurrentPosition(0);
  digitalWrite(enableY, HIGH);
  }
  //Movimiento de X
  digitalWrite(enableX, LOW);
  if(digitalRead(switch_x_left) == HIGH) 
  {
    while(digitalRead(switch_x_left) == HIGH)
    {
      stepperX.moveTo(posX);    
      stepperX.run();
      //delayMicroseconds(20);  //delay que evita que se trabe el motor y haga ruido, intenta procesar posiciones que no se calcularon todavia
      posX = posX - 1;          
     }
    if(digitalRead(switch_x_left) == LOW)           
      stepperX.stop();    
      posX = 0;     
      stepperX.setCurrentPosition(0);
      digitalWrite(enableX, HIGH);
  }
  else
  {
  posX = 0;
  stepperX.setCurrentPosition(0);
   digitalWrite(enableX, HIGH);
  }
  
  //Serial.println("En Posicion 0-0");
//  centro();
  disableMotors();
  }
