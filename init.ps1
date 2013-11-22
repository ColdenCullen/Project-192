# Copying external dependencies
"Copying binaries..."
xcopy ExternalDependencies\bin Output\Final\Debug /e /y /i /r
xcopy ExternalDependencies\bin Output\Final\Release /e /y /i /r

# Initializing NodeJS
"Installing NodeJS..."
msiexec /i "ExternalDependencies\installers\node\node.msi" /quiet /qn /norestart
"Initializing game dependencies..."
Start-Process init.bat -WorkingDirectory "Game"

function Update-Cmake( $file, $guid )
{
    $content = Get-Content $file
    $match = ".*?INCLUDE\(TestBigEndian\).*?"
    $replacement = "set_property( GLOBAL PROPERTY HLSLcc_GUID `"" + $guid + "`" )`n" +
                    "get_property( projectGUID GLOBAL PROPERTY HLSLcc_GUID )`n" +
                    "MESSAGE( STATUS `"Setting project GUID to: ${projectGUID}`")`n" +
                    "SET( libHLSLcc_GUID_CMAKE `"${projectGUID}`" CACHE INTERNAL `"ProjectGUID`" )`n" +
                    "SET( HLSLcc_GUID_CMAKE `"${projectGUID}`" CACHE INTERNAL `"ProjectGUID`" )`n" +
                    "`nINCLUDE(TestBigEndian)"

    if( $content -match $match ) {
        $content -replace $match, $replacement | Set-Content $file
    }
}

"Updating HLSLcc CMake file..."
Update-Cmake ([System.IO.Path]::GetFullPath( ".\ExternalDependencies\submodules\hlslcc\mk\CMakeLists.txt" )) "aa6e68b4-fb83-4093-95a5-dddf2b02e198"
Start-Process ".\ExternalDependencies\tools\cmake\cmake -G `"Visual Studio 11`"" -WorkingDirectory ".\ExternalDependencies\submodules\hlslcc\mk"

pause
