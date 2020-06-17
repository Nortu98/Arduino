//Arduino - Partie 2 Activité Dé

//variable des pins des leds
int pinLed[5]={2,3,4,5,6};

//pin 2 => Haut Gauche  = pinLed[0]
//pin 3 => Haut Droite  = pinLed[1]
//pin 4 => Centre       = pinLed[2]
//pin 5 => Bas Gauche   = pinLed[3]
//pin 4 => Bas Droite   = pinLed[4]

//Variable du pin du bouton
int pinBouton = 7;

//Tableau d'affichage des leds
boolean affichage[6][5]={
  //Haut Gauche, Haut Droite, Centre, Bas Gauche, Bas Droite
  0,0,0,0,0,  // affichage 0
  0,0,1,0,0,  // affichage 1
  0,1,0,1,0,  // affichage 2
  0,1,1,1,0,  // affichage 3
  1,1,0,1,1,  // affichage 4
  1,1,1,1,1}; // affichage 5

void setup() {
  for (int i=0;i<5;i++)
  {
    pinMode(pinLed[i],OUTPUT);
  }
  pinMode(pinBouton,INPUT_PULLUP);
  Serial.begin(9600);
  randomSeed(analogRead(0)); //initialise la séquence aléatoire
  setZero(); //appel de la fonction setZero
}

void loop() {
  boolean etatBouton = digitalRead(pinBouton); //lecture de l'étar du bouton
  if (!etatBouton) //test si bouton appuyé
  {
    Serial.println("nouveau tirage");
    setZero(); //appel de la fonction set Zero
    delay(500);
    for(int i=200; i<700; i = i+25){
      //exctinction brève des LEDs (100ms)
      setZero(); //appel de la fonction setZero
      delay(100);
      int nbAlea = random(1,6); //tirage d'un nombre aléatoire
      allumage(nbAlea); //appel de la fonction d'allumage
      Serial.println(nbAlea); //vue du tirage sur la console
      delay(i); //temporisation
    }
  }
}

//fonction pour éteindre tout les leds
void setZero(){
  allumage(0);  //appel de la fonction d'allumage
}

//fonction pour allumer les led en fonction du nombre mis en paramètre
void allumage(int res){
  //boucle pour chaque pin sur la ligne du tableau mis en paramètre de la fonction
  for (int p=0;p<5;p++) 
  {
    //res = ligne du tableau
    //p = colonne du tableau
    //etat c'est la led doit etre allumée ou pas
    boolean etat = affichage[res][p];
    //si etat = 0 la led est éteinte, si etat = 1 la led est allumée
    digitalWrite(pinLed[p],etat);
  }
}
