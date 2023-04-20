#include "pch.h"

using namespace winrt;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::System;


int wmain(int argc, wchar_t* argv[])
{
    // arg[0] = this exe's path
    // arg[1] = the minimum package major version (WinAppSdk 1.2.n = 2000, 1.3.n = 3000 ...)
    // arg[2] = Windows.System.ProcessorArchitecture enum value (x86 = 0, x64 = 9, arm64 = 12)

    if (argc != 3)
        return 3;

    int major;
    ProcessorArchitecture platform;

    try
    {
        major = std::stoi(argv[1]);
        platform = static_cast<ProcessorArchitecture>(std::stoi(argv[2]));
    }
    catch (const std::invalid_argument&)
    {
        return 2;
    }

    init_apartment();

    const std::wstring microsoft(L"8wekyb3d8bbwe");
    const hstring user;

    for (auto&& package : PackageManager().FindPackagesForUserWithPackageTypes(user, PackageTypes::Main))
    {
        if ((package.Id().Version().Major >= major) &&
            (package.Id().Architecture() == platform) &&
            (package.Dependencies().Size() == 1) &&
            (package.Id().PublisherId() == microsoft))
        {
            const std::wstring mainFullName{ package.Id().FullName() };

            if (mainFullName._Starts_with(L"Microsoft.WinAppRuntime.DDLM."))
            {
                // check the DDLM package has a dependency on a framework package
                auto&& dependency = package.Dependencies().GetAt(0);

                if (dependency.IsFramework())
                {
                    const std::wstring dependencyFullName{ dependency.Id().FullName() };

                    if (dependencyFullName._Starts_with(L"Microsoft.WindowsAppRuntime.1."))
                    {
                        // There is at least one WinAppSdk version 1.z.n that's suitable.
                        // The app also has a similar scheme when it calls the bootstrapper, but that
                        // additionally detects the latest available version (which may be this one).
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}
