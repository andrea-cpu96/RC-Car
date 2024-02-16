#include <SoftwareSerial.h>
#include "LoRa_E220.h"

SoftwareSerial lora(4, 5);


void setup() {
 
  lora.begin(9600);
  Serial.begin(9600);
  delay(500);

  uint8_t buff[] = { 0xC0, 0x00, 0x00, 0x62, 0x00, 0x17 };
 
  lora.write((uint8_t *)buff, 6);

  delay(500);

  Serial.println("Factory reset");

}

void loop() {
  
  if(lora.available())
  {

    char c = lora.read();
    Serial.println(c);

  }

}
