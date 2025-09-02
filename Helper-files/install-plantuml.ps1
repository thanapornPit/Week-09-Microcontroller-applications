# สคริปต์ติดตั้ง PlantUML Local
Write-Host "Installing PlantUML Local Renderer..." -ForegroundColor Green

# สร้างโฟลเดอร์
$plantUMLPath = "C:\Tools\PlantUML"
if (!(Test-Path $plantUMLPath)) {
    New-Item -ItemType Directory -Path $plantUMLPath -Force
    Write-Host "Created directory: $plantUMLPath" -ForegroundColor Green
}

# ดาวน์โหลด PlantUML JAR
$jarPath = "$plantUMLPath\plantuml.jar"
Write-Host "Downloading PlantUML JAR..." -ForegroundColor Yellow

try {
    $latestRelease = Invoke-RestMethod -Uri "https://api.github.com/repos/plantuml/plantuml/releases/latest"
    $downloadUrl = ($latestRelease.assets | Where-Object { $_.name -eq "plantuml.jar" }).browser_download_url
    
    if (!$downloadUrl) {
        # Fallback URL
        $downloadUrl = "https://github.com/plantuml/plantuml/releases/latest/download/plantuml.jar"
    }
    
    Invoke-WebRequest -Uri $downloadUrl -OutFile $jarPath -UseBasicParsing
    Write-Host "Downloaded PlantUML JAR to: $jarPath" -ForegroundColor Green
    
    # แสดงขนาดไฟล์
    $fileSize = (Get-Item $jarPath).Length / 1MB
    Write-Host "File size: $([math]::Round($fileSize, 2)) MB" -ForegroundColor Cyan
    
} catch {
    Write-Host "Error downloading PlantUML JAR: $($_.Exception.Message)" -ForegroundColor Red
    exit 1
}

# สร้าง batch file สำหรับใช้งานง่าย
$batchContent = @"
@echo off
java -jar "C:\Tools\PlantUML\plantuml.jar" %*
"@

$batchPath = "$plantUMLPath\plantuml.bat"
Set-Content -Path $batchPath -Value $batchContent
Write-Host "Created batch file: $batchPath" -ForegroundColor Green

# เพิ่ม PATH (ชั่วคราว)
$env:PATH += ";$plantUMLPath"
Write-Host "Added to PATH (temporary): $plantUMLPath" -ForegroundColor Cyan

Write-Host "`n=== Installation Summary ===" -ForegroundColor Yellow
Write-Host "PlantUML JAR: $jarPath" -ForegroundColor White
Write-Host "Batch file: $batchPath" -ForegroundColor White
Write-Host "`nUsage examples:" -ForegroundColor Yellow
Write-Host "  java -jar `"$jarPath`" diagram.puml" -ForegroundColor White
Write-Host "  plantuml.bat diagram.puml (if PATH is set)" -ForegroundColor White

Write-Host "`n✅ PlantUML Local installation completed!" -ForegroundColor Green
