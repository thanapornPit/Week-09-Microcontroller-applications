# การติดตั้ง Graphviz บน Windows

## วิธีที่ 1: ดาวน์โหลดจากเว็บไซต์ (แนะนำ)

### ขั้นตอน:
1. **ไปที่เว็บไซต์**: https://graphviz.org/download/
2. **เลือก Windows**: คลิก "Windows packages"
3. **ดาวน์โหลด installer**: เลือก `.msi` file (เช่น `graphviz-x.x.x-win32.msi`)
4. **รัน installer**: Double-click ไฟล์ที่ดาวน์โหลดมา
5. **ติดตั้ง**: ทำตาม wizard (เลือก "Add Graphviz to PATH" ⚠️ สำคัญ!)

### หลังติดตั้งเสร็จ:
```powershell
# ปิด PowerShell แล้วเปิดใหม่
# ทดสอบ
dot -V
```

## วิธีที่ 2: ใช้ winget (Windows Package Manager)

```powershell
# ติดตั้งผ่าน winget (มากับ Windows 10/11)
winget install graphviz
```

## วิธีที่ 3: ติดตั้ง Chocolatey แล้วใช้ choco

### ขั้นตอนที่ 1: ติดตั้ง Chocolatey
```powershell
# เปิด PowerShell as Administrator
# รัน command นี้
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```

### ขั้นตอนที่ 2: ติดตั้ง Graphviz
```powershell
# หลังจากติดตั้ง Chocolatey เสร็จ
choco install graphviz
```

## วิธีที่ 4: ใช้ Scoop

```powershell
# ติดตั้ง Scoop ก่อน
iwr -useb get.scoop.sh | iex

# ติดตั้ง Graphviz
scoop install graphviz
```

## การทดสอบหลังติดตั้ง

```powershell
# ตรวจสอบเวอร์ชัน
dot -V

# ตรวจสอบ PATH
$env:PATH -split ';' | Select-String -Pattern 'graphviz'

# ทดสอบสร้างรูป
cd "d:\GitHubRepos\__ENGEDU\2025-01-03376126-Microcontroller-applications\Week-09-Microcontroller-applications"
dot -Tpng esp32_architecture.dot -o esp32_architecture.png
```

## แก้ปัญหาที่พบบ่อย

### ปัญหา: command not found
**วิธีแก้**:
1. เพิ่ม PATH manually
2. ปิด PowerShell แล้วเปิดใหม่
3. ตรวจสอบ installation directory

### เพิ่ม PATH manually:
```powershell
# หา installation path
Get-ChildItem -Path "C:\Program Files*" -Name "*graphviz*" -Directory

# เพิ่ม PATH (แทนที่ <PATH_TO_GRAPHVIZ> ด้วย path จริง)
$env:PATH += ";C:\Program Files\Graphviz\bin"

# หรือเพิ่มถาวรผ่าน System Properties
```

## วิธีเพิ่ม PATH ถาวร (GUI):
1. กดปุ่ม `Windows + R`
2. พิมพ์ `sysdm.cpl` กด Enter
3. คลิก "Advanced" tab
4. คลิก "Environment Variables"
5. เลือก "Path" ใน "System variables"
6. คลิก "Edit"
7. คลิก "New" 
8. เพิ่ม `C:\Program Files\Graphviz\bin`
9. คลิก "OK" ทุกหน้าต่าง

---

## หลังติดตั้งเสร็จแล้ว สามารถสร้างภาพได้:

```powershell
# สร้างภาพ PNG
dot -Tpng esp32_architecture.dot -o esp32_architecture.png

# สร้างภาพ SVG (คุณภาพสูง)
dot -Tsvg esp32_architecture.dot -o esp32_architecture.svg

# สร้างภาพ PDF
dot -Tpdf esp32_architecture.dot -o esp32_architecture.pdf
```
