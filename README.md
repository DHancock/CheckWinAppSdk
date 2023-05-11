# CheckWinAppSdk

A simple command line utility that detects if the DDLM and Framework WinAppSdk packages are intalled. 
For use by a framework dependent app installer. The exit code indicates if a suitable sdk has been found.
The project only builds the x86 version because that will run on any of the three supported platforms.

It requires two position dependent parameters:

````
CheckWinApp.exe <version> <platform>
````

Where **&lt;version>** is the minimum MSIX package version of a &lt;major>.&lt;minor> WinAppSdk release.

The **&lt;platform>** is a Windows.System.ProcessorArchitecture enum value. Valid values are:

x86 = 0<br>
x64 = 9<br>
arm64 = 12<br>

For example:

````
CheckWinApp.exe 3000.851.1712.0 9
````

Will return **0** if a x64 WinAppSdk release 1.3.n is installed where n >= 1
