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
  SDbytes(path,sd);
  
  drawbitmap(sd);
  free(path); // deallocate memory used for char array
  delay(100);
}
