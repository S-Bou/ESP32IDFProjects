
/*SomeTask main file*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define ESP_INR_FLAG_DEFAULT 0
#define CONFIG_BUTTON_PIN 0
#define TASK1_TAG "TASK_1"
#define TASK2_TAG "TASK_2"

TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;
TaskHandle_t ISR = NULL;

void IRAM_ATTR button_isr_handler(void *arg)
{
    xTaskResumeFromISR(ISR);
    //portYIELD_FROM_ISR(  );
}
//Task that will react to button clicks
void button_task (void *arg)
{
    while(1){
        vTaskSuspend(NULL);
        ESP_LOGE("interrupt", "Button pressed!!!\n");
    }   
}

void task1 (void *arg)
{
    char buffer[20] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x11, 0x22, 0x33, 0x44, 0x55, 0x11, 0x22, 0x33, 0x44, 0x55, 0x11, 0x22, 0x33, 0x44, 0x55};
    while(1)
    {
        ESP_LOGI("TASK_1", "Hello from task 1 \n");    // I = info -> green colour
        vTaskDelay(1000 / portTICK_RATE_MS);
        ESP_LOG_BUFFER_HEX("buff", buffer, 20); //Show data from buffer array
        //Print time and ticks = ms/10
        printf("timestamp= %d tick count= %d \n", esp_log_timestamp(), xTaskGetTickCount());
    }

}

void task2 (void *arg)
{

    while(1)
    {
        ESP_LOGW(TASK2_TAG, "Hello from task 2 \n");    //W = warning -> yellow colour
        vTaskDelay(1000 / portTICK_RATE_MS);
    }

}

void app_main()
{
        //Set pins as GPIO
    gpio_pad_select_gpio(CONFIG_BUTTON_PIN);
    //Set pins as input or output
    gpio_set_direction(CONFIG_BUTTON_PIN, GPIO_MODE_INPUT);
    //Enable interrupt on falling (1->0) edge for button pin
    gpio_set_intr_type(CONFIG_BUTTON_PIN, GPIO_INTR_NEGEDGE);
    //Install the driver's GPIO ISR handler service, wich allows per-pin GPIO interrupt hendlers.
    //Install ISR service with default configuration
    gpio_install_isr_service(ESP_INR_FLAG_DEFAULT);
    //Attach the interrupt service routine
    gpio_isr_handler_add(CONFIG_BUTTON_PIN, button_isr_handler, NULL);
    //Creation of tasks
    xTaskCreate(button_task, "button_task", 4096, NULL, 10, &ISR);
    xTaskCreate(task1, "task1", 4096, NULL, 10, &myTask1Handle);
    xTaskCreatePinnedToCore(task2, "task2", 4096, NULL, 10, &myTask2Handle, 1);

}



