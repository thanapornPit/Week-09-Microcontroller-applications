# 📚 Week 09: ESP32 GPIO Architecture

> **หัวข้อ:** การศึกษาสถาปัตยกรรม ESP32 โดยเฉพาะระบบ GPIO และ Dual-Core Processing

---

## 📋 เอกสารการเรียนรู้

### 📖 เอกสารหลัก
- 📚 **[ใบความรู้ ESP32 GPIO Architecture](ESP32-GPIO-Knowledge-Sheet.md)**  
  เนื้อหาความรู้ครบถ้วนเกี่ยวกับสถาปัตยกรรม ESP32

- 📋 **[ใบงาน ESP32 GPIO Analysis](ESP32-GPIO-Worksheet.md)**  
  แบบฝึกหัดและการประเมินผล (100 คะแนน, 90 นาที)

---

## 🎨 ไดอะแกรมและภาพประกอบ

### 🏗️ ESP32 Architecture Diagram
![ESP32 Architecture](images/esp32_architecture.svg)

*สถาปัตยกรรมโดยรวมของ ESP32 แสดงความสัมพันธ์ระหว่าง Dual-Core CPU, Bus Matrix, GPIO System และ Peripheral Blocks*

---

## 📁 โครงสร้างไฟล์

```
Week-09-Microcontroller-applications/
├── 📚 ESP32-GPIO-Knowledge-Sheet.md    # ใบความรู้
├── 📋 ESP32-GPIO-Worksheet.md          # ใบงาน
├── 📖 README.md                        # ไฟล์นี้
├── 🛠️ auto_render_dot.ps1              # สคริปต์ Auto-render
├── 📂 image-src/                       # ไฟล์ต้นฉบับไดอะแกรม
│   ├── esp32_architecture.dot          # Graphviz source
│   └── esp32_architecture.puml         # PlantUML source
├── 📂 images/                          # ไฟล์ภาพที่ render แล้ว
│   ├── esp32_architecture.svg          # Vector graphics
│   └── esp32_architecture.png          # Raster graphics
├── 📂 examples/                        # ตัวอย่างและเอกสารอ้างอิง 🤫
│   ├── gpio-basic/                     # ตัวอย่าง GPIO พื้นฐาน
│   ├── adc-samples/                    # ตัวอย่าง ADC
│   ├── architecture-deep-dive/         # เนื้อหาขั้นสูง
│   └── README.md                       # คู่มือ Examples
└── 📂 .vscode/                         # VS Code settings
    ├── tasks.json                      # Auto-render tasks
    └── keybindings.json                # Keyboard shortcuts
```

---

## 🎯 จุดประสงค์การเรียนรู้

หลังจากศึกษาเนื้อหาในสัปดาห์นี้แล้ว ผู้เรียนจะสามารถ:

1. **🧠 เข้าใจสถาปัตยกรรม** อธิบายโครงสร้างและการทำงานของ ESP32 Dual-Core System
2. **🔌 วิเคราะห์ GPIO** เข้าใจระบบ GPIO Matrix และการ Multiplexing
3. **⚙️ ประยุกต์ใช้** วางแผนการใช้ GPIO pins และ Peripheral อย่างมีประสิทธิภาพ
4. **🛠️ เขียนโค้ด** กำหนดค่าและควบคุม GPIO ด้วย ESP-IDF
5. **🔧 แก้ปัญหา** วินิจฉัยและแก้ไขปัญหาที่เกี่ยวข้องกับ GPIO

---

## 🛠️ เครื่องมือและการติดตั้ง

### 📊 Diagram Rendering Tools

เรามีระบบ **Auto-render** สำหรับสร้างไดอะแกรมอัตโนมัติ:

#### 🚀 วิธีใช้ Auto-render Script
```powershell
# เริ่ม auto-renderer (จะ watch ไฟล์ใน image-src/)
powershell -ExecutionPolicy Bypass -File auto_render_dot.ps1
```

#### 🎯 VS Code Tasks
- กด `Ctrl+Shift+P` → พิมพ์ "Tasks: Run Task" → เลือก "🎯 Start DOT Auto-Renderer"
- กด `Ctrl+S` บนไฟล์ .dot จะ render อัตโนมัติ (ถ้า setup keybinding แล้ว)

