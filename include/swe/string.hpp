/**
 * @file string.hpp
 * @author Stellar Wolf Entertainment (SWE)
 * @brief String utility function declarations for the SWE library.
 *
 * This header provides a collection of reusable string manipulation utilities,
 * including case conversion, trimming, splitting, joining, comparison, and
 * formatting helpers. All functions are provided for both std::string and std::wstring types,
 * using a consistent naming convention (str_* & wstr_*). These utilities are designed for
 * efficiency and convenience in modern C++ projects.
 *
 * @copyright MIT License
 * @date created 2025-05-16
 * @version 1.0
 */
#pragma once

#include <algorithm>
#include <cctype>
#include <cwctype>
#include <sstream>
#include <string>
#include <vector>

namespace swe
{
    /**
     * @brief String comparison type for swe string utilities.
     */
    enum class string_compare_type
    {
        ordinal,             ///< Case-sensitive comparison.
        ordinal_ignore_case, ///< Case-insensitive comparison.
    };

    /**
     * @brief String split options for swe string utilities.
     */
    enum class string_split_options
    {
        none = 0,                     ///< No options.
        remove_empty_entries = 1,     ///< Remove empty entries from the result.
        trim_left = 2,                ///< Trim whitespace from the left of each entry.
        trim_right = 4,               ///< Trim whitespace from the right of each entry.
        trim = trim_left | trim_right ///< Trim whitespace from both ends of each entry.
    };

    /**
     * @brief Bitwise OR operator for string_split_options.
     */
    string_split_options operator|(string_split_options lhs, string_split_options rhs);

    /**
     * @brief Bitwise AND operator for string_split_options.
     */
    string_split_options operator&(string_split_options lhs, string_split_options rhs);

    /**
     * @brief Bitwise XOR operator for string_split_options.
     */
    string_split_options operator^(string_split_options lhs, string_split_options rhs);

    /**
     * @brief Bitwise NOT operator for string_split_options.
     */
    string_split_options operator~(string_split_options lhs);

    /**
     * @brief Bitwise OR assignment operator for string_split_options.
     */
    string_split_options& operator|=(string_split_options& lhs, string_split_options rhs);

    /**
     * @brief Bitwise AND assignment operator for string_split_options.
     */
    string_split_options& operator&=(string_split_options& lhs, string_split_options rhs);

    /**
     * @brief Bitwise XOR assignment operator for string_split_options.
     */
    string_split_options& operator^=(string_split_options& lhs, string_split_options rhs);

    // Narrow string (std::string) utilities

    /**
     * @brief Converts a string to lowercase.
     * @param str Input string.
     * @return Lowercase version of the input string.
     */
    std::string str_to_lower(const std::string& str);

    /**
     * @brief Converts a string to uppercase.
     * @param str Input string.
     * @return Uppercase version of the input string.
     */
    std::string str_to_upper(const std::string& str);

    /**
     * @brief Converts a string to title case.
     * @param str Input string.
     * @return Title-cased version of the input string.
     */
    std::string str_to_title(const std::string& str);

    /**
     * @brief Converts a string to a slug (lowercase, alphanumeric, separator).
     * @param str Input string.
     * @param separator Character to use as separator (default '_').
     * @return Slugified string.
     */
    std::string str_to_slug(const std::string& str, char separator = '_');

    /**
     * @brief Trims whitespace from both ends of a string.
     * @param str Input string.
     * @param whitespace Characters to trim (default: space, tab, newline, etc.).
     * @return Trimmed string.
     */
    std::string str_trim(const std::string& str, const std::string& whitespace = " \t\n\r\f\v");

    /**
     * @brief Trims whitespace from the left of a string.
     * @param str Input string.
     * @param whitespace Characters to trim (default: space, tab, newline, etc.).
     * @return Left-trimmed string.
     */
    std::string str_trim_left(const std::string& str, const std::string& whitespace = " \t\n\r\f\v");

    /**
     * @brief Trims whitespace from the right of a string.
     * @param str Input string.
     * @param whitespace Characters to trim (default: space, tab, newline, etc.).
     * @return Right-trimmed string.
     */
    std::string str_trim_right(const std::string& str, const std::string& whitespace = " \t\n\r\f\v");

