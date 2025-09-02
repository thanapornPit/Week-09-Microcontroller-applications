/*
 * ตัวอย่าง ADC Multiple Channels - อ่านหลาย ๆ sensor พร้อมกัน
 * แสดงการใช้งาน ADC หลาย channel และการจัดการ data
 */

#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <math.h>

#define TEMP_CHANNEL ADC1_CHANNEL_0    // GPIO 36 - Temperature
#define LIGHT_CHANNEL ADC1_CHANNEL_3   // GPIO 39 - Light sensor
#define POT_CHANNEL ADC1_CHANNEL_6     // GPIO 34 - Potentiometer

static const char *TAG = "MULTI_ADC";
static esp_adc_cal_characteristics_t adc_chars;

typedef struct {
    float temperature;
    float light_level;
    float pot_value;
    uint32_t timestamp;
} sensor_data_t;

void setup_multi_adc() {
    ESP_LOGI(TAG, "Setting up multiple ADC channels...");
    
    // กำหนดค่า ADC1
    adc1_config_width(ADC_WIDTH_BIT_12);
    
    // กำหนดค่าแต่ละ channel
    adc1_config_channel_atten(TEMP_CHANNEL, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(LIGHT_CHANNEL, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(POT_CHANNEL, ADC_ATTEN_DB_11);
    
    // สร้าง characteristics
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
    
    ESP_LOGI(TAG, "Multi-ADC setup complete");
}

sensor_data_t read_all_sensors() {
    sensor_data_t data = {0};
    
    // อ่านค่า Temperature (LM35)
    int temp_raw = adc1_get_raw(TEMP_CHANNEL);
    uint32_t temp_voltage = esp_adc_cal_raw_to_voltage(temp_raw, &adc_chars);
    data.temperature = temp_voltage / 10.0;  // LM35: 10mV/°C
    
    // อ่านค่า Light sensor (LDR)
    int light_raw = adc1_get_raw(LIGHT_CHANNEL);
    uint32_t light_voltage = esp_adc_cal_raw_to_voltage(light_raw, &adc_chars);
    data.light_level = (light_voltage / 3300.0) * 100.0;  // แปลงเป็น %
    
    // อ่านค่า Potentiometer
    int pot_raw = adc1_get_raw(POT_CHANNEL);
    uint32_t pot_voltage = esp_adc_cal_raw_to_voltage(pot_raw, &adc_chars);
    data.pot_value = (pot_voltage / 3300.0) * 100.0;  // แปลงเป็น %
    
    data.timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
    
    return data;
}

void sensor_monitoring_task(void *pvParameters) {
    sensor_data_t current_data;
    sensor_data_t previous_data = {0};
    
    while (1) {
        current_data = read_all_sensors();
        
        // แสดงผลเฉพาะเมื่อมีการเปลี่ยนแปลงมากกว่า threshold
        bool significant_change = 
            (fabs(current_data.temperature - previous_data.temperature) > 1.0) ||
            (fabs(current_data.light_level - previous_data.light_level) > 5.0) ||
            (fabs(current_data.pot_value - previous_data.pot_value) > 5.0);
            
        if (significant_change || (current_data.timestamp % 10000 < 100)) {
            ESP_LOGI(TAG, "=== Sensor Readings ===");
            ESP_LOGI(TAG, "Temperature: %.2f °C", current_data.temperature);
            ESP_LOGI(TAG, "Light Level: %.1f %%", current_data.light_level);
            ESP_LOGI(TAG, "Potentiometer: %.1f %%", current_data.pot_value);
            ESP_LOGI(TAG, "Timestamp: %lu ms", current_data.timestamp);
            ESP_LOGI(TAG, "=====================");
            
            previous_data = current_data;
        }
        
        vTaskDelay(pdMS_TO_TICKS(100));  // อ่านทุก 100ms
    }
}

void data_logger_task(void *pvParameters) {
    // Task นี้จะบันทึกข้อมูลเป็นระยะ (สำหรับ data logging)
    while (1) {
        sensor_data_t data = read_all_sensors();
        
        // บันทึกข้อมูลเป็น CSV format (สำหรับ Excel หรือ data analysis)
        printf("%lu,%.2f,%.1f,%.1f\n", 
               data.timestamp, 
               data.temperature, 
               data.light_level, 
               data.pot_value);
        
        vTaskDelay(pdMS_TO_TICKS(5000));  // บันทึกทุก 5 วินาที
    }
}

void app_main() {
    ESP_LOGI(TAG, "Starting Multi-ADC Sensor Example");
    
    setup_multi_adc();
    
    // แสดง CSV Header
    printf("Timestamp,Temperature,Light,Potentiometer\n");
    
    // สร้าง Tasks
    xTaskCreate(sensor_monitoring_task, "Sensor_Monitor", 4096, NULL, 5, NULL);
    xTaskCreate(data_logger_task, "Data_Logger", 4096, NULL, 3, NULL);
    
    ESP_LOGI(TAG, "All tasks started");
}
