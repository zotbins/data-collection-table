/**
 * @file clientTask.hpp
 * @brief Header file for Client class
 * @version 0.1
 * @date 2024-04-08
 *
 */

#ifndef CHECK_BUTTON_PRESSED
#define CHECK_BUTTON_PRESSED

#define LED_GPIO_NUM GPIO_NUM_4

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

class Task
{
public:
    /**
     * @brief Construct a new Task object. Parameters are needed for FreeRTOS.
     *
     * @param name Name of task
     * @param priority Priority number of task
     * @param stackSize Stack size of task
     */
    Task(const char *name, const int priority, const uint32_t stackSize)
        : mName(name), mPriority(priority), mStackSize(stackSize)
    {
    }

    /**
     * @brief Start execution of task
     *
     */
    virtual void start() = 0;

protected:
    /**
     * @brief Name of task
     *
     */
    const char *mName;

    /**
     * @brief Priority number of task
     *
     */
    const int mPriority;
    
    /**
     * @brief Task size of task
     *
     */
    const uint32_t mStackSize;
};

class ButtonTask : public Task
{
public:

    explicit ButtonTask(QueueHandle_t &messageQueue);

    void start() override;

private:

    static void taskFunction(void *task);

    void setup();

    void loop();
    
};

#endif