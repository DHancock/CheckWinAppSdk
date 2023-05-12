#include "pch.h"

using namespace winrt;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::System;


PackageVersion ConvertToPackageVersion(const std::wstring& str)
{
    PackageVersion version{ 0,0,0,0 };
    unsigned int lastPos{ 0 };

    for (int index = 0; index < 4; index++)
    {
        unsigned int pos{ str.find(L".", lastPos) };
        int value{ std::stoi(str.substr(lastPos, pos - lastPos)) };

        if ((value < 0) || (value > UINT16_MAX))
            throw std::invalid_argument("");

        switch (index)
        {
            case 0: version.Major = static_cast<uint16_t>(value); break;
            case 1: version.Minor = static_cast<uint16_t>(value); break;
            case 2: version.Build = static_cast<uint16_t>(value); break;
            case 3: version.Revision = static_cast<uint16_t>(value); break;
        }

        if ((pos == std::wstring::npos) || (str.size() <= (pos + 1)))
            break;

        lastPos = pos + 1;
    }

    return version;
}

bool IsValidPackageVersion(const PackageVersion& v, const PackageVersion& target)
{
    return (v.Major == target.Major) && (v.Minor >= target.Minor) && (v.Build >= target.Build) && (v.Revision >= target.Revision) ;
}



int wmain(int argc, wchar_t* argv[])
{
    // arg[0] = this exe's path
    // arg[1] = the minimum WinAppSdk MSIX package version
    // arg[2] = Windows.System.ProcessorArchitecture enum value (x86 = 0, x64 = 9, arm64 = 12)

    if (argc != 3)
        return 3;

    PackageVersion minVersion;
    ProcessorArchitecture platform;

    try
    {
        minVersion = ConvertToPackageVersion(argv[1]);
        platform = static_cast<ProcessorArchitecture>(std::stoi(argv[2]));
    }
    catch (const std::exception&)
    {
        return 2;
    }

    init_apartment();

    const hstring user;
    const std::wstring microsoft(L"8wekyb3d8bbwe");
    const std::wstring ddlmStart(L"Microsoft.WinAppRuntime.DDLM.");
    const std::wstring frameworkStart(L"Microsoft.WindowsAppRuntime.1.");
    
    for (auto&& package : PackageManager().FindPackagesForUserWithPackageTypes(user, PackageTypes::Main))
    {
        if (IsValidPackageVersion(package.Id().Version(), minVersion) &&
            (package.Id().Architecture() == platform) &&
            (package.Dependencies().Size() == 1) &&
            (package.Id().PublisherId() == microsoft))
        {
            const std::wstring fullName{ package.Id().FullName() };

            if ((fullName.size() > ddlmStart.size()) && (fullName.find(ddlmStart) == 0))
            {
                // check the DDLM package has a dependency on the framework package
                auto&& dependency = package.Dependencies().GetAt(0);

                if (dependency.IsFramework())
                {
                    const std::wstring frameworkName{ dependency.Id().FullName() };

                    if ((frameworkName.size() > frameworkStart.size()) && (frameworkName.find(frameworkStart) == 0))
                    {
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}


