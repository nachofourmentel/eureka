/*
  Sketch encargado de la lectura de la secuencia de botones.
  La Ouija va a estar mandando mensajes random, hasta que se interrumpa.
  Cuando las pistas se ejecutan correctamente, envia un HIGH al arduino con el sketch de la Ouija.
*/

/* CHECKEAR QUE ES EL TEMA DE LOS LEDS,  HAY UN ERROR, ESTAN AMBOS CON EL MISMOPIN -GLITCH */

//PIR ACTIVA BOTON/PALANCA
//PALANCA ACTIVA POSIBILIDAD DE APRETAR BOTONES
//AL APRETAR BOTONES EN SECUENCIA CORRECTA SE ABRE UN RELEd

int enableOuija = 12;  //va con 36
int ouijaRecibe = 13;   //va con 38

//amarllo 1 naranja 2 blsanco 3 rojo 4 marron 5 y 6 (botones)
//Tiene que tener un pin diferente a 9 por eso glitchea

//LED RELE
int led = 9; //37;

//Pir
int inputPin = 8; //22;      //Naranja - Gris Señal . marron - azul gnd - verde - violeta vcc
int pirState = LOW;
int val = 0;
int estado = 0;         //cambiar a cero para probar boton master

//Boton master
const int  botonmaster = 10; //36;        //verde y marron
int botonestado = 0;
int lastbonestado = 0;

//Palanca
const int  buttonPin2 = 7; //23;         //Amarillo y negro de cable bipolar negro y rojo
int buttonState2 = 0;
int lastButtonState2 = 0;

//Cerradura
int cerradura = 6;  //14;                 //Cable amarillo - violeta 12.  blanco - azul gnd . naranja - gris vcc



//Botones
int contador = 0;
int gano = 0;

int boton0 = 0; //30;
int boton1 = 11; //31;
int boton2 = 2; //32;
int boton3 = 3; //33;
int boton4 = 4; //34;   se rompio cable  // Este esta descvonecgtado porque hay un problema con el boton fisico
int boton5 = 5; //35;

int sumador = 0;

int estadoboton;
int contadorWord = 0;

void setup()
{
  //Serial - Dejar solo los print de numeros para el Max7
  Serial.begin(115200);
  // Salida al otro arduino.
  pinMode(ouijaRecibe, OUTPUT);
  pinMode(enableOuija, OUTPUT);

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

  pinMode(inputPin, INPUT);

  //Botones
  pinMode(boton0, INPUT_PULLUP);   // Digital INPUTS
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);
  pinMode(boton3, INPUT_PULLUP);
  pinMode(boton4, INPUT_PULLUP);
  pinMode(boton5, INPUT_PULLUP);

  digitalWrite(cerradura, HIGH);
  digitalWrite(led, HIGH);          //APAGA LED
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);



}//End setup

//-----------------------

