#include <Arduino.h>

static void MyTask1(void* pvParameters);
static void MyTask2(void* pvParameters);
static void MyTask3(void* pvParameters);
//Define
#define LED_PIN GPIO_NUM_2
#define BTN_PIN GPIO_NUM_27

//Task handler
TaskHandle_t Task1Handle = NULL;
TaskHandle_t Task2Handle = NULL;
TaskHandle_t Task3Handle = NULL;

bool task1Token = false;

SemaphoreHandle_t led_semaphore;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(F("Srtup running"));

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(BTN_PIN, INPUT_PULLUP);

  led_semaphore = xSemaphoreCreateBinary();
  xSemaphoreGive(led_semaphore);

  xTaskCreate(MyTask1, "Task1", 1024, NULL, 1, NULL);
  xTaskCreate(MyTask2, "Task2", 1024, NULL, 1, NULL);
  xTaskCreate(MyTask3, "IdleTask", 1024, NULL, 5, NULL);

}

void loop() {
  // put your main code here, to run repeatedly:
}

static void MyTask1(void* pvParameters)
{
  while (1)
  {
    if(task1Token)
    {
      if(xSemaphoreTake(led_semaphore, portMAX_DELAY) == pdTRUE)
      {
        Serial.println("Task 1 blink: ");
        digitalWrite(LED_PIN, HIGH);
        vTaskDelay(pdMS_TO_TICKS(3000));
        digitalWrite(LED_PIN, LOW);
        vTaskDelay(pdMS_TO_TICKS(7000));
        xSemaphoreGive(led_semaphore);
      }
    }
    else
    {
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    vTaskPrioritySet(Task2Handle, 2);
    vTaskPrioritySet(Task1Handle, 1);

  }
  
}

static void MyTask2(void* pvParameters)
{
  while (1)
  {
    if(xSemaphoreTake(led_semaphore, portMAX_DELAY) == pdTRUE)
    {
      for (int i = 0; i < 20; i++)
      {
        Serial.println("Task 2: ");
        digitalWrite(LED_PIN, HIGH);
        vTaskDelay(pdMS_TO_TICKS(500));
        digitalWrite(LED_PIN, LOW);
        vTaskDelay(pdMS_TO_TICKS(500));
      }
      xSemaphoreGive(led_semaphore);
    }
    vTaskPrioritySet(Task1Handle, 2);
    vTaskPrioritySet(Task2Handle, 1);
  }
}

static void MyTask3(void* pvParameters)
{
  while (1)
  {
    if(digitalRead(BTN_PIN) == LOW)
    {
      task1Token = !task1Token;
      Serial.println("Task 1 Statuse: " + String(task1Token));
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
  
}