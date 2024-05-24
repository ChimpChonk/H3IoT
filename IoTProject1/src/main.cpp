#include <Arduino.h>

void setup() {
  pinMode(GPIO_NUM_2, OUTPUT); //setup port for LED
  Serial.begin(115200);
  Serial.println("FUCK OFF");
}

void loop() {
  static int count = 0;
  digitalWrite(GPIO_NUM_2, HIGH);
  vTaskDelay(1000);
  digitalWrite(GPIO_NUM_2, LOW);
  vTaskDelay(1000);
  Serial.print("The count is now: ");
  Serial.println(count++);
}

