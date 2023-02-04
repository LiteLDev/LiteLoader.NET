@echo off

cd %~dp0..
setlocal enabledelayedexpansion

set LLNET_TOOTH_REMOTE_PATH=https://github.com/Tooth-Hub/LLDotNET.git

@REM rem Process System Proxy
@REM for /f "tokens=3* delims= " %%i in ('Reg query "HKCU\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v ProxyEnable') do (
@REM     if %%i==0x1 (
@REM         echo [INFO] System Proxy enabled. Adapting Settings...
@REM         for /f "tokens=3* delims= " %%a in ('Reg query "HKCU\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v ProxyServer') do set PROXY_ADDR=%%a
@REM         set http_proxy=http://!PROXY_ADDR!
@REM         set https_proxy=http://!PROXY_ADDR!
@REM         echo [INFO] System Proxy enabled. Adapting Settings finished.
@REM         echo.
@REM     )
@REM )


echo [INFO] Fetching tooth repo to GitHub ...
echo.

for /f "delims=" %%i in ('git describe --tags --always') do set LLNET_NOW_TAG_LONG=%%i
for /f "delims=-" %%i in ('git describe --tags --always') do set LLNET_NOW_TAG=%%i

echo LLNET_NOW_TAG_LONG %LLNET_NOW_TAG_LONG%
echo LLNET_NOW_TAG %LLNET_NOW_TAG%
echo.

git clone %LLNET_TOOTH_REMOTE_PATH% tooth-repo

cd tooth-repo
git fetch --all
git reset --hard origin/main
git checkout main
cd ..

echo.
echo [INFO] Fetching tooth-repo to GitHub finished
echo.

@REM remove refs directory in tooth repo
echo [INFO] Removing LiteLoader dir
rd /s /q tooth-repo\LiteLoader
echo [INFO] Removing lib dir
rd /s /q tooth-repo\lib
echo [INFO] Removing tooth.json
rd /s /q tooth-repo\tooth.json

@REM copy all SDK to tooth-repo
xcopy /e /y /i /q x64\Release\LiteLoader.NET.dll tooth-repo\LiteLoader\
xcopy /e /y /i /q x64\Release\LiteLoader.NET.runtimeconfig.json tooth-repo\LiteLoader\
xcopy /e /y /i /q x64\Release\Ijwhost.dll tooth-repo\lib\
xcopy /e /y /i /q output\RELEASE\tooth.json tooth-repo\tooth.json

cd tooth-repo
for /f "delims=" %%i in ('git status . -s') do set LLNET_SDK_NOW_STATUS=%%i
if "%LLNET_SDK_NOW_STATUS%" neq "" (
    echo [INFO] Modified files found.
    echo.
    git add .
    git commit -m "From LiteLoader.NET %LLNET_NOW_TAG%"
    echo.
    echo [INFO] Pushing to origin...
    echo.
    git push https://%USERNAME%:%REPO_KEY%@github.com/Tooth-Hub/LLDotNET.git
    cd ..
    echo.
    echo [INFO] Upload finished.
    echo.
    goto Finish
) else (
    cd ..
    echo.
    echo.
    echo [INFO] No modified files found.
    echo [INFO] No need to Upgrade tooth repo.
    goto Finish
)

:Finish
