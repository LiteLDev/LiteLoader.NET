@echo off

cd %~dp0..
setlocal enabledelayedexpansion

set LLNET_SDK_REMOTE_PATH=https://github.com/LiteLDev/SDK-dotnet.git

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


echo [INFO] Fetching SDK-dotnet to GitHub ...
echo.

for /f "delims=" %%i in ('git rev-parse --abbrev-ref HEAD') do set LLNET_NOW_BRANCH=%%i
for /f "delims=" %%i in ('git describe --tags --always') do set LLNET_NOW_TAG_LONG=%%i
for /f "delims=-" %%i in ('git describe --tags --always') do set LLNET_NOW_TAG=%%i

echo LLNET_NOW_BRANCH %LLNET_NOW_BRANCH%
echo LLNET_NOW_TAG_LONG %LLNET_NOW_TAG_LONG%
echo LLNET_NOW_TAG %LLNET_NOW_TAG%
echo.

if not exist SDK-dotnet/refs/LiteLoader/LiteLoader.NET.dll (
    echo [WARNING] SDK-dotnet files no found. Pulling from remote...
    echo.
    git clone %LLNET_SDK_REMOTE_PATH%
)

cd SDK-dotnet
git fetch --all
git reset --hard origin/%LLNET_NOW_BRANCH%
git checkout %LLNET_NOW_BRANCH%
cd ..

echo.
echo [INFO] Fetching SDK-dotnet to GitHub finished
echo.

@REM remove refs directory in SDK-dotnet
echo [INFO] Removing SDK-dotnet\refs\LiteLoader
rd /s /q SDK-dotnet\refs\LiteLoader

@REM copy all SDK to SDK-dotnet
xcopy /e /y /i /q x64\Release\LiteLoader.NET.dll SDK-dotnet\refs\LiteLoader\
xcopy /e /y /i /q x64\Release\LiteLoader.NET.xml SDK-dotnet\refs\LiteLoader\

cd SDK-dotnet
for /f "delims=" %%i in ('git status . -s') do set LLNET_SDK_NOW_STATUS=%%i
if "%LLNET_SDK_NOW_STATUS%" neq "" (
    echo [INFO] Modified files found.
    echo.
    git add .
    if "%LLNET_NOW_BRANCH%" == "main" (
        git commit -m "From LiteLoader.NET %LLNET_NOW_TAG%"
        if [%2] == [release] (
            git tag %LLNET_NOW_TAG%
        )
    ) else (
        git commit -m "From LiteLoader.NET %LLNET_NOW_TAG_LONG%"
    )
    echo.
    echo [INFO] Pushing to origin...
    echo.
    if [%1] neq [action] (
        git push origin %LLNET_NOW_BRANCH%
        git push --tags origin %LLNET_NOW_BRANCH%
    ) else (
        git push https://%USERNAME%:%REPO_KEY%@github.com/LiteLDev/SDK-dotnet.git %LLNET_NOW_BRANCH%
        git push --tags https://%USERNAME%:%REPO_KEY%@github.com/LiteLDev/SDK-dotnet.git %LLNET_NOW_BRANCH%
        if [%2] == [release] (
            git push -f https://%USERNAME%:%REPO_KEY%@github.com/LiteLDev/SDK-dotnet.git main
        )
    )
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
    echo [INFO] No need to Upgrade SDK-dotnet.
    goto Finish
)

:Finish
if [%1]==[action] goto End
timeout /t 3 >nul
:End