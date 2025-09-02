# Auto-render Graphviz DOT files when saved
param(
    [string]$WatchPath = "./image-src",
    [string[]]$Extensions = @("*.dot", "*.gv", "*.puml"),
    [string]$OutputPath = "./images"
)

Write-Host "🎯 Starting DOT/PlantUML file auto-renderer..." -ForegroundColor Green
Write-Host "📁 Watching: $((Get-Location).Path)/$WatchPath" -ForegroundColor Cyan
Write-Host "📄 Extensions: $($Extensions -join ', ')" -ForegroundColor Cyan
Write-Host "📂 Output: $((Get-Location).Path)/$OutputPath" -ForegroundColor Cyan
Write-Host "⚡ Press Ctrl+C to stop" -ForegroundColor Yellow
Write-Host ""

# Create output directory if not exists
if (!(Test-Path $OutputPath)) {
    New-Item -ItemType Directory -Path $OutputPath -Force | Out-Null
    Write-Host "📁 Created output directory: $OutputPath" -ForegroundColor Green
}

# Create FileSystemWatcher
$watcher = New-Object System.IO.FileSystemWatcher
$watcher.Path = $WatchPath
$watcher.Filter = "*.*"
$watcher.IncludeSubdirectories = $false
$watcher.EnableRaisingEvents = $true

# Define the action
$action = {
    $path = $Event.SourceEventArgs.FullPath
    $name = $Event.SourceEventArgs.Name
    $changeType = $Event.SourceEventArgs.ChangeType
    
    # Check if file extension matches
    $shouldProcess = $false
    foreach ($ext in $Extensions) {
        if ($name -like $ext) {
            $shouldProcess = $true
            break
        }
    }
    
    if ($shouldProcess -and $changeType -eq 'Changed') {
        $timestamp = Get-Date -Format "HH:mm:ss"
        Write-Host "[$timestamp] 🔄 Detected change: $name" -ForegroundColor Yellow
        
        # Wait a bit to ensure file is completely written
        Start-Sleep -Milliseconds 500
        
        try {
            # Get file info
            $file = Get-Item $path
            $baseName = [System.IO.Path]::GetFileNameWithoutExtension($file.Name)
            $extension = [System.IO.Path]::GetExtension($file.Name).ToLower()
            $directory = $file.Directory.FullName
            
            # Determine output paths
            $svgOutput = Join-Path (Join-Path (Split-Path $directory -Parent) $OutputPath) "$baseName.svg"
            $pngOutput = Join-Path (Join-Path (Split-Path $directory -Parent) $OutputPath) "$baseName.png"
            
            if ($extension -eq ".dot" -or $extension -eq ".gv") {
                # Render Graphviz DOT files
                Write-Host "    📊 Rendering DOT to SVG..." -ForegroundColor Cyan -NoNewline
                $result = & dot -Tsvg $path -o $svgOutput 2>&1
                if ($LASTEXITCODE -eq 0) {
                    Write-Host " ✅" -ForegroundColor Green
                } else {
                    Write-Host " ❌" -ForegroundColor Red
                    Write-Host "    Error: $result" -ForegroundColor Red
                }
                
                Write-Host "    🖼️  Rendering DOT to PNG..." -ForegroundColor Cyan -NoNewline
                $result = & dot -Tpng $path -o $pngOutput 2>&1
                if ($LASTEXITCODE -eq 0) {
                    Write-Host " ✅" -ForegroundColor Green
                    $fileSize = [math]::Round((Get-Item $pngOutput).Length / 1KB, 1)
                    Write-Host "    📄 Generated: $baseName.svg, $baseName.png ($fileSize KB)" -ForegroundColor Green
                } else {
                    Write-Host " ❌" -ForegroundColor Red
                    Write-Host "    Error: $result" -ForegroundColor Red
                }
            }
            elseif ($extension -eq ".puml") {
                # Check if PlantUML is available
                $plantumlJar = "C:\ProgramData\plantuml\plantuml.jar"
                if (Test-Path $plantumlJar) {
                    Write-Host "    🌱 Rendering PlantUML to PNG..." -ForegroundColor Cyan -NoNewline
                    $result = & java -jar $plantumlJar -tpng -o (Split-Path $pngOutput -Parent) $path 2>&1
                    if ($LASTEXITCODE -eq 0) {
                        Write-Host " ✅" -ForegroundColor Green
                    } else {
                        Write-Host " ❌" -ForegroundColor Red
                        Write-Host "    Error: $result" -ForegroundColor Red
                    }
                    
                    Write-Host "    🌱 Rendering PlantUML to SVG..." -ForegroundColor Cyan -NoNewline
                    $result = & java -jar $plantumlJar -tsvg -o (Split-Path $svgOutput -Parent) $path 2>&1
                    if ($LASTEXITCODE -eq 0) {
                        Write-Host " ✅" -ForegroundColor Green
                        if (Test-Path $pngOutput) {
                            $fileSize = [math]::Round((Get-Item $pngOutput).Length / 1KB, 1)
                            Write-Host "    📄 Generated: $baseName.svg, $baseName.png ($fileSize KB)" -ForegroundColor Green
                        }
                    } else {
                        Write-Host " ❌" -ForegroundColor Red
                        Write-Host "    Error: $result" -ForegroundColor Red
                    }
                } else {
                    Write-Host "    ⚠️  PlantUML JAR not found at $plantumlJar" -ForegroundColor Yellow
                    Write-Host "    💡 Using VS Code PlantUML extension instead..." -ForegroundColor Blue
                }
            }
        }
        catch {
            Write-Host "    ❌ Error processing file: $($_.Exception.Message)" -ForegroundColor Red
        }
        
        Write-Host ""
    }
}

# Register event handlers
Register-ObjectEvent -InputObject $watcher -EventName "Changed" -Action $action

try {
    # Keep the script running
    while ($true) {
        Start-Sleep -Seconds 1
    }
}
finally {
    # Cleanup
    $watcher.EnableRaisingEvents = $false
    $watcher.Dispose()
    Write-Host "🛑 Auto-renderer stopped." -ForegroundColor Red
}
