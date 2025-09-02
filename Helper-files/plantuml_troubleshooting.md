# แก้ปัญหา PlantUML ใน VS Code

## ปัญหา: "⚠️No PlantUML server, specify one with plantuml.server"

### วิธีแก้ปัญหา:

#### 1. ตรวจสอบ Extension
```bash
# ตรวจสอบว่าติดตั้ง PlantUML extension แล้วหรือไม่
# ใน VS Code: Ctrl+Shift+X → ค้นหา "PlantUML" by jebbs
```

#### 2. ตั้งค่า settings.json
```json
{
    "plantuml.server": "https://www.plantuml.com/plantuml",
    "plantuml.render": "PlantUMLServer",
    "plantuml.urlFormat": "png",
    "plantuml.exportFormat": "png",
    "plantuml.previewAutoUpdate": true
}
```

#### 3. Restart VS Code
- ปิด VS Code แล้วเปิดใหม่

#### 4. ทดสอบการทำงาน
```
1. เปิดไฟล์ .puml
2. กด Alt+D (หรือ Ctrl+Shift+P → "PlantUML: Preview Current Diagram")
3. ควรจะเห็น preview panel เปิดขึ้น
```

## รูปร่างใน PlantUML:

### สำหรับ Hardware Components:
```plantuml
' Bus Matrix - ใช้ rectangle (สี่เหลี่ยมผืนผ้า)
rectangle [Interconnect\nBus Matrix\nArbitrator] as MATRIX #Orange

' GPIO Array - ใช้ rectangle  
rectangle [GPIO PINS\n40 pins available\nMulti-function I/O] as GPIO #LightCyan

' Memory - ใช้ component (มุมโค้ง)
component [Memory Subsystem\nSRAM, Flash, RTC] as MEM #LightSteelBlue
```

### เปรียบเทียบรูปร่าง:
- `component` → 🔲 มุมโค้ง (software components)
- `rectangle` → ⬜ มุมแหลม (hardware blocks)  
- `node` → 📦 3D effect (physical hardware)
- `database` → 🛢️ ฐานข้อมูล
- `cloud` → ☁️ cloud services

## วิธีใช้งาน:

### Preview:
```
Alt+D                    = Preview diagram
Ctrl+Shift+P             = Command palette
"PlantUML: Preview"      = เปิด preview
"PlantUML: Export"       = Export เป็นรูปภาพ
```

### Export:
```
Ctrl+Shift+P → "PlantUML: Export Current Diagram"
- เลือกรูปแบบ: PNG, SVG, PDF
- ไฟล์จะถูกสร้างในโฟลเดอร์เดียวกัน
```

## Online Alternative:
หากยังไม่ทำงาน สามารถใช้ online editor:
- https://www.plantuml.com/plantuml/
- https://plantuml-editor.kkeisuke.dev/

คัดลอกโค้ด PlantUML ไปวางแล้วดูผลลัพธ์ได้เลย!

## ตัวอย่างที่ใช้งานได้:
ลองเปิดไฟล์ `shape_comparison.puml` ที่สร้างไว้เพื่อเปรียบเทียบรูปร่างต่างๆ
