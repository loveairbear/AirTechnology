
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


  uint8_t number = 0;
  uint8_t multiplier = 0;
  for(int i = 0 ; i < 2 ; i++){
    if(0 < (int)payload[i]-48 && (int)payload[i]-48!= 255 ){
      
      number =number*multiplier + (int)payload[i] - 48;
      multiplier += 10;
    }//endif
  }
  if (number== 1){ // This casts the first byte (char) into 
    refresh();
    heart(3);                   // integer for comparison agains 48 which is casted '0' char
    connection();
  }
  
  if (number == 2) {fetchNsketch("croc1");fetchNsketch("croc2");fetchNsketch("croc3");}
  if (number == 3) {fetchNsketch("emptyglass");fetchNsketch("halfglass");fetchNsketch("fullglass");connection();}
  if (number == 4) {refresh();heart(4);}
  if (number == 5) {hug("circle1");hug("circle2");hug("circle3");}
  if (number == 6) {fetchNsketch("apple");}
  if (number == 7) {fetchNsketch("food");}
  if (number == 8) {fetchNsketch("flamex101");fetchNsketch("flamex102");}
  if (number == 9) {fetchNsketch("magicbunny");}
  if (number == 10){fetchNsketch("ring");}
  if (number == 11){fetchNsketch("galleyship");}
  if (number == 12){fetchNsketch("coolbird");}
  if (number == 13){fetchNsketch("lollerpop");}
  if (number == 14){fetchNsketch("smokestacks");}
  if (number == 15){fetchNsketch("slimer");}
  if (number == 16){fetchNsketch("wispx1");}
  if (number == 17){fetchNsketch("looklskullfy");fetchNsketch("lookrskullfy");fetchNsketch("looklskullfy");}
  connection();
  matrix.setBrightness(brightness);
 }
 





