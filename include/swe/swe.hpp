/**
 * @file swe.hpp
 * @author Stellar Wolf Entertainment (SWE)
 * @brief SWE library version macros and version query functions.
 *
 * This header defines the version macros for the SWE library and provides
 * functions to query the version as a string, wide string, or as individual
 * major, minor, and patch numbers. These utilities are useful for feature
 * detection, compatibility checks, and displaying library version information.
 *
 * @copyright MIT License
 * @date created 2025-05-16
 * @version 1.0
 */
#pragma once

#include <string>

/**
 * @brief Major version number of the SWE library.
 */
#define SWE_VERSION_MAJOR 1

/**
 * @brief Minor version number of the SWE library.
 */
#define SWE_VERSION_MINOR 0

/**
 * @brief Patch version number of the SWE library.
 */
#define SWE_VERSION_PATCH 0

/**
 * @brief Combined numeric version of the SWE library in the format
 * (major * 1,000,000) + (minor * 1,000) + patch.
 *
 * Useful for easy numeric comparisons of library versions.
 */
#define SWE_VERSION ((SWE_VERSION_MAJOR * 1000000) + (SWE_VERSION_MINOR * 1000) + SWE_VERSION_PATCH)

/**
 * @brief Macro to check if the current version matches the specified
 * major, minor, and patch numbers.
 * 
 * This check ensures that the header file and the library are in agreement
 * on the exact version being used. if you just want to ensure that the lib
 * is at least the version of the header you can check with `get_version_number() >= SWE_VERSION`
 */
#define SWE_CHECK_VERSION() check_version(SWE_VERSION_MAJOR, SWE_VERSION_MINOR, SWE_VERSION_PATCH)

namespace swe
{
    /**
     * @brief Version string of the library.
     * 
     * @return A string representing the version of the library.
     */
    std::string get_version();

    /**
     * @brief Version string of the library.
     * 
     * @return A wide string representing the version of the library.
     */
    std::wstring get_wversion();

    /**
     * @brief Get the version of the library as major, minor, and patch numbers.
     * 
     * @param major Pointer to store the major version number.
     * @param minor Pointer to store the minor version number.
     * @param patch Pointer to store the patch version number.
     */
    void get_version(int* major, int* minor, int* patch);

    /**
     * @brief Get the version number of the library as an integer.
     * 
     * @return The version number in the format (major * 1,000,000) + (minor * 1,000) + patch.
     */
    int get_version_number();

    /**
     * @brief Check if the current version exactly matches the specified major, minor, and patch numbers.
     * 
     * This function verifies that the header and library versions are in sync,
     * helping catch accidental mismatches during development or deployment.
     * It primarily ensures the header does not declare features that are missing
     * in the linked library (e.g., a function added in the header but not implemented).
     * 
     * @param major Major version number to check.
     * @param minor Minor version number to check.
     * @param patch Patch version number to check.
     * 
     * @return true if the version matches; false otherwise.
     */
    bool check_version(int major, int minor, int patch);
} // namespace swe