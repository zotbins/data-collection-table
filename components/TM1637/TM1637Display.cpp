#include "TM1637Display.h" // Include the header
#include "Countdown.h"
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <driver/gpio.h>


#define CLK GPIO_NUM_3 // GPIO 3 on ESP32-Cam
#define DIO GPIO_NUM_1 // GPIO 1

void countdownDisplay() {
    TM1637Display display = TM1637Display(CLK, DIO); // Define the Display Object
    setup(display);
    countdown(display);
}

const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};


void setup(TM1637Display display){
    display.clear();
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1000 milliseconds;
}

// After button pressed countdown 3 to 0. 
void countdown(TM1637Display display){
    display.setBrightness(7); // 7 = max brightness
    for(int i = 3; i<=0; i--){
        display.showNumberDec(i, false, 1 ,0);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1000 milliseconds
        display.clear();   
    }
    display.setSegments(done); // Show done message 
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1000 milliseconds
    display.clear();
}

/*
While not counting down. For fun. "Idle Animation"
Will loop through the word Zot on all four displays
0 - leftmost
3 - rightmost
*/

// Display Z Character
const uint8_t zCharacter[] ={
    SEG_A | SEG_B | SEG_D | SEG_E | SEG_G
};

// Display O Character
const uint8_t oCharacter[] = {
    SEG_C | SEG_D | SEG_E | SEG_G
};

// Display t character
const uint8_t tCharacter[] = {
    SEG_D | SEG_E | SEG_F |  SEG_G
};

// void idle(TM1637Display* display){
//     int pos[3] = {0, 1, 2};
//     while(1){ // infinite loop break out of this somehow
//         display->clear();
//         display->setBrightness(7); 
//         display->setSegments(zCharacter, 1, pos[0]);
//         display->setSegments(oCharacter, 1, pos[1]);
//         display->setSegments(tCharacter, 1, pos[2]);

//         for(int i = 0; i < 3; i++){ // Shfit Right one
//             pos[i] = (pos[i] + 1) % 4;
//         }
//         vTaskDelay(500 / portTICK_PERIOD_MS);
//     }
// }