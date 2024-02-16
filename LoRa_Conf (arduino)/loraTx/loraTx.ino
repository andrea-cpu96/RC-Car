#include <SoftwareSerial.h>

SoftwareSerial lora(4, 5);


void setup() {
  

  pinMode(8, INPUT);
  pinMode(9, INPUT);


  lora.begin(9600);
  delay(500);
  Serial.begin(9600);
  delay(500);

  while(!lora.available());
  int cmd = lora.read();
  Serial.println("ok");


}

void loop() {
   
  int padX_raw = 0;
  int padY_raw = 0;
  int padX_old = 0;
  int padY_old = 0; 
  int padX = 0;
  int padY = 0;  
  int rx;
  int cmd = 0; 

  padX_raw = analogRead(0);
  padY_raw = analogRead(1);


  int pad_delta = 0;
  int flag = 0;

  padX = map(padX_raw, 0, 1023, 0, 180);
  padY = map(padY_raw, 0, 1023, 0, 255);

	// Evaluate the difference between angle and angle_new
	if(padX_old >= padX)
		pad_delta = padX_old- padX;
	else
		pad_delta = padX- padX_old;

	// Update the angle only for changes of at least 2 degrees
	if(pad_delta > 10)
  {

		flag = 1;
    padX_old = padX;
  
  }

	// Evaluate the difference between speed and speed_new
	if(padY_old >= padY)
		pad_delta = padY_old- padY;
	else
		pad_delta = padY- padY_old;

	// Update the speed only for changes of at least 500 mV
	if(pad_delta > 20)
  {

		flag = 1;
    padY_old = padY;

  }



if(flag)
{

  flag = 0;

  lora.write(padX);

  Serial.println("invio1");

  while(!lora.available());

  cmd = lora.read();
  Serial.println("ok");

  lora.write(padY);
  while(!lora.available());

  cmd = lora.read();
  Serial.println("ok");

}

}
