//-----------------------------------------
// Ouija Eureka  OCTUBRE 2017
// SON 2 ARDUINOS,  ARDUINO MEGA -> OUIJA  ARDUINO UNO -> LECTURA DE BOTONES.
//----------------------------------------
/*
 * Ouija Eureka Octubre 2017
  Sketch encargado de la lectura de la secuencia de botones.
  La Ouija va a estar mandando mensajes random, hasta que se interrumpa.
  Cuando las pistas se ejecutan correctamente, envia un HIGH al arduino con el sketch de la Ouija.
*/

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

// NO SE PORQUE TIENEN LA LOGICA INVERTIDA. LOW son cambios, HIGH, es 0
int enableX = 7;  //Enables de los motores (Cambiar)
int enableY = 12;

// INPUT QUE AL RECIBIR HIGH INTERRUMPE SECUENCIAS DE MOVIMIENTO

const int enableOuija = 36; //Corresponde al pin 12 del arduino uno
const int ouijaRecibe = 38; //Corresponde al pin 13 del arduino uno.

// INPUT DE BOTON MASTER
const int botonMaster = 40;

//Estado de arranque
int botonestado = 0;
int lastbonestado = 0;
int estado = 0;

//Idioma Default: Español
//int idioma = 0;

//Punteros
long posX = 0;
long posY = 0;

//Fines de carrera // IDENTIFICAR.
int switch_x_left = A0;
int switct_y_top = A2;
int switch_x_right = A3;
int switch_y_bottom = A1;

long randomNumber;  //Numero random para disparar mensajes.

//Lista de letras. Usando movewithkeyboard() podes sacarla posicion en pasos de cada letra. 40 Maximo
long coordinatesTable[41][3] = {

 -900, 129000, 'a',
  100, 16000, 'b',
  2100, 17900, 'c',
  6100, 19900, 'd',
  11000, 21000, 'e',
  15000, 22000, 'f',
  19000, 23000, 'g',
  23000, 23000, 'h',
  27000, 22000, 'i',
  30000, 20000, 'j',
  34000, 19000, 'k',
  38000, 18000, 'l',
  41000, 16000, 'm',
  -350, 10000, 'n',
  2000, 12000, 'o',
  6000, 15000, 'p',
  9000, 16000, 'q',
  13000, 17000, 'r',
  16000, 19000, 's',
  20000, 18000, 't',
  24000, 19000, 'u',
  26000, 17000, 'v',
  30000, 17000, 'w',
  34000, 15000, 'x',
  37000, 13000, 'y',
  40000, 11000, 'z',
  35600, 5500, '0',
  7600, 4000, '1',
  10600, 4000, '2',
  13600, 4000, '3',
  16600, 4000, '4',
  19600, 4000, '5',
  22600, 4000, '6',
  25600, 4000, '7',
  28600, 4000, '8',
  32600, 4000, '9',
  5000, 35300, '+',        //si //dibujo del diablo.
  42000, 35300, '-',       //no
  21500, 3800, '!',      //adios //volver a programar.
  100, 100, '.'
};


void setup()
{
  //PINES - BOTON MASTER - BOTON IDIOMA
  pinMode(enableOuija,INPUT);
  pinMode(ouijaRecibe, INPUT);
  pinMode(botonMaster, INPUT_PULLUP);

  pinMode(STEP_X, OUTPUT);
  pinMode(STEP_Y, OUTPUT);
  pinMode(DIR_X, OUTPUT);
  pinMode(DIR_Y, OUTPUT);
  pinMode(enableX, OUTPUT);
  pinMode(enableY, OUTPUT);

  //Lo coloco en modo half step, asi no se saltea pasos el driver.
  pinMode(MS1_Y, OUTPUT);
  pinMode(MS1_X, OUTPUT);
  digitalWrite(MS1_X, HIGH);
  digitalWrite(MS1_Y, HIGH);
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
  //Serial.begin(115200);
  // Delay para que la Arduija empieze despues que el arduino Uno
  delay(2000);

}

