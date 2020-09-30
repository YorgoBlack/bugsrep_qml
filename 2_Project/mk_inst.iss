#define MyAppName "Программа сбора статистики дефектов"
#define MyAppVersion "1.0"
#define MyAppPublisher "Owen"
#define MyAppURL "http://www.owen.ru/"
#define LibFolder "..\libs"
#define BaseDir "..\release\release"
#define DeployDir "..\deploy"
#define MyAppExeName "bugsapp.exe"
#define SetupBaseName   "setup_BugsApp_"
#define AppVersion      GetFileVersion(AddBackslash(BaseDir) + MyAppExeName)

[Setup]
AppId={{19296576-8490-4B52-87E4-AB1997F76157}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={code:SetupPathVar}
DisableProgramGroupPage=yes
OutputDir=..\4_Release
OutputBaseFilename={#SetupBaseName + AppVersion}
Compression=lzma
SolidCompression=yes


[Languages]
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

; deploy command 
; copy exe file to deploy dir; cd deploy dir 
; windeployqt --release --qmldir ..\3_Source  .\
;
[Files]
Source: {#DeployDir}\*; DestDir: {app}; Flags: ignoreversion recursesubdirs



[Icons]
Name: "{commonprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: {group}\{#MyAppName}\{cm:UninstallProgram,{#MyAppName}}; Filename: {uninstallexe}; WorkingDir: {app}\uninstall

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[code]
var
strGroup: String;

function SetupPathVar(Param: String): String;
  var
  strPath: String;
begin
    // Ставим значение по умолчанию...
      Result := ExpandConstant('{pf}\Owen\{#MyAppName}');
      strGroup:=ExpandConstant('Owen\{#MyAppName}');
end;
