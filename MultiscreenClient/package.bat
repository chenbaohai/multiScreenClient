del /s /q C:\Output\*.*
for /f "delims=" %%i in ('%MSYS_PATH%pwd /b') do set str=%%i
%MSYS_PATH%sh.exe --login -c "make --directory %str% BUILD_ENV=release"
rem mingw32-make BUILD_ENV=release
cd /d bin
copy .\MultiScreenClient\MultiScreenClient.exe .\Client
cd /d SetupFactory
SUF70Design.exe /build multiScreenClient.sf7
