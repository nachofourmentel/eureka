#include <avr/pgmspace.h>
#include <AccelStepper.h>    
#define MAX_ARRAY_LENGTH 32

//-----------------------------------------
//##########Ouija Eureka 2017
//----------------------------------------

//Modo manual = 1 hace que se mueva con el teclado, en 0 corre la secuencia de mensajes
#define Manual  1

//Elegir un mensaje de la lista
#define MensajeNro 0
#define TiempoEntrePalabras 1000

/* Lista de Mensajes...
0 - hola / hello
1 - vayanse
2 - fuera
3 -  cuidado
4 - eureka
5 - 
6 - Frase : Fuera de aqui

*/

// Definicion de ambos motores
#define STEP_X 2
#define DIR_X 3
#define STEP_Y 9
#define DIR_Y 8

//Tipo de pasos del motor.
#define MS1_Y 4
#define MS1_X 5

AccelStepper stepperX(1, STEP_X, DIR_X);     //X axis
AccelStepper stepperY(1, STEP_Y, DIR_Y);     //Y axis   //(driver=true, step, dir)

int enableX = 7;  //Enables de los motores (Cambiar)
int enableY = 12;

//Punteros
long posX = 0; 
long posY = 0;

int switch_x_left = A0;    //Fines de carrera
int switct_y_top = A2;    //antes era a1

//No se usan por ahora
int switch_x_right = A3;
int switch_y_bottom =A1;

// int bigButton = 12;     //Boton que da inicio a X secuencia

long randomNumber;  //Numero random para disparar mensajes.

//Lista de letras. Usando movewithkeyboard() podes sacarla posicion en pasos de cada letra. 40 Maximo
long coordinatesTable[41][3] = {
  
  -50,20400,'a',
  2700,21000,'b',
  6100,23000,'c',
  8000,24400,'d',
  13800,26400,'e',
  18000,27300,'f',
  21300,28500,'g',
  25300,27500,'h',
  29600,26500,'i',
  33600,26500,'j',
  36600,24500,'k',
  40600,23500,'l',     
  42300,20500,'m',            
  -50,16000,'n',
  3100,18000,'o',
  7400,19200,'p',
  10800,20400,'q',
  15000,23300,'r',
  18300,23500,'s',
  21300,24500,'t',
  25300,23500,'u',
  28600,23500,'v',
  32600,21500,'w',
  35600,20500,'x',
  39400,18500,'y',
  42600,16500,'z',            
  35600,13500,'0',  
  7600,13500,'1',
  10600,13500,'2',
  13600,13500,'3',
  16600,13500,'4',
  19600,13500,'5',
  22600,13500,'6',
  25600,13500,'7',
  28600,13500,'8',
  32600,13500,'9',
  5000,35300,'+',          //si
  42000,35300,'-',         //no
  22500,10500,'!',        //adios
  1000,1000,'.'
 };

//------------------------------------------------------------------------------

void setup()
{  
 //pinMode(bigButton, INPUT_PULLUP);     //Pullup evita tener que usar resistencia para el boton de arranque.
  randomSeed(analogRead(0));            //Lee el analog 0 para generar numeros random
  pinMode(STEP_X,OUTPUT);
  pinMode(STEP_Y,OUTPUT);
  pinMode(DIR_X,OUTPUT);
  pinMode(DIR_Y,OUTPUT);
  pinMode(enableX, OUTPUT);
  pinMode(enableY, OUTPUT);
  //Lo coloco en modo half step, asi no se saltea pasos el driver.
  pinMode(MS1_Y,OUTPUT);
  pinMode(MS1_X,OUTPUT);
  digitalWrite(MS1_X,HIGH);
  digitalWrite(MS1_Y,HIGH);
  disableMotors();  //apago los motores al arranque
////Aceleracion y velocidad de los motores ESTO INFLUYE EN LAS POSICIONES.
  stepperX.setMaxSpeed(20000.0);
  stepperX.setAcceleration(5000);
//  stepperY.setMaxSpeed(20000.0);
//  stepperY.setAcceleration(5000);

  stepperY.setMaxSpeed(18000.0);
  stepperY.setAcceleration(4000);

  //Sensores para encontrar el 0
  pinMode(switch_x_left, INPUT_PULLUP); 
  pinMode(switct_y_top, INPUT_PULLUP);
  pinMode(switch_x_right, INPUT_PULLUP); //Sensores extras de los fondos, sin uso por ahora
  pinMode(switch_y_bottom, INPUT_PULLUP);

  //Find Zero
  homeing();   
  //Cuando este funcionando sin la PC conviene desactivarlo.
  Serial.begin(115200);
}

//------------------------------------------------------------------------------

