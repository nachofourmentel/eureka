//------------------------------------------------------------------------------
/*
 //Lista de mensajes que pueden ser enviados por la Ouija  
    Genera numero random del 1-7 (Siempre un numero arriba de la cantidad de cases)
    switch (randomNumber) para que sea aleatorio. Sino MensajeNro
    Elije el mensaje que seleccionamos al principio del sketch. El simbolo "." hace referencia al 0.0, conviene siempre ponerlo al final del mensaje asi vuelve rapido a la posicion de 0.0

*/
void ouijaMessage()
{
    enableMotors();
    randomNumber = random(7); //no le des bola
    
    switch (randomNumber) //aca va la variable
     {
      case 0:
        {char arrayThing[30] = {'a','m','.',0};
        ouijaPrint(arrayThing);
        homeing();}
        break;
         case 1:
        {
        char arrayThing2[30] = {'v','a','y','a','n','s','e',0};
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
        char arrayThing6[30] = {'m','a',0};;
        ouijaPrint(arrayThing6);
      homeing();}
        break;
        
        ////////////////////////////////////////////////////////////////////
        //Asi se construyen frases.
        //
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
void ouijaMessageEnglish()
{
    enableMotors();
    randomNumber = random(2);
    switch (randomNumber)
     {
      case 0:
        {char arrayThing[30] = {'h','o','l','a','.',0};
        ouijaPrint(arrayThing);
        homeing();}
        break;
         case 1:
        {
        char arrayThing2[30] = {'l','e','a','v','e','.',0};
        ouijaPrint(arrayThing2);
        homeing();}
        break;
        case 2:
        {
        char arrayThing3[30] = {'o','u','t',0};;
        char arrayThing4[30] = {'o','f',0};;
        char arrayThing5[30] = {'h','e','r','e','.',0};;        
        ouijaPrint(arrayThing3);
        delay(TiempoEntrePalabras);
        ouijaPrint(arrayThing4);
        delay(TiempoEntrePalabras);
        ouijaPrint(arrayThing5);
        homeing();        }
        break;
        default: 
        disableMotors();
     }
    disableMotors();
}

