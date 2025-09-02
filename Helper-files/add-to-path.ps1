# เพิ่ม Java และ PlantUML ลง PATH ถาวร
Write-Host "Adding Java and PlantUML to System PATH..." -ForegroundColor Green

# Java PATH
$javaPath = "C:\Program Files\Java\jre1.8.0_461\bin"
$plantUMLPath = "C:\Tools\PlantUML"

# ตรวจสอบ Java path
if (Test-Path $javaPath) {
    Write-Host "Found Java at: $javaPath" -ForegroundColor Green
} else {
    Write-Host "Java path not found: $javaPath" -ForegroundColor Red
    exit 1
}

# ตรวจสอบ PlantUML path
if (Test-Path $plantUMLPath) {
    Write-Host "Found PlantUML at: $plantUMLPath" -ForegroundColor Green
} else {
    Write-Host "PlantUML path not found: $plantUMLPath" -ForegroundColor Red
    exit 1
}

# เพิ่ม PATH ถาวร (ต้องรัน as Administrator)
try {
    # อ่าน PATH ปัจจุบัน
    $currentPath = [Environment]::GetEnvironmentVariable("PATH", "Machine")
    
    # ตรวจสอบว่า Java path มีอยู่แล้วหรือไม่
    if ($currentPath -notlike "*$javaPath*") {
        $newPath = $currentPath + ";$javaPath"
        [Environment]::SetEnvironmentVariable("PATH", $newPath, "Machine")
        Write-Host "Added Java to System PATH" -ForegroundColor Green
    } else {
        Write-Host "Java already in System PATH" -ForegroundColor Yellow
    }
    
    # ตรวจสอบว่า PlantUML path มีอยู่แล้วหรือไม่
    if ($currentPath -notlike "*$plantUMLPath*") {
        $newPath = [Environment]::GetEnvironmentVariable("PATH", "Machine") + ";$plantUMLPath"
        [Environment]::SetEnvironmentVariable("PATH", $newPath, "Machine")
        Write-Host "Added PlantUML to System PATH" -ForegroundColor Green
    } else {
        Write-Host "PlantUML already in System PATH" -ForegroundColor Yellow
    }
    
    Write-Host "`n✅ PATH updated successfully!" -ForegroundColor Green
    Write-Host "Please restart PowerShell or VS Code to use the new PATH" -ForegroundColor Cyan
    
} catch {
    Write-Host "`n❌ Failed to update System PATH" -ForegroundColor Red
    Write-Host "Please run this script as Administrator" -ForegroundColor Yellow
    Write-Host "Or add manually via System Properties > Environment Variables" -ForegroundColor Yellow
}

Write-Host "`n=== Quick Test ===" -ForegroundColor Yellow
Write-Host "Current session PATH includes:" -ForegroundColor White
if ($env:PATH -like "*Java*") {
    Write-Host "✅ Java (current session)" -ForegroundColor Green
} else {
    Write-Host "❌ Java (not in current session)" -ForegroundColor Red
}

if ($env:PATH -like "*PlantUML*") {
    Write-Host "✅ PlantUML (current session)" -ForegroundColor Green
} else {
    Write-Host "❌ PlantUML (not in current session)" -ForegroundColor Red
}

Write-Host "`nUsage after restart:" -ForegroundColor Cyan
Write-Host "  java -version" -ForegroundColor White
Write-Host "  plantuml diagram.puml" -ForegroundColor White
