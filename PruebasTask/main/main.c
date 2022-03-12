
/*SomeTask main file*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;

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

    for(int i=0; i<5; i++)
    {
        printf("Hello from task 2 \n");
        vTaskDelay(1000 / portTICK_RATE_MS);
    }

}

void app_main()
{

    xTaskCreate(task1, "task1", 4096, NULL, 10, &myTask1Handle);
    xTaskCreatePinnedToCore(task2, "task2", 4096, NULL, 10, &myTask2Handle, 1);

}



