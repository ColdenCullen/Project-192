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
    $replacement =	"SET( HLSLcc_GUID_CMAKE `"65CF13E0-F4B4-4A0E-8340-85A1467F6815`" CACHE INTERNAL `"projectGUID`" )`n" +
                    "SET( libHLSLcc_GUID_CMAKE `"844FF918-0146-43C2-8765-0BD5B27FB689`" CACHE INTERNAL `"projectGUID`" )`n" +
					"SET( ZERO_CHECK_GUID_CMAKE `"FF5E981C-2EBF-4ED7-BE4B-61C5D57DDF34`" CACHE INTERNAL `"projectGUID`" )`n" +
					"SET( ALL_BUILD_GUID_CMAKE `"FE11796B-F824-4971-BCD3-90DD4EE4AF02`" CACHE INTERNAL `"projectGUID`" )`n" +
                    "`nINCLUDE(TestBigEndian)"

    if( $content -match $match ) {
        $content -replace $match, $replacement | Set-Content $file
    }
}

"Updating HLSLcc CMake file..."
Update-Cmake ([System.IO.Path]::GetFullPath( ".\ExternalDependencies\submodules\hlslcc\mk\CMakeLists.txt" ))
Start-Process -FilePath ".\ExternalDependencies\tools\cmake\bin\cmake" -ArgumentList "-G `"Visual Studio 11`"" -WorkingDirectory ".\ExternalDependencies\submodules\hlslcc\mk" -NoNewWindow -Wait
