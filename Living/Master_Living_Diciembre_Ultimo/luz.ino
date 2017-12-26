
void parpadeo() {
  randprend = random (randpre);
  randapag = random (randapa);
  digitalWrite(luz, HIGH);
  delay(randprend);
  digitalWrite(luz, LOW);
  delay(randapag);
  //digitalWrite(13, HIGH); Si esta descomentado deja las luces apagadas, si no, las deja prendidas


}

void apagonUno() {
  digitalWrite(luz, HIGH);//Apaga las luces
  delay(5000);
  digitalWrite(luz, LOW);//Prende


}
void apagonDos() {
  digitalWrite(luz, HIGH);//Apaga las luces
  delay(8000);
digitalWrite(luz, LOW);//Prende
}
void apagonTres() {
  digitalWrite(luz, HIGH);//Apaga las luces
  delay(10000);
digitalWrite(luz, LOW);//Prende
}
