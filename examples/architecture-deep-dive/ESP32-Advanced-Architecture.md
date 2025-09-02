# 🔬 ESP32 Architecture Deep Dive

> **Note:** ไฟล์นี้เป็นเอกสารเสริมสำหรับผู้ที่ต้องการเข้าใจ ESP32 ในระดับลึก 
> เหมาะสำหรับการอ้างอิง หรือการศึกษาด้วยตนเอง 📚

---

## 🧠 CPU Architecture Details

### Xtensa LX6 Processor Core

```
┌─────────────────────────────────────────┐
│              CPU Core                   │
├─────────────────────────────────────────┤
│  📦 Instruction Cache (32 KB)          │
│  📦 Data Cache (32 KB)                 │
│  🔄 Load/Store Unit                     │
│  ⚡ Arithmetic Logic Unit (ALU)        │
│  🎯 Branch Prediction Unit             │
│  📊 Performance Counters               │
└─────────────────────────────────────────┘
```

#### Key Features:
- **32-bit RISC architecture**
- **Harvard architecture** (separate instruction/data paths)
- **7-stage pipeline**
- **IEEE 754 single-precision FPU**
- **16/24/32-bit instruction encoding**

### Dual-Core Configuration

```c
// Core Assignment Example
void app_main() {
    // PRO CPU (Core 0) - Default for most tasks
    xTaskCreatePinnedToCore(
        wifi_task,          // Task function
        "WiFi_Handler",     // Task name
        4096,              // Stack size
        NULL,              // Parameters
        5,                 // Priority
        NULL,              // Task handle
        0                  // Core 0 (PRO CPU)
    );
    
    // APP CPU (Core 1) - For application logic
    xTaskCreatePinnedToCore(
        sensor_task,        // Task function
        "Sensor_Reading",   // Task name
        4096,              // Stack size
        NULL,              // Parameters
        5,                 // Priority
        NULL,              // Task handle
        1                  // Core 1 (APP CPU)
    );
}
```

---

## 🚌 Bus Matrix Deep Dive

### Bus Architecture

```
                    ┌─────────────────┐
                    │   Bus Matrix    │
                    │   Arbitrator    │
                    └─────────┬───────┘
                              │
    ┌─────────────────────────┼─────────────────────────┐
    │                         │                         │
┌───▼───┐                 ┌───▼───┐                 ┌───▼───┐
│ Core0 │                 │ Core1 │                 │  DMA  │
│(PRO)  │                 │(APP)  │                 │ Units │
└───────┘                 └───────┘                 └───────┘
```

#### Arbitration Policy:
1. **Round Robin** for equal priority
2. **Priority-based** for different priority levels
3. **Starvation prevention** mechanisms
4. **Burst support** for efficient transfers

### Memory Map

```
0x4000_0000 - 0x4007_FFFF : Data RAM (512 KB)
0x4008_0000 - 0x4009_FFFF : Data RAM (128 KB) 
0x4020_0000 - 0x4027_FFFF : Instruction RAM (512 KB)
0x5000_0000 - 0x503F_FFFF : RTC Memory (8 KB)
0x6000_0000 - 0x6FFF_FFFF : External RAM (PSRAM)
```

---

## 🔌 GPIO Matrix Architecture

### Two-Stage Multiplexing System

#### Stage 1: IO MUX
```c
// IO MUX Register Structure (simplified)
typedef struct {
    uint32_t mcu_oe       : 1;    // Output enable
    uint32_t slp_sel      : 1;    // Sleep selection
    uint32_t slp_pd       : 1;    // Sleep pull down
    uint32_t slp_pu       : 1;    // Sleep pull up
    uint32_t slp_ie       : 1;    // Sleep input enable
    uint32_t slp_oe       : 1;    // Sleep output enable
    uint32_t fun_pd       : 1;    // Function pull down
    uint32_t fun_pu       : 1;    // Function pull up
    uint32_t fun_ie       : 1;    // Function input enable
    uint32_t fun_drv      : 2;    // Function drive strength
    uint32_t mcu_sel      : 3;    // MCU selection
    uint32_t reserved     : 19;
} io_mux_reg_t;
```

