
# Java library with some Win32 system calls

### Package content

This is a Java package that contains some Windows system calls used in the Arduino IDE, we used JNI to not depend on JNA library.

### How to build

The header is generated with javah tool, the command to run from the root folder is:

`"$JAVA_HOME/bin/javah.exe" -cp src cc.arduino.os.windows.Win32Syscalls`

this command produce a file named: `cc_arduino_os_windows_Win32Syscalls.h`

To build the DLL, in theory, we can use any C/C++ compiler, BTW our tests with Cygwin
revealed that the required API:

```
#include <windows.h>
#include <VersionHelpers.h>
#include <ShellScalingAPI.h>
#include <Shlobj.h>
```

are not all available, so I opted to use Visual Studio 2017 Community, the procedure is:

1. Create a new Empty Project
2. On the "Solution Explorer" right-click on the "Header files" folder:
   -> "Add" -> "Existing item" and select `cc_arduino_os_windows_Win32Syscalls.h`
3. Do the same for "Source files" folder:
   -> "Add" -> "Existing item" and select `cc_arduino_os_windows_Win32Syscalls.c`
4. Open Project Properties:
   -> "General" -> "Configuration Type" -> Select "Dynamic Library (.dll)"
5. Project Properties:
   "C/C++" -> "All Options" -> "Additional Include Directories" -> add your JDK `include` and `include\win32` folder path.
   For example: `C:\Program Files (x86)\Java\jdk1.8.0_131\include;C:\Program Files (x86)\Java\jdk1.8.0_131\include\win32`
6. Project Properites:
   "Linker" -> "Input" -> "Additional Dependencies" -> add to the existing line the file "Shcore.lib".
7. You should be good to go now, so launch the build from the menu: "Build" -> "Build Solution".

