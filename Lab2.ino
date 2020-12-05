#include <LiquidCrystal.h>
#include <Wire.h> 
#include <MsTimer2.h>
 LiquidCrystal lcd(13,12,11,10,9,8);
 int on=0;
 int cont=0;
 int i=0;
 int j=0;
 int k=0;
 int A=7;
 int B=6;
 int C=5;
 int D=4;
 int a;
 int b;
 const int leds[4] = {4,5,6,7};
void setup() {
   for(i=0;i<4;i++){ 
    pinMode(leds[i],OUTPUT);
  }
  i=0;
   lcd.begin(16,4);
   Serial.begin(9600);
   attachInterrupt(0,activacion,LOW);
   attachInterrupt(1,contador,LOW);
   pinMode(A,OUTPUT);
   pinMode(B,OUTPUT);
   pinMode(C,OUTPUT);
   pinMode(D,OUTPUT);
   MsTimer2::set(1000,reloj);
}

void loop() {

 if(cont==2){

cambio1();
    cambio();
    }
   if(cont==1){
    luces();
    }
}
void reloj(){
  if(j<59)
    j++;
  else{
    j=0;
    if(i<23){
      i++;
    }
     else{
      i=0;
      }
    } 
  lcd.setCursor(0,1);
  lcd.print("Hora:");
  if(i<10){
    lcd.setCursor(6,1);
    lcd.print("0");
    lcd.setCursor(7,1);
    lcd.print(i);
  }
  else{
    lcd.setCursor(6,1);
    lcd.print(i);
  }
    
  if(j<10){
     lcd.setCursor(9,1);
     lcd.print("0");
     lcd.setCursor(10,1);
     lcd.print(j);
  }
  else{ //Caso contrario
     lcd.setCursor(9,1);
     lcd.print(j); 
  }
  lcd.setCursor(8,1);
  lcd.print(":");
 }

void sensor(){
  if(digitalRead(A2)==HIGH || digitalRead(A3)==HIGH || digitalRead(A4)==HIGH || digitalRead(A5)==HIGH)
    Serial.println("On");
  else
    Serial.println("Off");
}

void cambio(){
  j=analogRead(0);
  j=map(j,0,1023,0,59);
}

void cambio1(){
  i=analogRead(1);
  i=map(i,0,1023,0,23);
}

void luces(){
  for(;a<cont;a++){
      for(b=0;b<67;b++){
        int num = random(4);
        digitalWrite(leds[num],HIGH);
        delay(150);
        digitalWrite(leds[num],LOW);
        delay(150);
      }
    }
  }

void lucesoff(){
        digitalWrite(A,LOW);
        digitalWrite(B,LOW);
        digitalWrite(C,LOW);
        digitalWrite(D,LOW);
}

void activacion(){
  switch(on){
      case 0:
        lcd.begin(16,4);
        lcd.setCursor(0,0);
        lcd.print("Laboratorio 2");
         MsTimer2::start();
        on++;
      break;
      case 1:
        lcd.setCursor(0,2);
        lcd.print("Modo");
        on++;
      break;
      case 2:
        lcd.clear(); 
        MsTimer2::stop();
        lcd.noDisplay();
        lucesoff();
        on=0;
        cont=0;
      break;
    }
}

void contador(){
  if(on==2){
    switch(cont){
      case 0:
        lcd.setCursor(0,3);
        lcd.print("Luces       ");
        cont++;
      break;
      case 1:
        lcd.setCursor(0,3);
        lcd.print("Cambio Hora");
        i=0;
        j=0;
        b=0;
        a=0;
        b=100;
        a=1;  
        cambio1();
        cambio();
        cont++;
        lucesoff();
      break;
      case 2:
        lcd.setCursor(0,3);
        lcd.print("Sensores    ");
        sensor();
        b=0;
        a=0;
        cont=0;
      break;
    }
  }
}
