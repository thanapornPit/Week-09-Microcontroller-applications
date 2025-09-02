# การใช้ SVG ใน GitHub Markdown

## วิธีการแสดง SVG ใน GitHub

### 1. วิธีที่ดีที่สุด: อัปโหลดเป็น Asset ใน Repository
```markdown
![ESP32 Architecture](./esp32_architecture.svg)
```

### 2. วิธีอื่นๆ ที่รองรับ:

#### A. ใช้ HTML img tag (แนะนำสำหรับ SVG)
```html
<img src="./esp32_architecture.svg" alt="ESP32 Architecture" width="800">
```

#### B. ใช้ HTML object tag
```html
<object data="./esp32_architecture.svg" type="image/svg+xml" width="800" height="600">
    Your browser does not support SVG
</object>
```

#### C. ใช้ Raw GitHub URL
```markdown
![ESP32 Architecture](https://raw.githubusercontent.com/username/repo-name/main/path/to/esp32_architecture.svg)
```

### 3. ข้อดีของ SVG ใน GitHub:
- ✅ **Vector Graphics**: ขยายได้ไม่เสียคุณภาพ
- ✅ **ไฟล์เล็ก**: เร็วในการโหลด
- ✅ **รองรับ Dark/Light Theme**: สามารถปรับสีได้
- ✅ **Interactive**: รองรับ hover effects (ถ้ามี)
- ✅ **SEO Friendly**: search engine อ่านได้

### 4. ข้อจำกัดใน GitHub:
- ❌ **JavaScript ใน SVG**: GitHub จะ strip JavaScript ออก
- ❌ **External Links**: ลิงก์ภายนอกอาจไม่ทำงาน
- ❌ **Complex Animations**: อาจมีปัญหากับ animation บางประเภท

## วิธีทดสอบ SVG ใน GitHub:

### ขั้นตอน:
1. **Commit และ Push** ไฟล์ `esp32_architecture.svg` ไปยัง repository
2. **สร้าง/แก้ไข README.md** หรือไฟล์ markdown อื่น
3. **เพิ่มโค้ด** markdown หรือ HTML
4. **ดูผลลัพธ์** ใน GitHub web interface

### ตัวอย่างการใช้ใน README.md:
```markdown
# ESP32 Architecture

## Block Diagram

<div align="center">
    <img src="./esp32_architecture.svg" alt="ESP32 Architecture Diagram" width="100%">
</div>

ภาพแสดงสถาปัตยกรรมของ ESP32 ที่ประกอบด้วย:
- **Dual-Core Processors**: PRO CPU และ APP CPU
- **GPIO Matrix**: ระบบจัดการ I/O ที่ยืดหยุ่น
- **Peripheral Blocks**: ADC, DAC, PWM, UART, I2C, SPI

## รายละเอียดเพิ่มเติม

สำหรับข้อมูลเพิ่มเติม ดูที่ [Week-09-ESP32-GPIO.md](./Week-09-ESP32-GPIO.md)
```

## การปรับแต่ง SVG สำหรับ GitHub:

### เพิ่ม responsive behavior:
```html
<img src="./esp32_architecture.svg" 
     alt="ESP32 Architecture" 
     style="width: 100%; max-width: 800px; height: auto;">
```

### เพิ่ม Dark Mode Support:
```html
<picture>
  <source media="(prefers-color-scheme: dark)" srcset="./esp32_architecture_dark.svg">
  <source media="(prefers-color-scheme: light)" srcset="./esp32_architecture_light.svg">
  <img src="./esp32_architecture.svg" alt="ESP32 Architecture">
</picture>
```

## เปรียบเทียบ SVG vs PNG ใน GitHub:

| คุณสมบัติ | SVG | PNG |
|-----------|-----|-----|
| **คุณภาพ** | ✅ Vector (ไม่เสียคุณภาพ) | ❌ Raster (เสียคุณภาพเมื่อขยาย) |
| **ขนาดไฟล์** | ✅ เล็ก (15KB) | ❌ ใหญ่ (37KB) |
| **Loading Speed** | ✅ เร็ว | ⚠️ ช้ากว่า |
| **รองรับใน Browser** | ✅ ทุก modern browser | ✅ ทุก browser |
| **สีพื้นหลัง** | ✅ โปร่งใส/ปรับได้ | ❌ คงที่ |
| **Text Selection** | ✅ เลือกข้อความได้ | ❌ เลือกไม่ได้ |

## คำแนะนำ:
1. **ใช้ SVG** สำหรับ technical diagrams
2. **ใช้ PNG** สำหรับรูปภาพที่มี gradient ซับซ้อน
3. **ทดสอบใน GitHub** ก่อนใช้งานจริง
4. **เพิ่ม alt text** เสมอเพื่อ accessibility

ใน GitHub จะ render SVG ได้ดีมาก! 🎯
