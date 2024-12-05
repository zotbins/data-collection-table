#include "CheckButtonPressed.hpp"

#include "esp_log.h"

#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "Countdown.h"

//Initialization of components used as parameters for RTOS functions
static const char *name = "ButtonTask";
static const int priority = 1;
static const uint32_t stackSize = 4096;

//Used for Logging for tasks executed on the ESP32
static const char* TAG = "button";

ButtonTask::ButtonTask(QueueHandle_t &messageQueue) : Task(name, priority, stackSize)
{
}

void ButtonTask::start()
{
    xTaskCreate(taskFunction, mName, mStackSize, this, mPriority, nullptr);
    ESP_LOGI(TAG, "Task Creation Complete");
}

void ButtonTask::taskFunction(void *task)
{
    ButtonTask *buttonTask = static_cast<ButtonTask *>(task);
    ESP_LOGI(TAG, "Running Setup now");
    buttonTask->setup();
    ESP_LOGI(TAG, "Running loop now");
    buttonTask->loop();
}

void ButtonTask::setup()
{
    //Change LED to 14
    esp_rom_gpio_pad_select_gpio(GPIO_NUM_14);
    gpio_set_direction(GPIO_NUM_14, GPIO_MODE_INPUT);
    gpio_set_direction(LED_GPIO_NUM, GPIO_MODE_OUTPUT);
    
    ESP_LOGI(TAG, "Setup no Complete");
    
}

bool debounce = false;

void flash(){
    ESP_LOGI(TAG, "Waiting 1 Sec");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "Waiting 2 Sec");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "Waiting 3 Sec");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    gpio_set_level(LED_GPIO_NUM, 1);
    ESP_LOGI(TAG, "Setting Flash High");
    vTaskDelay(250/portTICK_PERIOD_MS);
    gpio_set_level(LED_GPIO_NUM, 0);
    vTaskDelay(25/portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "Not Exiting until button is unpressed");
}

void ButtonTask::loop()
{
    int button;
    while (1)
    {
        
        vTaskDelay(10 / portTICK_PERIOD_MS); // Delay for 10 milliseconds
        //ESP_LOGI(TAG,"it works!");
        // ESP_LOGI(TAG, "Loop for BUtton is Running");
        
        button = gpio_get_level(GPIO_NUM_14); // check button level
        
        if(button == 1 && debounce == false) {
            debounce = true;
            // We turn the Displaypm
            //countdownDisplay();
            // gpio_set_level(LED_GPIO_NUM, 1);
            ESP_LOGI(TAG, "buttn detect");
            do{
                flash();
                //countdownDisplay();
                button = gpio_get_level(GPIO_NUM_14);
            }while(button==1);

            debounce = false;
        } else {
            // turn on flash
            //gpio_set_level(GPIO_NUM_4, 0);
            // ESP_LOGI(TAG, "button not");
            continue;
        }
    }
}
