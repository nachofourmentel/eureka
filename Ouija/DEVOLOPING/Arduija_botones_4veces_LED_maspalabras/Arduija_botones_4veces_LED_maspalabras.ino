//-----------------------------------------
//##########  Ouija Eureka  Mayo 2017
//----------------------------------------
//Modo manual = 1 hace que se mueva con el teclado, en 0 corre la secuencia de mensajes
#define Manual  1


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
int switch_y_bottom = A1;

// int bigButton = 12;     //Boton que da inicio a X secuencia

long randomNumber;  //Numero random para disparar mensajes.

//Lista de letras. Usando movewithkeyboard() podes sacarla posicion en pasos de cada letra. 40 Maximo
long coordinatesTable[41][3] = {

  0, 14000, 'a',
  4000, 16000, 'b',
  5900, 18400, 'c',
  10000, 20000, 'd',
  14000, 21000, 'e',
  19000, 23000, 'f',
  21200, 22700, 'g',
  25200, 21700, 'h',
  29700, 21300, 'i',
  32200, 19700, 'j',
  36000, 19000, 'k',
  41200, 17200, 'l',
  42000, 16500, 'm',
  -350, 9400, 'n',
  4000, 11000, 'o',
  6900, 14400, 'p',
  12000, 16000, 'q',
  15000, 17000, 'r',
  19000, 19000, 's',
  23000, 18000, 't',
  26400, 18000, 'u',
  30000, 18000, 'v',
  32200, 15700, 'w',
  35200, 13000, 'x',
  39700, 12200, 'y',
  42000, 11000, 'z',
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
  26000, 5000, '!',      //adios //volver a programar.
  1000, 1000, '.'
};

//------------------------------------------------------------------------------ Hasta aca ouija
//A partir de aca botones

//PIR ACTIVA BOTON/PALANCA
//PALANCA ACTIVA POSIBILIDAD DE APRETAR BOTONES
//AL APRETAR BOTONES EN SECUENCIA CORRECTA SE ABRE UN RELE

//amarllo 1 naranja 2 blsanco 3 rojo 4 marron 5 y 6 (botones)
int ledPin = 1;

//Pir
int inputPin = 22;      //Naranja - Gris Señal . marron - azul gnd - verde - violeta vcc
int pirState = LOW;
int val = 0;
int estado = 0;         //cambiar a cero para probar boton master

//Boton master
const int  botonmaster = 36;        //verde y marron
int botonestado = 0;
int lastbonestado = 0;

//Palanca
const int  buttonPin2 = 23;         //Amarillo y negro de cable bipolar negro y rojo
int buttonState2 = 0;
int lastButtonState2 = 0;

//Cerradura
int cerradura = 14;                 //Cable amarillo - violeta 12.  blanco - azul gnd . naranja - gris vcc

//LED RELE
int led = 37;


//Botones
int contador = 0;
int gano = 0;

int boton0 = 30;
int boton1 = 31;
int boton2 = 32;
int boton3 = 33;
int boton4 = 34;          // Este esta descvonecgtado porque hay un problema con el boton fisico
int boton5 = 35;

int sumador = 0;

int estadoboton;
int contadorWord = 0;

