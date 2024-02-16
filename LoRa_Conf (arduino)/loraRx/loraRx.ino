#include <SoftwareSerial.h>

SoftwareSerial lora(4, 5);


void setup() {
  
  pinMode(12, OUTPUT);
  lora.begin(9600);
  delay(500);
  Serial.begin(9600);
  delay(500);

  Serial.println("Start RX");

}


void loop() {

  if(lora.available())
  {
      digitalWrite(12, HIGH);
      int cmd = lora.read();

      Serial.println(cmd);
      Serial.println("HI");

      if(cmd == '0')
      {
         
        digitalWrite(12, LOW);

      }
      else if(cmd == '1')
      {

          digitalWrite(12, HIGH);

      }

      delay(500);

  }

 
}