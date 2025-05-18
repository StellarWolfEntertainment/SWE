#include "../include/swe/swe.hpp"

namespace swe
{
    std::string get_version()
    {
        return std::to_string(SWE_VERSION_MAJOR) + "." + std::to_string(SWE_VERSION_MINOR) + "." + std::to_string(SWE_VERSION_PATCH);
    }

    std::wstring get_wversion()
    {
        return std::to_wstring(SWE_VERSION_MAJOR) + L"." + std::to_wstring(SWE_VERSION_MINOR) + L"." + std::to_wstring(SWE_VERSION_PATCH);
    }

    void get_version(int* major, int* minor, int* patch)
    {
        if (major)
        {
            *major = SWE_VERSION_MAJOR;
        }

        if (minor)
        {
            *minor = SWE_VERSION_MINOR;
        }

        if (patch)
        {
            *patch = SWE_VERSION_PATCH;
        }
    }

    int get_version_number()
    {
        return SWE_VERSION;
    }

    bool check_version(int major, int minor, int patch)
    {
        return (major == SWE_VERSION_MAJOR) && (minor == SWE_VERSION_MINOR) && (patch == SWE_VERSION_PATCH);
    }

} // namespace swe