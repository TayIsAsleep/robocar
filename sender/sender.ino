//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define joyX A0
#define joyY A1

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();

  Serial.begin(9600);
}
void loop()
{
  int xVal = analogRead(joyX);
  int yVal = analogRead(joyY);

  // Define 
  String str(String(xVal) + " " + String(yVal));
  
  // Length (with one extra character for the null terminator)
  int str_len = str.length() + 1; 
  
  // Prepare the character array (the buffer) 
  char text[str_len];
  
  // Copy it over 
  str.toCharArray(text, str_len);
  
  //Send message to receiver
  radio.write(&text, sizeof(text));
  
  delay(100);
}
