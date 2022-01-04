#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

void setup() {
  
    u8g2.begin();

    u8g2.enableUTF8Print(); 
}

void loop() {

    u8g2.firstPage();
    do {


      u8g2.setFont(u8g2_font_10x20_tf);
   

   
      u8g2.setCursor(5, 17);
      u8g2.print("Que faut-il");

      u8g2.setCursor(5, 40); 
      u8g2.print("ce faire");

      u8g2.setCursor(5, 62); 
      u8g2.print("tatouer ?");

    
    } while ( u8g2.nextPage() );


    delay(10000);
}
