ECHO OFF

ECHO Copying binaries...
xcopy ExternalDependencies\bin Output\Final\Debug /e /y /i /r
xcopy ExternalDependencies\bin Output\Final\Release /e /y /i /r

ECHO Initializing NodeJS
msiexec /i ExternalDependencies\installers\Node.msi /quiet /qn /norestart
start cmd /c "cd Game && init.bat"

pause
