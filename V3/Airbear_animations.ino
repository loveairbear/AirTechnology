

//AIRBEAR ANIMATIONS
uint8_t heartx[]  = {4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 2};//Outer layer of the heart
uint8_t hearty[]  = {5, 4, 3, 2, 1, 0, 0, 1, 0, 0, 1, 2, 3, 4, 3};

uint8_t heartx1[] = {4, 5, 6, 6, 5, 4, 3, 2, 2, 3};//Middle layer of the heart
uint8_t hearty1[] = {4, 3, 2, 1, 1, 2, 1, 1, 2, 3};

uint8_t heartx2[] = {4, 5, 3}; //Core of the heart
uint8_t hearty2[] = {3, 2, 2};




void setPixelColor( uint16_t x, int y, uint8_t r, uint8_t g, uint8_t b, uint16_t brightness) {
  int  color = matrix.Color((brightness * r / 255) , (brightness * g / 255), (brightness *b / 255)); // the pgm_read is exponential gamma correction
  matrix.drawPixel(x, y, color);
  matrix.show();
}




uint32_t Wheel(byte WheelPos) { // The Color Wheel which will select a color baseed on the input base
  if (WheelPos < 85) {
    return matrix.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return matrix.Color(255 - WheelPos * 3, 0, WheelPos * 3); 
  }
  else {
    WheelPos -= 170;
    return matrix.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

int heart(uint8_t showing) {
  if (showing == 1) { //
    matrix.setBrightness(brightness);

    for (int j = 0; j < 256; j++) { 
      //if (cancelpin()){return(1);}
      for (int lol = 0;  lol < 15 ; lol++) {// + 30 ( 2 colors at same time),9 double rainbow , the + 40 added to j causes a faster color change in the ring

        matrix.drawPixel(heartx[lol], hearty[lol], (Wheel((lol + j  ) & 255)));
        matrix.show();
      }

      for (int lol = 0;  lol < 10 ; lol++) {

        matrix.drawPixel(heartx1[lol], hearty1[lol], Wheel((lol + j) & 255));
        matrix.show();
      }

      for (int lol = 0;  lol < 3 ; lol++) {


        matrix.drawPixel(heartx2[lol], hearty2[lol], Wheel((lol + j) & 255));
        matrix.show();
      }
    }
    fader(brightness, 20);
    refresh();
    return (showing);
  }
  if (showing == 2) { // Full raibow cycling through heart
    matrix.setBrightness(brightness);
    for (int j = 0; j < 256 ; j++) { 
      //if(cancelpin()){return(2);}
      for (int lol = 0;  lol < 14 ; lol++) {
        int color = Wheel(((lol * 255 / 14) + j) & 255); 
        matrix.drawPixel(heartx[lol], hearty[lol], color);
        matrix.show();
      }

    }
    fader(brightness, 20);
    refresh();
    return (2);
    
  }

  if (showing == 3) {// rainbow heart which has 2 colors on the screen at a time
    matrix.setBrightness(brightness);
    for (int j = 0; j < 256; j++) { 
      //if (cancelpin()){return(3);}
      for (int lol = 0;  lol < 15 ; lol++) {
        int color = (Wheel((lol + j + 40  ) & 255));

        matrix.drawPixel(heartx[lol], hearty[lol], color);
        matrix.show();
      }

      for (int lol = 0;  lol < 10 ; lol++) {

        matrix.drawPixel(heartx1[lol], hearty1[lol], Wheel((lol + j) & 255));
        matrix.show();
      }

      for (int lol = 0;  lol < 3 ; lol++) {
        matrix.drawPixel(heartx2[lol], hearty2[lol], Wheel((lol + j) & 255));
        matrix.show();
      }
    }
    fader(brightness, 20);
    refresh();
    return (showing);
  }



  if (showing == 4) {// Red Heart
    matrix.setBrightness(brightness);    
    for (uint8_t lol = 0;  lol < 15 ; lol++) {
      matrix.drawPixel(heartx[lol], hearty[lol], matrix.Color(255,0,0));
      matrix.show();
    }

    for (uint8_t lol = 0;  lol < 10 ; lol++) {
      matrix.drawPixel(heartx1[lol], hearty1[lol], matrix.Color(255,0,0));
      matrix.show();
    }

    for (uint8_t lol = 0;  lol < 3 ; lol++) {
      //int color = Wheel(((lol * 256 /14) + j) & 255);

      matrix.drawPixel(heartx2[lol], hearty2[lol], matrix.Color(255,0,0));
      matrix.show();
    }
    return (showing);
  }
}

/*
void lightningstorm(){


  int cloud = matrix.Color(120, 120, 120);
  matrix.drawLine(0, 2, 7, 2, cloud);
  matrix.drawLine(0, 1, 3, 1, cloud);
  matrix.drawLine(1, 0, 2, 0, cloud);
  matrix.drawLine(0, 3, 2, 3, cloud);
  matrix.drawLine(6, 3, 7, 3, cloud);
  matrix.drawLine(5, 3, 6, 1, cloud);
  matrix.drawPixel(1, 4, cloud);
  matrix.show();
  delay(500);
  int lightning = matrix.Color(255, 255, 0);
  matrix.drawLine(3, 5, 6, 5, lightning);
  matrix.drawPixel(3, 4, lightning);
  matrix.drawPixel(4, 6, lightning);
  matrix.drawPixel(5, 4, lightning);
  matrix.drawPixel(6, 6, lightning);
  matrix.drawPixel(7, 7, lightning);
  matrix.show();
  delay(50);
  matrix.fillScreen(0);
  matrix.drawLine(0, 2, 7, 2, cloud);
  matrix.drawLine(0, 1, 3, 1, cloud);
  matrix.drawLine(1, 0, 2, 0, cloud);
  matrix.drawLine(0, 3, 2, 3, cloud);
  matrix.drawLine(6, 3, 7, 3, cloud);
  matrix.drawLine(5, 3, 6, 1, cloud);
  matrix.drawPixel(1, 4, cloud);
  matrix.show();
  delay(300);
  matrix.drawLine(3, 5, 6, 5, lightning);
  matrix.drawPixel(3, 4, lightning);
  matrix.drawPixel(4, 6, lightning);
  matrix.drawPixel(5, 4, lightning);
  matrix.drawPixel(6, 6, lightning);
  matrix.drawPixel(7, 7, lightning);
  matrix.show();
  delay(1000);
  matrix.fillScreen(0);
}
*/
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

void fader(int prebrightness, int timer) {
  for (int q = prebrightness ; q >= 0  ; q--) {

    matrix.setBrightness(q);
    matrix.show();
    delay(timer);
  }
  matrix.setBrightness(brightness);
}
