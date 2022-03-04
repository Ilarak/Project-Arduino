#include <Servo.h>
#include <SPI.h>
#include <SD.h>
#define sdCardPinChipSelect 10  
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
String question[16][6]={{"U=RI","R=I/U","A=21","B=10","1","Quelle formule doit on se faire tatouer"},
                        {"le lion","le rat","le chien","le chat","3","Quel est l'annimal prefere de REMI"},
                        {"3h","1h","2h","4h","1","a quelle heure FRANCOIS se couche en periode scolaire"},
                        {"Memoria","Scorpions","Telephone","Genesis","2","quel est le groupe de musique preferé de LENA ?"},
                        {"10h","8h","5h","12h","2","combien de temps passe ATHENA à reviser le samedi en moyenne"}, //5
                        {"Harry Potter 6","Sunshine","Prometheus","Brice de Nice 3","4","lequel de ces films JULIEN prefere ?"},
                        {"URSS","IRLANDAIS","FRANCAIS","ANGLAIS","2","quel est l'hymne national préféré de ROMAIN ?"},
                        {"Ce bon vieux Staline","Mao Zedong","Kim Jong-Un","Poutine","2","zzzzzz"},
                        {"Thermo","EVN","Elec","Electromag","1","zzzzzz"}, 
                        {"Koralie","Axel","Julien","Ce bon vieux Staline","4","zzzzzz"}, //10
                        {"Italienne","Canadienne","Coreenne","Etasunienne","2","Quel est la 2ème nationalité de ELISA ?"},
                        {"Demon Hunter","Megadeth","Iron Maiden","Three Days Grace","4","zzzzzz"},
                        {"1","2","3","4","2","zzzzzz"},
                        {"Laos", "Etat-Unis","Chine","France","2","zzzzzz"},
                        {"FullMetalAlchimist", "L'attaque des titans", "One piece"," Naruto", "1","zzzzzz"}, //15 
                        {"cote dazure","var","aude", "gart","4","zzzzzz"},};   //il manque 7 personnes  
                             
int nbDeReponseJuste=0;
String reponse="f";
bool again=true;
int QuestionSelectionee;  
bool questionPosee[16];

char BlueT;

void setup() {
     
 
  
  
  bD.attach(4); //bras droit
  bG.attach(5); //bras gauche
  jD.attach(3); //jambe droite    0 pour avancer
  jG.attach(2);  //jambe gauche   150 pour avancer*/
  Serial.begin(9600);
  Serial.print("*1"+String("bla")+"*");
  Serial.print("*2"+String("bla")+"*");
  Serial.print("*3"+String("bla")+"*");
  Serial.print("*4"+String("")+"*");
  tft.begin();
  tft.setRotation(1);

  tft.fillScreen(ILI9341_NAVY);
  tft.setTextWrap(true);
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(3);

  delay (1000);
}

void loop() {
  for (int k=0;k<15;k++){
    questionPosee[k]=false;}
  Serial.print("*G"+String(0)+"*");
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
    Serial.print("*1"+String(question[QuestionSelectionee][0])+"*");
    Serial.print("*2"+String(question[QuestionSelectionee][1])+"*");
    Serial.print("*3"+String(question[QuestionSelectionee][2])+"*");
    Serial.print("*4"+String(question[QuestionSelectionee][3])+"*");    
    
    
    while (again==true){
      tft.setCursor(0, 0);
      tft.print( question[QuestionSelectionee][5]);
      if (Serial.available()){
        Serial.println("test");
        BlueT=Serial.read();
        if(BlueT=='A'){ //Button Pressed
          again=false;
          if (question[QuestionSelectionee][1]=="1"){
            reponse="j";
          }
        }
        if(BlueT=='B'){ //Button Pressed
          again=false;
          if (question[QuestionSelectionee][1]=="2"){
            reponse="j";
          }
        }
        if(BlueT=='C'){ //Button Pressed
          again=false;
          if (question[QuestionSelectionee][1]=="3"){
            reponse="j";
          }
        }
        if(BlueT=='D'){ //Button Pressed
          again=false;
          if (question[QuestionSelectionee][1]=="4"){
            reponse="j";
        }
      }
     }
    }
   again=true;
   //faire les réactions en fonction de si la réponse est juste ou non
   if (reponse=="j"){
      nbDeReponseJuste+=1;
      bonneReponse();//réaction réponse juste
      reponse="f";        
    }
   else{
    mauvaiseReponse(); //réaction réponse fausse
    }
   
   Serial.print("*G"+String(numeroQuestion+1)+"*");
  }
}
 /* //réaction finale en fonction des réponses juste
  if (nbDeReponseJuste==10){
   * réaction 100%}
   *else if(nbDeReponseJuste<=2){
   *réaction tu es nul}
   *else if(3<=nbDeReponse<=5){
   *}
   *else if (6<=nbDeReponse<=7){
   *}
   *else{
   *}
*/   


void maxBras(int nb, int vitesse){ //vitesse en ms
    Serial.println("oui");
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


void mauvaiseReponse(){
  jD.write(0);
  jG.write(150);
  maxBras(4,2.5);
  jD.write(150);
  jG.write(0);
  maxBras(4,2.5);
  jD.write(90);
  jG.write(90);
  //image écran, on peut le faire plus longtemps si besoin
}

void bonneReponse(){
  jD.write(0);
  jG.write(0);
  maxBras(4,15);
}
  
  
