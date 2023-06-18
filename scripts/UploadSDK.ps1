Set-Location -Path "..\"

Set-Variable -Name "LLNET_SDK_REMOTE_PATH" -Value "https://github.com/LiteLDev/SDK-dotnet.git"

Write-Output -InputObject "[INFO] Fetching SDK-dotnet to GitHub ..."
Write-Output -InputObject ""

git describe --tags --always | Set-Variable -Name "LLNET_NOW_TAG"

Write-Output -InputObject "LLNET_NOW_TAG $LLNET_NOW_TAG"
Write-Output -InputObject ""

if (!(Test-Path -Path ".\SDK-dotnet\refs\LiteLoader\LiteLoader.NET.dll" -PathType leaf)) {
    Write-Output -InputObject "[WARNING] SDK-dotnet files no found. Pulling from remote..."
    Write-Output -InputObject ""
    git clone $LLNET_SDK_REMOTE_PATH
}

Set-Location -Path ".\SDK-dotnet"
git fetch --all
git reset --hard origin/dev
git checkout dev
Set-Location -Path "..\"

Write-Output -InputObject ""
Write-Output -InputObject "[INFO] Fetching SDK-dotnet to GitHub finished"
Write-Output -InputObject ""

# remove refs directory in SDK-dotnet
Write-Output -InputObject "[INFO] Removing SDK-dotnet\refs\LiteLoader"
Remove-Item -Path ".\SDK-dotnet\refs\LiteLoader\*" -Recurse

# copy all SDK to SDK-dotnet
Copy-Item -Path ".\x64\Release\LiteLoader.NET.dll" -Destination ".\SDK-dotnet\refs\LiteLoader\LiteLoader.NET.dll"
Copy-Item -Path ".\x64\Release\LiteLoader.NET.xml" -Destination ".\SDK-dotnet\refs\LiteLoader\LiteLoader.NET.xml"

Set-Location -Path ".\SDK-dotnet"
git status . -s | Set-Variable -Name "LLNET_SDK_NOW_STATUS"
if ($LLNET_SDK_NOW_STATUS -ne "") {
    Write-Output "[INFO] Modified files found."
    Write-Output -InputObject ""
    git add .
    git commit -m "From LiteLoader.NET $LLNET_NOW_TAG"
    Write-Output -InputObject ""
    Write-Output "[INFO] Pushing to origin..."
    Write-Output -InputObject ""
    git push "https://$env:USERNAME`:$env:REPO_KEY@github.com/LiteLDev/SDK-dotnet.git" dev
    if ($args[0] -eq "release") {
        git tag $LLNET_NOW_TAG
        git push --tags "https://$env:USERNAME`:$env:REPO_KEY@github.com/LiteLDev/SDK-dotnet.git" dev
        git log -n1 --format=format:"%H" | Set-Variable -Name "LLNET_SDK_NOW_HASH"
        git checkout main
        git reset --hard $LLNET_SDK_NOW_HASH
        git push -f origin main
    }
    Set-Location "..\"
    Write-Output -InputObject ""
    Write-Output -InputObject "[INFO] Upload finished."
    Write-Output -InputObject ""
} else {
    Set-Location "..\"
    Write-Output -InputObject ""
    Write-Output -InputObject ""
    Write-Output -InputObject "[INFO] No modified files found."
    Write-Output -InputObject "[INFO] No need to Upgrade SDK-dotnet."
}
