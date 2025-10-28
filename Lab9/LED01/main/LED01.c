#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// กำหนด GPIO สำหรับ LED 3 ดวง
#define LED1_GPIO GPIO_NUM_2
#define LED2_GPIO GPIO_NUM_0
#define LED3_GPIO GPIO_NUM_4

// หน่วงเวลาในหน่วยมิลลิวินาทีระหว่างแต่ละดวง
#define DELAY_MS 500

// สร้าง array ของ GPIO LED เพื่อง่ายต่อการวนลูป
static const gpio_num_t led_gpios[] = {LED1_GPIO, LED2_GPIO, LED3_GPIO};

#define NUM_LEDS (sizeof(led_gpios) / sizeof(led_gpios[0]))

void app_main(void) {
    // ตั้งค่า GPIO ของ LED ทุกดวงเป็น output
    for (int i = 0; i < NUM_LEDS; i++) {
        gpio_reset_pin(led_gpios[i]);
        gpio_set_direction(led_gpios[i], GPIO_MODE_OUTPUT);
    }

    while(1) {
        // เปิดไฟ LED ทีละดวงเรียงกันไป
        for (int i = 0; i < NUM_LEDS; i++) {
            gpio_set_level(led_gpios[i], 1); // เปิด LED
            vTaskDelay(pdMS_TO_TICKS(500));  // หน่วงเวลา 0.5 วินาที
        }

        // หน่วงเวลา 1 วินาทีหลังจากไฟติดครบทุกดวง
        vTaskDelay(pdMS_TO_TICKS(1000));

        // ปิดไฟ LED ทุกดวง
        for (int i = 0; i < NUM_LEDS; i++) {
            gpio_set_level(led_gpios[i], 0); // ปิด LED
        }

        // หน่วงเวลา 1 วินาทีก่อนเริ่มลำดับใหม่
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}