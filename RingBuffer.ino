#include "CircularBuffer.h"

CircularBuffer Fifo(25);

void setup() {
  Serial.begin(115200);

  delay(1000);

  randomSeed(analogRead(0)); //allows a random start

  Serial.print("Fifo Size: ");
  Serial.println(Fifo.BufferSize());

  Serial.print("Fifo Usage: ");
  Serial.print(Fifo.BufferCount());
  Serial.print(" of ");
  Serial.println(Fifo.BufferSize());
  Serial.print("Fifo Status: ");
  Serial.println(Fifo.Status());

  Serial.println("Filling Fifo....");

  uint8_t randNumber;

  for (uint8_t i = 0; i < Fifo.BufferSize() + 4; ++i) { //+4 to demonstrate overflow
    //generate random number between 0 and Fifo.BufferSize()-1 (inclusive)
    randNumber = random(0, Fifo.BufferSize());
    Serial.print(randNumber);
    Serial.print(" ");
    Fifo.Put(randNumber);
  }

  Serial.print("\nFifo Usage: ");
  Serial.print(Fifo.BufferCount());
  Serial.print(" of ");
  Serial.println(Fifo.BufferSize());
  Serial.print("Fifo Status: ");
  Serial.println(Fifo.Status());

  Serial.println("Reading from Fifo....");

  uint8_t data;

  for (uint8_t i = 0; i < Fifo.BufferSize() + 4; ++i) { //+4 to demonstrate no rollover if overflow has occurred
    Fifo.Get(data);
    Serial.print(data);
    Serial.print(" ");
  }

  Serial.print("\nFifo Usage: ");
  Serial.print(Fifo.BufferCount());
  Serial.print(" of ");
  Serial.println(Fifo.BufferSize());
  Serial.print("Fifo Status: ");
  Serial.println(Fifo.Status());

}

void loop() {
  // put your main code here, to run repeatedly:

}
