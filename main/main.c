#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

#define LOW 0
#define HIGH 1

#define LED 2

void app_main(void) {
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    while (true) {
        gpio_set_level(LED, LOW);
        vTaskDelay(1000 / portTICK_RATE_MS);
        gpio_set_level(LED, HIGH);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
    
}