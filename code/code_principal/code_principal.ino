#include <Servo.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_CLK 13
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_DC 8
#define TFT_CS 10
#define TFT_RST 9
// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC

// If using the breakout, change pins as desired
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

Servo bD;
Servo bG;
Servo jD;
Servo jG;

//liste avec toute les questions
String question[16][6]={{"U=RI","R=I/U","A=21","B=10","1","Quelle formule doit-on se faire tatouer ?"},
                        {"le lion","le rat","le chien","le chat","3","Quel est l'animal prefere de REMI ?"},
                        {"3h","1h","2h","4h","1","A quelle heure FRANCOIS se couche en periode scolaire ?"},
                        {"Memoria","Scorpions","Telephone","Genesis","2","Quel est le groupe de musique prefere de LENA ?"},
                        {"10h","8h","5h","12h","2","Combien de temps passe ATHENA à reviser le samedi en moyenne ?"}, //5
                        {"Harry Potter 6","Sunshine","Prometheus","Brice de Nice 3","4","Lequel de ces films JULIEN prefere ?"},
                        {"URSS","IRLANDAIS","FRANCAIS","ANGLAIS","2","Quel est l'hymne national prefere de ROMAIN ?"},
                        {"Laos", "Etats-Unis","Chine","France","2","Quel pays LOUISE n'a pas visite ?"},
                        {"Thermo","EVN","Elec","Electromag","1","Quelle est la matiere prefere de "}, 
                        {"Koralie","Axel","Julien","Ce bon vieux Staline","4","Quel est le camarade préféré de ANTOINE ?"}, //10
                        {"Italienne","Canadienne","Coreenne","Etasunienne","2","Quel est la 2ème nationalité de ELISA ?"},
                        {"Demon Hunter","Megadeth","Iron Maiden","Three Days Grace","4","Quel est le groupe de musique favori de AXEL ?"},
                        {"1","2","3","4","2","Combien de frère et soeur à ZOE ?"},
                        {"Ce bon vieux Staline","Mao Zedong","Kim Jong-Un","Poutine","2","Quel est le dictateur preferé de MAXIME ?"},
                        {"FullMetalAlchimist", "L'attaque des titans", "One piece"," Naruto", "1","Quel est l'anime preferé de KORALIE ?"}, //15 
                        {"cote dazur","var","aude", "gart","4","Dans quel département est né LAURE-ANNE ?"},};
                             
int nbDeReponseJuste=0;
String reponse="f";
bool again=true;
int QuestionSelectionee;  
bool questionPosee[16];

char BlueT;

void setup() {
  bD.attach(5); //bras droit      180 en haut
  bG.attach(6); //bras gauche     0 en haut
  jD.attach(3); //jambe droite    0 pour avancer
  jG.attach(2);  //jambe gauche   150 pour avancer*/
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial1.print("*1"+String("")+"*");
  Serial1.print("*2"+String("")+"*");
  Serial1.print("*3"+String("")+"*");
  Serial1.print("*4"+String("")+"*");    
  tft.begin();
  tft.setRotation(1);

  tft.fillScreen(ILI9341_NAVY);
  tft.setTextWrap(true);
   tft.setTextSize(3);

  delay (1000);
}

void loop() {
  Serial1.print("*G"+String(0)+"*");
  for (int k=0;k<15;k++){
    questionPosee[k]=false;}
  for (int numeroQuestion=0;numeroQuestion<=10;numeroQuestion+=1){  
     //choisir une question
     bool trouver = false;
     while (trouver==false){
      QuestionSelectionee=random(16);
      if ((questionPosee[QuestionSelectionee])==false){
        questionPosee[QuestionSelectionee]=true;
        trouver=true;
        }
     }
     
     Serial.println(QuestionSelectionee);
     

    //afficher les proposition de réponse sur l'écran    
    Serial1.print("*1"+String(question[QuestionSelectionee][0])+"*");
    Serial1.print("*2"+String(question[QuestionSelectionee][1])+"*");
    Serial1.print("*3"+String(question[QuestionSelectionee][2])+"*");
    Serial1.print("*4"+String(question[QuestionSelectionee][3])+"*");    
    tft.setTextColor(ILI9341_YELLOW);
    tft.setCursor(0, 0);
    tft.print( question[QuestionSelectionee][5]);
    
    
    while (again==true){
      
      if (Serial1.available()){
        Serial.println("test");
        BlueT=Serial1.read();
        if(BlueT=='A'){ //Button Pressed
          again=false;
          if (question[QuestionSelectionee][4]=="1"){
            reponse="j";
          }
        }
        if(BlueT=='B'){ //Button Pressed
          again=false;
          if (question[QuestionSelectionee][4]=="2"){
            reponse="j";
          }
        }
        if(BlueT=='C'){ //Button Pressed
          again=false;
          if (question[QuestionSelectionee][4]=="3"){
            reponse="j";
          }
        }
        if(BlueT=='D'){ //Button Pressed
          again=false;
          if (question[QuestionSelectionee][4]=="4"){
            reponse="j";
        }
      }
     }
    }
    again=true;
    tft.setTextColor(ILI9341_NAVY);
    tft.setCursor(0, 0);
    tft.print( question[QuestionSelectionee][5]);
    //faire les réactions en fonction de si la réponse est juste ou non
    if (reponse=="j"){
       nbDeReponseJuste+=1;
       bonneReponse();//réaction réponse juste
       reponse="f";        
     }
    else{
     mauvaiseReponse(); //réaction réponse fausse
    }
   
    Serial1.print("*G"+String(numeroQuestion+1)+"*");
  }

//réaction finale en fonction des réponses juste
  if (nbDeReponseJuste<=10){
   parfait();
   }
  else{
    nul();
   }

}  


void maxBras(int nb, int vitesse){ //vitesse en ms
    while (nb>=0){
      for (int i=0;i<180;i++){
        bD.write(i);
        bG.write(180-i);
        delay (vitesse);
      }
      for (int i=180;i>0;i--){
        bD.write(i);
        bG.write(180-i);
        delay (vitesse);
      }
      nb--;
    }
  }
  
void brasContent(int nb, int vitesse, int max, int min){
  while (nb>=0){
      for (int i=min;i<max;i++){
        bD.write(i);
        bG.write(180-i);
        delay (vitesse);
      }
      for (int i=max;i>min;i--){
        bD.write(i);
        bG.write(180-i);
        delay (vitesse);
      }
      nb--;
    }
  bG.write(180);
  bD.write(0);
  }

void brasQuiTombe(int vitesse){
  for (int i=180;i>0;i--){
        bD.write(i);
        bG.write(180-i);
        delay (vitesse);
      }
  }

void mauvaiseReponse(){
  jD.write(0);
  jG.write(150);
  maxBras(4,2.5);
  jD.write(150);
  jG.write(0);
  maxBras(4,2.5);
  jD.write(90);
  jG.write(90);
  bG.write(180);
  bD.write(0);
}

void bonneReponse(){
  brasContent(10,8,180,150);
}

void parfait(){
  jD.write(0);
  jG.write(0);
  brasContent(10,8,180,150);
  jD.write(90);
  jG.write(90);
  }

void nul(){
  jD.write(100);
  jG.write(80);
  brasQuiTombe(20);
  jD.write(90);
  jG.write(90);
  }
