# VS Code Configurations
### Before you begin
1. Install Github desktop and clone the repo on your computer to any location you like.  
2. Make a new folder name ".vscode" and add the files from the repo (in folder .vscode above). This folder must be in the root of the repo.
3. Then in file explorer, on the top, click on `view → Hidden Items`. Now you should see a .git folder.
4. Go to `.git → info` and open the `exclude` file in Notepad/Notepad++.
5. Type .vscode in the file and save the file. This will prevent your vscode configurations files from syncing with the repo.

Your Exclude file must look like below:
```
# git ls-files --others --exclude-from=.git/info/exclude
# Lines that start with '#' are comments.
# For a project mostly in C, the following would be a good set of
# exclude patterns (uncomment them if you want to use them):
# *.[oa]
# *~
.vscode
```

### Configurations
**The following commands will make a lot of changes to your vscode environment. Remember to backup the values just in case you want to revert to original configuration.**


While specifying the  MSYS2 install location in the following files, the location has to be formatted as shown in example:
```
Say MSYS2 install at: C:\MSYS64
Then (path-to-msys2-install) is C:\\MSYS2
```

1. For `tasks.json` : Open the file in notepad/notepad++ and edit the `(path-to-msys2-location)` with your install location. Only replace the following lines according to your system configuration.
```
{
    "tasks": [
        {
            "type": "shell",
            "label": "C/C++: gcc.exe with GTK",
            "command": "cd '${fileDirname}'\r && cc `pkg-config gtk+-3.0 --cflags` ${fileBasename} -o ${fileBasenameNoExtension} `pkg-config gtk+-3.0 --libs`",
            "args": [],
            "options": {
                "cwd": "(path-to-msys2-location)\\mingw64\\bin"       <------------- Change this!!
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Task with GTK libraries for C GUI programs."
        }   
    ],
    "version": "2.0.0"
}

```

2. For `launch.json` : Open the file in notepad/notepad++ and edit the `(path-to-msys2-location)` with your install location. Only replace the following lines according to your system configuration.
```
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [

        {
            "name": "GCC with GTK",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "(path-to-msys2-location)\\mingw64\\bin\\gdb.exe",           <------------- Change this!!
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: gcc.exe with GTK"
        }   
    ]
}
```
3. For `c_cpp_properties.json` : Open the file in notepad/notepad++ and edit the `(path-to-msys2-location)` with your install location. Only replace the following lines according to your system configuration.
```
{
    
    "env": {
        "myDefaultIncludePath": [
            "${workspaceFolder}",
            "(path-to-msys2-location)//mingw64//include//*"          <------------- Change this!!
        ]
    },

    "configurations": [
        {
            "name": "Win32 with GTK includes",
            "intelliSenseMode": "windows-gcc-x64",
            "includePath": [
                "(path-to-msys2-location)//mingw64//include//gtk-3.0",                  <------------- Change this!!
                "(path-to-msys2-location)//mingw64//include//pango-1.0",                <------------- Change this!!
                "(path-to-msys2-location)//mingw64//include",                           <------------- Change this!!
                "(path-to-msys2-location)//mingw64//include//glib-2.0",                 <------------- Change this!!
                "(path-to-msys2-location)//mingw64//lib//glib-2.0//include",            <------------- Change this!!
                "(path-to-msys2-location)//mingw64//include//harfbuzz",                 <------------- Change this!!
                "(path-to-msys2-location)//mingw64//include//freetype2",                <------------- Change this!! 
                "(path-to-msys2-location)//mingw64//include//libpng16",                 <------------- Change this!!
                "(path-to-msys2-location)//mingw64//include//fribidi",                  <------------- Change this!!
                "(path-to-msys2-location)//mingw64//include//cairo",                    <------------- Change this!!
                "(path-to-msys2-location)//mingw64//include//lzo",                      <------------- Change this!!
                "(path-to-msys2-location)//mingw64//include//pixman-1",                 <------------- Change this!!
                "(path-to-msys2-location)//mingw64//include//gdk-pixbuf-2.0",           <------------- Change this!!
                "(path-to-msys2-location)//mingw64//include//atk-1.0"                   <------------- Change this!!
            ],
            "compilerPath": "(path-to-msys2-location)//mingw64//bin//gcc.exe",          <------------- Change this!! 
            "cStandard": "gnu17",
            "cppStandard": "gnu++14"
        }
    ],
    "version": 4
}
```

4. Open VS Code (not in current folder) and press `ctrl+shift+P` . In popup type`settings json` and select `Preferences: Open settings (JSON)`. In the same file add the following commands and modify accordingly. Once this is done click on terminal and you should see `name@name MINGW64 /d/folder`.
```
    "terminal.integrated.shell.windows": "(path-to-msys2-location)\\usr\\bin\\bash.exe",          <------------- Change this!!
    "terminal.integrated.shellArgs.windows": ["--login",],
    "terminal.integrated.env.windows": {
            "CHERE_INVOKING": "1",
            "MSYSTEM": "MINGW64",
    },
```

You are now ready to build applications in VS code. Go back to your repo folder and right click to "Open with VS Code". No errors must be reported. Then open gui.c and press F5. 

**Note: If your terminal gets stuck on pressing F5, Then click on your terminal and press Ctrl+C. This glitch is common and will happen quite a few times. You may encounter other errors while running the program. Simply re-run the program if this happens.**
