#include <avr/pgmspace.h>
#include <AccelStepper.h>//include the Accel Stepper Library 
#define MAX_ARRAY_LENGTH 32


//Modo manual = 1 hace que se mueva con el teclado, en 0 corre la secuencia de mensajes
#define Manual  1

// Definicion de ambos motores
#define STEP_X 2
#define DIR_X 3
#define STEP_Y 9
#define DIR_Y 8
AccelStepper stepperX(1, STEP_X, DIR_X);     //X axis
AccelStepper stepperY(1, STEP_Y, DIR_Y);     //Y axis   //(driver=true, step, dir)

int enableX = 7;  //Enables de los motores (Cambiar)
int enableY = 12;

//Punteros
long posX = 0; 
long posY = 0;

int switch_x_left = A0;    //Fines de carrera
int switct_y_top = A1;

//No se usan por ahora
//int switch_x_right = A3;
//int switch_y_bottom =A4;
// int bigButton = 12;     //Boton que da inicio a X secuencia

long randomNumber;  //Numero random para disparar mensajes.

//Lista de letras. Usando movewithkeyboard() podes sacarla posicion en pasos de cada letra.
//unsigned int coordinatesTable[39][3] = {
long coordinatesTable[39][3] = {

  100,-10400,'a',
  1600,-9100,'b',
  3300,-8000,'c',
  5300,-7100,'d',
  7100,-5900,'e',
  9100,-5500,'f',
  10900,-5400,'g',
  12800,-5900,'h',
  14700,-6200,'i',
  16800,-6800,'j',
  18600,-7500,'k',
  20300,-8300,'l',
  0,0,'m',
  100,-12400,'n',
  2000,-10900,'o',
  4300,-9800,'p',
  6400,-9100,'q',
  8300,-8200,'r',
  10000,-7500,'s',
  12000,-7300,'t',
  14000,-7500,'u',
  15800,-8100,'v',
  17700,-8900,'w',
  19900,-9800,'x',
  21800,-10600,'y',
  0,0,'z',
  2000,-1500,'0',
  18000,-1500,'1',
  18000,-19700,'2',
  2000,-19700,'3',
  10700, 12900,'4',
  0,0,'5',
  0,0,'6',
  14800,-12400,'8',
  0,0,'9',
  4400,10,'+',//YES
  19900,10,'-',//NO
  0,0,'!',//GOODBYE
  11700,100,'.'//SPACE
};


//------------------------------------------------------------------------------


void setup()
{  
  Serial.begin(115200);     //Serial print para debug, no afecta desempeño de motores, pero cuando este listo apagarlo.
  Serial.flush();
  //pinMode(bigButton, INPUT_PULLUP);     //Pullup evita tener que usar resistencia para el boton de arranque.
  randomSeed(analogRead(0));            //Lee el analog 0 para generar numeros random


  pinMode(STEP_X,OUTPUT);
  pinMode(STEP_Y,OUTPUT);
  pinMode(DIR_X,OUTPUT);
  pinMode(DIR_Y,OUTPUT);
  pinMode(enableX, OUTPUT);
  pinMode(enableY, OUTPUT);
  disableMotors();  //apago los motores al arranque
  
  
////Aceleracion y velocidad de los motores ESTO INFLUYE EN LAS POSICIONES.
//  stepperX.setMaxSpeed(3500.0);
//  stepperX.setAcceleration(6000.0);
//  stepperY.setMaxSpeed(1500.0);
//  stepperY.setAcceleration(2000.0);

    
  stepperX.setMaxSpeed(3500.0);
  stepperX.setAcceleration(5000.0);
  stepperY.setMaxSpeed(2000.0);
  stepperY.setAcceleration(5000.0);

 //Sensores para encontrar el 0
  pinMode(switch_x_left, INPUT_PULLUP); 
  pinMode(switct_y_top, INPUT_PULLUP);
  
//  pinMode(switch_x_right, INPUT_PULLUP); //Sensores extras de los fondos, sin uso por ahora
//  pinMode(switch_y_bottom, INPUT_PULLUP);

  //Find Zero
   homeing();      
}


//------------------------------------------------------------------------------

