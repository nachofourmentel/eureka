/*
   Programa test de motores
*/

//X
const int pinDirX = 3;
const int pinStepsX = 2;
const int pinResetX = 7;
//Y
const int pinDirY = 8;
const int pinStepsY = 9;
const int pinResetY = 13;

//variables correspondientes al motor
int speedXY = 5; 
long pasos = 40000;


void setup() {
  pinMode(pinStepsX, OUTPUT);
  pinMode(pinDirX, OUTPUT);
  pinMode(pinResetX, OUTPUT);
  pinMode(pinStepsY, OUTPUT);
  pinMode(pinDirY, OUTPUT);
  pinMode(pinResetY, OUTPUT);
  digitalWrite(pinResetX, LOW);
  digitalWrite(pinResetY, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  
  }

void loop() {
 Movimiento2();

 
}
void Movimiento1(){
 
  for(int i = 0; i < pasos; i++){
    arriba();
    izquierda();
    }
  for(int i = 0; i < pasos; i++){
    abajo();
    derecha();
    }
}
void Movimiento2(){
 
  for(int i = 0; i < pasos; i++){
    abajo();
    derecha();
    }

  for(int i = 0; i < pasos; i++){
    arriba();
    izquierda();
    }
  }

void moveMotor(int pinStep, int velocidad) {
  digitalWrite(pinStep, HIGH);
  delayMicroseconds(velocidad);
  digitalWrite(pinStep, LOW);
  delayMicroseconds(velocidad);
}

void derecha() {
  digitalWrite(pinDirX, LOW);
  moveMotor(pinStepsX, speedXY);
}

void izquierda() {
  digitalWrite(pinDirX, HIGH);
  moveMotor(pinStepsX, speedXY);
}

void arriba() {
  digitalWrite(pinDirY, LOW);
  moveMotor(pinStepsY, speedXY);
}

void abajo() {
  digitalWrite(pinDirY, HIGH);
  moveMotor(pinStepsY, speedXY);
}


