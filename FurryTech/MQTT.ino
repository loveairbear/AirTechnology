
boolean connection() {
  if (client.connected()) {
    client.subscribe("protobear/com");
    return (true);
  }
  else {
    while(!client.connected()){
      client.connect("arduinoClient","fnhnuaqc","uHKb4wF1tRKe");
    }//endwhile 
  }//endif
}//end func


void callback(char* topic, byte* payload, unsigned int length) {
  refresh();

  uint8_t number = 0;
  uint8_t multiplier = 0;
  for(int i = 0 ; i < 2 ; i++){
      if(0 < (int)payload[i]-48 && (int)payload[i]-48!= 255 ){ // the process is to cast integer on first byte of payload array, 
        number = number*multiplier + (int)payload[i] - 48; // then subtract integer cast byte equivalent of "0" which is 48, so 3 in bytes is 51 then subtract
        multiplier += 10; 
      }//endif
      if(0 < (int)payload[0]-48 && (int)payload[1]-48 == 0){ //because im still not amazing at math and making a beautiful number parser here lies and exception
        number = ((int)payload[0]-48)*10; 
      }//endif
    }// end forloop
  /*
    For some reason, the number 10 cannot be parsed 
  */ 
  if(number==30){
    GhostColor[0] = 0;
    GhostColor[1] = 0;
    GhostColor[2] = 255;
    notificationflag=true;
  }
  if(number==1){fetchNsketch("epicface",animode,7,false);} 
  if(number==2){fetchNsketch("croc",animode,3,false);}
  if(number==3){fetchNsketch("wg0face",1,0,false);}
  if(number==4){hug("circle1");hug("circle2");hug("circle3");}
  if(number==5){fetchNsketch("kissy",animode,16,false);}
  if(number==6){fetchNsketch("cloud",animode,11,false);}
  if(number==7){fetchNsketch("chesth",animode,12,false);}
  if(number==8){fetchNsketch("link" ,1,0,false);}
  if(number==9){fetchNsketch("food" ,1,0,false);}
  if(number==10){fetchNsketch("fire" ,animode,2,false);}
  if(number==11){fetchNsketch("meteor",animode,14,false);}
  if(number==12){fetchNsketch("monkey",1,0,false);}
  if(number==13){fetchNsketch("dragon",animode,17,false);}
  if(number==14){fetchNsketch("mario",1,0,false);}
  if(number==15){fetchNsketch("let",animode,5,false);}
  if(number==16){fetchNsketch("snowcloud",1,0,false);}
  if(number==17){fetchNsketch("stormcloud",1,0,false);}
  if(number==18){fetchNsketch("parrot",1,0,false);}
  if(number==19){fetchNsketch("creeperd",animode,23,false);}
  if(number==20){fetchNsketch("calci",animode,3,false);}
  if(number==21 || number==22 || number==23){
    int matrixwidth = matrix.width();
    while(true){
      matrix.fillScreen(0);
      matrix.setCursor(matrixwidth, 0);
      if(sendnrecv(animode)>0){break;}
      if(number==21){
        matrix.print(F("xoxo"));
        if(--matrixwidth < -45) {matrixwidth = matrix.width();}
      }
      else if(number==22){
        matrix.print(F("ftw"));
        if(--matrixwidth < -26) {matrixwidth = matrix.width();}
      }
      else if(number==23){
        matrix.print(F("ROFL!"));
        if(--matrixwidth < -30) {matrixwidth= matrix.width();}
      }
      matrix.show();
      delay(120);
      matrix.show();
    }
  
  }
  if(number==24){fetchNsketch("moon",5,8,true);}
  if(number==25){fetchNsketch("sun",5,7,true);}
  if(number==26){fetchNsketch("at",animode,0,false);pulse();pulse();pulse();}
  
  
  else{
    connection();
    matrix.setBrightness(brightness);
  }
 
}



