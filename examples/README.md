# 💡 Examples & References

> **🤫 Hidden Learning Zone**  
> ไฟล์ในโฟลเดอร์นี้เป็นตัวอย่างและเอกสารอ้างอิงสำหรับการศึกษาด้วยตนเอง  
> เหมาะสำหรับผู้ที่อยากเรียนรู้เพิ่มเติมหรือต้องการดูตัวอย่างการเขียนโค้ดจริง

---

## 📁 โครงสร้างโฟลเดอร์

```
examples/
├── 🔌 gpio-basic/                    # ตัวอย่าง GPIO พื้นฐาน
│   ├── led_button_example.c          # LED + Button แบบง่าย
│   └── gpio_interrupt_example.c      # การใช้ Interrupt
├── 📊 adc-samples/                   # ตัวอย่าง ADC
│   ├── temperature_sensor.c          # อ่านค่าเซนเซอร์อุณหภูมิ
│   └── multi_sensor_logger.c         # อ่านหลาย sensor พร้อมกัน
├── 🏗️ architecture-deep-dive/        # เนื้อหาขั้นสูง
│   └── ESP32-Advanced-Architecture.md # สถาปัตยกรรมระดับลึก
└── 📖 README.md                      # ไฟล์นี้
```

---

## 🎯 วิธีใช้งาน

### 📚 สำหรับการเรียนรู้
- **เริ่มต้น:** ดูไฟล์ในโฟลเดอร์ `gpio-basic/` ก่อน
- **ขั้นกลาง:** ศึกษาตัวอย่างใน `adc-samples/`
- **ขั้นสูง:** อ่านเอกสารใน `architecture-deep-dive/`

### 🔧 สำหรับการพัฒนา
- **Copy & Paste:** สามารถคัดลอกโค้ดไปใช้ในโปรเจคได้
- **Modify:** ปรับแต่งให้เหมาะกับการใช้งานของตนเอง
- **Reference:** ใช้เป็นเอกสารอ้างอิงในการเขียนโค้ด

---

## 🔌 GPIO Examples

### 💡 LED & Button (พื้นฐาน)
```c
// ตัวอย่างการใช้งานพื้นฐาน
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2
#define BUTTON_PIN GPIO_NUM_0

void setup_gpio() {
    // LED เป็น Output
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    
    // Button เป็น Input with Pull-up
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);
}
```

### ⚡ Interrupt (ขั้นกลาง)
```c
// การใช้ Interrupt แทน Polling
static void IRAM_ATTR gpio_isr_handler(void* arg) {
    // ISR code here - ต้องเร็วและไม่ใช้ FreeRTOS functions
}

void setup_interrupt() {
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_PIN, gpio_isr_handler, NULL);
    gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_NEGEDGE);
}
```

---

## 📊 ADC Examples

### 🌡️ Temperature Sensor
```c
// อ่านค่าอุณหภูมิจาก LM35
float read_temperature() {
    int raw = adc1_get_raw(ADC1_CHANNEL_0);
    uint32_t voltage = esp_adc_cal_raw_to_voltage(raw, &adc_chars);
    return voltage / 10.0;  // LM35: 10mV/°C
}
```

### 📈 Data Logging
```c
// บันทึกข้อมูลเป็น CSV format
printf("%lu,%.2f,%.1f,%.1f\n", 
       timestamp, temperature, light_level, pot_value);
```

---

## 🏗️ Architecture Deep Dive

### 🧠 สิ่งที่จะได้เรียนรู้
- **CPU Core Assignment** - การแบ่งงานระหว่าง 2 cores
- **Memory Management** - การจัดการ RAM และ Cache
- **Register Programming** - การเขียนโค้ดระดับ Register
- **Performance Optimization** - เทคนิคเพิ่มประสิทธิภาพ
- **Power Management** - การประหยัดพลังงาน

### 🎯 เหมาะสำหรับ
- ผู้ที่ต้องการเข้าใจ ESP32 ในระดับลึก
- นักพัฒนาที่ต้องการ optimize performance
- ผู้ที่สนใจ embedded systems architecture

---

## 💡 Tips & Tricks

### 🚀 Performance Tips
```c
// ใช้ IRAM สำหรับโค้ดที่ต้องการความเร็ว
IRAM_ATTR void fast_function() {
    // Critical code here
}

// ใช้ direct register access
GPIO.out_w1ts = (1 << PIN_NUMBER);  // Set pin
GPIO.out_w1tc = (1 << PIN_NUMBER);  // Clear pin
```

### 🔧 Debugging Tips
```c
// Monitor system performance
printf("Free heap: %d bytes\n", esp_get_free_heap_size());
printf("CPU freq: %d MHz\n", rtc_clk_cpu_freq_value(rtc_clk_cpu_freq_get()));
```

### 📊 Memory Tips
```c
// Allocate DMA-capable memory
uint8_t* buffer = heap_caps_malloc(size, MALLOC_CAP_DMA);

// Check memory usage
multi_heap_info_t info;
heap_caps_get_info(&info, MALLOC_CAP_INTERNAL);
```

---

## 🎓 Learning Path

### 🔰 Beginner (1-2 weeks)
1. LED Blink
2. Button Input
3. Basic GPIO functions

### 🔸 Intermediate (2-3 weeks)
1. GPIO Interrupts
2. ADC Reading
3. PWM Control
4. Multiple Tasks

### 🔥 Advanced (1-2 months)
1. Register-level programming
2. Dual-core optimization
3. Memory management
4. Real-time systems

---

## 🤔 เมื่อไหร่ควรใช้ Examples เหล่านี้?

### ✅ ใช้เมื่อ:
- **ติดปัญหา** ในการทำใบงาน
- **อยากดู** ตัวอย่างโค้ดจริง
- **ต้องการเข้าใจ** มากกว่าที่สอนในคลาส
- **อยากลอง** features ต่าง ๆ ของ ESP32
- **กำลังทำ** final project

### ⚠️ ระวัง:
- **อย่าคัดลอก** ทั้งหมดไปใส่ในใบงาน
- **ให้เข้าใจ** ก่อนนำไปใช้
- **ปรับแต่ง** ให้เหมาะกับงานของตนเอง

---

## 🆘 Need Help?

### 📚 เอกสารเพิ่มเติม
- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/)
- [ESP32 Technical Reference](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)

### 💬 Community
- [ESP32.com Forums](https://www.esp32.com/)
- [Reddit r/esp32](https://www.reddit.com/r/esp32/)
- [GitHub ESP32 Examples](https://github.com/espressif/esp-idf/tree/master/examples)

### 🎯 Best Practices
- **เริ่มจากง่าย** ไปหายาก
- **ทำความเข้าใจ** ก่อนเขียนโค้ด
- **ทดสอบ** ทีละส่วนย่อย
- **Comment** โค้ดให้ชัดเจน

---

*🎯 Remember: การเรียนรู้ที่ดีที่สุดคือการลงมือทำจริง!*

---

*📝 Note: ไฟล์เหล่านี้เป็น "Hidden Learning Materials" ที่สามารถใช้เป็นแหล่งอ้างอิงได้ตลอดเวลา*  
*🤫 ครูรู้ว่านักศึกษาจะมาดู แต่นี่คือการเรียนรู้แบบ "Discovery Learning" ที่ดีนะ!*