#### Stage 2: GPIO Matrix
```c
// GPIO Matrix Routing Example
void route_uart_to_custom_pins() {
    // Route UART0 TX to GPIO 4
    gpio_matrix_out(GPIO_NUM_4, U0TXD_OUT_IDX, false, false);
    
    // Route GPIO 5 to UART0 RX
    gpio_matrix_in(GPIO_NUM_5, U0RXD_IN_IDX, false);
    
    // Configure IO MUX for GPIO function
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_5, GPIO_MODE_INPUT);
}
```

### GPIO Capabilities Matrix

| GPIO | ADC1 | ADC2 | DAC | Touch | PWM | Notes |
|------|------|------|-----|-------|-----|-------|
| 0    | -    | -    | -   | Touch1| ✓   | Strapping pin |
| 1    | -    | -    | -   | -     | ✓   | UART0_TX |
| 2    | -    | ADC2_2| -   | Touch2| ✓   | Strapping pin |
| 3    | -    | -    | -   | -     | ✓   | UART0_RX |
| 4    | -    | ADC2_0| -   | Touch0| ✓   | - |
| 5    | -    | -    | -   | -     | ✓   | Strapping pin |
| ... | ...  | ...  | ... | ...   | ... | ... |
| 25   | -    | ADC2_8| DAC1| -     | ✓   | - |
| 26   | -    | ADC2_9| DAC2| -     | ✓   | - |
| 27   | -    | ADC2_7| -   | Touch7| ✓   | - |
| 32   | ADC1_4| -   | -   | Touch9| ✓   | - |
| 33   | ADC1_5| -   | -   | Touch8| ✓   | - |
| 34   | ADC1_6| -   | -   | -     | -   | Input only |
| 35   | ADC1_7| -   | -   | -     | -   | Input only |
| 36   | ADC1_0| -   | -   | -     | -   | Input only |
| 39   | ADC1_3| -   | -   | -     | -   | Input only |

---

## ⚡ Power Management Deep Dive

### Sleep Modes Comparison

```c
// Light Sleep - Fast wake-up
void enter_light_sleep() {
    esp_sleep_enable_timer_wakeup(1000000); // 1 second
    esp_light_sleep_start();
}

// Deep Sleep - Ultra low power
void enter_deep_sleep() {
    esp_sleep_enable_timer_wakeup(10000000); // 10 seconds
    esp_deep_sleep_start();
}

// Hibernation - Lowest power
void enter_hibernation() {
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 0); // Wake on button
    esp_deep_sleep_start();
}
```

### Power Consumption Table

| Mode | CPU | WiFi | Bluetooth | Consumption | Wake-up Time |
|------|-----|------|-----------|-------------|--------------|
| Active | 240MHz | On | On | ~160-260 mA | - |
| Modem Sleep | 240MHz | Off | Off | ~15-20 mA | < 1ms |
| Light Sleep | Off | Off | Off | ~0.8 mA | < 5ms |
| Deep Sleep | Off | Off | Off | ~10 μA | 300-1000ms |
| Hibernation | Off | Off | Off | ~2.5 μA | 300-1000ms |

---

## 🔧 Register-Level Programming

### Direct Register Access Example

```c
#include "soc/gpio_reg.h"
#include "soc/gpio_struct.h"

void fast_gpio_toggle() {
    // Method 1: Using registers directly
    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << 2));  // Set GPIO 2
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << 2));  // Clear GPIO 2
    
    // Method 2: Using GPIO structure
    GPIO.out_w1ts = (1 << 2);  // Set GPIO 2
    GPIO.out_w1tc = (1 << 2);  // Clear GPIO 2
}

void configure_gpio_registers() {
    // Enable output for GPIO 2
    GPIO.enable_w1ts = (1 << 2);
    
    // Set function to GPIO (not peripheral)
    GPIO.func_out_sel_cfg[2].func_sel = 256;  // GPIO function
    
    // Configure pull-up/down
    REG_SET_BIT(GPIO_PIN2_REG, GPIO_PIN2_PU);     // Pull-up
    REG_CLR_BIT(GPIO_PIN2_REG, GPIO_PIN2_PD);     // No pull-down
}
```

---

## 🎯 Performance Optimization Tips