void loop()
{
//  if(digitalRead(bigButton) == LOW)     //Boton de inicio si fuera necesario
//  {
//   ouijaMessage();     //Selecciona un mensaje de la lsita
//  }

  //Mover con el teclado  W A S D  Para sacar posiciones en pasos.
if (Manual == 1){moveWithKeyboard();}else{ouijaMessage();}

}
//------------------------------------------------------------------------------
void enableMotors()
{
  digitalWrite(enableX, LOW);
  digitalWrite(enableY, LOW);
}
//------------------------------------------------------------------------------
void disableMotors()
{
  digitalWrite(enableX, HIGH);
  digitalWrite(enableY, HIGH);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ouijaDelay(void){delay(200);} //Un delay para que se demore con las letras, asi parece mas real
//------------------------------------------------------------------------------

//Revisa la tabla hasta encontrar el simbolo que coincide
int findSymbolInTable(char symbol){
  int tableIndex;
  
  for(tableIndex = 0; tableIndex <= 39; tableIndex++){
    if(symbol == char(coordinatesTable[tableIndex][2])){
      Serial.print("Char FOUND = ");
      Serial.println(tableIndex);
      return tableIndex;
      delay(200);         //Esto estaria evitando que se trabe el X
    }
  }
     return -1; //if we got to the point
                // we didn't find our value in the table 
}

//------------------------------------------------------------------------------
//Mueve la plancha hasta el proximo simbolo
void moveToSymbol(char character)
{
  int tableIndex = findSymbolInTable(character);

  Serial.print("x = ");
  Serial.println(coordinatesTable[tableIndex][0]);

  Serial.print("y = ");
  Serial.println(coordinatesTable[tableIndex][1]);
  
//MoveMotors
  
  stepperX.moveTo(coordinatesTable[tableIndex][0]);
  stepperY.moveTo(coordinatesTable[tableIndex][1]);
  
// ORIGINAL WHILE 
  while((stepperX.distanceToGo() != 0) || (stepperY.distanceToGo() != 0)){
    Serial.println(stepperX.distanceToGo());
    delayMicroseconds(100);
    stepperY.run();
    delayMicroseconds(100);
    stepperX.run();
    //if(digitalRead(switch_x_right) == LOW || digitalRead(switch_y_bottom) == LOW)
    //homeing();
  }
 
//Ejes por separado
//  while(stepperX.distanceToGo()){ 
//    
//    stepperX.run();
//  }
//    while(stepperY.distanceToGo()){ 
//    
//    stepperY.run();
//  }
  

  return;
}


//------------------------------------------------------------------------------
void ouijaPrint(char* charArray){
  int i;
  for(i = 0; i <= MAX_ARRAY_LENGTH; i++){

    Serial.println("Letra encontrada:");
    Serial.print(charArray[i]); //Debug the array as we move
    Serial.println("");
    if(charArray[i] != 0){
      enableMotors();
      ouijaDelay();
      moveToSymbol(charArray[i]);
      ouijaDelay();
      disableMotors();  
      //if(digitalRead(switch_x_right) == LOW || digitalRead(switch_y_bottom) == LOW)
      //homeing();
    } //Only move if there if valid data, if not let the loop run out.
    else break;
  }
  return;
}
//------------------------------------------------------------------------------
//Stores different messages to be speled out by the Ouija 
void ouijaMessage()
{
    enableMotors();
    randomNumber = random(5);//Generate a random number between 1-5
    //switch (randomNumber) //switch messages based on that random number
    switch (4) //switch messages based on that random number

    {
      case 0:
        {char arrayThing[30] = {'0','1','2','3',0};
        ouijaPrint(arrayThing);
        homeing();}//Go back to home after each massage is printed
        break;
      case 1:
        {
        char arrayThing2[30] = {'3','2','1','0',0};
        ouijaPrint(arrayThing2);
        homeing();}
        break;
      case 2:
        {
        char arrayThing3[30] = {'3','1','0','2',0};;
        ouijaPrint(arrayThing3);
      homeing();}
        break;
      case 3:
        {
        char arrayThing4[30] = {'0','2','1','3',0};;
        ouijaPrint(arrayThing4);
        homeing();}
        break;
      case 4:
        {
        char arrayThing5[30] = {'a','b','c','d','e','f','g','h','i','j','k',0};;
        ouijaPrint(arrayThing5);
      homeing();}
        break;
      default: 
        disableMotors();
     }
    disableMotors();
}
//------------------------------------------------------------------------------
//Funcion para mover el sistema con el teclado. WASD  100 pasos
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
//funcion que busca el 0
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
      delayMicroseconds(200); //delay que evita que se trabe el motor, intenta procesar posiciones que no se calcularon todavia
      posY = posY + 1;    //Este suma, no resta. Si se pone en resta, cambia le 0 por el eje opuesto. Esto depende de donde queres que arranque
      Serial.println(posY);
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
      delayMicroseconds(200); //delay que evita que se trabe el motor, intenta procesar posiciones que no se calcularon todavia
      posX = posX - 1;          
      Serial.println(posX);    
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
  
  Serial.println("En Posicion 0-0");
  disableMotors();
}