    /**
     * @brief Replaces all occurrences of a substring with another string.
     * @param str Input string.
     * @param from Substring to replace.
     * @param to Replacement string.
     * @return Modified string with replacements.
     */
    std::string str_replace(const std::string& str, const std::string& from, const std::string& to);

    /**
     * @brief Checks if a string starts with a given prefix.
     * @param str Input string.
     * @param prefix Prefix string.
     * @param compare_type Comparison type (case-sensitive or case-insensitive).
     * @return True if str starts with prefix, false otherwise.
     */
    bool str_starts_with(const std::string& str, const std::string& prefix, string_compare_type compare_type = string_compare_type::ordinal);

    /**
     * @brief Checks if a string ends with a given suffix.
     * @param str Input string.
     * @param suffix Suffix string.
     * @param compare_type Comparison type (case-sensitive or case-insensitive).
     * @return True if str ends with suffix, false otherwise.
     */
    bool str_ends_with(const std::string& str, const std::string& suffix, string_compare_type compare_type = string_compare_type::ordinal);

    /**
     * @brief Compares two strings for equality.
     * @param str1 First string.
     * @param str2 Second string.
     * @param compare_type Comparison type (case-sensitive or case-insensitive).
     * @return True if strings are equal, false otherwise.
     */
    bool str_equals(const std::string& str1, const std::string& str2, string_compare_type compare_type = string_compare_type::ordinal);

    /**
     * @brief Splits a string by a delimiter character.
     * @param str Input string.
     * @param delimiter Delimiter character.
     * @return Vector of split substrings.
     */
    std::vector<std::string> str_split(const std::string& str, char delimiter, string_split_options options = string_split_options::remove_empty_entries);

    /**
     * @brief Joins a vector of strings with a delimiter.
     * @param strings Vector of strings to join.
     * @param delimiter Delimiter string.
     * @return Joined string.
     */
    std::string str_join(const std::vector<std::string>& strings, const std::string& delimiter);

    /**
     * @brief Obfuscates a string using a simple XOR cipher with a key.
     * 
     * This function performs a simple XOR operation on each character of the input string
     * with the corresponding character of the key. If the key is shorter than the string,     * 
     * it wraps around to the beginning of the key.
     * 
     * @param str Input string.
     * @param key Key for the XOR cipher.
     * 
     * @return Obfuscated string.
     */
    std::string str_obfuscate(const std::string& str, const std::string& key);

    /**
     * @brief De-obfuscates a string using a simple XOR cipher with a key.
     * 
     * This function reverses the obfuscation process by performing a simple XOR operation
     * on each character of the input string with the corresponding character of the key.
     * If the key is shorter than the string, it wraps around to the beginning of the key.
     * 
     * @param str Input string.
     * @param key Key for the XOR cipher.
     * 
     * @return De-obfuscated string.
     */
    std::string str_deobfuscate(const std::string& str, const std::string& key);

    // Wide string (std::wstring) utilities

    /**
     * @brief Converts a wide string to lowercase.
     * @param str Input wide string.
     * @return Lowercase version of the input wide string.
     */
    std::wstring wstr_to_lower(const std::wstring& str);

    /**
     * @brief Converts a wide string to uppercase.
     * @param str Input wide string.
     * @return Uppercase version of the input wide string.
     */
    std::wstring wstr_to_upper(const std::wstring& str);

    /**
     * @brief Converts a wide string to title case.
     * @param str Input wide string.
     * @return Title-cased version of the input wide string.
     */
    std::wstring wstr_to_title(const std::wstring& str);

    /**
     * @brief Converts a wide string to a slug (lowercase, alphanumeric, separator).
     * @param str Input wide string.
     * @param separator Separator character (default L'_').
     * @return Slugified wide string.
     */
    std::wstring wstr_to_slug(const std::wstring& str, wchar_t separator = L'_');