void loop()
{
//  if(digitalRead(SWITCH DE IDIOMA HIGH) == LOW)     //SECUENCIA DE BOTONES
//  {
//   ouijaMessage();     //Selecciona un mensaje random de la lista
//  }
//else{adios();}
//

//PROGRAMACION DE POSICIONES:  Mover con el teclado  W A S D  Para sacar posiciones en pasos.
if (Manual == 1){moveWithKeyboard();} else {ouijaMessage();}
}
//------------------------------------------------------------------------------
void enableMotors()
{
  digitalWrite(enableX, LOW);
  digitalWrite(enableY, LOW);
}
void disableMotors()
{
  digitalWrite(enableX, HIGH);
  digitalWrite(enableY, HIGH);
}
//------------------------------------------------------------------------------
void ouijaDelay(void){delay(200);}    //Un delay para que se demore con las letras, asi da el efecto fantasmal.
//------------------------------------------------------------------------------

//Revisa la tabla hasta encontrar el simbolo que coincide
int findSymbolInTable(char symbol){
  int tableIndex;
  
  for(tableIndex = 0; tableIndex <= 39; tableIndex++){
    if(symbol == char(coordinatesTable[tableIndex][2])){
      return tableIndex;
    }
  }
     return -1;
}

//------------------------------------------------------------------------------
//Mueve la plancha hasta el proximo simbolo
void moveToSymbol(char character)
{
  int tableIndex = findSymbolInTable(character);
  stepperX.moveTo(coordinatesTable[tableIndex][0]);
  delayMicroseconds(20);
  stepperY.moveTo(coordinatesTable[tableIndex][1]);
  delayMicroseconds(20);
  
  while((stepperX.distanceToGo() != 0) || (stepperY.distanceToGo() != 0)){
    stepperY.run();
    stepperX.run();
    //Fines de carrera de protección || Cuando esta buscando las letras y toca alguno de esos sensores extremos, se vuelve a la posicion de 0. Y habria que reiniciarlo.
    if(digitalRead(switch_x_right) == LOW || digitalRead(switch_y_bottom) == LOW){ 
      disableMotors();
      stepperY.setCurrentPosition(0);
      stepperX.setCurrentPosition(0);
      delay(2000);
      homeing();
      }
  }
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
      }
    else break;
  }
  return;
}
//-----------------ADIOS
void adios() {
  enableMotors();
  moveToSymbol('!');
  homeing();
  disableMotors();
  }

//------------------------------------------------------------------------------
//Lista de mensajes que pueden ser enviados por la Ouija 
void ouijaMessage()
{
    enableMotors();
    randomNumber = random(6); //Genera numero random del 1-6 (poner en relaciona a los cases)
    //switch (randomNumber) para que sea aleatorio. Sino MensajeNro
    //Elije el mensaje que seleccionamos al principio del sketch. El simbolo "." hace referencia al 0.0, conviene siempre ponerlo al final del mensaje asi vuelve rapido a la posicion de 0.0
    switch (5)
     {
      case 0:
        {char arrayThing[30] = {'h','o','l','a','.',0};
        ouijaPrint(arrayThing);
        homeing();}
        break;
         case 1:
        {
        char arrayThing2[30] = {'v','a','y','a','n','s','e','.',0};
        ouijaPrint(arrayThing2);
        homeing();}
        break;
         case 2:
        {
        char arrayThing3[30] = {'f','u','e','r','a','.',0};;
        ouijaPrint(arrayThing3);
      homeing();}
        break;
      case 3:
        {
        char arrayThing4[30] = {'c','u','i','d','a','d','o','.',0};;
        ouijaPrint(arrayThing4);
        homeing();}
        break;
      case 4:
        {
        char arrayThing5[30] = {'e','u','r','e','k','a','.',0};;
        ouijaPrint(arrayThing5);
      homeing();}
        break;
      case 5:
        {
        char arrayThing6[30] = {'m','a','.',0};;
        ouijaPrint(arrayThing6);
      homeing();}
        break;
        //Asi se construyen frases.
        case 6:
        {
        char arrayThing10[30] = {'f','u','e','r','a',0};;
        char arrayThing11[30] = {'d','e',0};;
        char arrayThing12[30] = {'a','q','u','i','.',0};;        
        ouijaPrint(arrayThing10);
        delay(TiempoEntrePalabras);
        ouijaPrint(arrayThing11);
        delay(TiempoEntrePalabras);
        ouijaPrint(arrayThing12);
        homeing();        }
        break;     
        default: 
        disableMotors();
     }
    disableMotors();
}
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
//----------------------------------------------------------
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
  
  Serial.println("En Posicion 0-0");
  disableMotors();
}
