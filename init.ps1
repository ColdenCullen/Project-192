# Copying external dependencies
"Copying binaries..."
xcopy ExternalDependencies\bin Output\Final\Debug /e /y /i /r
xcopy ExternalDependencies\bin Output\Final\Release /e /y /i /r

# Initializing NodeJS
"Installing NodeJS..."
msiexec /i "ExternalDependencies\installers\node\node.msi" /quiet /qn /norestart
"Initializing game dependencies..."
Start-Process init.bat -WorkingDirectory "Game"

function Update-Cmake( $file )
{
    $content = Get-Content $file
    $match = ".*?INCLUDE\(TestBigEndian\).*?"
    $replacement =	"set_property( GLOBAL PROPERTY HLSLcc_GUID `"aa6e68b4-fb83-4093-95a5-dddf2b02e198`" )`n" +
					"set_property( GLOBAL PROPERTY libHLSLcc_GUID `"844FF918-0146-43C2-8765-0BD5B27FB689`" )`n" +
                    "get_property( exeGUID GLOBAL PROPERTY HLSLcc_GUID )`n" +
					"get_property( libGUID GLOBAL PROPERTY libHLSLcc_GUID )`n" +
                    "MESSAGE( STATUS `"Setting exe GUID to: `${exeGUID}`")`n" +
					"MESSAGE( STATUS `"Setting lib GUID to: `${libGUID}`")`n" +
                    "SET( HLSLcc_GUID_CMAKE `"`${exeGUID}`" CACHE INTERNAL `"projectGUID`" )`n" +
                    "SET( libHLSLcc_GUID_CMAKE `"`${libGUID}`" CACHE INTERNAL `"projectGUID`" )`n" +
                    "`nINCLUDE(TestBigEndian)"

    if( $content -match $match ) {
        $content -replace $match, $replacement | Set-Content $file
    }
}

"Updating HLSLcc CMake file..."
Update-Cmake ([System.IO.Path]::GetFullPath( ".\ExternalDependencies\submodules\hlslcc\mk\CMakeLists.txt" ))
Start-Process -FilePath ".\ExternalDependencies\tools\cmake\bin\cmake" -ArgumentList "-G `"Visual Studio 11`"" -WorkingDirectory ".\ExternalDependencies\submodules\hlslcc\mk" -NoNewWindow -Wait
