#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#define PIN 12
#include <FileIO.h>
#include <Bridge.h>

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
NEO_MATRIX_TOP   + NEO_MATRIX_LEFT +
NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
NEO_GRB            + NEO_KHZ800);

int sd[64];

void drawbitmap(int colorbuffer[] ){
  
  int bufferindex = 0;
  for (int y = 7 ; y >= 0 ; y--){ //after the color array is built, they are pushed into this loop where it build the each pixel 
    for (int x = 0 ; x < 8 ; x++){     //and displays according to the color array
        matrix.drawPixel(x,y,colorbuffer[bufferindex]);
        bufferindex++;
        
    }
 }
matrix.show();
}// END FUNCTION
void SDbytes(char path[],int sdarray[]){
  File w=FileSystem.open(path,FILE_READ);
  for(int i = 0 ; i <64; i++){
    int x;
    x=w.read() << 8; // Extract the MSB of the 16-bit integer
    x |= w.read(); // Append the LSB to the previous MSB
    sdarray[i] = x;  
  }//end forloop
  w.close();
}// end function
void hug(char path[]){
  SDbytes(path,sd);
  for(int i = 0; i <= 255; i++){
    matrix.setBrightness(i);
    drawbitmap(sd);
  
  }
    for(int i = 255; i>=0; i--){
    matrix.setBrightness(i);
    drawbitmap(sd);
    delay(2);
  
  }

}

void draw(char* werd){
  SDbytes(werd,sd);
  drawbitmap(sd);
  delay(2000);
  x = "";

  

}

void setup() {
  // put your setup code here, to run once:
    pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  matrix.begin();
  matrix.setBrightness(200);
  matrix.fillScreen(0);
  
  Bridge.begin();
  FileSystem.begin();
  
  digitalWrite(13,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  draw("lookrskullfy");
  //draw("flamex102");
  //draw("wispx1");
  draw("pinetree");
  draw("food");
  draw("pirateship");
  draw("clouds");
  draw("lookrskullfy");
  draw("magicbunny");
  draw("emptyglass");
  draw("halfglass");
  draw("fullglass");
  draw("galleyship");
  draw("pirateship");
  draw("slimer");
  draw("pinetree");

}
