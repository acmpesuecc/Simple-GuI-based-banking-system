## GTK Installaton Instructions

Steps to install the library:

1. Install the GTK+ Library from the website: [GTK+](https://www.gtk.org/docs/installations/windows/#using-gtk-from-msys2-packages).
2. Configure VSCode to Build and Debug C GUI programs.


## GTK+ install notes

Step 1: Installing the MSYS2 system. You can do that from here: [MSYS2](https://www.msys2.org/). While installing, **make sure to remember where the system is installed**. This will be needed later.
Follow all the steps mentoined on the website. After the install, you will have two installations of MinGW on your system. I would suggest uninstalling the one installed before (installed by you) to avoid confusion later.


### Path variables
Add `(path to msys2 install)\mingw64\bin` to your system's path environmental variable. To change environmental variables: `Start → Settings → System → About → Advanced System settings → Environment Variables`

Also make a new variable with variable name `PKG_CONFIG_PATH` and variable value `(path to msys2 install)\mingw64\lib\pkgconfig\`

Here, `(path to msys2 install)` is the path to msys2 installation.

Open a command prompt and run the following commands:

1. `gcc -v`
2. `pkg-config`

If the above commands shoud return information similar to:

1. `gcc -v`
```
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=D:/msys64/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/10.2.0/lto-wrapper.exe
Target: x86_64-w64-mingw32
Configured with: ../gcc-10.2.0/configure --prefi...
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 10.2.0 (Rev10, Built by MSYS2 project)
```
2. `pkg-config`
```
Please specify at least one package name on the command line.
```

If these are return errors, then tell me.

After the above commands work, open a MSYS2 MinGW 64-bit shell (`Start → MSYS2 → MSYS2 MinGW 64-bit`) and follow steps on the gtk website. For now step 4 can be ignored. If everything goes well, the gtk library is now installed. 

You can test this by running the sample GUI app in the Test GUI folder.

## Building in shell

To build apps with these libraries, the following command will be used: ```gcc `pkg-config --cflags gtk+-3.0` filename.c -o filename `pkg-config --libs gtk+-3.0` ```

**Note: The above command does not work in windows cmd or powershell! It will only work in the newly installed shells. Preferably use the MinGW shell used earlier.**

IF you have some GTK code, then you can build it by following these steps:

1. Open a MSYS2 MinGW 64-bit shell (`Start → MSYS2 → MSYS2 MinGW 64-bit`).
2. cd into working directory.
3. Run the command ```gcc `pkg-config --cflags gtk+-3.0` filename.c -o filename `pkg-config --libs gtk+-3.0` ``` . Do not forget to change filename with your filename.

An executable will be made if no errors occur.
