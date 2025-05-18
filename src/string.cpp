#include "../include/swe/string.hpp"
#include <algorithm>
#include <cctype>
#include <cwctype>
#include <iterator>
#include <sstream>

namespace swe
{

    string_split_options operator|(string_split_options lhs, string_split_options rhs)
    {
        return static_cast<string_split_options>(static_cast<int>(lhs) | static_cast<int>(rhs));
    }

    string_split_options operator&(string_split_options lhs, string_split_options rhs)
    {
        return static_cast<string_split_options>(static_cast<int>(lhs) & static_cast<int>(rhs));
    }

    string_split_options operator^(string_split_options lhs, string_split_options rhs)
    {
        return static_cast<string_split_options>(static_cast<int>(lhs) ^ static_cast<int>(rhs));
    }

    string_split_options operator~(string_split_options lhs)
    {
        return static_cast<string_split_options>(~static_cast<int>(lhs));
    }

    string_split_options& operator|=(string_split_options& lhs, string_split_options rhs)
    {
        lhs = lhs | rhs;
        return lhs;
    }

    string_split_options& operator&=(string_split_options& lhs, string_split_options rhs)
    {
        lhs = lhs & rhs;
        return lhs;
    }

    string_split_options& operator^=(string_split_options& lhs, string_split_options rhs)
    {
        lhs = lhs ^ rhs;
        return lhs;
    }

    bool has_flag(string_split_options options, string_split_options flag)
    {
        return (options & flag) == flag;
    }

    // --- Narrow string (std::string) utilities ---

    std::string str_to_lower(const std::string& str)
    {
        std::string result(str);
        std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
        return result;
    }

