#include <Arduino.h>

volatile u_int8_t x = 0; 

IRAM_ATTR void mineISR() //ISR routine called under interrupt
{
  x++;
}

void setup() {
  pinMode(GPIO_NUM_2, OUTPUT); //setup port for LED
  pinMode(GPIO_NUM_27, INPUT_PULLUP); //Datapin should not be undefined. Must be "1"
  Serial.begin(115200);
  Serial.println("Starting");
  attachInterrupt(digitalPinToInterrupt(GPIO_NUM_27), mineISR, FALLING); //setup for IRQ...

}

void loop() {
  noInterrupts();
  if(x)
  {
    x--;
    Serial.println("This is an interrupt button click.");
  }
  interrupts();
  // vTaskDelay(10);

  // if(!digitalRead(GPIO_NUM_27))
  // {
  //   digitalWrite(GPIO_NUM_2, HIGH);
  //   Serial.println("Press");
  // }
  // else {
  //   digitalWrite(GPIO_NUM_2, LOW);
  // }

  // vTaskDelay(100);
}

