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

      if(cmd < 20)
      {

        digitalWrite(10, HIGH);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);

      }
      else if( ( cmd > 80 ) && ( cmd <= 100 ))
      {

        digitalWrite(10, LOW);
        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);

      }      
      else if( ( cmd > 100 ) && ( cmd < 120 ))
      {

        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
        digitalWrite(13, LOW);

      }  
      else if(cmd > 180)
      {

        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);

      }    
      else
      {

        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);

      }    



      Serial.println(cmd);

      //delay(500);

  }

 
}