void setup()
{
  //PINES - BOTON MASTER - BOTON IDIOMA
  //pinMode(bigButton, INPUT_PULLUP);     //Pullup evita tener que usar resistencia para el boton de arranque.
  //pinMode(pinIdioma, INPUT_PULLUP);

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
  Serial.begin(115200);

  //Hasta aca OUIJA-------------------------------------------------------------

  
  //A partir de aca botones
  //Boton master
  pinMode(botonmaster, INPUT_PULLUP);


  //Cerradura
  pinMode(cerradura, OUTPUT);

  //Led
  pinMode(led, OUTPUT);


  //Palanca
  //  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);

  //Botones
  pinMode(boton0, INPUT_PULLUP);   // Digital INPUTS
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);
  pinMode(boton3, INPUT_PULLUP);
  pinMode(boton4, INPUT_PULLUP);
  pinMode(boton5, INPUT_PULLUP);



  digitalWrite(cerradura, HIGH);
  digitalWrite(led, HIGH);//APAGA LED

}//End setup

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

  //Princpio state MESA BOTONES
  //LEEMOS LOS BOTONES
  
  int botonval0 = digitalRead(boton0);
  int botonval1 = digitalRead(boton1);
  int botonval2 = digitalRead(boton2);
  int botonval3 = digitalRead(boton3);
  int botonval4 = digitalRead(boton4);
  int botonval5 = digitalRead(boton5);



  //0, 1, 5, 1, 3
  
  //O SEA 1, 2, 6, 2, 4
  int pista1 = botonval0;//Primer pista correcta
  int pista2 = botonval1;//Segunda pista y cuarta pista
  int pista3 = botonval5;//Tercer pista correcta
  int pista5 = botonval3;//Cuarta pista correcta

  int pistano1 = botonval2;
  int pistano2 = botonval4;//Cuarta pista correcta

  //Boton master
  //SI SE ACTIVA EL BOTON MASTER...
  
  botonestado = digitalRead(botonmaster);

  if (botonestado != lastbonestado) {
    if (botonestado == HIGH) {

    } else {
      //Apretado1
      //Serial.println("on");
      //Manda un valor al MAX
      Serial.println(75);
      digitalWrite(led, HIGH);

      delay(6000);
      contador = 0;
      // Serial.println("estado 1");
      estado = 1;

    }
    delay(50);
  }
  lastbonestado = botonestado;

  //End boton master


  switch (estado) {
    case 1:

      digitalWrite(cerradura, HIGH);        //Cierra la cerradura cuando apreta el boton master
      //  digitalWrite(led, HIGH);

      //Pir
      val = digitalRead(inputPin);  // read input value
      if (val == HIGH) {            // check if the input is HIGH
        digitalWrite(ledPin, HIGH);  // turn LED ON
        if (pirState == LOW) {
          // we have just turned on

          Serial.println(99);
          // We only want to print on the output change, not state
          pirState = HIGH;
          estado = 2;
        }
      } else {
        digitalWrite(ledPin, LOW); // turn LED OFF
        if (pirState == HIGH) {
          // we have just turned of
          // Serial.println(0);
          // We only want to print on the output change, not state
          pirState = LOW;
        }
      }


      break;

    case 2:
      //digitalWrite(led, HIGH);
      //Palanca
      buttonState2 = digitalRead(buttonPin2);

      if (buttonState2 == HIGH) {
        // Serial.println(75);
        //delay(1000);
        //   estado = 3;
        digitalWrite(led , LOW);

        //Botones
        //Pista 1
        if (pista1 == LOW && contador == 0) {
          contador = 1;
        }
        else if (pista1 == LOW && contador != 0) {
          contador = 1;
        }

        //Pista 2 y 4
        if (pista2 == LOW && contador == 1 ) {
          contador += 3;
          sumador = 0;
        } else if (pista2 == LOW && contador == 10) { //o 10 en vez de 20

          contador += 15;
          sumador = 0;
        }

        //else if (pista2 == LOW && contador != 1 || pista2 == LOW && contador != 4 || pista2 == LOW && contador != 20) {
        else if (pista2 == LOW && contador != 4 && pista2 == LOW && contador != 25 ) {
          contador = 0;
          sumador += 1;
        }

        //Pista 3
        if (pista3 == LOW && contador == 4 ) {
          contador += 6;
          sumador = 0;
        }
        else  if (pista3 == LOW && contador != 10) {
          contador = 0;
          sumador += 1;

        }

        //Pista 5
        if (pista5 == LOW && contador == 25) {
          contador += 15;
          sumador = 0;
        }
        else  if (pista5 == LOW && contador != 40 ) {
          contador = 0;
          sumador += 1;
        }

        //Aca van las TECLAS que NO son una pista. Que resetean el contador / secuencia
        if (botonval2 == LOW || botonval4 == LOW ) {
          contador = 0;
          sumador += 1;

        }

        if (contador == 40 ) { //El numero es 20 por logica de la secuencia de numeros triangular
          Serial.println(100);
          estadoboton = 10;
          estado = 4;
          // delay(20000);
          // digitalWrite(cerradura, LOW);
          // delay(1000);
          //digitalWrite(cerradura, HIGH);
          // delay(1000);
          // contador = 0;
          //estado = 0;
        }

        if (sumador == 2500) { //Este numero es hasta cambiar la lectura de los bostones por lastbutton etc
          estadoboton = contadorWord;
          estado = 4;
        }
        Serial.println(contador);
        //  Serial.println(sumador);

      } else {
        digitalWrite(led , HIGH);

      }
      // if (buttonState2 != lastButtonState2) {
      // if (buttonState2 == LOW) {
      // estado = 2;

      //} else {
      //Apretado1
      // Serial.println("Baja");
      //Serial.println(75);
      //delay(1000);
      //estado = 3;
      // }
      //delay(50);
      //}
      // lastButtonState2 = buttonState2;
      break;

    case 3:

      estado = 2;




      break;// este estado esta al pedo hay que sacarlo

    case 4: //Movimiento OUIJA

      //Principio mensajes ouija
      // estadoboton = 2;
      enableMotors();
      // randomNumber = random(7); //no le des bola

      switch (estadoboton) //aca va la variable
      {

        case 0:
          {
            char arrayThing3[30] = {'f', 'u', 'e', 'r', 'a', '.', 0};;
            ouijaPrint(arrayThing3);
            homeing();
            sumador = 0;
            contadorWord += 1;
            estado = 2;


          }
          break;

        case 1:
          {
            char arrayThing3[30] = {'h', 'u', 'y', 'a', 'n', '.', 0};;
            ouijaPrint(arrayThing3);
            homeing();
            sumador = 0;
            contadorWord += 1;
            estadoboton = 0;
            estado = 2;


          }
          break;
        case 2:
          {
            char arrayThing3[30] = {'h', 'e', 'l', 'p', '.', 0};;
            ouijaPrint(arrayThing3);
            homeing();
            sumador = 0;
            contadorWord += 1;
            estadoboton = 0;
            estado = 2;


          }
          break;
        case 3:
          {
            char arrayThing3[30] = {'d', 'i', 'a', 'b', 'l', 'o', '.', 0};;
            ouijaPrint(arrayThing3);
            homeing();
            sumador = 0;
            contadorWord += 1;
            estadoboton = 0;
            estado = 2;


          }
          break;

        case 4:
          {
            char arrayThing3[30] = {'c', 'u', 'i', 'd', 'a', 'd', 'o', '.', 0};;
            ouijaPrint(arrayThing3);
            homeing();
            sumador = 0;
            contadorWord += 1;
            estadoboton = 0;
            estado = 2;

          }
          break;
        case 5:
          {
            char arrayThing3[30] = {'y', 'a', 'v', 'i', 'e', 'n', 'e', 'n', '.', 0};;
            ouijaPrint(arrayThing3);
            homeing();
            sumador = 0;
            contadorWord += 1;
            estadoboton = 0;
            estado = 2;

          }
          break;
        case 6:
          {
            char arrayThing3[30] = {'e', 's', 't', 'a', 'n', 'a', 'q', 'u','i', '.', 0};;
            ouijaPrint(arrayThing3);
            homeing();
            sumador = 0;
            contadorWord = 0;
            estadoboton = 0;
            estado = 2;

          }
          break;
        case 10:
          {
            char arrayThing3[30] = {'!', '.', 0};;
            ouijaPrint(arrayThing3);
            digitalWrite(cerradura, LOW);
            digitalWrite(led, HIGH);//APAGA LED
            contadorWord = 0;
            homeing();
            delay(1000);
            //digitalWrite(cerradura, HIGH);
            delay(1000);

            estado = 0;
            contador = 0;
            sumador = 0;
          }
          break;

        ////////////////////////////////////////////////////////////////////
        //Asi se construyen frases.
        //
        case 11:
          {
            char arrayThing10[30] = {'f', 'u', 'e', 'r', 'a', 0};;
            char arrayThing11[30] = {'d', 'e', 0};;
            char arrayThing12[30] = {'a', 'q', 'u', 'i', '.', 0};;
            ouijaPrint(arrayThing10);
            delay(TiempoEntrePalabras);
            ouijaPrint(arrayThing11);
            delay(TiempoEntrePalabras);
            ouijaPrint(arrayThing12);
            homeing();
          }
          break;
        default:
          disableMotors();
      }
      disableMotors();

      //Fin mensajes ouija

      break;


  }//End estado




  //End mesa-------------------------------------------------------------------------------------------------
  //MODO PROGRAMACION DE POSICIONES:  Mover con el teclado  W A S D  Para sacar posiciones en pasos.
  if (Manual == 1) {
    moveWithKeyboard();
  } else {
    //   ouijaMessage();
  }
}//End loop
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
void ouijaDelay(void) {
  delay(200); //Un delay para que se demore con las letras, asi da el efecto fantasmal.
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
      //Serial.println("Freno de EMERGENCIA");
      homeing();
    }
  }
  return;
}

//------------------------------------------------------------------------------
void ouijaPrint(char* charArray) {
  int i;
  for (i = 0; i <= MAX_ARRAY_LENGTH; i++) {
    //  Serial.println("Letra encontrada:");
    // Serial.print(charArray[i]);
    // Serial.println("");
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

