#include <Servo.h>

Servo middle, left, right, claw;

char var = 0;
int m = 90;
int l = 90;
int r = 90;
int c = 90;
char commande = 'n';
int sens = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  middle.attach(11);
  left.attach(10);
  right.attach(9);
  claw.attach(6);
}

void move(){
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    // read the incoming byte:
    var = Serial.read();
    if (var == 'm' or var == 'l' or var == 'r' or var == 'c'){
      commande = var;
      sens = 0;
    }
    if (var == '+'){
      sens = 10;
    }  
    if (var ==  '-'){
      sens = -10;
    }
    // say what you got:
    Serial.println(var);

    
  }
  if (commande == 'm' and sens != 0) {
    if (m+sens >= 0 and m+sens <= 180){
      m = m+sens;
    }
    middle.write(m);
    Serial.println(m);
    sens = 0;
    commande = 'n';
    delay(100);
  }
  if (commande == 'l' and sens != 0) {
    if (l+sens >= 10 and l+sens <= 140){
      l = l+sens;
    }
    left.write(l);
    Serial.println(l);
    sens = 0;
    commande = 'n';
    delay(100);
  }
  if (commande == 'r' and sens != 0) {
    if (r+sens >= 30 and r+sens <= 180){
      r = r+sens;
    }
    right.write(r);
    Serial.println(r);
    sens = 0;
    commande = 'n';
    delay(100);
  }
  if (commande == 'c' and sens != 0) {
    if (c+sens >= 0 and c+sens <= 180){
      c = c+sens;
    }
    claw.write(c);
    Serial.println(c);
    sens = 0;
    commande = 'n';
    delay(100);
  }


}
