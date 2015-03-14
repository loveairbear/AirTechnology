#include <Bridge.h>
#include <FileIO.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 12// pin for contolling data pin in matrix


int sdarray[64]; // Buffer array for bitmap rendering

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
NEO_MATRIX_TOP   + NEO_MATRIX_LEFT +
NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
NEO_GRB            + NEO_KHZ800);


void SDbytes(char path[],int sdarray[]){
File w=FileSystem.open(path,FILE_READ);

  int x;
for(int i = 0 ; i < 64; i++){
  
  x=w.read() << 8; // Extract the MSB of the 16-bit integer
  x |= w.read(); // Append the LSB to the previous MSB
  sdarray[i] = x;  
}//end forloop
w.close();

}// end function

void drawbitmap(int colorbuffer[] ) {

  int bufferindex = 0;
  for (int y = 7 ; y >= 0 ; y--) { //after the color array is built, they are pushed into this loop where it build the each pixel
    for (int x = 0 ; x < 8 ; x++) {    //and displays according to the color array
      matrix.drawPixel(x, y, colorbuffer[bufferindex]);
      bufferindex++;

    }
  }
  matrix.show();
}

void fetchNsketch(char* werd){
  char* w = "/mnt/sda1/Dsprites/";
  char* path =(char*)malloc(strlen(w)+strlen(werd)+1); /* make space for the new string (should check the return value ...) */
  strcpy(path, w); /* copy name into the new var, used strncpy to combat buffer overflow*/
  strcat(path, werd); /* add the extension */
  SDbytes(path,sdarray);

  drawbitmap(sdarray);

  free(path); // deallocate memory used for char array
  delay(1000);

}


void setup() {
  // put your setup code here, to run once:
Bridge.begin();
FileSystem.begin();
Serial.begin(9600);
matrix.begin();
matrix.setBrightness(255);
matrix.fillScreen(0);
matrix.show();
matrix.drawPixel(0,0,matrix.Color(0,255,255));
matrix.show();
delay(500);
matrix.fillScreen(0);
matrix.show();
}

void loop() {

/*
  // put your main code here, to run repeatedly:
File w=FileSystem.open("/mnt/sda1/AirTech/www/DecodedSprites/clouds",FILE_READ);
for(int i = 0 ; i < 64 ; i++){
  int x;
  x=w.read() ; //msb
  x |= w.read() <<8; //lsb
  sdarray[i] = x;
}//end forloop
w.close();
*/
fetchNsketch("apple");
/*
fetchNsketch("confuzzleskullfy");
fetchNsketch("mountainview");
fetchNsketch("flamex101");
fetchNsketch("flamex102");
fetchNsketch("food");
fetchNsketch("emptyglass");
fetchNsketch("halfglass");
fetchNsketch("fullglass");
fetchNsketch("manatwall");
fetchNsketch("pinetree");
fetchNsketch("slimer");
fetchNsketch("wispx1");
fetchNsketch("galleyship");
fetchNsketch("looklskullfy");
fetchNsketch("lookrskullfy");
fetchNsketch("coolbird");
fetchNsketch("lollerpop");
fetchNsketch("magicbunny");
fetchNsketch("ring");
fetchNsketch("exclamaskullfy");
fetchNsketch("smokestacks");
fetchNsketch("xmastree");
fetchNsketch("lul");
*/
}
