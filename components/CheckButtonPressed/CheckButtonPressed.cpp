#include "CheckButtonPressed.hpp"

#include "esp_log.h"

#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "Countdown.h"

static const char *name = "ButtonTask";
static const int priority = 1;
static const uint32_t stackSize = 4096;

static const char* TAG = "button";

ButtonTask::ButtonTask(QueueHandle_t &messageQueue) : Task(name, priority, stackSize)
{
}

void ButtonTask::start()
{
    xTaskCreate(taskFunction, mName, mStackSize, this, mPriority, nullptr);
}

void ButtonTask::taskFunction(void *task)
{
    ButtonTask *buttonTask = static_cast<ButtonTask *>(task);
    buttonTask->setup();
    buttonTask->loop();
}

void ButtonTask::setup()
{
    esp_rom_gpio_pad_select_gpio(LED_GPIO_NUM);
    gpio_set_direction(LED_GPIO_NUM, GPIO_MODE_OUTPUT);
    
}

void ButtonTask::loop()
{
    while (1)
    {

        vTaskDelay(10 / portTICK_PERIOD_MS); // Delay for 10 milliseconds
        ESP_LOGI(TAG,"it works!");
        
        int button = gpio_get_level(GPIO_NUM_14); // check button level
        if(button == 1) {
            // turn off flash
            countdownDisplay();
        } else {
            // turn on flash
        }
    }
}