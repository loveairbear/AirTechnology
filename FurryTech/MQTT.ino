
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
      number =number*multiplier + (int)payload[i] - 48; // then subtract integer cast byte equivalent of "0" which is 48, so 3 in bytes is 51 then subtract
      multiplier += 10; 
    }//endif
  }
  /*
    For some reason, the number 10 cannot be parsed 
  */  
  if (number== 1){while true {fetchNsketch("cloud",0,11);}}
  if (number==2){while true {fetchNsketch("kissy",0,16);}}
  if (number==3){while true {fetchNsketch("croc",0,3);}}
  if(number==4){while true {fetchNsketch("chesth",0,12);}}
  if(number==5){
      hug("circle1");
    hug("circle2");
    hug("circle3");}
  if(number==6){fetchNsketch("link" ,0,0);}
  if(number==7){fetchNsketch("food" ,0,0);}
  if(number==8){fetchNsketch("fire" ,0,2);}
  if(number==9){fetchNsketch("epicface",0,7);}
  if(number==10){heart(3);}
  if(number==11){fetchNsketch("monkey",0,0);}
  if(number==12){heart(2);}
  if(number==13){fetchNsketch("mario",0,0);}
  if(number==14){fetchNsketch("let",0,5);}
  if(number==15){fetchNsketch("snowcloud",0,0);}
  if(number==16){fetchNsketch("stormcloud",0,0);}
  if(number==17){fetchNsketch("parrot",0,0);}
  if(number==18){fetchNsketch("link",0,0);}
  if(number==19){fetchNsketch("wg0face",0,0);}
  if(number==20){fetchNsketch("calci",0,3);}
  else{
    connection();
    matrix.setBrightness(brightness);
  }
 
}




