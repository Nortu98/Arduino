//Arduino - Partie 1 Activité K2000
int pinBouton = 8;

//variable des pins des led
int pinLed[5]={2,3,4,5,6};

//Tableau d'ordre d'affichage des led
boolean affichage[8][5]={
  1,0,0,0,0,
  0,1,0,0,0,
  0,0,1,0,0,
  0,0,0,1,0,
  0,0,0,0,1,
  0,0,0,1,0,
  0,0,1,0,0,
  0,1,0,0,0};

void setup() {
  for (int i=0;i<5;i++)
  {
    pinMode(pinLed[i],OUTPUT);
    digitalWrite(pinLed[i],LOW);
  }
}

void loop() {
  // boucle de séquence d'affichage
  for (int i=0;i<8;i++) 
  {
    // boucle pour chaque pin
    for (int p=0;p<5;p++) 
    {
      boolean etat = affichage[i][p];
      digitalWrite(pinLed[p],etat);
    }
    delay(300);
  }
}
