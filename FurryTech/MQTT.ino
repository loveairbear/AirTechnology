
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
    if(0 < (int)payload[i]-48 && (int)payload[i]-48!= 255 ){ // the process is to cast integer on first byte of payload array, 
      number =number*multiplier + (int)payload[i] - 48; // then subtract integer cast byte equivalent of "0" which is 48, so 3 in bytes is 51 then subtract
      multiplier += 10; 
    }//endif
  }
  /*
    For some reason, the number 10 cannot be parsed 
  */
  
  if (number== 1){ 
    refresh();
  //  heart(3);                   
    connection();
  }
  else{
    connection();
    matrix.setBrightness(brightness);
  }
 
}




