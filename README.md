# CheckWinAppSdk

A simple command line utility that detects if the DDLM and Framework WinAppSdk packages are intalled. 
For use by a framework dependent app installer. The exit code indicates if a suitable sdk has been found.
The project only builds the x86 version because that will run on any of the three supported platforms.

It requires two position dependent parameters:

````
CheckWinApp.exe &lt;version> &lt;platform>
````

Where **&lt;version>** is the minimum MSIX package version of a &lt;major>.&lt;minor> WinAppSdk release. ([Reference](https://github.com/DHancock/WinAppSdkCleaner/blob/main/WinAppSdkCleaner/versions.json))

The **&lt;platform>** is a Windows.System.ProcessorArchitecture enum value. Valid values are:

x86 = 0
x64 = 9
arm64 = 12

For example:

````
CheckWinApp.exe 3000.851.1712.0 9
````

Will return **0** if an x64 WinAppSdk 1.3.1 to 1.3.(1 + n) has been installed. 
