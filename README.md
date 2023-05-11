# CheckWinAppSdk

A simple command line utility that detects if the DDLM and framework WinAppSdk packages are installed. 
For use by a framework dependent app installer. The exit code indicates if a suitable sdk has been found.
The project only builds the x86 version because that will run on any of the three supported platforms.

It requires two position dependent parameters:

````
CheckWinAppSdk.exe <version> <platform>
````


Where **&lt;version>** is the minimum MSIX package version of a &lt;major>.&lt;minor> WinAppSdk release. ([Reference](https://github.com/DHancock/WinAppSdkCleaner/blob/main/WinAppSdkCleaner/versions.json))

The **&lt;platform>** is a Windows.System.ProcessorArchitecture enum value. Valid values are:

x86 = 0<br>
x64 = 9<br>
arm64 = 12<br>

For example:

````
CheckWinApp.exe 3000.851.1712.0 9
````

Will return **0** if an x64 WinAppSdk 1.3.1 to 1.3.(1 + n) has been installed. 
