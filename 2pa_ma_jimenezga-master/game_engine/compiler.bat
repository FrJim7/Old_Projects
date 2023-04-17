@REM
@cls
@echo off

echo ---------------------------------------------------------------------------
echo ----                    Deleted Previous Executable                     ---
del .\bin\*exe
del .\build\*.obj
del .\build\*.pdb
del .\build\*.ilk
echo ---------------------------------------------------------------------------

echo.
cl /c /MDd /nologo /Zi /GR- /EHs .\src\imgui\*.cc -I .\include -I .\deps\SFML\include -I .\include\imgui
cl /c /MDd /nologo /Zi /GR- /EHs .\src\*.cc -I .\include -I .\deps\SFML\include
cl /c /MDd /nologo /Zi /GR- /EHs .\src\*.c -I .\include -I .\deps\SFML\include
echo. 

echo ---------------------------------------------------------------------------
echo ----                             LINKING                                ---
echo --------------------------------------------------------------------------- 
cl /MDd /nologo /Zi /GR- /EHs /Fe:.\bin\output.exe .\*.obj .\deps\SFML\lib\*-d.lib .deps\Windows\*.lib opengl32.lib user32.lib gdi32.lib shell32.lib Ws2_32.lib
echo.

echo ---------------------------------------------------------------------------
echo ----                             MOVING                                ---- 
echo ---------------------------------------------------------------------------
echo.
move *.obj .\build
move *.ilk .\build
move .\bin\*.ilk .\build
echo. 
echo ---------------------------------------------------------------------------
echo ----                            FINALIZED                              ----
echo ---------------------------------------------------------------------------
echo.  


