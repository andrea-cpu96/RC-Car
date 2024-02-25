#include <SoftwareSerial.h>

SoftwareSerial lora(4, 5);


void setup() {
  

  pinMode(8, INPUT);
  pinMode(9, INPUT);


  lora.begin(9600);
  delay(500);
  Serial.begin(9600);
  delay(500);

}

void loop() {
   
  delay(500);
  lora.write(1);
  
  Serial.println("ok");

}