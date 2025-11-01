# Use CMake\NMake to configure and build the program

# By default, it use the SDK from Visual studio [version] if installed.
# This will set an explicit version, but only if it is greater then the minimal required for Visual Studio  
# Tested with: 10.0.19041.0
#$env:WindowsSdkDir     = "C:\Program Files (x86)\Windows Kits\10\"
#$env:WindowsSdkVersion = "10.0.19041.0\"



# Build output and configuration
$build_type = "Debug" # Release
$out_nmake = "build-win"
$out_vs = "build-win-vs"
$Create_vs_project_files= $false    # $true # Creates Visual Studio project files, in addition.

# 1.1 Create output build folder if it doesn't exist and switch to it
Write-Host "`n- Create output build folder and switch to it." -ForegroundColor green 
New-Item -ItemType Directory -Force -Path $out_nmake | Out-Null
Write-Host "Switched to: $out_nmake" 
Set-Location $out_nmake

# 1.2 Make sure the VC environment variables are set n THIS terminal, before running CMake!
# - can not copy this via CMakeList.txt because it must exist before running CMakeList.txt
#
$file_VCEnv_vars = "MSVC-env.vars"
$file_VCEnv_Executor = "Init-env.bat"
Copy-Item ..\cmake\CMakeLists_Init-env.bat -Destination $file_VCEnv_Executor 
Write-Host "`n- Setup MSVC environment variables are read into this Power-shell session." -ForegroundColor Cyan 


# 1.2.1
# Catch the environment MS VC variables defined in:'vcvars64.bat' in the file: $file_VCEnv_vars.
# And apply the variables in this file to our current Power-Shell CLI environment.
#
# Issue avoided:
# - CMD.EXE has a command-line length limit (~8191 characters).
# - Directly calling vcvars64.bat and capturing environment variables may fail with 'input line too long'.
# - Workaround: Use a fixed environment file generated once by $file_VCEnv_Executor .
# - On subsequent runs, reuse this file to load environment variables.
# - This avoids the 'line too long' issue by not regenerating the environment every time.
#
if (-not (Test-Path $file_VCEnv_vars)) {                                    # Only run when file is not yet created
    Write-Host "Environment file not found. Running $file_VCEnv_Executor ..." -ForegroundColor Yellow
    #cmd.exe /c "..\$file_VCEnv_Executor  `"$($file_VCEnv_vars)`""           # Alternative    
    & cmd.exe /c ".\$file_VCEnv_Executor  `"$($file_VCEnv_vars)`""
    if ($LASTEXITCODE -ne 0) {
    
        Write-Host "`nException. Code: ($LASTEXITCODE) `n $_" -ForegroundColor Red
        Write-Host " - Usual code 255 means that the MSVC environment variables are read too many times (MS Issue)`n Simply close the Powershell CLI and start an new power-shell will resolve this`n`n" -ForegroundColor Yellow
        Set-Location ..
        exit $LASTEXITCODE
    }    
}
else {
    Write-Host "File with Environment VC variables already exists. Skipping creating of it. Ignoring: $file_VCEnv_Executor ."
}

# 1.2.2 Import environment variables from the created environment variables file, into the current PowerShell session.
Write-Host "Using environment file: $file_VCEnv_vars to set the VC Environment variables"
Get-Content $file_VCEnv_vars | ForEach-Object {
    $pair = $_ -split '=', 2
    if ($pair.Length -eq 2) {
        [Environment]::SetEnvironmentVariable($pair[0], $pair[1], 'Process')
    }
}


# 2. Run CMake to configure and make the makefile file for NMake (Windows, this requires the MSVC vars from 1.2) 
Write-Host "`n`n- BUILD: configure the Windows makefile (CMake for Windows)"  -ForegroundColor Green
##cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=$build_type -DCMAKE_SYSTEM_VERSION=$env:WindowsSdkVersion


# 3.1 Run nmake to build the the application using the makefile
Write-Host "`n- RUN: Build the project based on the generated makefile (NMake for Windows) "  -ForegroundColor Green
Write-Host "`- USING WIN SDK: $env:WindowsSdkDir"  -ForegroundColor Green
Write-Host "`- USING WIN Version: $env:WindowsSdkVersion"  -ForegroundColor Green

nmake
# nmake VERBOSE=1
Write-Host "`nDone, Building the project (using NMake)"  -ForegroundColor Green


#3.2 output the created executable
$targetFile = "target_name.txt"
if (Test-Path $targetFile) {
    $targetName = Get-Content $targetFile
    $buildDir = (Get-Location).Path   # current folder where script runs
    $exeFullPath = Join-Path -Path $buildDir -ChildPath "$targetName"
    $quotedCall = '& "' + "$exeFullPath.exe" + '"'
    Write-Host "- Execute: (copy past):`n`t`t`t $quotedCall`n" -ForegroundColor Cyan

} else {
    Write-Host "Warning: Target name file '$targetFile' not found.`n" -ForegroundColor Red 
}

#3.3 Copy the .dll file
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$SourceFile = Join-Path $ScriptDir "glfw3.dll"
$DestinationFolder = ".\"
if (Test-Path -Path $SourceFile -PathType Leaf) {
    if (-not (Test-Path -Path $DestinationFolder -PathType Container)) {    
        New-Item -Path $DestinationFolder -ItemType Directory | Out-Null
    }

    Copy-Item -Path $SourceFile -Destination $DestinationFolder -Force
    Write-Host "Copied dependency '$SourceFile'." -ForegroundColor Green
}else {
    Write-Host "Warning: Dependency DLL file '$SourceFile' not found.`n" -ForegroundColor Red 
}





# 4. OPTIONAL Build Visual Studio files
if ($Create_vs_project_files -eq $true) {
    Write-Host "`n`nOptional Build Visual Studio project files:"  -ForegroundColor Yellow -NoNewline
    Write-Host "`n`n- BUILD: configure the Windows Visual Studio solution and project files"  -ForegroundColor Green
    Set-Location ..
    New-Item -ItemType Directory -Force -Path $out_vs | Out-Null
    Set-Location $out_vs
    cmake ..  -G "Visual Studio 17 2022"
    Write-Host "`nDone, creating WindowsVisual Studio Project files!!"  -ForegroundColor Yellow
    Write-Host "- Use Visual Studio to build your project `n`n" 
}





Set-Location ..

