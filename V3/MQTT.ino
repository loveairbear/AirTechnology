
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


  if ((int)payload[0]-48 == 1){
    heart(4);
    connection();
  }
  
  if (((int)payload[0] - 48) == 2) {
    hug("/mnt/sda1/Dsprites/circle1");
    hug("/mnt/sda1/Dsprites/circle2");
    hug("/mnt/sda1/Dsprites/circle3");
  }
  else {
    refresh();
    connection();
  }
}






