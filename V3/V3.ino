
/*
      ___                       ___                         ___           ___           ___     
     /  /\        ___          /  /\         _____         /  /\         /  /\         /  /\    
    /  /::\      /  /\        /  /::\       /  /::\       /  /:/_       /  /::\       /  /::\   
   /  /:/\:\    /  /:/       /  /:/\:\     /  /:/\:\     /  /:/ /\     /  /:/\:\     /  /:/\:\  
  /  /:/~/::\  /__/::\      /  /:/~/:/    /  /:/~/::\   /  /:/ /:/_   /  /:/~/::\   /  /:/~/:/  
 /__/:/ /:/\:\ \__\/\:\__  /__/:/ /:/___ /__/:/ /:/\:| /__/:/ /:/ /\ /__/:/ /:/\:\ /__/:/ /:/___
 \  \:\/:/__\/    \  \:\/\ \  \:\/:::::/ \  \:\/:/~/:/ \  \:\/:/ /:/ \  \:\/:/__\/ \  \:\/:::::/
  \  \::/          \__\::/  \  \::/~~~~   \  \::/ /:/   \  \::/ /:/   \  \::/       \  \::/~~~~ 
   \  \:\          /__/:/    \  \:\        \  \:\/:/     \  \:\/:/     \  \:\        \  \:\     
    \  \:\         \__\/      \  \:\        \  \::/       \  \::/       \  \:\        \  \:\    
     \__\/                     \__\/         \__\/         \__\/         \__\/         \__\/    

Dis my code bruh
 avrdude -c linuxgpio -C /etc/avrdude.conf -p m32u4 -U lfuse:w:0xFF:m -U hfuse:w:0xD8:m -U efuse:w:[color=red][b]0xFB[/b][/color]:m -Uflash:w:$1:i $2

 */
 
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 12// pin for contolling data pin in matrix
#include <FileIO.h>

#include <Bridge.h>

#include <SPI.h>

#include <PubSubClient.h>

#include <YunClient.h>

#include <Process.h>

uint8_t brightness = 255;

Process p;


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
NEO_MATRIX_TOP   + NEO_MATRIX_LEFT +
NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
NEO_GRB            + NEO_KHZ800);


YunClient yun;
PubSubClient client("m10.cloudmqtt.com",16233,callback,yun);



 uint8_t heartpin  = 9; // blue button -- left paw
 uint8_t squarepin  = 8; //grey button -- right paw
 uint8_t crosspin  = 6; //red button --left foot
 uint8_t circlepin  = 5; // yellow button -- right foot

int sd[64];
uint8_t vibratepin = 11;


boolean refresh(){
  matrix.fillScreen(0);
  matrix.show();
  return(true);
}
void vibrate(){
  digitalWrite(vibratepin,HIGH);
  delay(70);
  digitalWrite(vibratepin,LOW);
}



void setup() {
  Bridge.begin();
  FileSystem.begin();
  matrix.begin();
  Serial.begin(9600); // For debugging, wait until the serial console is connected.
  matrix.setBrightness(brightness);//Brigthness for NEOPIXEL matrix
  matrix.fillScreen(0);
  matrix.show(); 
  p.runShellCommand("madplay /mnt/sda1/AirTech/www/Mp3playback/bloop.mp3");
  heart(2);
  pinMode(vibratepin,OUTPUT);
  pinMode(heartpin,INPUT);
  pinMode(squarepin, INPUT);
  pinMode(crosspin, INPUT);
  pinMode(circlepin,INPUT);
  Serial.println(F("m"));
  connection(); // function to connect to mqtt server 


}

void loop(){

  
 
  
 
  
  

  button();
  connection();
  client.loop();
  



     /* 
      for (int i = 0;i<256;i++){
       setPixelColor(3,3,0,255,255,i);
       matrix.show();
      setPixelColor(3,4,0,255,255,i);
      matrix.show();
     setPixelColor(4,4,0,255,255,i);
     matrix.show();
    setPixelColor(4,3,0,255,255,i);
    matrix.show();
     button();
  connection();
  client.loop();  
    }
     
      for (int i = 255;i>=0;i--){
       setPixelColor(3,3,0,255,255,i);
       matrix.show();
      setPixelColor(3,4,0,255,255,i);
     matrix.show();
     setPixelColor(4,4,0,255,255,i);
    
    matrix.show();
    setPixelColor(4,3,0,255,255,i);
   matrix.show(); 
     button();
  connection();
  client.loop();  
    }
*/
}