#### 📋 Tools ที่รองรับ
- **Graphviz DOT** (.dot, .gv) → SVG, PNG
- **PlantUML** (.puml) → SVG, PNG  
- **Output ไปที่:** `images/` folder

---

## 🧪 กิจกรรมการเรียนรู้

### 📚 ระยะเวลา: 3 ชั่วโมง

| ลำดับ | กิจกรรม | เวลา | เอกสาร |
|-------|---------|------|---------|
| 1 | ศึกษาใบความรู้ ESP32 Architecture | 60 นาที | [Knowledge Sheet](ESP32-GPIO-Knowledge-Sheet.md) |
| 2 | วิเคราะห์ไดอะแกรม Architecture | 30 นาที | [Images](images/) |
| 3 | ทำใบงานส่วนที่ 1-2 (ทฤษฎี) | 45 นาที | [Worksheet](ESP32-GPIO-Worksheet.md) |
| 4 | ทำใบงานส่วนที่ 3 (การเขียนโค้ด) | 30 นาที | [Worksheet](ESP32-GPIO-Worksheet.md) |
| 5 | ทำใบงานส่วนที่ 4 (การแก้ปัญหา) | 15 นาที | [Worksheet](ESP32-GPIO-Worksheet.md) |

---

## ✅ เกณฑ์การประเมิน

### 📊 การแบ่งคะแนน (100 คะแนน)
- **ความเข้าใจพื้นฐาน** (20 คะแนน): สถาปัตยกรรม ESP32, GPIO system
- **การวิเคราะห์ Peripheral** (30 คะแนน): ตารางเปรียบเทียบ, Pin planning  
- **การเขียนโค้ด** (25 คะแนน): GPIO configuration, ADC setup
- **การแก้ปัญหา** (25 คะแนน): Problem solving, Performance analysis

### 🏆 เกณฑ์เกรด
- **A (80-100):** เข้าใจและประยุกต์ใช้ได้ดีเยี่ยม
- **B (70-79):** เข้าใจและประยุกต์ใช้ได้ดี  
- **C (60-69):** เข้าใจในระดับพื้นฐาน
- **D (50-59):** เข้าใจบางส่วน ต้องศึกษาเพิ่มเติม
- **F (0-49):** ไม่ผ่านเกณฑ์ ต้องทำใหม่

---

## 📚 เอกสารอ้างอิง

### 📖 Documentation
- [ESP32 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/)
- [GPIO & RTC GPIO - ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html)

### 🛠️ Development Tools
- [ESP-IDF Getting Started](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/)
- [VS Code ESP-IDF Extension](https://marketplace.visualstudio.com/items?itemName=espressif.esp-idf-extension)

---

## 🤝 การสนับสนุน

### 💬 ติดต่อผู้สอน
- **Email:** [instructor@example.com](mailto:instructor@example.com)
- **Office Hours:** จันทร์-ศุกร์ 13:00-16:00
- **Location:** ห้อง XXX อาคาร YYY

### 🆘 ความช่วยเหลือ
- กรณีมีปัญหาเทคนิค: ดู [Troubleshooting Guide](ESP32-GPIO-Knowledge-Sheet.md#การแก้ปัญหา)
- กรณีติดตั้ง Tools: ดู [Installation Guide](auto_render_dot.ps1)

---

## 📈 การพัฒนาต่อเนื่อง

### 🔮 หัวข้อต่อไป
- **Week 10:** ESP32 Communication Protocols (UART, SPI, I2C)
- **Week 11:** ESP32 ADC และ PWM Advanced Techniques  
- **Week 12:** ESP32 Wi-Fi และ Bluetooth Programming

### 🎯 โปรเจคแนะนำ
- IoT Sensor Dashboard with ESP32
- Smart Home Controller  
- Wireless Sensor Network
- Real-time Data Logger

---

*📅 อัปเดตล่าสุด: September 2025*  
*👨‍💻 พัฒนาโดย: Microcontroller Applications Course Team*  
*📘 เวอร์ชัน: 1.0*
