//Arduino - Partie 2 Activité Dé

//variable des pins des leds
#define PIN_DS 8   //pin 14  75HC595    
#define PIN_STCP 9  //pin 12  75HC595
#define PIN_SHCP 10 //pin 11  75HC595

//nombre de registre a decalage
#define numberOf74hc595 1 

// nombre de pin du registre a decalage
#define numOfRegisterPins numberOf74hc595 * 8

boolean registers[numOfRegisterPins];


//Variable du pin du bouton
int pinBouton = 2;

//Tableau d'affichage des leds
boolean affichage[8][7]={
  //Haut Gauche, Haut Droite, Gauche, Centre, Droite, Bas Gauche, Bas Droite
  0,0,0,0,0,0,0,  // affichage 0
  0,0,0,1,0,0,0,  // affichage 1
  0,1,0,0,0,1,0,  // affichage 2
  0,1,0,1,0,1,0,  // affichage 3
  1,1,0,0,0,1,1,  // affichage 4
  1,1,0,1,0,1,1,  // affichage 5
  1,1,1,0,1,1,1,  // affichage 6
  1,1,1,1,1,1,1   // affichage 7
};
void setup() {
  pinMode(PIN_DS, OUTPUT);
  pinMode(PIN_STCP, OUTPUT);
  pinMode(PIN_SHCP, OUTPUT);
  pinMode(pinBouton,INPUT_PULLUP);
  clearRegisters();
  writeRegisters();
  Serial.begin(9600);
  randomSeed(analogRead(0)); //initialise la séquence aléatoire
  setZero(); //appel de la fonction setZero
}

// Mettre toutes les valeurs a 0 pour le resigtre
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
     registers[i] = LOW;
  }
} 

// affectation des valeurs engregistrés dans le tableau "registers" et application (visualisation) des valeurs a la fin
void writeRegisters(){
 
 // Tant que LOW les modifications ne seront pas affectés
  digitalWrite(PIN_STCP, LOW);
 
 // boucle pour affecter chaque pin des 74hc595
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
 
    //doit etre a l'etat bas pour changer de colonne plus tard
    digitalWrite(PIN_SHCP, LOW);
 
    // recuperation de la valeur dans le tableau registers
    int val = registers[i];
 
    //affecte la valeur sur le pin DS correspondant a un pin du 74hc595
    digitalWrite(PIN_DS, val);
    //colonne suivante
    digitalWrite(PIN_SHCP, HIGH);
 
  }
  //applique toutes les valeurs au 74hc595
  digitalWrite(PIN_STCP, HIGH);
 
}

// enregistre une valeur pour un registre etat haut ou bas 
void setRegisterPin(int index, int value){
  registers[index] = value;
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
      int nbAlea = random(1,7); //tirage d'un nombre aléatoire
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
  for (int p=0;p<7;p++) 
  {
    //res = ligne du tableau
    //p = colonne du tableau
    //etat c'est la led doit etre allumée ou pas
    boolean etat = affichage[res][p];
    //si etat = 0 la led est éteinte, si etat = 1 la led est allumée
    setRegisterPin(p,etat);
  }
  writeRegisters();
}
