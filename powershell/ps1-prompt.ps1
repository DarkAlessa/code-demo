$esc=$([char]27) # ESC or `e in ASCII table
$promtSymbol = ""
$currentDir = (Get-Location | Get-Item).Name
Write-Host "$esc[38;2;255;255;255;48;2;255;36;20m $env:COMPUTERNAME $esc[0m$esc[38;2;255;255;255;48;2;255;36;20m$promtSymbol$esc$esc[0m$esc[38;2;255;255;255;48;2;255;36;20m Windows $esc[0m$esc[38;2;255;36;20;48;2;255;176;50m$esc[0m$esc[38;2;50;50;50;48;2;255;176;50m $currentDir$esc[0m$esc[38;2;255;176;50m$esc[0m"