    std::string str_to_upper(const std::string& str)
    {
        std::string result(str);
        std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });
        return result;
    }

    std::string str_to_title(const std::string& str)
    {
        std::string result(str);
        bool new_word = true;
        std::transform(result.begin(), result.end(), result.begin(),
                       [&new_word](char c) -> char
                       {
                           if (std::isspace(c))
                           {
                               new_word = true;
                               return c;
                           }
                           if (new_word)
                           {
                               new_word = false;
                               return std::toupper(c);
                           }
                           return std::tolower(c);
                       });
        return result;
    }

    std::string str_to_slug(const std::string& str, char separator)
    {
        std::string result;
        bool last_was_sep = true;
        for (char c : str)
        {
            if (std::isalnum(static_cast<unsigned char>(c)))
            {
                result += std::tolower(static_cast<unsigned char>(c));
                last_was_sep = false;
            }
            else if (!last_was_sep)
            {
                result += separator;
                last_was_sep = true;
            }
        }
        // Remove trailing separator
        if (!result.empty() && result.back() == separator)
            result.pop_back();
        return result;
    }

    std::string str_trim(const std::string& str, const std::string& whitespace)
    {
        const auto begin = str.find_first_not_of(whitespace);
        if (begin == std::string::npos)
            return "";
        const auto end = str.find_last_not_of(whitespace);
        return str.substr(begin, end - begin + 1);
    }

    std::string str_trim_left(const std::string& str, const std::string& whitespace)
    {
        const auto begin = str.find_first_not_of(whitespace);
        if (begin == std::string::npos)
            return "";
        return str.substr(begin);
    }

    std::string str_trim_right(const std::string& str, const std::string& whitespace)
    {
        const auto end = str.find_last_not_of(whitespace);
        if (end == std::string::npos)
            return "";
        return str.substr(0, end + 1);
    }

    std::string str_replace(const std::string& str, const std::string& from, const std::string& to)
    {
        if (from.empty())
            return str;
        std::string result;
        size_t pos = 0, prev = 0;
        while ((pos = str.find(from, prev)) != std::string::npos)
        {
            result.append(str, prev, pos - prev);
            result += to;
            prev = pos + from.size();
        }
        result.append(str, prev, std::string::npos);
        return result;
    }

    bool str_starts_with(const std::string& str, const std::string& prefix, string_compare_type compare_type)
    {
        if (prefix.size() > str.size())
            return false;
        if (compare_type == string_compare_type::ordinal_ignore_case)
        {
            for (size_t i = 0; i < prefix.size(); ++i)
                if (std::tolower(static_cast<unsigned char>(str[i])) != std::tolower(static_cast<unsigned char>(prefix[i])))
                    return false;
            return true;
        }
        return str.compare(0, prefix.size(), prefix) == 0;
    }

    bool str_ends_with(const std::string& str, const std::string& suffix, string_compare_type compare_type)
    {
        if (suffix.size() > str.size())
            return false;
        size_t offset = str.size() - suffix.size();
        if (compare_type == string_compare_type::ordinal_ignore_case)
        {
            for (size_t i = 0; i < suffix.size(); ++i)
                if (std::tolower(static_cast<unsigned char>(str[offset + i])) != std::tolower(static_cast<unsigned char>(suffix[i])))
                    return false;
            return true;
        }
        return str.compare(offset, suffix.size(), suffix) == 0;
    }

    bool str_equals(const std::string& str1, const std::string& str2, string_compare_type compare_type)
    {
        if (str1.size() != str2.size())
            return false;
        if (compare_type == string_compare_type::ordinal_ignore_case)
        {
            for (size_t i = 0; i < str1.size(); ++i)
                if (std::tolower(static_cast<unsigned char>(str1[i])) != std::tolower(static_cast<unsigned char>(str2[i])))
                    return false;
            return true;
        }
        return str1 == str2;
    }

    std::vector<std::string> str_split(const std::string& str, char delimiter, string_split_options options)
    {
        if (str.empty())
            return {};

        std::vector<std::string> result;
        std::istringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delimiter))
        {
            if (token.empty() && has_flag(options, string_split_options::remove_empty_entries))
                continue;

            bool ltrim = has_flag(options, string_split_options::trim_left);
            bool rtrim = has_flag(options, string_split_options::trim_right);

            if (ltrim)
            {
                if (rtrim)
                {
                    token = str_trim(token);
                }
                else
                {
                    token = str_trim_left(token);
                }
            }
            else if (rtrim)
            {
                token = str_trim_right(token);
            }

            result.push_back(token);
        }

        if (!str.empty() && str.back() == delimiter && !has_flag(options, string_split_options::remove_empty_entries))
        {
            result.push_back("");
        }

        return result;
    }

    std::string str_join(const std::vector<std::string>& strings, const std::string& delimiter)
    {
        if (strings.empty())
            return "";
        std::ostringstream oss;
        auto it = strings.begin();
        oss << *it++;
        for (; it != strings.end(); ++it)
            oss << delimiter << *it;
        return oss.str();
    }

    std::string str_obfuscate(const std::string& str, const std::string& key)
    {
        std::string result;
        size_t key_length = key.length();
        for (size_t i = 0; i < str.length(); ++i)
        {
            result += str[i] ^ key[i % key_length];
        }
        return result;
    }

    std::string str_deobfuscate(const std::string& str, const std::string& key)
    {
        return str_obfuscate(str, key); // XOR is symmetric
    }

    // --- Wide string (std::wstring) utilities ---

    std::wstring wstr_to_lower(const std::wstring& str)
    {
        std::wstring result(str);
        std::transform(result.begin(), result.end(), result.begin(), [](wchar_t c) { return std::towlower(c); });
        return result;
    }

    std::wstring wstr_to_upper(const std::wstring& str)
    {
        std::wstring result(str);
        std::transform(result.begin(), result.end(), result.begin(), [](wchar_t c) { return std::towupper(c); });
        return result;
    }

    std::wstring wstr_to_title(const std::wstring& str)
    {
        std::wstring result(str);
        bool new_word = true;
        std::transform(result.begin(), result.end(), result.begin(),
                       [&new_word](wchar_t c) -> wchar_t
                       {
                           if (std::iswspace(c))
                           {
                               new_word = true;
                               return c;
                           }
                           if (new_word)
                           {
                               new_word = false;
                               return std::towupper(c);
                           }
                           return std::towlower(c);
                       });
        return result;
    }

    std::wstring wstr_to_slug(const std::wstring& str, wchar_t separator)
    {
        std::wstring result;
        bool last_was_sep = true;
        for (wchar_t c : str)
        {
            if (std::iswalnum(c))
            {
                result += std::towlower(c);
                last_was_sep = false;
            }
            else if (!last_was_sep)
            {
                result += separator;
                last_was_sep = true;
            }
        }
        if (!result.empty() && result.back() == separator)
            result.pop_back();
        return result;
    }

    std::wstring wstr_trim(const std::wstring& str, const std::wstring& whitespace)
    {
        const auto begin = str.find_first_not_of(whitespace);
        if (begin == std::wstring::npos)
            return L"";
        const auto end = str.find_last_not_of(whitespace);
        return str.substr(begin, end - begin + 1);
    }

    std::wstring wstr_trim_left(const std::wstring& str, const std::wstring& whitespace)
    {
        const auto begin = str.find_first_not_of(whitespace);
        if (begin == std::wstring::npos)
            return L"";
        return str.substr(begin);
    }

    std::wstring wstr_trim_right(const std::wstring& str, const std::wstring& whitespace)
    {
        const auto end = str.find_last_not_of(whitespace);
        if (end == std::wstring::npos)
            return L"";
        return str.substr(0, end + 1);
    }

    std::wstring wstr_replace(const std::wstring& str, const std::wstring& from, const std::wstring& to)
    {
        if (from.empty())
            return str;
        std::wstring result;
        size_t pos = 0, prev = 0;
        while ((pos = str.find(from, prev)) != std::wstring::npos)
        {
            result.append(str, prev, pos - prev);
            result += to;
            prev = pos + from.size();
        }
        result.append(str, prev, std::wstring::npos);
        return result;
    }

    bool wstr_starts_with(const std::wstring& str, const std::wstring& prefix, string_compare_type compare_type)
    {
        if (prefix.size() > str.size())
            return false;
        if (compare_type == string_compare_type::ordinal_ignore_case)
        {
            for (size_t i = 0; i < prefix.size(); ++i)
                if (std::towlower(str[i]) != std::towlower(prefix[i]))
                    return false;
            return true;
        }
        return str.compare(0, prefix.size(), prefix) == 0;
    }

    bool wstr_ends_with(const std::wstring& str, const std::wstring& suffix, string_compare_type compare_type)
    {
        if (suffix.size() > str.size())
            return false;
        size_t offset = str.size() - suffix.size();
        if (compare_type == string_compare_type::ordinal_ignore_case)
        {
            for (size_t i = 0; i < suffix.size(); ++i)
                if (std::towlower(str[offset + i]) != std::towlower(suffix[i]))
                    return false;
            return true;
        }
        return str.compare(offset, suffix.size(), suffix) == 0;
    }

    bool wstr_equals(const std::wstring& str1, const std::wstring& str2, string_compare_type compare_type)
    {
        if (str1.size() != str2.size())
            return false;
        if (compare_type == string_compare_type::ordinal_ignore_case)
        {
            for (size_t i = 0; i < str1.size(); ++i)
                if (std::towlower(str1[i]) != std::towlower(str2[i]))
                    return false;
            return true;
        }
        return str1 == str2;
    }

    std::vector<std::wstring> wstr_split(const std::wstring& str, wchar_t delimiter, string_split_options options)
    {
        if (str.empty())
            return {};

        std::vector<std::wstring> result;
        std::wistringstream ss(str);
        std::wstring token;
        while (std::getline(ss, token, delimiter))
        {
            if (token.empty() && has_flag(options, string_split_options::remove_empty_entries))
                continue;

            bool ltrim = has_flag(options, string_split_options::trim_left);
            bool rtrim = has_flag(options, string_split_options::trim_right);

            if (ltrim)
            {
                if (rtrim)
                {
                    token = wstr_trim(token);
                }
                else
                {
                    token = wstr_trim_left(token);
                }
            }
            else if (rtrim)
            {
                token = wstr_trim_right(token);
            }

            result.push_back(token);
        }

        if (!str.empty() && str.back() == delimiter && !has_flag(options, string_split_options::remove_empty_entries))
        {
            result.push_back(L"");
        }

        return result;
    }

    std::wstring wstr_join(const std::vector<std::wstring>& strings, const std::wstring& delimiter)
    {
        if (strings.empty())
            return L"";
        std::wostringstream oss;
        auto it = strings.begin();
        oss << *it++;
        for (; it != strings.end(); ++it)
            oss << delimiter << *it;
        return oss.str();
    }

    std::wstring wstr_obfuscate(const std::wstring& str, const std::wstring& key)
    {
        std::wstring result;
        size_t key_length = key.length();
        for (size_t i = 0; i < str.length(); ++i)
        {
            result += str[i] ^ key[i % key_length];
        }
        return result;
    }

    std::wstring wstr_deobfuscate(const std::wstring& str, const std::wstring& key)
    {
        return wstr_obfuscate(str, key); // XOR is symmetric
    }

} // namespace swe