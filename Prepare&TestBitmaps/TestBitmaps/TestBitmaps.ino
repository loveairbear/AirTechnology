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

void fetchNsketch(char* werd){
  char* w = "/mnt/sda1/Dsprites/";
  char* path =(char*)malloc(strlen(w)+strlen(werd)+1); /* make space for the new string (should check the return value ...) */
  strcpy(path, w); /* copy name into the new var, used strncpy to combat buffer overflow*/
  strcat(path, werd); /* add the extension */
  SDbytes(path,sd);
  
  drawbitmap(sd);
  free(path); // deallocate memory used for char array
  delay(2000); // timer for next bitmap
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

  fetchNsketch("lookrskullfy");
  //fetchNsketch("flamex102");
  //fetchNsketch("wispx1");
  fetchNsketch("pinetree");
  fetchNsketch("food");
  fetchNsketch("pirateship");
  fetchNsketch("clouds");
  fetchNsketch("lookrskullfy");
  fetchNsketch("magicbunny");
  fetchNsketch("emptyglass");
  fetchNsketch("halfglass");
  fetchNsketch("fullglass");
  fetchNsketch("galleyship");
  fetchNsketch("pirateship");
  fetchNsketch("slimer");
  fetchNsketch("pinetree");

}
