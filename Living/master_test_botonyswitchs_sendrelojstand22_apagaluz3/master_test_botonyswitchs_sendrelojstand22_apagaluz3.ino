//Recibe un DIGITAL OUTPUT LOW DE OTRO ARDUINO/BOTON
// ENVIA UN "1" A MAX 7, EL CUAL REPRODUCE UN VIDEO
//ESTO ACTIVA SENSOR ULTRASONICO, EL CUAL AL DETECTAR CERCANIA DE UN OBJETO CIERRA UN RELE, EL CUAL ABRE UNA CERRADURA ELECTROMAGNETICA
//  Este va para el arduino UNO
//Primero recibe los 5v de EL PIANO, luego espera a que se ponga la mano en el sensor, hasta que esto no suceda,
//no lee el piano nuevamente. Cuando el sensor lee la mano cerca, abre el rele (PIN 12) que abre la cerradura electromagnetica
//Testeado hasta PIANO/SENSOR DE MANO. Testeado con dos RELE. El rele "luz"controla el preindo y apagado general de las luces.
//El rele "Cerradura" abre la cerradura una vez que se prende pone la mano en el sensor de presencia
//Eureka leg
//7/03/2017 Santiago Terigi

//RECORDAR QUE LOS RELES SE PRENDEN EN LOW, ASIQUE ESTA "INVERTIDO"
//CAMBIAR NOMBRES DE VARIABLES Y AGREGARLE COLOR

int boton = 6;// Rojo de piano envia estado
int luz = 12;//Control general de las luces //Verde de cerradura - va a proto - negro corto
int cerradura = 10;//Cerradura abre primer puerta

long distancia;
long tiempo;

int estado;
int ultimoestado;

int inputPin = 9;
int pirState = LOW;
int val = 0;
//ULTRASONICO
int outsen = 9;//NARANJA NDE ULTRASONICO
int insen = 8;//AMARILLO DE ULTRASONICO. EL POSITIVO ES EL QUE TIENE UN PIN ROJO CONECTADO A UN CABLE ZUL (DE RED).
//--------------EL NEGATIVO ES EL PIN NARANJA CONECTADO A UNC ABLE VERDE
int leesensor = 0;







int dist1 = 120;
int dist2 = 200;//Distancia en milimetros para regular el sensor de presencia de la mano


















//Luces
int tiempoluces = 25;//Cantidad de veces que ocurre el fenomeno. Esta var
int randpre = 500;
int randapa = 1000;
int randprend;
int randapag;

//Delay mano
int delaymano = 30000;
//int delaymano = 5000;

//Boton prende y switch
int  buttonPin = 5;    // SWITCH DE IDIOMA . CABLES  MASA Y ROJO
int  buttonPin2 = 4; //BOTON MASTER DEL JUEGO. NARANJA Y BLANCO

int buttonState = 0;
int lastButtonState = 0;
int buttonState2 = 0;
int lastButtonState2 = 0;

//Send relojes
const int  reset = 3;
const int paracorre = 2; 
//Recibe de max
int value;



void setup() {

  //RelojSend
  pinMode(reset, OUTPUT);
  digitalWrite(reset, LOW);
  pinMode(paracorre, OUTPUT);
  digitalWrite(paracorre, LOW);
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
 pinMode(inputPin, INPUT);   
 
  pinMode(boton, INPUT_PULLUP);
  pinMode(cerradura, OUTPUT);
  pinMode(luz, OUTPUT);
  Serial.begin(9600);

  pinMode(outsen, OUTPUT);
  pinMode(insen, INPUT);


}

void loop() {



  //Boton y siwtch idioma
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);

  // compare the buttonState to its previous state
  //idioma
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      Serial.println(5);

    } else {
      Serial.println(6);
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }

  //boton Master
  if (buttonState2 != lastButtonState2) {
    // if the state has changed, increment the counter
    if (buttonState2 == LOW) {
      Serial.println(buttonState2);
      Serial.println(9);
      digitalWrite(reset, LOW);
      digitalWrite(paracorre, LOW);//pongo en 60 el reloj 
      
      delay(112000);        // Serial.println("on");
      
      digitalWrite(reset, HIGH);   // reloj cuenta
      digitalWrite(paracorre, HIGH);


    } else {
      //Serial.println(6);
    }
    delay(50);
  }


  lastButtonState = buttonState;
  lastButtonState2 = buttonState2;

  //Termina boton switch e idioma

  //Empieza lectura serial de max
  if (Serial.available()) {
    value = Serial.read();
    Serial.println(value);

    if (value == 100) {
      apagonUno();
    }

    if (value == 200) {
      apagonDos();
    }

    if (value == 250) {
      digitalWrite(reset, LOW);   // reloj pausa
      digitalWrite(paracorre, HIGH);
      apagonTres();
      delay(10000);
    }
  }



  switch (leesensor) {
    case 0:
      // put your main code here, to run repeatedly:
      estado = digitalRead(boton);

      if (estado != ultimoestado) {
        //nada
      }
      if (estado == HIGH) {
        //  digitalWrite(LED, LOW);
        //Serial.println(0);
      } else {//O sea si pusieron bien la contrasñea del piano !!!!!!!!!!!!!!!!!!


        Serial.println(1);//Esto envia un 1 a MAX,el cual activa el video de la tele
        digitalWrite(luz, HIGH);//Apaga las luces
        delay(delaymano);//Delay par aleer sensors

        leesensor = 1;

      }
      delay(20);
      ultimoestado = estado;

      break;
    case 1:
//      // delay(10000);//Delay espera prenda tele
//      //Esto sucede cuando ponen bien la contrasñea del piano
//      digitalWrite(outsen, LOW); /* Por cuestión de estabilización del sensor*/
//      delayMicroseconds(5);
//      digitalWrite(outsen, HIGH); /* envío del pulso ultrasónico*/
//      delayMicroseconds(10);
//      tiempo = pulseIn(insen, HIGH);
//      distancia = int(0.017 * tiempo);
////            Serial.print("distancia ");
////             Serial.println(distancia);
////      delay(1000);
//      //ESTO ES CUANDO PONEN LA MANO EN EL SENSOR
//      if (distancia > dist1 && distancia < dist2) {
//        Serial.println(2);//Esto es para enviar a max
//        //leesensor = 0;//descomentar para que funcione
//
//        for (int i = 0; i <= tiempoluces; i++) {
//          parpadeo();
//        }
//        digitalWrite(luz, LOW);//Prende la luz
//        delay(100);
//
//        digitalWrite(cerradura, HIGH);
//        delay(500);
//        digitalWrite(cerradura, LOW);
//        delay(500);
//        leesensor = 0;
//
        
        val = digitalRead(inputPin);  // Leemos el PIR
      Serial.println(val);
      if (val == HIGH) {
        if (pirState == LOW) {
          //Entra alguien a la sala y ejecutamos video X 2
          Serial.println("HIGH");
          pirState = HIGH;
         }
      } else {
        //digitalWrite(ledPin, LOW); // turn LED OFF
        if (pirState == HIGH) {
          Serial.println("LOW");
          pirState = LOW;
        }
      }             // wait for a second
        Serial.println(2);//Esto es para enviar a max


      }
      //Serial.println(distancia);
      delay(50);

      break;


  }
} //end loop
