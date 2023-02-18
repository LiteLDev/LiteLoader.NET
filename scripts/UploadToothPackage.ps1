Set-Location -Path "..\"

Set-Variable -Name "LLNET_TOOTH_REMOTE_PATH" -Value "https://github.com/Tooth-Hub/LLDotNET.git"

Write-Output -InputObject "[INFO] Fetching tooth repo to GitHub ..."
Write-Output -InputObject ""

git describe --tags --always | Set-Variable -Name "LLNET_NOW_TAG"

Write-Output -InputObject "LLNET_NOW_TAG $LLNET_NOW_TAG"
Write-Output -InputObject ""

git clone $LLNET_TOOTH_REMOTE_PATH

Set-Location -Path ".\LLDotNET"
git fetch --all
git reset --hard origin/main
git checkout main
Set-Location -Path "..\"

Write-Output -InputObject ""
Write-Output -InputObject "[INFO] Fetching tooth repo to GitHub finished"
Write-Output -InputObject ""

# remove refs directory in tooth repo
Write-Output -InputObject  "[INFO] Removing LiteLoader dir"
Remove-Item -Path ".\LLDotNET\LiteLoader\*" -Recurse
Write-Output -InputObject  "[INFO] Removing lib dir"
Remove-Item -Path ".\LLDotNET\lib\*" -Recurse
Write-Output -InputObject "[INFO] Removing tooth.json"
Remove-Item -Path ".\LLDotNET\tooth.json" -Recurse

# copy all to tooth repo
Copy-Item -Path ".\x64\Release\LiteLoader.NET.dll" -Destination ".\LLDotNET\LiteLoader\LiteLoader.NET.dll"
Copy-Item -Path ".\x64\Release\LiteLoader.NET.runtimeconfig.json" -Destination ".\LLDotNET\LiteLoader\LiteLoader.NET.runtimeconfig.json"
Copy-Item -Path ".\x64\Release\Ijwhost.dll" -Destination ".\LLDotNET\lib\Ijwhost.dll"
Copy-Item -Path ".\output\RELEASE\tooth.json" -Destination ".\LLDotNET\tooth.json"

Set-Location -Path ".\LLDotNET"
git status . -s | Set-Variable -Name "LLNET_TOOTH_NOW_STATUS"
if ($LLNET_TOOTH_NOW_STATUS -ne "") {
    Write-Output "[INFO] Modified files found."
    Write-Output -InputObject ""
    git add .
    git commit -m "From LiteLoader.NET $LLNET_NOW_TAG"
    Write-Output -InputObject ""
    Write-Output "[INFO] Pushing to origin..."
    Write-Output -InputObject ""
    git push "https://$env:USERNAME`:$env:REPO_KEY@github.com/Tooth-Hub/LLDotNET.git" main
    git tag $LLNET_NOW_TAG
    git push --tags "https://$env:USERNAME`:$env:REPO_KEY@github.com/Tooth-Hub/LLDotNET.git" main
    Set-Location "..\"
    Write-Output -InputObject ""
    Write-Output -InputObject "[INFO] Upload finished."
    Write-Output -InputObject ""
} else {
    Set-Location "..\"
    Write-Output -InputObject ""
    Write-Output -InputObject ""
    Write-Output -InputObject "[INFO] No modified files found."
    Write-Output -InputObject "[INFO] No need to Upgrade tooth repo."
}