    /**
     * @brief Trims whitespace from both ends of a wide string.
     * @param str Input wide string.
     * @param whitespace Characters to trim (default: space, tab, newline, etc.).
     * @return Trimmed wide string.
     */
    std::wstring wstr_trim(const std::wstring& str, const std::wstring& whitespace = L" \t\n\r\f\v");

    /**
     * @brief Trims whitespace from the left of a wide string.
     * @param str Input wide string.
     * @param whitespace Characters to trim (default: space, tab, newline, etc.).
     * @return Left-trimmed wide string.
     */
    std::wstring wstr_trim_left(const std::wstring& str, const std::wstring& whitespace = L" \t\n\r\f\v");

    /**
     * @brief Trims whitespace from the right of a wide string.
     * @param str Input wide string.
     * @param whitespace Characters to trim (default: space, tab, newline, etc.).
     * @return Right-trimmed wide string.
     */
    std::wstring wstr_trim_right(const std::wstring& str, const std::wstring& whitespace = L" \t\n\r\f\v");

    /**
     * @brief Replaces all occurrences of a substring with another wide string.
     * @param str Input wide string.
     * @param from Substring to replace.
     * @param to Replacement wide string.
     * @return Modified wide string with replacements.
     */
    std::wstring wstr_replace(const std::wstring& str, const std::wstring& from, const std::wstring& to);

    /**
     * @brief Checks if a wide string starts with a given prefix.
     * @param str Input wide string.
     * @param prefix Prefix wide string.
     * @param compare_type Comparison type (case-sensitive or case-insensitive).
     * @return True if str starts with prefix, false otherwise.
     */
    bool wstr_starts_with(const std::wstring& str, const std::wstring& prefix, string_compare_type compare_type = string_compare_type::ordinal);

    /**
     * @brief Checks if a wide string ends with a given suffix.
     * @param str Input wide string.
     * @param suffix Suffix wide string.
     * @param compare_type Comparison type (case-sensitive or case-insensitive).
     * @return True if str ends with suffix, false otherwise.
     */
    bool wstr_ends_with(const std::wstring& str, const std::wstring& suffix, string_compare_type compare_type = string_compare_type::ordinal);

    /**
     * @brief Compares two wide strings for equality.
     * @param str1 First wide string.
     * @param str2 Second wide string.
     * @param compare_type Comparison type (case-sensitive or case-insensitive).
     * @return True if wide strings are equal, false otherwise.
     */
    bool wstr_equals(const std::wstring& str1, const std::wstring& str2, string_compare_type compare_type = string_compare_type::ordinal);

    /**
     * @brief Splits a wide string by a delimiter character.
     * @param str Input wide string.
     * @param delimiter Delimiter character.
     * @return Vector of split wide substrings.
     */
    std::vector<std::wstring> wstr_split(const std::wstring& str, wchar_t delimiter, string_split_options options = string_split_options::remove_empty_entries);

    /**
     * @brief Joins a vector of wide strings with a delimiter.
     * @param strings Vector of wide strings to join.
     * @param delimiter Delimiter wide string.
     * @return Joined wide string.
     */
    std::wstring wstr_join(const std::vector<std::wstring>& strings, const std::wstring& delimiter);

    /**
     * @brief Obfuscates a wide string using a simple XOR cipher with a key.
     * 
     * This function performs a simple XOR operation on each character of the input wide string
     * with the corresponding character of the key. If the key is shorter than the string, it wraps
     * around to the beginning of the key.
     * 
     * @param str Input wide string.
     * @param key Key for the XOR cipher.
     * 
     * @return Obfuscated wide string.
     */
    std::wstring wstr_obfuscate(const std::wstring& str, const std::wstring& key);

    /**
     * @brief De-obfuscates a wide string using a simple XOR cipher with a key.
     * 
     * This function reverses the obfuscation process by performing a simple XOR operation
     * on each character of the input wide string with the corresponding character of the key.
     * If the key is shorter than the string, it wraps around to the beginning of the key.
     * 
     * @param str Input wide string.
     * @param key Key for the XOR cipher.
     * 
     * @return De-obfuscated wide string.
     */
    std::wstring wstr_deobfuscate(const std::wstring& str, const std::wstring& key);

} // namespace swe