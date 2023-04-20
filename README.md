# CheckWinAppSdk

A simple command line utility that detects if the DDLM and Framework WinAppSdk packages are intalled. 
For use by a framework dependent app installer. The exit code indicates if a suitable sdk has been found.
The project only builds the x86 version because that will run on any of the three supported platforms.

It requires two position dependent parameters:

````
CheckWinApp.exe &lt;version> &lt;platform>
````

Where **&lt;version>** is the package major version of the minimum required WinAppSdk version.

All WinAppSdk 1.2.n semantic versions have a package major version of 2000
All WinAppSdk 1.3.n semantic versions have a package major version of 3000 etc.

The **&lt;platform>** is the Windows.System.ProcessorArchitecture enum value. Valid values are:

x86 = 0
x64 = 9
arm64 = 12

For example:

````
CheckWinApp.exe 3000 9
````

Will return **0** if at least an x64 WinAppSdk 1.3.n has been installed. 
