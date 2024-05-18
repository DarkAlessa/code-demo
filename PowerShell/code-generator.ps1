Clear-Host
#Validate Input
$projectName = [string]$(Write-Host "Project Name : " -ForegroundColor Yellow -NoNewline; Read-Host)

New-Item -Path "." -Name $projectName -ItemType Directory
"src", "build", "bin"        | ForEach-Object{New-Item -Name ".\$projectName\$_" -ItemType Directory}
"CMakeLists.txt", "build.sh" | ForEach-Object{New-Item -Name ".\$projectName\$_" -ItemType File}
<#
$MultilineComment = @"
    /*
     * Lisa Blackpink
     */
"@
Add-Content -Path $currentPath\MyFile.txt -Value $projectName
Add-Content -Path $currentPath\MyFile.txt -Value $MultilineComment
#>