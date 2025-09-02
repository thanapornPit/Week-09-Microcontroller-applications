# ติดตั้ง PlantUML Local Renderer ที่เครื่องเอง

## วิธีที่ 1: ใช้ Java + PlantUML JAR (แนะนำ)

### ขั้นตอน:

#### 1. ติดตั้ง Java
```powershell
# ตรวจสอบ Java
java -version

# หากไม่มี ติดตั้งผ่าน winget
winget install Oracle.JavaRuntimeEnvironment
# หรือ
winget install Microsoft.OpenJDK.11
```

#### 2. ดาวน์โหลด PlantUML JAR
```powershell
# สร้างโฟลเดอร์สำหรับ PlantUML
mkdir C:\Tools\PlantUML
cd C:\Tools\PlantUML

# ดาวน์โหลด PlantUML JAR (ใช้ PowerShell)
Invoke-WebRequest -Uri "https://github.com/plantuml/plantuml/releases/latest/download/plantuml.jar" -OutFile "plantuml.jar"

# หรือดาวน์โหลดจาก
# https://plantuml.com/download
```

#### 3. ทดสอบ PlantUML
```powershell
# ทดสอบใน terminal
cd "d:\GitHubRepos\__ENGEDU\2025-01-03376126-Microcontroller-applications\Week-09-Microcontroller-applications"

# สร้างรูปจากไฟล์ .puml
java -jar "C:\Tools\PlantUML\plantuml.jar" esp32_architecture.puml

# สร้างหลายรูปแบบ
java -jar "C:\Tools\PlantUML\plantuml.jar" -tpng esp32_architecture.puml
java -jar "C:\Tools\PlantUML\plantuml.jar" -tsvg esp32_architecture.puml
java -jar "C:\Tools\PlantUML\plantuml.jar" -tpdf esp32_architecture.puml
```

#### 4. ตั้งค่า VS Code ให้ใช้ Local JAR
```json
// .vscode/settings.json
{
    "plantuml.render": "Local",
    "plantuml.jar": "C:\\Tools\\PlantUML\\plantuml.jar",
    "plantuml.commandArgs": ["-charset", "UTF-8"],
    "plantuml.exportFormat": "png",
    "plantuml.previewAutoUpdate": true
}
```

## วิธีที่ 2: ติดตั้งผ่าน Chocolatey

```powershell
# ติดตั้ง PlantUML
choco install plantuml

# ทดสอบ
plantuml -version
plantuml esp32_architecture.puml
```

## วิธีที่ 3: ใช้ Node.js + node-plantuml

```powershell
# ติดตั้ง Node.js (หากยังไม่มี)
winget install OpenJS.NodeJS

# ติดตั้ง node-plantuml
npm install -g node-plantuml

# ใช้งาน
puml generate esp32_architecture.puml -o esp32_architecture.png
```

## วิธีที่ 4: ใช้ Docker (สำหรับ Advanced Users)

```powershell
# Pull PlantUML Docker image
docker pull plantuml/plantuml-server

# รัน PlantUML server locally
docker run -d -p 8080:8080 plantuml/plantuml-server

# ตั้งค่า VS Code ให้ใช้ local server
# "plantuml.server": "http://localhost:8080"
```

## การตั้งค่า VS Code สำหรับ Local PlantUML

### Settings.json ที่แนะนำ:
```json
{
    "plantuml.render": "Local",
    "plantuml.jar": "C:\\Tools\\PlantUML\\plantuml.jar",
    "plantuml.commandArgs": [
        "-charset", "UTF-8",
        "-config", "config.puml"
    ],
    "plantuml.exportFormat": "png",
    "plantuml.exportSubFolder": false,
    "plantuml.exportOutDir": ".",
    "plantuml.previewAutoUpdate": true,
    "plantuml.includepaths": ["./"],
    "plantuml.diagramsRoot": "./"
}
```

## สคริปต์อัตโนมัติสำหรับติดตั้ง

### install-plantuml.ps1
```powershell
# ตรวจสอบ Java
Write-Host "Checking Java installation..." -ForegroundColor Green
try {
    $javaVersion = java -version 2>&1
    Write-Host "Java found: $($javaVersion[0])" -ForegroundColor Green
} catch {
    Write-Host "Java not found. Installing..." -ForegroundColor Yellow
    winget install Microsoft.OpenJDK.11
}

# สร้างโฟลเดอร์
$plantUMLPath = "C:\Tools\PlantUML"
if (!(Test-Path $plantUMLPath)) {
    New-Item -ItemType Directory -Path $plantUMLPath -Force
    Write-Host "Created directory: $plantUMLPath" -ForegroundColor Green
}

# ดาวน์โหลด PlantUML JAR
$jarPath = "$plantUMLPath\plantuml.jar"
if (!(Test-Path $jarPath)) {
    Write-Host "Downloading PlantUML JAR..." -ForegroundColor Yellow
    Invoke-WebRequest -Uri "https://github.com/plantuml/plantuml/releases/latest/download/plantuml.jar" -OutFile $jarPath
    Write-Host "Downloaded PlantUML JAR to: $jarPath" -ForegroundColor Green
} else {
    Write-Host "PlantUML JAR already exists at: $jarPath" -ForegroundColor Green
}

# ทดสอบ
Write-Host "Testing PlantUML..." -ForegroundColor Green
java -jar $jarPath -version

Write-Host "`nPlantUML installation completed!" -ForegroundColor Green
Write-Host "VS Code settings path: $jarPath" -ForegroundColor Cyan
```

## การใช้งาน

### Command Line:
```powershell
# สร้างรูปจากไฟล์ .puml
java -jar "C:\Tools\PlantUML\plantuml.jar" *.puml

# สร้างแบบ real-time watch
java -jar "C:\Tools\PlantUML\plantuml.jar" -gui

# สร้างรูปแบบต่างๆ
java -jar "C:\Tools\PlantUML\plantuml.jar" -tpng -o ./images *.puml
java -jar "C:\Tools\PlantUML\plantuml.jar" -tsvg -o ./images *.puml
```

### VS Code:
- กด **Alt+D** เพื่อ preview
- **Ctrl+Shift+P** → "PlantUML: Export Current Diagram"

## ข้อดีของ Local Installation:

✅ **ไม่ต้องพึ่งอินเทอร์เน็ต**  
✅ **ความเร็วสูง**  
✅ **ความปลอดภัย** (ไม่ส่งข้อมูลออนไลน์)  
✅ **ใช้งาน offline ได้**  
✅ **ควบคุมเวอร์ชันได้**  

## ลำดับความแนะนำ:

1. **Java + JAR** (เสถียรที่สุด)
2. **Chocolatey** (ง่ายที่สุด)
3. **Node.js** (สำหรับ web developers)
4. **Docker** (สำหรับ advanced users)

ลองวิธีไหนก่อนครับ?
