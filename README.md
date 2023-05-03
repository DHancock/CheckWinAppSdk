# CheckWinAppSdk

A simple command line utility that detects if the DDLM and framework WinAppSdk packages are installed. 
For use by a framework dependent app installer. The exit code indicates if a suitable sdk has been found.
The project only builds the x86 version because that will run on any of the three supported platforms.

It requires two position dependent parameters:

````
CheckWinAppSdk.exe <version> <platform>
````

Where **&lt;version>** is the package major version of the required WinAppSdk version.<br>

All WinAppSdk 1.2.n versions have a package major version of 2000<br>
All WinAppSdk 1.3.n versions have a package major version of 3000 etc.<br>

The **&lt;platform>** is the Windows.System.ProcessorArchitecture enum value. Valid values are:

x86 = 0<br>
x64 = 9<br>
arm64 = 12<br>

For example:

````
CheckWinAppSdk.exe 3000 9
````

Will return **0** if an x64 WinAppSdk 1.3.n framework and DDLM packages are available for the current user.
