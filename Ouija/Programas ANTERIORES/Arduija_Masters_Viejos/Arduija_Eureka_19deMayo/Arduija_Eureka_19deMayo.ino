//-----------------------------------------
//##########  Ouija Eureka  Mayo 2017
//----------------------------------------
//Modo manual = 1 hace que se mueva con el teclado, en 0 corre la secuencia de mensajes
#define Manual  0


#include <avr/pgmspace.h>
#include <AccelStepper.h>    
#define MAX_ARRAY_LENGTH 41

//Elegir un mensaje de la lista
#define MensajeNro 0 //NO SE USA

#define TiempoEntrePalabras 1000  //Tiempo entre palabra de cada frase.

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

//Idioma Default: Español
int idioma = 0;

//Punteros
long posX = 0; 
long posY = 0;

//Fines de carrera // IDENTIFICAR.
int switch_x_left = A0;    
int switct_y_top = A2;    
int switch_x_right = A3;
int switch_y_bottom =A1;

// int bigButton = 12;     //Boton que da inicio a X secuencia

long randomNumber;  //Numero random para disparar mensajes.

//Lista de letras. Usando movewithkeyboard() podes sacarla posicion en pasos de cada letra. 40 Maximo
long coordinatesTable[41][3] = {
  
  -350,15000,'a',
  2000,16400,'b',
  5900,18400,'c',
  9200,19700,'d',
  13200,21700,'e',
  17200,21700,'f',
  21200,22700,'g',
  25200,21700,'h',
  29200,21700,'i',
  32200,19700,'j',
  36000,19000,'k',
  40000,17000,'l',     
  42000,16500,'m',            
  -350,9400,'n',
  3000,12400,'o',
  6900,14400,'p',
  10200,15700,'q',
  14200,17700,'r',
  21200,18700,'s',
  21200,18700,'t',
  25200,17700,'u',
  28200,17700,'v',
  32200,15700,'w',
  35200,13000,'x',
  38700,12600,'y',
  42000,11000,'z',            
  35600,5500,'0',  
  7600,4000,'1',
  10600,4000,'2',
  13600,4000,'3',
  16600,4000,'4',
  19600,4000,'5',
  22600,4000,'6',
  25600,4000,'7',
  28600,4000,'8',
  32600,4000,'9',
  5000,35300,'+',          //si //dibujo del diablo.
  42000,35300,'-',         //no
  22500,10500,'!',        //adios //volver a programar.
  1000,1000,'.'
 };

//------------------------------------------------------------------------------

void setup()
{  
  //PINES - BOTON MASTER - BOTON IDIOMA
  //pinMode(bigButton, INPUT_PULLUP);     //Pullup evita tener que usar resistencia para el boton de arranque.
  //pinMode(pinIdioma, INPUT_PULLUP);
  
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

  //Aceleracion y velocidad de los motores ESTO INFLUYE EN LAS POSICIONES. No modificar.
  // Velocidades ORIGINALES.
/*
  stepperX.setMaxSpeed(20000.0);
  stepperX.setAcceleration(5000);
  stepperY.setMaxSpeed(18000.0);
  stepperY.setAcceleration(4000);

*/
  // Velocidades ACTUALES.
  stepperX.setMaxSpeed(10000.0);
  stepperX.setAcceleration(9000);
  stepperY.setMaxSpeed(10000.0);
  stepperY.setAcceleration(8000);

  //Sensores para encontrar el 0
  pinMode(switch_x_left, INPUT_PULLUP); 
  pinMode(switct_y_top, INPUT_PULLUP);
  pinMode(switch_x_right, INPUT_PULLUP); 
  pinMode(switch_y_bottom, INPUT_PULLUP);

  //BUSCA LA POSICION 0-0
  homeing();   
  //Cuando este funcionando sin la PC conviene desactivarlo.
  Serial.begin(115200);
}

//------------------------------------------------------------------------------

void loop()
{
/* // Modo switch de idiomas.
if (PALANCA){todo aca adentro.}
idioma = digitalRead(pinIdioma);
if( SECUENCIA DE BOTONES CORRECTA){

if(idioma == 0){ouijaMessage();} else if (idioma == 1){ ouijaMessageEnglish();}
}
else
{ adios();}

*/
//-------------------------------------------------------------------------------------------------
//MODO PROGRAMACION DE POSICIONES:  Mover con el teclado  W A S D  Para sacar posiciones en pasos.
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
      //Serial.println("Freno de EMERGENCIA");
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
    Serial.print(charArray[i]); 
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
//----------------- CENTRO
void centro() {
  enableMotors();
  moveToSymbol('+');
}

