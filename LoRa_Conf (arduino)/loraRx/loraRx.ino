#include <SoftwareSerial.h>

SoftwareSerial lora(4, 5);


void setup() {
  
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  lora.begin(9600);
  delay(500);
  Serial.begin(9600);
  delay(500);

  Serial.println("Start RX");

}


void loop() {

  if(lora.available())
  {
      int cmd = lora.read();


      Serial.println(cmd);

      //delay(500);

  }

 
}