
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
}
  if(number==1){fetchNsketch("epicface",animode,7);} 
  if(number==2){fetchNsketch("croc",animode,3);}
  if(number==3){fetchNsketch("wg0face",1,0);}
  if(number==4){hug("circle1");hug("circle2");hug("circle3");}
  if(number==5){fetchNsketch("kissy",animode,16);}
  if(number==6){fetchNsketch("cloud",animode,11);}
  if(number==7){fetchNsketch("chesth",animode,12);
  if(number==8){fetchNsketch("link" ,1,0);}
  if(number==9){fetchNsketch("food" ,1,0);}
  if(number==10){fetchNsketch("fire" ,animode,2);}
  if(number==11){heart(3)}
  if(number==12){fetchNsketch("monkey",1,0);}
  if(number==13){heart(2);}
  if(number==14){fetchNsketch("mario",1,0);}
  if(number==15){fetchNsketch("let",animode,5);}
  if(number==16){fetchNsketch("snowcloud",1,0);}
  if(number==17){fetchNsketch("stormcloud",1,0);}
  if(number==18){fetchNsketch("parrot",1,0);}
  if(number==19){fetchNsketch("link",1,0);}
  if(number==20){fetchNsketch("calci",animode,3);}
  else{
    connection();
    matrix.setBrightness(brightness);
  }
 
}



