/*
 * ตัวอย่าง GPIO Interrupt - การใช้ Interrupt แทน Polling
 * เมื่อกดปุ่มจะเกิด Interrupt และเปลี่ยนสถานะ LED ทันที
 */

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

#define LED_PIN GPIO_NUM_2
#define BUTTON_PIN GPIO_NUM_0

static const char *TAG = "GPIO_INTERRUPT";
static QueueHandle_t gpio_evt_queue = NULL;
static bool led_state = false;

static void IRAM_ATTR gpio_isr_handler(void* arg) {
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

static void gpio_task_example(void* arg) {
    uint32_t io_num;
    
    while (1) {
        if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            ESP_LOGI(TAG, "GPIO[%d] interrupt triggered", io_num);
            
            // Toggle LED
            led_state = !led_state;
            gpio_set_level(LED_PIN, led_state);
            ESP_LOGI(TAG, "LED toggled to %s", led_state ? "ON" : "OFF");
            
            // Simple debounce
            vTaskDelay(pdMS_TO_TICKS(200));
        }
    }
}

void setup_gpio_interrupt() {
    // LED Configuration
    gpio_config_t led_config = {
        .pin_bit_mask = (1ULL << LED_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&led_config);
    
    // Button Configuration with Interrupt
    gpio_config_t button_config = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE  // Trigger on falling edge
    };
    gpio_config(&button_config);
    
    // สร้าง Queue สำหรับ Interrupt events
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    
    // สร้าง Task สำหรับจัดการ Interrupt
    xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);
    
    // ติดตั้ง ISR service
    gpio_install_isr_service(0);
    
    // เพิ่ม ISR handler สำหรับ button pin
    gpio_isr_handler_add(BUTTON_PIN, gpio_isr_handler, (void*) BUTTON_PIN);
    
    ESP_LOGI(TAG, "GPIO interrupt setup complete");
}

void app_main() {
    ESP_LOGI(TAG, "Starting GPIO Interrupt Example");
    setup_gpio_interrupt();
}
