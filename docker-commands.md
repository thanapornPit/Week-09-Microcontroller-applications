# ESP32 Docker Commands Reference
# คำสั่งที่ใช้บ่อยสำหรับ ESP32 development ด้วย Docker

## 🚀 Quick Start Commands

### 1. สร้าง project ใหม่
```bash
# สร้าง project structure
docker run --rm -v %cd%:/project -w /project espressif/idf:v5.1.2 idf.py create-project my_project

# หรือใน PowerShell (Windows)
docker run --rm -v %cd%:/project -w /project espressif/idf:v5.1.2 idf.py create-project my_project
```

### 2. Build project
```bash
# Build ทั้ง project
docker run --rm -v %cd%:/project -w /project espressif/idf:v5.1.2 idf.py build

# Build และดู size
docker run --rm -v %cd%:/project -w /project espressif/idf:v5.1.2 idf.py size
```

### 3. Clean project
```bash
# ลบไฟล์ build
docker run --rm -v %cd%:/project -w /project espressif/idf:v5.1.2 idf.py fullclean
```

### 4. Configuration
```bash
# เปิด menuconfig (ใน interactive mode)
docker run --rm -it -v %cd%:/project -w /project espressif/idf:v5.1.2 idf.py menuconfig
```

## 🔧 ใช้กับ Docker Compose

### 1. เริ่ม container
```bash
# เริ่ม container แบบ interactive
docker-compose run --rm esp-idf

# หรือเข้า container ที่รันอยู่แล้ว
docker-compose exec esp-idf bash
```

### 2. ใน container (หลังจากเข้า bash แล้ว)
```bash
# ตรวจสอบ ESP-IDF version
idf.py --version

# สร้าง project
idf.py create-project led_blink

# เข้าไปใน project directory
cd led_blink

# Build
idf.py build

# ดู size ของ firmware
idf.py size

# Configuration
idf.py menuconfig
```

## 📱 Flash Commands (หลังจาก build แล้ว)

### ใช้ esptool (ติดตั้งแยก)
```bash
# Flash bootloader, partition table, และ app
esptool.py --chip esp32 --port COM3 --baud 921600 \
  --before default_reset --after hard_reset write_flash \
  0x1000 build/bootloader/bootloader.bin \
  0x8000 build/partition_table/partition-table.bin \
  0x10000 build/my_project.bin

# หรือใช้คำสั่งง่าย ๆ (สำหรับ app binary เท่านั้น)
esptool.py --chip esp32 --port COM3 --baud 921600 write_flash 0x10000 build/my_project.bin
```

### ใช้ ESP32 Flash Tool (GUI)
1. เปิด esp32-flash-tool.exe
2. เลือก COM port
3. เลือกไฟล์ .bin
4. กด Flash

## 🛠️ Troubleshooting

### ปัญหาที่พบบ่อย:

1. **Container ไม่สามารถ access serial port**
   - ใช้ Docker build + host flash แทน
   - หรือใช้ WSL2 + usbipd-win

2. **Permission denied**
   ```bash
   # เพิ่ม user ใน docker group (Linux)
   sudo usermod -aG docker $USER
   ```

3. **Volume mounting ไม่ทำงาน**
   - ตรวจสอบ path ใน Windows ต้องใช้ forward slash
   - ตัวอย่าง: /c/Users/... แทน C:\Users\...

4. **Build ช้า**
   - ใช้ volume cache: `-v esp-idf-cache:/root/.espressif`
   - หรือใช้ bind mount: `-v ~/.espressif:/root/.espressif`

## 📚 Project Structure ที่แนะนำ

```
my_esp32_project/
├── CMakeLists.txt          # Root CMake file
├── docker-compose.yml     # Docker configuration
├── main/                  # Main source code
│   ├── CMakeLists.txt
│   └── main.c
├── components/            # Custom components (optional)
├── build/                 # Build output (auto-generated)
└── README.md
```

## 🎯 สำหรับนักศึกษา: Workflow แนะนำ

1. **Setup** (ครั้งแรกเท่านั้น)
   ```bash
   # Clone project template
   git clone <project-repo>
   cd esp32-project
   
   # Pull ESP-IDF image
   docker pull espressif/idf:v5.1.2
   ```

2. **Development Loop**
   ```bash
   # 1. เขียน code ใน main/main.c
   # 2. Build
   docker-compose run --rm esp-idf idf.py build
   
   # 3. Flash (ใช้ portable tool)
   # 4. Test บน hardware
   # 5. กลับไปขั้นตอน 1
   ```

3. **Debug**
   ```bash
   # ดู log ผ่าน serial monitor
   # หรือใช้ PuTTY/Arduino IDE Serial Monitor
   ```
