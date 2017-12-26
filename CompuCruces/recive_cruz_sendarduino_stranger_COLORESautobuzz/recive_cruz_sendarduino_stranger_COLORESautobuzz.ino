int value;
int cruz = 11;
int cruzstate;
int lastButtonState;
int delayLuz = 600;

int turbina = 7;//amarillo//ahora turbina es reset
const int cerrad = 4; //naranja//este es el que suma al contador que recibe la otra pc para accionar los eventos

String color[3] = { "Red", "Yellow", "Blue" };
//Luces stranger
#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 100
#define DATA_PIN 3

//Teclas / Luces

#define A 1
#define a 33
#define l_A 12
#define l_a 13
#define l_a2 14

#define B 2
#define b 34
#define l_B 15
#define l_b 16
#define l_b2 17

#define C 3
#define c 35
#define l_C 18
#define l_c 19
#define l_c2 20

#define D 4
#define d 36
#define l_D 21
#define l_d 22
#define l_d2 23

#define E 5
#define e 37
#define l_E 24
#define l_e 25
#define l_e2 26

#define F 6
#define f 38
#define l_F 27
#define l_f 28
#define l_f2 29

#define G 7
#define g 39
#define l_G 29
#define l_g 30
#define l_g2 31

#define H 8
#define h 40
#define l_H 32
#define l_h 33

#define I 9
#define i 41
#define l_I 5
#define l_i 6

#define J 10
#define j 42
#define l_J 61
#define l_j 62
#define l_j2 63

#define K 11
#define k 43
#define l_K 59
#define l_k 60

#define L 12
#define l 44
#define l_L 56
#define l_l 57

#define M 13
#define m 45
#define l_M 52
#define l_m 53
#define l_m2 54

#define N 14
#define n 46
#define l_N 50
#define l_n 51

#define O 15
#define o 47
#define l_O 47
#define l_o 48
#define l_o2 49

#define P 16
#define p 48
#define l_P 45
#define l_p 46

#define Q 17
#define q 49
#define l_Q 42
#define l_q 43

#define R 18
#define r 50
#define l_R 67
#define l_r 68

#define S 19
#define s 51
#define l_S 70
#define l_s 71

#define T 20
#define t 52
#define l_T 73
#define l_t 74
#define l_t2 75

#define U 21
#define u 53
#define l_U 76
#define l_u 77
#define l_u2 78

#define V 22
#define v 54
#define l_V 79
#define l_v 80
#define l_v2 81

#define W 23
#define w 55
#define l_W 83
#define l_w 84
#define l_w2 85

#define X 24
#define x 56
#define l_X 86
#define l_x 87
#define l_x 88

#define Y 25
#define y 57
#define l_Y 90
#define l_y 91

#define Z 26
#define z 58
#define l_Z 93
#define l_z 94
#define l_z2 95



int tecla;

// Define the array of leds
CRGB leds[NUM_LEDS];


void setup() {
  pinMode(cruz, INPUT_PULLUP);
  pinMode(cerrad, OUTPUT);
  pinMode(turbina, OUTPUT);
  Serial.begin(9600);
  digitalWrite(turbina, LOW);

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);


}

