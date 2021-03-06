
boolean connection() {
  if (client.connected()) {
    client.subscribe("protobear/com");
    if(notificationflag==false){
      GhostColor[0]=255;
      GhostColor[1]=255;
      GhostColor[2]=10;
    }
    client.loop();
      
    return (true);
  }
  else {
    if(!client.connected()){
      
      for(int i = 0 ; i<10;i++){
        client.connect("arduinoClient","apjtgmvm","Y2c5YXfdCULY");
        if(client.connected()){client.loop();return true;
      }
      
      }
      GhostColor[0]=150;
      GhostColor[1]=150;
      GhostColor[2]=150;
      return false;
    }//endwhile 
  }//endif
}//end func


void callback(char* topic, byte* payload, unsigned int length) {
  refresh();
 uint8_t number=0;
 uint8_t multiplier=0;
  
  for(int n=0;n<length;n++){
    number = number*multiplier+(payload[n]-48);
    multiplier += 10;
  }
  
  if(number==30){
    GhostColor[0] = 0;
    GhostColor[1] = 10;
    GhostColor[2] = 255;
    notificationflag=true;
  }
  if(number==1){fetchNsketch("epicface",animode,7,false);} 
  if(number==2){fetchNsketch("croc",animode,3,false);}
  if(number==3){fetchNsketch("kitty",animode,3,false);}
  if(number==4){
    hug("circle1");hug("circle2");hug("circle3");
   }
  if(number==5){fetchNsketch("kissy",animode,16,false);}
  if(number==6){fetchNsketch("cloud",animode,11,false);}
  if(number==7){fetchNsketch("chesth",animode,12,false);}
  if(number==8){fetchNsketch("meteor" ,animode,15,false);}
  if(number==9){fetchNsketch("food" ,1,0,false);}
  if(number==10){fetchNsketch("fire" ,animode,2,false);}
  if(number==11){fetchNsketch("rocket",animode,10,false);}
  if(number==12){fetchNsketch("monkey",1,0,false);}
  if(number==13){fetchNsketch("dragon",animode,17,false);}
  if(number==14){fetchNsketch("angel",animode,12,false);}
  if(number==15){fetchNsketch("hb",animode,2,false);}
  if(number==16){fetchNsketch("snowcloud",1,0,false);}
  if(number==17){fetchNsketch("lightning",animode,3,false);}
  if(number==18){fetchNsketch("if",1,0,true);}
  if(number==19){fetchNsketch("zen",1,0,true);}
  if(number==20){fetchNsketch("calci",animode,3,false);}
        if(number==21){
        fetchNsketch("xoxo",animode,19,false);
      }
  if(number==22 || number==23 || number==28){
    int matrixwidth = matrix.width();
    while(true){
      matrix.fillScreen(0);
      matrix.setCursor(matrixwidth, 0);
      if(sendnrecv(animode)>0){break;}
      else if(number==22){
        matrix.print(F("ftw"));
        if(--matrixwidth < -26) {matrixwidth = matrix.width();}
      }
      else if(number==23){
        matrix.print(F("ROFL!"));
        if(--matrixwidth < -30) {matrixwidth= matrix.width();}
      }
      else if(number==28){
        matrix.print(F("4x9=36"));
        if(--matrixwidth < -30) {matrixwidth= matrix.width();}
      }
      matrix.show();
      delay(120);
      matrix.show();
    }//
  }
  if(number==24){fetchNsketch("moon",5,8,true);}
  if(number==25){fetchNsketch("sun",5,7,false);}
  if(number==26){    
    fetchNsketch("at",1,0,false);
    delay(2000);
    for(int i = 255;i>=0;i-=5){
      matrix.setBrightness(i);
      matrix.show();
      delay(5);
  }
  matrix.setBrightness(brightness);
  matrix.show();
}
  if(number==27){fetchNsketch("chat",animode,6,false);}
  if(number==28){fetchNsketch("trees",animode,5,false);}
  if(number==29){fetchNsketch("bleuf",1,0,false);}
  //if(number==30){fetchNsketch("clock",1,0,false);}
  if(number==31){fetchNsketch("feubleu",1,0,false);}
  if(number==32){fetchNsketch("berobor",1,0,false);}
  if(number==33){fetchNsketch("borbor",1,0,false);}
  if(number==34){fetchNsketch("stopwatch",1,0,false);}
  if(number==35){fetchNsketch("meditate",1,0,false);}
  if(number==36){fetchNsketch("wrench",1,0,false);}
  if(number==37){fetchNsketch("gft",1,0,false);}
  if(number==38){fetchNsketch("creeperd",animode,23,false);}
  
  else{
    connection();
    matrix.setBrightness(brightness);
  }
 
}



