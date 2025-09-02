/*
 * ตัวอย่าง ADC อ่านค่า Analog - Temperature Sensor
 * อ่านค่าจาก ADC และแปลงเป็นค่าอุณหภูมิ
 * 
 * Hardware:
 * - Temperature sensor (LM35 หรือ NTC): GPIO 36 (ADC1_CH0)
 * - หรือใช้ Potentiometer สำหรับทดสอบ
 */

#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define ADC_CHANNEL ADC1_CHANNEL_0  // GPIO 36
#define ADC_ATTEN ADC_ATTEN_DB_11   // 0-3.3V range
#define ADC_WIDTH ADC_WIDTH_BIT_12  // 12-bit resolution (0-4095)

static const char *TAG = "ADC_EXAMPLE";
static esp_adc_cal_characteristics_t adc_chars;

void setup_adc() {
    ESP_LOGI(TAG, "Configuring ADC...");
    
    // กำหนดค่า ADC1
    adc1_config_width(ADC_WIDTH);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);
    
    // สร้าง characteristics สำหรับการแปลงค่า
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(
        ADC_UNIT_1, 
        ADC_ATTEN, 
        ADC_WIDTH, 
        1100,  // Default Vref
        &adc_chars
    );
    
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        ESP_LOGI(TAG, "Using Vref from eFuse");
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        ESP_LOGI(TAG, "Using Two Point calibration from eFuse");
    } else {
        ESP_LOGI(TAG, "Using default Vref");
    }
}

float read_temperature_lm35() {
    // อ่านค่า ADC (0-4095)
    int adc_reading = adc1_get_raw(ADC_CHANNEL);
    
    // แปลงเป็น voltage (mV)
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, &adc_chars);
    
    // แปลงเป็นอุณหภูมิ สำหรับ LM35 (10mV/°C)
    float temperature = voltage / 10.0;
    
    ESP_LOGI(TAG, "ADC: %d, Voltage: %d mV, Temperature: %.2f °C", 
             adc_reading, voltage, temperature);
    
    return temperature;
}

float read_voltage() {
    // สำหรับอ่านค่า voltage ทั่วไป
    int adc_reading = 0;
    
    // อ่านหลายครั้งแล้วเฉลี่ย (ลด noise)
    for (int i = 0; i < 10; i++) {
        adc_reading += adc1_get_raw(ADC_CHANNEL);
    }
    adc_reading /= 10;
    
    // แปลงเป็น voltage
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, &adc_chars);
    float voltage_v = voltage / 1000.0;  // แปลงเป็น Volt
    
    ESP_LOGI(TAG, "Raw ADC: %d, Voltage: %.3f V", adc_reading, voltage_v);
    
    return voltage_v;
}

void adc_task(void *pvParameters) {
    while (1) {
        // อ่านค่าอุณหภูมิ
        float temp = read_temperature_lm35();
        
        // หรือแค่อ่านค่า voltage
        // float voltage = read_voltage();
        
        // แสดงผลทุก 2 วินาที
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main() {
    ESP_LOGI(TAG, "Starting ADC Temperature Example");
    
    setup_adc();
    
    // สร้าง Task สำหรับอ่าน ADC
    xTaskCreate(adc_task, "ADC_Task", 4096, NULL, 5, NULL);
    
    ESP_LOGI(TAG, "ADC task started");
}
