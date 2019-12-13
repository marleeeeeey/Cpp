; The name of the installer
Name "Arkanoid"

; The file to write
OutFile "ArkanoidInstaller.exe"

; The default installation directory
InstallDir $PROGRAMFILES\Marleeeeeey\Arkanoid

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\Marleeeeeey\Arkanoid" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "Arkanoid"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "Arkanoid.exe"
  File "Arkanoid.ico"
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\Marleeeeeey\Arkanoid "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Marleeeeeey_Arkanoid" "DisplayName" "Arkanoid"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Marleeeeeey_Arkanoid" "Publisher" "Sergey Tyulenev"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Marleeeeeey_Arkanoid" "DisplayIcon" "$INSTDIR\Arkanoid.ico"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Marleeeeeey_Arkanoid" "DisplayVersion" "0.9"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Marleeeeeey_Arkanoid" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Marleeeeeey_Arkanoid" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Marleeeeeey_Arkanoid" "NoRepair" 1
  WriteUninstaller "$INSTDIR\uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\Marleeeeeey\Arkanoid"
  CreateShortcut "$SMPROGRAMS\Marleeeeeey\Arkanoid\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortcut "$SMPROGRAMS\Marleeeeeey\Arkanoid\Arkanoid.lnk" "$INSTDIR\Arkanoid.exe" "" "$INSTDIR\Arkanoid.ico" 0
  CreateShortcut "$DESKTOP\Arkanoid.lnk" "$INSTDIR\Arkanoid.exe" "" "$INSTDIR\Arkanoid.ico" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Marleeeeeey_Arkanoid"
  DeleteRegKey HKLM SOFTWARE\Marleeeeeey\Arkanoid

  ; Remove files and uninstaller
  Delete $INSTDIR\Arkanoid.exe
  Delete $INSTDIR\Arkanoid.ico
  Delete $INSTDIR\uninstall.exe

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Marleeeeeey\Arkanoid\*.*"
  Delete "$DESKTOP\Arkanoid.lnk"

  ; Remove directories used
  RMDir "$SMPROGRAMS\Marleeeeeey\Arkanoid"
  RMDir "$INSTDIR"

SectionEnd