void loop() {

  //Apaga todos los deds
  leds[0] = CRGB::Black;
  FastLED.show();

  //Recibe señal cruces

  cruzstate = digitalRead(cruz);

  // compare the buttonState to its previous state
  if (cruzstate != lastButtonState) {
    // if the state has changed, increment the counter
    if (cruzstate == HIGH) {
      // Serial.println("APAGADO");
      // Serial.println("Nocruz");
      Serial.println(0);
      delay(500);


    } else {
      Serial.println(1);
      //      digitalWrite(LED, HIGH);
      delay(500);
      //      digitalWrite(LED, LOW);

    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = cruzstate;

  //Recibe de max
  if (Serial.available()) { //250,251,252 . son los numeros que recibe en cada ipsta
    value = Serial.read();
    //Aca van los valores que envia max por cada letra
    //Que se deberan corresponder con un numero del array de leds
    //(el numero depende de la posicion de los leds. Van de 0 a 100
    //Se definen arriba del todo



    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == a ||  value == A) {
      leds[l_A] = CRGB::Blue;
      leds[l_a] = CRGB::Red;
      leds[l_a2] = CRGB::Green;
      FastLED.show();
      delay(600);
      leds[l_A] = CRGB::Black;
      leds[l_a] = CRGB::Black;
      leds[l_a2] = CRGB::Black;
      FastLED.show();
      //delay(100);
    }

    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == b ||  value == B) {
      leds[l_B] = CRGB::Red;
      leds[l_b] = CRGB::Green;
      leds[l_b2] = CRGB::Blue;
      FastLED.show();
      delay(delayLuz);
      leds[l_B] = CRGB::Black;
      leds[l_b] = CRGB::Black;
      leds[l_b2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == C ||  value == c) {
      leds[l_C] = CRGB::Blue;
      leds[l_c] = CRGB::Yellow;
      leds[l_c2] = CRGB::Green;
      FastLED.show();
      delay(delayLuz);
      leds[l_C] = CRGB::Black;
      leds[l_c] = CRGB::Black;
      leds[l_c2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == D ||  value == d) {
      leds[l_D] = CRGB::Green;
      leds[l_d] = CRGB::Yellow;
      leds[l_d2] = CRGB::Blue;
      FastLED.show();
      delay(delayLuz);
      leds[l_d] = CRGB::Black;
      leds[l_D] = CRGB::Black;
      leds[l_d2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == E ||  value == e) {
      leds[l_E] = CRGB::Yellow;
      leds[l_e] = CRGB::Green;
      leds[l_e2] = CRGB::Blue;
      FastLED.show();
      delay(delayLuz);
      leds[l_E] = CRGB::Black;
      leds[l_e] = CRGB::Black;
      leds[l_e2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == F ||  value == f) {
      leds[l_f] = CRGB::Green;
      leds[l_F] = CRGB::Yellow;
      leds[l_f2] = CRGB::Blue;
      FastLED.show();
      delay(delayLuz);
      leds[l_F] = CRGB::Black;
      leds[l_f] = CRGB::Black;
      leds[l_f2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == G ||  value == g) {
      leds[l_G] = CRGB::Blue;
      leds[l_g] = CRGB::Yellow;
      leds[l_g2] = CRGB::Green;
      FastLED.show();
      delay(delayLuz);
      leds[l_G] = CRGB::Black;
      leds[l_g] = CRGB::Black;
      leds[l_g2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == H ||  value == h) {
      leds[l_H] = CRGB::Green;
      leds[l_h] = CRGB::Blue;
      //      leds[l_h2] = CRGB::Yellow;
      FastLED.show();
      delay(delayLuz);
      leds[l_H] = CRGB::Black;
      leds[l_h] = CRGB::Black;
      //    leds[l_h2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == I ||  value == i) {
      leds[l_I] = CRGB::Green;
      leds[l_i] = CRGB::Blue;
      //      leds[l_i2] = CRGB::Yellow;
      FastLED.show();
      delay(delayLuz);
      leds[l_I] = CRGB::Black;
      leds[l_i] = CRGB::Black;
      //    leds[l_i2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == J ||  value == j) {
      leds[l_J] = CRGB::Green;
      leds[l_j] = CRGB::Yellow;
      leds[l_j2] = CRGB::Blue;
      FastLED.show();
      delay(delayLuz);
      leds[l_J] = CRGB::Black;
      leds[l_j] = CRGB::Black;
      leds[l_j2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == K ||  value == k) {
      leds[l_K] = CRGB::Yellow;
      leds[l_k] = CRGB::Green;
      //      leds[l_k2] = CRGB::Yellow;
      FastLED.show();
      delay(delayLuz);
      leds[l_K] = CRGB::Black;
      leds[l_k] = CRGB::Black;
      //    leds[l_k2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == L ||  value == l) {
      leds[l_L] = CRGB::Green;
      leds[l_l] = CRGB::Blue;
      //      leds[l_l2] = CRGB::Yellow;
      FastLED.show();
      delay(delayLuz);
      leds[l_L] = CRGB::Black;
      leds[l_l] = CRGB::Black;
      //    leds[l_l2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == M ||  value == m) {
      leds[l_M] = CRGB::Yellow;
      leds[l_m] = CRGB::Green;
      leds[l_m2] = CRGB::Blue;
      FastLED.show();
      delay(delayLuz);
      leds[l_M] = CRGB::Black;
      leds[l_m] = CRGB::Black;
      leds[l_m2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == N ||  value == n) {
      leds[l_N] = CRGB::Yellow;
      leds[l_n] = CRGB::Blue;
      //      leds[l_n2] = CRGB::Yellow;
      FastLED.show();
      delay(delayLuz);
      leds[l_N] = CRGB::Black;
      leds[l_n] = CRGB::Black;
      //    leds[l_n2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == O ||  value == o) {
      leds[l_O] = CRGB::Yellow;
      leds[l_o] = CRGB::Green;
      leds[l_o2] = CRGB::Blue;
      FastLED.show();
      delay(delayLuz);
      leds[l_O] = CRGB::Black;
      leds[l_o] = CRGB::Black;
      leds[l_o2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == P ||  value == p) {
      leds[l_P] = CRGB::Yellow;
      leds[l_p] = CRGB::Blue;
      //      leds[l_p2] = CRGB::Yellow;
      FastLED.show();
      delay(delayLuz);
      leds[l_P] = CRGB::Black;
      leds[l_p] = CRGB::Black;
      //    leds[l_q2] = CRGB::Black;
      FastLED.show();
    }

    if (value == Q ||  value == q) {
      leds[l_Q] = CRGB::Blue;
      leds[l_q] = CRGB::Green;
      //      leds[l_p2] = CRGB::Yellow;
      FastLED.show();
      delay(delayLuz);
      leds[l_Q] = CRGB::Black;
      leds[l_q] = CRGB::Black;
      //    leds[l_q2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == R ||  value == r) {
      leds[l_R] = CRGB::Blue;
      leds[l_r] = CRGB::Yellow;
      //      leds[l_r2] = CRGB::Yellow;
      FastLED.show();
      delay(delayLuz);
      leds[l_R] = CRGB::Black;
      leds[l_r] = CRGB::Black;
      //    leds[l_r2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == S ||  value == s) {
      leds[l_S] = CRGB::Green;
      leds[l_s] = CRGB::Yellow;
      //      leds[l_s2] = CRGB::Yellow;
      FastLED.show();
      delay(delayLuz);
      leds[l_S] = CRGB::Black;
      leds[l_s] = CRGB::Black;
      //    leds[l_s2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == T ||  value == t) {
      leds[l_T] = CRGB::Blue;
      leds[l_t] = CRGB::Green;
      leds[l_t2] = CRGB::Red;
      FastLED.show();
      delay(delayLuz);
      leds[l_T] = CRGB::Black;
      leds[l_t] = CRGB::Black;
      leds[l_t2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == U ||  value == u) {
      leds[l_U] = CRGB::Yellow;
      leds[l_u] = CRGB::Red;
      leds[l_u2] = CRGB::Green;
      FastLED.show();
      delay(delayLuz);
      leds[l_U] = CRGB::Black;
      leds[l_u] = CRGB::Black;
      leds[l_u2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == V ||  value == v) {
      leds[l_V] = CRGB::Yellow;
      leds[l_v] = CRGB::Blue;
      leds[l_v2] = CRGB::Red;
      FastLED.show();
      delay(delayLuz);
      leds[l_V] = CRGB::Black;
      leds[l_v] = CRGB::Black;
      leds[l_v2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == W ||  value == w) {
      leds[l_W] = CRGB::Yellow;
      leds[l_w] = CRGB::Red;
      leds[l_w2] = CRGB::Green;
      FastLED.show();
      delay(delayLuz);
      leds[l_W] = CRGB::Black;
      leds[l_w] = CRGB::Black;
      leds[l_w2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == X ||  value == x) {
      leds[l_X] = CRGB::Yellow;
      leds[l_x] = CRGB::Blue;
      //      leds[l_x2] = CRGB::Yellow;
      FastLED.show();
      delay(delayLuz);
      leds[l_x] = CRGB::Black;
      leds[l_X] = CRGB::Black;
      //    leds[l_x2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == y ||  value == Y) {
      leds[l_Y] = CRGB::Yellow;
      leds[l_y] = CRGB::Red;
      //      leds[l_y2] = CRGB::Yellow;
      FastLED.show();
      delay(delayLuz);
      leds[l_Y] = CRGB::Black;
      leds[l_y] = CRGB::Black;
      //    leds[l_y2] = CRGB::Black;
      FastLED.show();
    }
    //Si es tecla A o a prende los primeros dos leds de rojo
    if (value == Z ||  value == z) {
      leds[l_Z] = CRGB::Yellow;
      leds[l_z] = CRGB::Blue;
      leds[l_z2] = CRGB::Red;
      FastLED.show();
      delay(delayLuz);
      leds[l_Z] = CRGB::Black;
      leds[l_z] = CRGB::Black;
      leds[l_z2] = CRGB::Black;
      FastLED.show();
    }
    //A partir de aca son los valores que envia max cuando ponen bien las palabras

    // Serial.println(value);
    if (value == 99) {//Reset / quizas halla q cambiar este numero para que no se pise con el valr de las letras
      digitalWrite(turbina, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(turbina, LOW);    // turn the LED off by making the voltage LOW
      delay(1000);
    }
    if (value ==   250) {
//      digitalWrite(cerrad, HIGH);
//      delay(1000);
//      digitalWrite(cerrad, LOW);
//      delay(1000);
    }
    if (value ==   251) {
//      digitalWrite(cerrad, HIGH);
//      delay(1000);
//      digitalWrite(cerrad, LOW);
//      delay(1000);
    }
    if (value ==   252) {
      digitalWrite(cerrad, HIGH);
      delay(1000);
      digitalWrite(cerrad, LOW);
      delay(1000);
      digitalWrite(turbina, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(turbina, LOW);    // turn the LED off by making the voltage LOW
      delay(1000);

    }
  }

}
