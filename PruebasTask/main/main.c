
/*SomeTask main file*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t myTaskHandle = NULL;

void task1 (void *arg)
{

while(1)
{
    printf("Hello from task 1 \n");
    vTaskDelay(1000 / portTICK_RATE_MS);
}

}

void task2 (void *arg)
{

while(1)
{
    printf("Hello from task 2 \n");
    vTaskDelay(1000 / portTICK_RATE_MS);
}

}

void app_main()
{

    xTaskCreate(task1, "task1", 4096, NULL, 10, &myTaskHandle);
    xTaskCreatePinnedToCore(task2, "task2", 4096, NULL, 10, &myTaskHandle, 1);

}