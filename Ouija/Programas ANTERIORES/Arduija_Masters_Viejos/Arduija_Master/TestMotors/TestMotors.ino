/*
MS1  MS2 MS3 Microstep Resolution  Excitation Mode

L L L Full Step 2 Phase
H L L Half Step 1-2 Phase
L H L Quarter Step  W1-2 Phase
H H L Eigth Step  2W1-2 Phase
H H H Sixteenth Step  4W1-2 Phase
*/

//Declare pin functions on Arduino
#define stpX 9
#define dirX 8
#define MS1X 12
#define MS2X 11
#define MS3X 10
#define ENX 13

//Motor Y
#define stp 2
#define dir 3
#define MS1 4
#define MS2 5
#define MS3 6
#define EN  7

//Declare variables for functions
char user_input;
int x;
int y;
int state;
int nPasos = 2000;

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(stpX, OUTPUT);
  pinMode(dirX, OUTPUT);
  pinMode(MS1X, OUTPUT);
  pinMode(MS2X, OUTPUT);
  pinMode(MS3X, OUTPUT);
  pinMode(ENX, OUTPUT);
  resetBEDPins();

  Serial.begin(115200); //Open Serial connection for debugging
  Serial.println("Begin motor control");
  Serial.println();
  //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("1. Turn at default microstep mode.");
  Serial.println("2. Reverse direction at default microstep mode.");
  Serial.println("3. Turn at 1/16th microstep mode.");
  Serial.println("4. Step forward and reverse directions.");
  Serial.println();
}
//Main loop
void loop() {
  while(Serial.available()){
      user_input = Serial.read(); //Read user input and trigger appropriate function
      digitalWrite(EN, LOW); //Pull enable pin low to set FETs active and allow motor control
      if (user_input =='1')
      {
         StepForwardDefault();
      }
      else if(user_input =='2')
      {
        ReverseStepDefault();
      }
      else if(user_input =='3')
      {
        SmallStepMode();
      }
      else if(user_input =='4')
      {
        ForwardBackwardStep();
      }
      else
      {
        Serial.println("Invalid option entered.");
      }
     resetBEDPins();
  }
}
//Default microstep mode function
void StepForwardDefault()
{
  Serial.println("Moving forward at default step mode.");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  digitalWrite(dirX, LOW); //Pull direction pin low to move "forward"
  for(x= 1; x<nPasos; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    digitalWrite(stpX,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    digitalWrite(stpX,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}
//Reverse default microstep mode function
void ReverseStepDefault()
{
  Serial.println("Moving in reverse at default step mode.");
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  digitalWrite(dirX, HIGH); //Pull direction pin high to move in "reverse"
  for(x= 1; x<nPasos; x++)  //Loop the stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    digitalWrite(stpX,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    digitalWrite(stpX,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}
// 1/16th microstep foward mode function
void SmallStepMode()
{
  Serial.println("Stepping at 1/16th microstep mode.");
  //Configuracion primer motor 
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  digitalWrite(MS1, LOW); //Pull MS1,MS2, and MS3 high to set logic to 1/16th microstep resolution
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
  //Configuracion segundo motor
  digitalWrite(dirX, LOW); //Pull direction pin low to move "forward"
  digitalWrite(MS1X, LOW); //Pull MS1,MS2, and MS3 high to set logic to 1/16th microstep resolution
  digitalWrite(MS2X, LOW);
  digitalWrite(MS3X, LOW);
  for(x= 1; x<1000; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    digitalWrite(stpX,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    digitalWrite(stpX,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}
//Forward/reverse stepping function
void ForwardBackwardStep()
{
  Serial.println("Alternate between stepping forward and reverse.");
  for(x= 1; x<5; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    //Read direction pin state and change it
    state=digitalRead(dir);
    if(state == HIGH)
    {
      digitalWrite(dir, LOW);
      digitalWrite(dirX, LOW);
    }
    else if(state ==LOW)
    {
      digitalWrite(dir,HIGH);
      digitalWrite(dirX, HIGH);
    }

    for(y=1; y<nPasos; y++)
    {
      digitalWrite(stp,HIGH); //Trigger one step forward
      digitalWrite(stpX,HIGH); //Trigger one step forward
      delay(1);
      digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
      digitalWrite(stpX,LOW); //Pull step pin low so it can be triggered again
      delay(1);
    }
  }
  Serial.println("Enter new option");
  Serial.println();
}
void resetBEDPins(){
   digitalWrite(EN, LOW);
   digitalWrite(dir, LOW);
   digitalWrite(stp,LOW);
   digitalWrite(MS1, LOW); 
   digitalWrite(MS2, LOW);
   digitalWrite(MS3, LOW);
   //Segundo Motor

   digitalWrite(ENX, LOW);
   digitalWrite(dirX, LOW);
   digitalWrite(stpX,LOW);
   digitalWrite(MS1X, LOW); 
   digitalWrite(MS2X, LOW);
   digitalWrite(MS3X, LOW);  
  
  }
