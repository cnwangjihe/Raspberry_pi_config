### Create Shortcut ###  

```powershell
    $dir = ""
    $WshShell = New-Object -ComObject WScript.Shell
    $Shortcut = $WshShell.CreateShortcut("$dir\XXX.lnk")
    $Shortcut.TargetPath = ""  # full path, like "C:\Windows\calc.exe"
    $Shortcut.Arguments = ""
    $Shortcut.Save()
```