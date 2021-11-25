//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <AccelStepper.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

// Variables
int offset;
int xVal;

void setup()
{
  offset = 0;
  xVal = 0;
  
  stepper.setMaxSpeed(1000);
  
  //stepper.setCurrentPosition(0);
  while (!Serial);
    Serial.begin(9600);
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    
    xVal = text.toInt();

    if (offset == 0){
      offset = xVal;
    }

    
    Serial.println(offset);
    Serial.println(xVal - offset);
  }

  if (offset != 0){
      stepper.moveTo(xVal - offset);
      stepper.setSpeed(100);
  }

  stepper.run();
}
