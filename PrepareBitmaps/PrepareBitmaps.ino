#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif
#define PIN 12
#include <FileIO.h>
#include <Bridge.h>

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
                            NEO_MATRIX_TOP   + NEO_MATRIX_LEFT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

int a[64];

void SDbytes(char path[], int sdarray[]) {
  File w = FileSystem.open(path, FILE_READ);
  int x;
  for (int i = 0 ; i < 64; i++) {
    x = w.read() << 8; // Extract the MSB of the 16-bit integer
    x |= w.read(); // Append the LSB to the previous MSB
    sdarray[i] = x;
  }//end forloop
  w.close();

}// end function


void getem(char filepath[], int colorbuffer[64]) {
  //Serial.println("function opened");
  int r = 0;
  int g = 0;  //initializing/resetting  all colors and all values
  int b = 0;
  int bitmapcolor = matrix.Color(0, 0, 0);
  int seeking = 51;
  //int seeking = 54; // location of color code in binary/hex
  File  thebmp = FileSystem.open(filepath, FILE_READ);
  Serial.println(thebmp);


  //int  colorbuffer[64]; // a temporary array where the converted rgb values will be stored
  //int seeking = 51; //this is the starting point where the actual color data is stored anything before is simply header and properties info

  for (int x = 0 ; x < 64 ; x++) {
    seeking = seeking + 3;// skip every 3 hex byte, essentially skip to next color
    thebmp.seek(seeking);

    for (int i = 1 ; i <= 3 ; i++) {

      if (i = 1) {
        b = thebmp.read();

      }

      if (i = 2) {
        g = thebmp.read();

      }

      if (i = 3) {
        r = thebmp.read();

        bitmapcolor = matrix.Color(onlypos(r, 40), g, b); //this value acts as a temporary storage to then place in the other storage
      }
    }
    colorbuffer[x] = bitmapcolor;  //this then appends the bitmapcolor value in, if you read the values here they arnt standard RGB or HEX

  }

  thebmp.close();
}// END FUNCTION
void drawbitmap(int colorbuffer[] ) {

  int bufferindex = 0;
  for (int y = 7 ; y >= 0 ; y--) { //after the color array is built, they are pushed into this loop where it build the each pixel
    for (int x = 0 ; x < 8 ; x++) {    //and displays according to the color array
      matrix.drawPixel(x, y, colorbuffer[bufferindex]);
      bufferindex++;

    }
  }
  matrix.show();
}// END FUNCTION


int onlypos(int number, int subtracter) {
  if (number >= 200) {
    return (number - subtracter);
  }
  if (number < 200) {
    return number;
  }
}// END FUNCTION
void sdwrite(char filepath[], int array[]) {
  File f = FileSystem.open(filepath, FILE_WRITE);
  for (int i = 0; i < 64 ; i++) {
    int high = highByte(array[i]);
    int low =  lowByte(array[i]);
    f.write(high);
    f.write(low);
  }
  f.close();
}
void fetchNsketch(char* werd) {
  /*
  char* w = "/mnt/sda1/Dsprites/";
  char* path =(char*)malloc(strlen(w)+strlen(werd)+1); /* make space for the new string (should check the return value ...) */
  //strcpy(path, w); /* copy name into the new var, used strncpy to combat buffer overflow*/
  //strcat(path, werd); /* add the extension */

  SDbytes(werd, a);

  drawbitmap(a);
  //free(path); // deallocate memory used for char array
  //delay(100);
}
void fullpkg(char* werd, char* decoded) {

  char* w = "/mnt/sda1/Sprites/";
  char* path = (char*)malloc(strlen(w) + strlen(werd) + 1); /* make space for the new string (should check the return value ...) */
  strcpy(path, w); /* copy name into the new var, used strncpy to combat buffer overflow*/
  strcat(path, werd); /* add the extension */
  getem(path, a);
  free(path);
  char* f = "/mnt/sda1/Dsprites/";
  char* file = (char*)malloc(strlen(f) + strlen(decoded) + 1); /* make space for the new string (should check the return value ...) */
  strcpy(file, f); /* copy name into the new var, used strncpy to combat buffer overflow*/
  strcat(file, decoded); /* add the extension */
  sdwrite(file, a);
  fetchNsketch(file);
  free(file);
  delay(500);
}


void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  matrix.begin();
  matrix.setBrightness(200);
  matrix.fillScreen(0);
  Bridge.begin();
  FileSystem.begin();

  digitalWrite(13, LOW);
}


void loop() {
  
  fullpkg("dragon.bmp", "dragon");
  fullpkg("360ninja2.bmp","360ninja2");
  fullpkg("360ninja3.bmp","360ninja3");
  fullpkg("360ninja4.bmp","360ninja4");
  /*
  fullpkg("fullglass.bmp","fullglass");
  fullpkg("evey.bmp","evee");
  fullpkg("emptyglass.bmp","emptyglass");
  fullpkg("food.bmp","food");
  fullpkg("croc3.bmp","croc3");
  fullpkg("croc2.bmp","croc2");
  fullpkg("croc1.bmp","croc1");
  fullpkg("circle1.bmp","circle1");
  fullpkg("circle2.bmp","circle2");
  fullpkg("circle3.bmp","circle3");
  fullpkg("wg0face.bmp","gundam");
  fullpkg("apple.bmp","apple");
  fullpkg("starcastf3x.bmp","star3x");
  fullpkg("starcastf3o.bmp","star3");
  fullpkg("starcastf2.bmp","star2");
  fullpkg("squirtle.bmp","squirtle");
  fullpkg("starcast.bmp","starcast");
  fullpkg("rooster.bmp","rooster");
  fullpkg("pikasnu.bmp","pikachu");
  fullpkg("pikaface.bmp","pikaface");
  fullpkg("peach.bmp","peach");
  */
  digitalWrite(13, HIGH);
  delay(20000);
  digitalWrite(13, LOW);

}
