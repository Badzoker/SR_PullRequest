rmdir /s /q "ipch"
rmdir /s /q "Debug"
rmdir /s /q "Release"

rmdir /s /q .\MyClient\Include\Debug
rmdir /s /q .\MyClient\Include\ipch
rmdir /s /q .\MyClient\Include\Release
rmdir /s /q .\MyClient\Include\x64

rmdir /s /q .\Engine\System\Include\Debug
rmdir /s /q .\Engine\Utility\Include\Debug

del /f /q .\MyClient\Bin\MyClient.exe
del /f /q .\MyClient\Bin\MyClient.ilk
del /f /q .\MyClient\Bin\MyClient.pdb
del /f /q Second_SR.VC.db