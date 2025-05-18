/**
 * @file ci_map.hpp
 * @author Stellar Wolf Entertainment (SWE)
 * @brief Case-insensitive string-keyed map types for the SWE library.
 *
 * This header provides case-insensitive associative containers for mapping string or wide string keys to values.
 * Both std::map and std::unordered_map variants are provided, using custom hash and equality functors
 * for case-insensitive string comparison. Useful for settings, lookups, or any data where case-insensitive
 * string or wstring keys are required.
 *
 * @copyright MIT License
 * @date created 2025-05-16
 * @version 1.0
 */

#pragma once

#include "string.hpp"

#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include <unordered_map>

namespace swe
{
    /**
     * @brief Case-insensitive hash functor for std::unordered_map with std::string keys.
     */
    struct ci_hash
    {
        inline size_t operator()(const std::string& str) const noexcept
        {
            size_t hash = 0;
            for (char c : str)
            {
                hash = (hash << 5) + hash + std::tolower(c);
            }
            return hash;
        }
    };

    /**
     * @brief Case-insensitive hash functor for std::unordered_map with std::wstring keys.
     */
    struct wci_hash
    {
        inline size_t operator()(const std::wstring& str) const noexcept
        {
            size_t hash = 0;
            for (wchar_t c : str)
            {
                hash = (hash << 5) + hash + std::towlower(c);
            }
            return hash;
        }
    };

    /**
     * @brief Case-insensitive equality functor for std::(unordered_)map with std::string keys.
     */
    struct ci_equal
    {
        inline bool operator()(const std::string& lhs, const std::string& rhs) const noexcept
        {
            return str_equals(lhs, rhs, string_compare_type::ordinal_ignore_case);
        }
    };

    /**
     * @brief Case-insensitive equality functor for std::(unordered_)map with std::wstring keys.
     */
    struct wci_equal
    {
        inline bool operator()(const std::wstring& lhs, const std::wstring& rhs) const noexcept
        {
            return wstr_equals(lhs, rhs, string_compare_type::ordinal_ignore_case);
        }
    };

    /**
     * @brief Case-insensitive std::unordered_map with std::string keys.
     * @tparam T Value type.
     * @tparam Alloc Allocator type.
     */
    template <typename T, typename Alloc = std::allocator<std::pair<const std::string, T>>>
    using unordered_ci_map = std::unordered_map<std::string, T, ci_hash, ci_equal, Alloc>;

    /**
     * @brief Case-insensitive std::map with std::string keys.
     * @tparam T Value type.
     * @tparam Alloc Allocator type.
     */
    template <typename T, typename Alloc = std::allocator<std::pair<const std::string, T>>>
    using ci_map = std::map<std::string, T, ci_equal, Alloc>;

    /**
     * @brief Case-insensitive std::unordered_map with std::wstring keys.
     * @tparam T Value type.
     * @tparam Alloc Allocator type.
     */
    template <typename T, typename Alloc = std::allocator<std::pair<const std::wstring, T>>>
    using unordered_wci_map = std::unordered_map<std::wstring, T, wci_hash, wci_equal, Alloc>;

    /**
     * @brief Case-insensitive std::map with std::wstring keys.
     * @tparam T Value type.
     * @tparam Alloc Allocator type.
     */
    template <typename T, typename Alloc = std::allocator<std::pair<const std::wstring, T>>>
    using wci_map = std::map<std::wstring, T, wci_equal, Alloc>;

} // namespace swe