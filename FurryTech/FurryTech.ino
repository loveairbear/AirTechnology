/*
  ____,__, ____, ____ ____, ____,____, 
 (-/_|(-| (-|__)(-|__|-|_, (-/_|(-|__) 
 _/  |,_|_,_|  \,_|__)_|__,_/  |,_|  \,
 
 birthed by QIA, the next newtype
 
 
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

uint8_t idlex[]={0,1,2,3,3,2,1,0,0,1,2,3,4,5,6,7,6,5,4,4,5,6,7,6,5,4,3,3,2,1,0,0,0};

uint8_t idley[]={0,1,1,2,3,4,4,5,6,7,7,6,6,7,7,6,5,5,4,3,2,2,1,0,0,0,1,2,3,3,2,1,0};
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
  delay(60);
  Bridge.begin();
  FileSystem.begin();
  matrix.begin();
  //Serial.begin(9600); // For debugging, wait until the serial console is connected.
  matrix.setBrightness(brightness);//Brigthness for NEOPIXEL matrix
  matrix.fillScreen(0);
  matrix.show(); 
  playmusic("bloop.mp3");
  heart(2);
  pinMode(vibratepin,OUTPUT);
  
  pinMode(heartpin,INPUT);
  pinMode(squarepin, INPUT);
  pinMode(crosspin, INPUT);
  pinMode(circlepin,INPUT);
  client.connect("arduinoClient","fnhnuaqc","uHKb4wF1tRKe");
  connection(); // function to connect to mqtt server 
}

void loop(){
  button();
  connection();
  client.loop();

/*

      for(int i = 0;i < 34;i++){
        matrix.drawPixel(idlex[i],idley[i],matrix.Color(255,0,255));
       
        setPixelColor(idlex[(i-1)%33],idley[(i-1)%33],255,0,255,100);
        setPixelColor(idlex[(i-2)%33],idley[(i-2)%33],255,0,255,60);
        setPixelColor(idlex[(i-3)%33],idley[(i-3)%33],255,0,255,30);
        setPixelColor(idlex[(i-4)%33],idley[(i-4)%33],255,0,255,10);
        matrix.show();
             button();
        connection();
        client.loop(); 
        delay(100);
      }
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
