# วิธีการสร้างและ Render Block Diagram สำหรับ ESP32

## 1. Graphviz (DOT Language)
### การติดตั้ง:
```bash
# Windows (ใช้ winget - แนะนำ)
winget install Graphviz.Graphviz

# หรือใช้ Chocolatey
choco install graphviz

# หรือดาวน์โหลดจาก https://graphviz.org/download/
```

### การ Render:
```bash
# สร้างภาพ PNG
dot -Tpng esp32_architecture.dot -o esp32_architecture.png

# สร้างภาพ SVG (คุณภาพสูง)
dot -Tsvg esp32_architecture.dot -o esp32_architecture.svg

# สร้างภาพ PDF
dot -Tpdf esp32_architecture.dot -o esp32_architecture.pdf
```

### ข้อดี:
- ✅ ควบคุมรายละเอียดได้มาก
- ✅ Output คุณภาพสูง
- ✅ รองรับหลายรูปแบบไฟล์
- ✅ เหมาะสำหรับเอกสารทางเทคนิค

### ข้อเสีย:
- ❌ Syntax ค่อนข้างซับซ้อน
- ❌ ต้องติดตั้งโปรแกรม

## 2. Mermaid
### การใช้งาน:
```markdown
# ใน GitHub/GitLab Markdown
```mermaid
[รหัส mermaid ที่สร้างไว้]
```

### Online Editor:
- https://mermaid.live/
- https://mermaid-js.github.io/mermaid-live-editor/

### การ Render:
```bash
# ติดตั้ง mermaid-cli
npm install -g @mermaid-js/mermaid-cli

# สร้างภาพ
mmdc -i esp32_architecture.mermaid -o esp32_architecture.png
```

### ข้อดี:
- ✅ Syntax ง่าย อ่านเข้าใจง่าย
- ✅ รองรับใน GitHub/GitLab
- ✅ มี Online Editor
- ✅ รองรับ Icons และ Emoji

### ข้อเสีย:
- ❌ ควบคุมรายละเอียดได้น้อยกว่า Graphviz
- ❌ Layout อาจไม่ perfect เสมอ

## 3. PlantUML
### การติดตั้ง:
```bash
# ต้องมี Java
# ดาวน์โหลด plantuml.jar จาก https://plantuml.com/download
```

### การ Render:
```bash
# สร้างภาพ PNG
java -jar plantuml.jar esp32_architecture.puml

# สร้างภาพ SVG
java -jar plantuml.jar -tsvg esp32_architecture.puml
```

### Online Editor:
- https://www.plantuml.com/plantuml/
- https://plantuml-editor.kkeisuke.dev/

### ข้อดี:
- ✅ เหมาะสำหรับ UML diagrams
- ✅ รองรับหลายประเภท diagram
- ✅ มี Online Editor
- ✅ Integration กับ VS Code, IntelliJ

### ข้อเสีย:
- ❌ ต้องมี Java
- ❌ ไม่เหมาะสำหรับ complex layout

## 4. เครื่องมืออื่นๆ ที่แนะนำ

### Draw.io (diagrams.net)
- **URL**: https://app.diagrams.net/
- **ข้อดี**: 
  - ✅ Web-based, ไม่ต้องติดตั้ง
  - ✅ UI แบบ Drag & Drop
  - ✅ เทมเพลตเยอะ
  - ✅ Export ได้หลายรูปแบบ
- **ข้อเสีย**: 
  - ❌ ไม่ใช่ text-based (ไม่ version control ง่าย)

### Lucidchart
- **URL**: https://lucidchart.com/
- **ข้อดี**: 
  - ✅ Professional looking
  - ✅ Collaboration features
  - ✅ เทมเพลตสวย
- **ข้อเสีย**: 
  - ❌ ต้องจ่ายเงิน (มี free tier จำกัด)

### Excalidraw
- **URL**: https://excalidraw.com/
- **ข้อดี**: 
  - ✅ Hand-drawn style
  - ✅ Web-based, free
  - ✅ เหมาะสำหรับ sketching
- **ข้อเสีย**: 
  - ❌ Style อาจไม่เหมาะสำหรับเอกสารทางการ

### Dia
- **ข้อดี**: 
  - ✅ Open source
  - ✅ เหมาะสำหรับ technical diagrams
- **ข้อเสีย**: 
  - ❌ UI ค่อนข้างเก่า

## คำแนะนำการเลือกใช้

### สำหรับเอกสารทางเทคนิค:
1. **Graphviz** - หากต้องการควบคุมรายละเอียดสูง
2. **PlantUML** - หากเป็น UML หรือ component diagram
3. **Draw.io** - หากต้องการความง่ายและเร็ว

### สำหรับ GitHub/Documentation:
1. **Mermaid** - รองรับใน Markdown โดยตรง
2. **PlantUML** - ผ่าน GitHub integration

### สำหรับการนำเสนอ:
1. **Draw.io** - สวยงาม, professional
2. **Lucidchart** - หากงบอนุญาต

## ตัวอย่างการใช้ใน VS Code

### Extensions ที่แนะนำ:
1. **Graphviz (dot) language support**
2. **PlantUML**
3. **Mermaid Markdown Syntax Highlighting**
4. **Draw.io Integration**

### การ Preview:
```json
// settings.json สำหรับ PlantUML
{
    "plantuml.server": "https://www.plantuml.com/plantuml",
    "plantuml.render": "PlantUMLServer",
    "plantuml.urlFormat": "png",
    "plantuml.previewAutoUpdate": true
}
```

### วิธีแก้ปัญหา "No PlantUML server":
1. **ติดตั้ง PlantUML extension** ใน VS Code
2. **ตั้งค่า settings.json** ตามด้านบน
3. **Restart VS Code**
4. **กด Ctrl+Shift+P** → พิมพ์ "PlantUML: Preview Current Diagram"

### ทดสอบ PlantUML:
- เปิดไฟล์ `.puml` 
- กด **Alt+D** เพื่อ preview
- หรือ **Ctrl+Shift+P** → "PlantUML: Export Current Diagram"