### 1. CPU Core Assignment Strategy
```c
// Best Practices for Core Assignment
void optimal_task_assignment() {
    // PRO CPU (Core 0): Network, Bluetooth, System tasks
    xTaskCreatePinnedToCore(wifi_task, "WiFi", 4096, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(bluetooth_task, "BT", 4096, NULL, 5, NULL, 0);
    
    // APP CPU (Core 1): Application logic, sensors, calculations
    xTaskCreatePinnedToCore(sensor_task, "Sensors", 4096, NULL, 5, NULL, 1);
    xTaskCreatePinnedToCore(calculation_task, "Math", 4096, NULL, 5, NULL, 1);
}
```

### 2. Memory Access Optimization
```c
// IRAM vs DRAM placement
IRAM_ATTR void critical_function() {
    // Code here executes from IRAM (faster)
    // Use for interrupt handlers and time-critical code
}

// DMA-friendly buffer allocation
uint8_t* create_dma_buffer(size_t size) {
    // Allocate DMA-capable memory
    return heap_caps_malloc(size, MALLOC_CAP_DMA);
}
```

### 3. GPIO Performance Tweaks
```c
// High-speed GPIO operations
void high_speed_gpio_setup() {
    // Set maximum drive strength
    gpio_set_drive_capability(GPIO_NUM_2, GPIO_DRIVE_CAP_3);
    
    // Use direct register access for speed
    volatile uint32_t* gpio_out_reg = &GPIO.out;
    
    // Fast toggle in loop
    for (int i = 0; i < 1000; i++) {
        *gpio_out_reg |= (1 << 2);   // Set
        *gpio_out_reg &= ~(1 << 2);  // Clear
    }
}
```

---

## 📊 Debugging and Profiling

### Performance Monitoring
```c
#include "esp_system.h"
#include "esp_timer.h"

void performance_monitoring() {
    // CPU frequency
    rtc_cpu_freq_config_t freq_config;
    rtc_clk_cpu_freq_get_config(&freq_config);
    printf("CPU Frequency: %d MHz\n", freq_config.freq_mhz);
    
    // Free heap memory
    printf("Free heap: %d bytes\n", esp_get_free_heap_size());
    
    // Task watermark (unused stack)
    printf("Task watermark: %d\n", uxTaskGetStackHighWaterMark(NULL));
    
    // System time
    int64_t time_us = esp_timer_get_time();
    printf("System time: %lld us\n", time_us);
}
```

### Memory Analysis
```c
void memory_analysis() {
    multi_heap_info_t info;
    
    // Internal RAM
    heap_caps_get_info(&info, MALLOC_CAP_INTERNAL);
    printf("Internal RAM - Total: %d, Free: %d, Largest: %d\n",
           info.total_free_bytes, info.total_allocated_bytes, info.largest_free_block);
    
    // PSRAM (if available)
    heap_caps_get_info(&info, MALLOC_CAP_SPIRAM);
    printf("PSRAM - Total: %d, Free: %d\n", 
           info.total_free_bytes, info.total_allocated_bytes);
}
```

---

## 🔬 Advanced Features

### Custom Boot Process
```c
// Custom partition table
void custom_boot_setup() {
    // Get running partition
    const esp_partition_t* running = esp_ota_get_running_partition();
    printf("Running partition: %s\n", running->label);
    
    // Custom NVS initialization
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
}
```

### Hardware Security
```c
#include "esp_efuse.h"

void security_features() {
    // Check if secure boot is enabled
    bool secure_boot = esp_efuse_read_field_bit(ESP_EFUSE_SECURE_BOOT_EN);
    printf("Secure Boot: %s\n", secure_boot ? "Enabled" : "Disabled");
    
    // Check flash encryption
    bool flash_encryption = esp_efuse_read_field_bit(ESP_EFUSE_FLASH_CRYPT_CNT);
    printf("Flash Encryption: %s\n", flash_encryption ? "Enabled" : "Disabled");
}
```

---

## 📚 Additional Resources

### Datasheet References
- ESP32 Technical Reference Manual (1000+ pages)
- Xtensa Instruction Set Architecture (ISA) Reference Manual
- ESP32 Hardware Design Guidelines

### Development Tools
- ESP-IDF (Official framework)
- ESP32 Eclipse Plugin
- OpenOCD for debugging
- ESP32 ULP Coprocessor programming

### Community Resources
- ESP32.com Forums
- GitHub ESP32 Examples
- YouTube: ESP32 Advanced Tutorials

---

*⚠️ Note: This document contains advanced topics. Start with basic examples first!*