//------------------------
// ACA COMIENZA EL LOOP
//-----------------------
void loop()
{
  //PROGRAMACION DE POSICIONES:  Mover con el teclado  W A S D  Para sacar posiciones en pasos.
  //if (Manual == 1) { moveWithKeyboard();  }
  // Debugin 36 enable 38 Adios
  /*
     Serial.print("PIn 36 ENABLE    ");
     Serial.print("");
     Serial.println(digitalRead(enableOuija));

    
     Serial.print("PIn 38 ADIOS    ");
     Serial.print("");
     Serial.println(digitalRead(ouijaRecibe));
  
 */
  // ACA TAMBIEN LEEMOS EL BOTON MASTER - PIN 40
  botonestado = digitalRead(botonMaster);
  Serial.println(digitalRead(botonMaster));
  
  if (botonestado != lastbonestado) {
    if (botonestado == HIGH) {
    } else {
      //Master apretado
    Serial.println("MASTER DETECTADO");
Serial.print("- MOVIENDOME A ESTADO 1");
      delay(5000);
      estado = 1;
    }
    delay(50);
  }
  lastbonestado = botonestado;

  switch (estado) {

    case 0:
    // ACA TAMBIEN LEEMOS EL BOTON MASTER - PIN 40
  botonestado = digitalRead(botonMaster);
  Serial.println(digitalRead(botonMaster));
  
  if (botonestado != lastbonestado) {
    if (botonestado == HIGH) {
    } else {
      //Master apretado
    Serial.println("MASTER DETECTADO");
Serial.print("- MOVIENDOME A ESTADO 1");
      delay(5000);
      estado = 1;
    }
    delay(50);
  }
  lastbonestado = botonestado;
    break;
    case 1:
      Serial.println("EN ESTADO 1 - ESPERANDO PALANCA");
      if (digitalRead(enableOuija) == 0 ) {
        //Mensajes Aleatorios
        Serial.println("ESTA LLEGANDO EL 0, ME MUEVO.");
        
        //Tener en cuenta que esto funciona con for, por ende traba el codigo.
        ouijaMessage();
      }
      /* // PINIDIOMA
      if (digitalRead(pinIdioma) == 0) {ouijaMessage(); else { ouijaMessageEnglish();} */
      else  if (digitalRead(enableOuija) == 1 ) {
       Serial.println(" APAGADO - DISABLEMOTORS ");
        homeing();
        disableMotors();
        delay(50);
      }
      break;

    case 2:
      Serial.println("EN ESTADO 2  - REPOSO STAND BY");
      //Modo de reposo Stand-By
      //Entramos despues de recibir un Adios();
      homeing();
      disableMotors();
      delay(1000);
      break;

//    default:
//      Serial.println("EN ESTADO DEFAULT");
//      homeing();
//      disableMotors();
//      delay(1000);
//      break;
  }


}
//------------------------------------------------------------------------------
void enableMotors() {
  digitalWrite(enableX, LOW);
  digitalWrite(enableY, LOW);
}
void disableMotors() {
  digitalWrite(enableX, HIGH);
  digitalWrite(enableY, HIGH);
}
//------------------------------------------------------------------------------
void ouijaDelay(void) {
  delay(200);
}
//------------------------------------------------------------------------------
//Revisa la tabla hasta encontrar el simbolo que coincide
int findSymbolInTable(char symbol) {
  int tableIndex;

  for (tableIndex = 0; tableIndex <= 39; tableIndex++) {
    if (symbol == char(coordinatesTable[tableIndex][2])) {
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

  while ((stepperX.distanceToGo() != 0) || (stepperY.distanceToGo() != 0)) {
    stepperY.run();
    stepperX.run();
    //Fines de carrera de protección || Cuando esta buscando las letras y toca alguno de esos sensores extremos, se vuelve a la posicion de 0. Y habria que reiniciarlo.
    if (digitalRead(switch_x_right) == LOW || digitalRead(switch_y_bottom) == LOW) {
      disableMotors();
      stepperY.setCurrentPosition(0);
      stepperX.setCurrentPosition(0);
      delay(2000);
      Serial.println("Freno de EMERGENCIA");
      homeing();
    }
    if (digitalRead(ouijaRecibe) == 0) {
      disableMotors();
      stepperY.setCurrentPosition(0);
      stepperX.setCurrentPosition(0);
      delay(1000);
      Serial.println("RECIBI INFORMACION");
      homeing();
      adios();
      Serial.println("ADIOS TERMINADO - ENTRANDO EN ESTADO 2" );
      estado = 2;
     }
  }
  return;
}

//------------------------------------------------------------------------------
void ouijaPrint(char* charArray) {
  int i;
  for (i = 0; i <= MAX_ARRAY_LENGTH; i++) {
      Serial.println("Letra encontrada:");
     Serial.print(charArray[i]);
     Serial.println("");
    if (charArray[i] != 0) {
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
  //delay(20000);
  enableMotors();
  moveToSymbol('.');
  moveToSymbol('!');
  homeing();
  disableMotors();
  estado = 2;
}

//----------------- CENTRO
void centro() {
  enableMotors();
  moveToSymbol('+');
  disableMotors();
}