void loop() {
  //Princpio state MESA BOTONES
  //LEEMOS LOS BOTONES

  int botonval0 = digitalRead(boton0);
  int botonval1 = digitalRead(boton1);
  int botonval2 = digitalRead(boton2);
  int botonval3 = digitalRead(boton3);
  int botonval4 = digitalRead(boton4);
  int botonval5 = digitalRead(boton5);
  /*
       // Debug de botones
      if (botonval0 == LOW) {Serial.println("Boton 0");}
      if (botonval1 == LOW) {Serial.println("Boton 1!!!!!!!!!!");}
      if (botonval3 == LOW) {Serial.println("Boton 3");}
      if (botonval4 == LOW) {Serial.println("Boton 4");}
      if (botonval5 == LOW) {Serial.println("Boton 5");}
  */
  // SECUENCIA DE BOTONES. PARA ABRIR LA PUERTA.
  //0, 1, 5, 1, 3

  //O SEA 1, 2, 6, 2, 4
  int pista1 = botonval0;//Primer pista correcta
  int pista2 = botonval1;//Segunda pista y cuarta pista
  int pista3 = botonval5;//Tercer pista correcta
  int pista5 = botonval3;//Cuarta pista correcta

  int pistano1 = botonval2;
  int pistano2 = botonval4;//Cuarta pista correcta


  //Boton master (El boton rojo de la puerta)
  //SI SE ACTIVA EL BOTON MASTER... Booteamos.
  botonestado = digitalRead(botonmaster);

  if (botonestado != lastbonestado) {
    if (botonestado == HIGH) {

    } else {

      //Apretado1
      //Serial.println("MASTER DETECTADO");
      //Manda un valor al MAX y corre un video X
      Serial.println(75);
      //ACA HAY ALGO RARO.
      delay(5000);
      contador = 0;
      //Serial.println("estado 1");
      estado = 1;

    }
    delay(50);
  }
  lastbonestado = botonestado;

  //SELECTOR DE ESTADOOS
  // ESTADO UNO INICIALIZA LA CERRADURA
  // ESTADO DOS LEE BOTONES Y EJECUTA LA OUIJA
  switch (estado) {


    case 1:

      //Cierra la cerradura  de la puerta del exorcista cuando apreta el boton master
      //digitalWrite(cerradura, HIGH);
      //que corno es led ?
      digitalWrite(led, HIGH);

      //Pir
      val = digitalRead(inputPin);  // Leemos el PIR
      if (val == HIGH) {
        //digitalWrite(ledPin, HIGH);  // Prendia un led por el rele al pedo
        if (pirState == LOW) {
          //Entra alguien a la sala y ejecutamos video X 2
          Serial.println(99);
          pirState = HIGH;
          // EL PIR DETECTA LA PRESENCIA, ENTRAMOS AL ESTADO 2.
          estado = 2;
          // Serial.println("PIR FUNCIONANDO- ESTADO 2");
        }
      } else {
        //digitalWrite(ledPin, LOW); // turn LED OFF
        if (pirState == HIGH) {
          // we have just turned of
          // Serial.println(0);
          // We only want to print on the output change, not state
          pirState = LOW;
        }
      }


      break;


    case 2:

      //LEEMOS la Palanca. Si alguien la baja...
      delay(2000);
      buttonState2 = digitalRead(buttonPin2);
      if (buttonState2 == 1) {
        //Serial.println("PALANCA");
        //Serial.println(75);
        //delay(1000);
        //estado = 3;
        //Ahora si prendemos le led de la tabla.
        digitalWrite(led , LOW);
        //Habilitamos la Ouija, esto esta funcionando.
        //En el otro codigo, habilita entrar al modo OuijaMessage, Sino deberia quedarse en el molde.
        //Serial.println("OUIJA HABILITADA");
        digitalWrite(12, LOW);

        //Seccion de lectura de Botones
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

        //Secuencia de botones correcta  0-1-5-1-3
        if (contador == 40 ) {
          //Ejecutamos un video X
          Serial.println(100);
          //Frenamos la Ouija
          delay(1000);
          //        Serial.println("OUIJA ADIOS");
          digitalWrite(13, LOW); //??
          contador = 0;
          sumador = 0;
          //      Serial.println("CORRECTO");
         
          estado = 4;

        }
        if (sumador == 2500) { //Este numero es hasta cambiar la lectura de los bostones por lastbutton etc
          sumador = 0;
          //    Serial.println("SUMADOR 2500");
        }

//        Serial.println(contador);
//        Serial.println(sumador);

      } else {
        //Creo que esto es lo que hace los glitches de la luz, no se porque esta.
        //No se para que esto.
        //digitalWrite(led , HIGH);
        //digitalWrite(12, HIGH);

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

    case 4:
      //Serial.println("MODO REPOSO");
      delay(25000);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      digitalWrite(cerradura, LOW);
      digitalWrite(led, HIGH); // ??


  }
}
