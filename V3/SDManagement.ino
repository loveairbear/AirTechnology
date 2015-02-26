
void SDbytes(char path[],int sdarray[]){
  File w=FileSystem.open(path,FILE_READ);
  for(int i = 0 ; i < 64; i++){
    int x;
    x=w.read() << 8; // Extract the MSB of the 16-bit integer
    x |= w.read(); // Append the LSB to the previous MSB
    sdarray[i] = x;  
  }//end forloop
  w.close();
}// end function


//AIRBEAR BITMAP
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

/*
void draw(char* werd){
   char* w = "/mnt/sda1/AirTech/www/DecodedSprites/";
  SDbytes(strcat(w,werd),sd);
  drawbitmap(sd);
  

}
*/

