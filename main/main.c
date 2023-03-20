#include <stdio.h>
#include <driver/i2c.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"
#include "HD44780.h"

#define LOW 0
#define HIGH 1

//Defines de pinos de componentes
#define LED 2
#define BUZZER 32


//defines do LCD
#define LCD_ADDR 0x27
#define SDA_PIN  21
#define SCL_PIN  22
#define LCD_COLS 16
#define LCD_ROWS 2

void LCD_DemoTask(void* param) {
    char num[20];
    uint8_t led_level = HIGH;
    while (true) {
        LCD_home();  //set cursor on (0, 0)
        LCD_clearScreen();
        LCD_writeStr("16x2 I2C LCD");
        vTaskDelay(3000 / portTICK_RATE_MS);
        LCD_clearScreen();
        LCD_writeStr("Lets Count 0-10!");
        vTaskDelay(3000 / portTICK_RATE_MS);
        LCD_clearScreen();
        gpio_set_level(BUZZER, HIGH);
        for (int i = 0; i <= 10; i++) {
            gpio_set_level(LED, led_level);
            LCD_setCursor(8, 1);
            sprintf(num, "num %d", i);  //formata uma string e coloca no ponteiro num
            LCD_writeStr(num);
            vTaskDelay(1000 / portTICK_RATE_MS);
            led_level = !led_level;
        }
        gpio_set_level(BUZZER, LOW);
    }
}

void setup() {
    LCD_init(LCD_ADDR, SDA_PIN, SCL_PIN, LCD_COLS, LCD_ROWS);
    gpio_set_direction(BUZZER, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
}

void app_main(void) {
    setup();
    xTaskCreate(&LCD_DemoTask, "Demo Task", 2048, NULL, 5, NULL);
}