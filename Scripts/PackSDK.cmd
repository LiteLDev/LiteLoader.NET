@echo off

cd ..

del /F /Q LiteLoader.NETSDK\LiteLoader.NET.dll 2>nul
del /F /Q LiteLoader.NETSDK\LiteLoader.NET.xml 2>nul

echo [INFO] Packing LiteLoader.NETSDK...
echo.

copy /Y x64\Release\LiteLoader.NET.dll LiteLoader.NETSDK\LiteLoader.NET.dll
copy /Y x64\Release\LiteLoader.NET.xml LiteLoader.NETSDK\LiteLoader.NET.xml

if [%1] neq [action] goto Zipped
echo.
echo [INFO] Zipping Files...
cd LiteLoader.NETSDK
..\SDK\Tools\7zip\7za.exe a -y -tzip -mmt -mx=3 ..\LiteLoader.NETSDK.zip *
cd ..
:Zipped

echo.
echo [INFO] Packing LiteLoader.NETSDK... DONE!

if [%1]==[action] goto End
timeout /t 3 >nul
:End
