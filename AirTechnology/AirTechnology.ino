/*
  ____,__, ____, ____ ____, ____,____, 
 (-/_|(-| (-|__)(-|__|-|_, (-/_|(-|__) 
 _/  |,_|_,_|  \,_|__)_|__,_/  |,_|  \,
 
 Birthed by Imran Ahmed
 
 
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

Process p;
// MATRIX INTIALIZATION // For airbear FLEXIBLE matrix

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
NEO_MATRIX_TOP   + NEO_MATRIX_LEFT +
NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
NEO_GRB            + NEO_KHZ800);

// For adafruit 8x8 RIGID matrix
/*
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
NEO_GRB            + NEO_KHZ800);
*/
//Ghost Animation
uint8_t idlex[]={0,1,2,3,3,2,1,0,0,1,2,3,4,5,6,7,6,5,4,4,5,6,7,6,5,4,3,3,2,1,0,0,0};

uint8_t idley[]={0,1,1,2,3,4,4,5,6,7,7,6,6,7,7,6,5,5,4,3,2,2,1,0,0,0,1,2,3,3,2,1,0};

/* VARIABLES FOR MQTT */
YunClient yun;
PubSubClient client("m10.cloudmqtt.com",16233,callback,yun);


/* VARIABLES FOR BUTTONS */
#define heartpin 9 // blue button -- left paw
#define squarepin 8 //grey button -- right paw
#define hugpin 7
#define crosspin 6 //red button --left foot
#define circlepin 5 // yellow button -- right foot

int sd[64]; //buffer array for bitmap rendering
#define vibratepin 11
char* branch="protobear/sig";
uint8_t index = 0;// global index to scroll through emoticons in sendmode

char* mqttmsg;//global buffer for mqtt, this way i can control how i latch my mqtt messages for latch function


//Mode and exit flags//
uint8_t animode=0; // mode signals for program mechanics
uint8_t mqttsig=0; //exit status for program mechanics
uint8_t exitsig=0;
bool notificationflag=false;

//Interfaced vars
uint8_t GhostColor[]={0,255,255}; // This is the idle animation which also provides push notification
uint8_t brightness = 255;  // Should be a multiple of 5
const uint8_t soundsize = 14;

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
  delay(200);
  //Serial.begin(9600);
  Bridge.begin();
  FileSystem.begin();
  matrix.begin();
  matrix.setBrightness(brightness);//Brightness for NEOPIXEL matrix
  matrix.fillScreen(0);
  matrix.show(); 
  matrix.setTextWrap(false);
  matrix.setTextColor(matrix.Color(0,255,0));
  pinMode(vibratepin,OUTPUT);
  pinMode(heartpin,INPUT);
  pinMode(squarepin, INPUT);
  pinMode(crosspin, INPUT);
  pinMode(circlepin,INPUT);
  pinMode(hugpin,INPUT);
  client.connect("arduinoClient","fnhnuaqc","uHKb4wF1tRKe");
  connection(); // function to connect to mqtt server 
  playmusic("light");
  //fetchNsketch("monkey",1,0,false);
  vibrate();
}

void loop(){
  //fetchNsketch("hb",0,2,true);
  /*
  heart(1);
  heart(2);
  heart(3);
  heart(4);
  delay(3000);
  /*
  fetchNsketch("angel",2,12,false);
  
  matrix.setBrightness(brightness);

  fetchNsketch("hb",0,2,true);
  fetchNsketch("hb",0,2,true);
    fetchNsketch("hb",0,2,true);
  

 /*
  fetchNsketch("muzak",0,2,true);
  fetchNsketch("muzak",0,2,true);
    fetchNsketch("muzak",0,2,true);
  fetchNsketch("muzak",0,2,true);
  /*
  lightningstorm();
  lightningstorm();
  lightningstorm();
  lightningstorm();
  /*
  fetchNsketch("at",1,0,false);
  for(int i = 255;i>=0;i-=5){
    matrix.setBrightness(i);
    matrix.show();
    delay(5);
  }
    fetchNsketch("at",1,0,false);
  for(int i = 255;i>=0;i-=5){
    matrix.setBrightness(i);
    matrix.show();
    delay(5);
  }
  fetchNsketch("at",1,0,false);
  for(int i = 255;i>=0;i-=5){
    matrix.setBrightness(i);
    matrix.show();
    delay(5);
  }
    fetchNsketch("at",1,0,false);
  for(int i = 255;i>=0;i-=5){
    matrix.setBrightness(i);
    matrix.show();
    delay(5);
  }
    fetchNsketch("at",1,0,false);
  for(int i = 255;i>=0;i-=5){
    matrix.setBrightness(i);
    matrix.show();
    delay(5);
  }
  fetchNsketch("at",1,0,false);
  for(int i = 255;i>=0;i-=5){
    matrix.setBrightness(i);
    matrix.show();
    delay(5);
  }  fetchNsketch("at",1,0,false);
  for(int i = 255;i>=0;i-=5){
    matrix.setBrightness(i);
    matrix.show();
    delay(5);
  }
    fetchNsketch("at",1,0,false);
  for(int i = 255;i>=0;i-=5){
    matrix.setBrightness(i);
    matrix.show();
    delay(5);
  }
  fetchNsketch("at",1,0,false);
  for(int i = 255;i>=0;i-=5){
    matrix.setBrightness(i);
    matrix.show();
    delay(5);
  }
  /*
  matrix.setBrightness(250);
  fetchNsketch("sun",5,7,true);
  fetchNsketch("sun",5,7,true);
  fetchNsketch("sun",5,7,true);
  fetchNsketch("sun",5,7,true);
  
  fetchNsketch("cloud",animode,11,true);
  fetchNsketch("chesth",animode,12,true);
  fetchNsketch("dragon",animode,17,true);
  fetchNsketch("kissy",animode,16,true);
  
  fetchNsketch("calci",animode,3,true);
  */
      connection();
      for(int i = 0;i < 36;i++){
        if(notificationflag==true && i%2==0){ // if the notification flag is active then create arrowhead around ghost
          matrix.drawPixel(idlex[(i)%36],idley[(i)%36]-1,matrix.Color(GhostColor[0],GhostColor[1],GhostColor[2]));
          matrix.drawPixel(idlex[(i)%36]+1,idley[(i)%36]-1,matrix.Color(GhostColor[0],GhostColor[1],GhostColor[2]));
          matrix.drawPixel(idlex[(i)%36]+1,idley[(i)%36],matrix.Color(GhostColor[0],GhostColor[1],GhostColor[2]));
        }
        setPixelColor(idlex[(i)%37],idley[(i)%36],GhostColor,255);
        setPixelColor(idlex[(i-1)%38],idley[(i-1)%36],GhostColor,150);
        setPixelColor(idlex[(i-2)%39],idley[(i-2)%36],GhostColor,125);
        setPixelColor(idlex[(i-3)%36],idley[(i-3)%36],GhostColor,100);
        matrix.show();
        button();
        //offline();
        client.loop(); 
        delay(180);
        refresh();
      }
      refresh();
      //for(int i=0;i<10000;i++){button();client.loop(); }
   
  

}
