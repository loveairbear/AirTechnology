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
  int b[64];
  int c[64];

void getem(char filepath[], int colorbuffer[64]){
//Serial.println("function opened");
int r = 0;
int g = 0;  //initializing/resetting  all colors and all values
int b = 0;
int bitmapcolor = matrix.Color(0,0,0);
int seeking = 51;
//int seeking = 54; // location of color code in binary/hex
File  thebmp = FileSystem.open(filepath,FILE_READ);  
Serial.println(thebmp);

 
 //int  colorbuffer[64]; // a temporary array where the converted rgb values will be stored
  //int seeking = 51; //this is the starting point where the actual color data is stored anything before is simply header and properties info

   for (int x = 0 ; x < 64 ; x++){
        seeking = seeking + 3;// skip every 3 hex byte, essentially skip to next color
        thebmp.seek(seeking);

         for (int i = 1 ; i <= 3 ; i++){
         
           if (i = 1){
             b = thebmp.read();
             
           }
         
            if (i = 2){
            g = thebmp.read();

            }
         
            if (i = 3){
            r = thebmp.read(); 
         
            bitmapcolor = matrix.Color(onlypos(r,40),g,b); //this value acts as a temporary storage to then place in the other storage
          }
        }
        colorbuffer[x] = bitmapcolor;  //this then appends the bitmapcolor value in, if you read the values here they arnt standard RGB or HEX  

}

 thebmp.close();
}// END FUNCTION
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


int onlypos(int number, int subtracter){
if (number >= 200){return(number-subtracter);}  
if (number < 200){return number;}

  
}// END FUNCTION

/*
SDbytes(String file,int WritingArray){
int sdarray[64];
String path = "/mnt/sda1/DSprites/"
  
File w = FileSystem.open(path+file,FILE_WRITE);
for (int i = 0; i <64 ; i++){
  int high = highByte(WritingArray[i]);
  int low =  lowByte(WritingArray[i]);
  w.write(high);
  w.write(low);
}
w.close();


File w=FileSystem.open(path+file,FILE_READ);
for(int i = 1 ; i < 65 ; i++){
  int x;
  x=w.read() << 8; //msb
  x |= w.read() <<8; //lsb
  sdarray[i] = x;  
}//end forloop
w.close();
return sdarray;
}
*/

void sdwrite(char filepath[],int array[]){
File f = FileSystem.open(filepath,FILE_WRITE);
for (int i = 0; i <64 ; i++){
  int high = highByte(array[i]);
  int low =  lowByte(array[i]);
  f.write(high);
  f.write(low);
}
f.close();
}
void setup() {
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  matrix.begin();
  matrix.setBrightness(200);
  matrix.fillScreen(0);
  
  Bridge.begin();
  FileSystem.begin();
  
  digitalWrite(13,LOW);
  }

void loop(){
    getem("/mnt/sda1/Sprites/wispx1.bmp",a);
    getem("/mnt/sda1/Sprites/speechlessskullfy.bmp",b);
    getem("/mnt/sda1/Sprites/surlyskullfy.bmp",c);

    
    sdwrite("/mnt/sda1/DSprites/wispx1",a);   
    sdwrite("/mnt/sda1/DSprites/speechlessskullfy",b);
    sdwrite("/mnt/sda1/DSprites/surlyskullfy",c);
    
 digitalWrite(13,HIGH);
delay(20000);
digitalWrite(13,LOW);

}  
