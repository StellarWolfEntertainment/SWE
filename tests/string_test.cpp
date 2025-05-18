#include "../include/swe/string.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

// Traits to unify narrow and wide string APIs
template <typename T>
struct StringAPI;

template <>
struct StringAPI<std::string>
{
    using CharType = char;
    using StringType = std::string;
    using VectorType = std::vector<std::string>;

    static StringType to_lower(const StringType& s)
    {
        return swe::str_to_lower(s);
    }
    static StringType to_upper(const StringType& s)
    {
        return swe::str_to_upper(s);
    }
    static StringType to_title(const StringType& s)
    {
        return swe::str_to_title(s);
    }
    static StringType to_slug(const StringType& s)
    {
        return swe::str_to_slug(s);
    }
    static StringType trim(const StringType& s)
    {
        return swe::str_trim(s);
    }
    static StringType trim_left(const StringType& s)
    {
        return swe::str_trim_left(s);
    }
    static StringType trim_right(const StringType& s)
    {
        return swe::str_trim_right(s);
    }
    static StringType replace(const StringType& s, const StringType& old_val, const StringType& new_val)
    {
        return swe::str_replace(s, old_val, new_val);
    }
    static bool starts_with(const StringType& s, const StringType& prefix)
    {
        return swe::str_starts_with(s, prefix);
    }
    static bool ends_with(const StringType& s, const StringType& suffix)
    {
        return swe::str_ends_with(s, suffix);
    }
    static bool equals(const StringType& s1, const StringType& s2, swe::string_compare_type type)
    {
        return swe::str_equals(s1, s2, type);
    }
    static VectorType split(const StringType& s, CharType delimiter, swe::string_split_options options)
    {
        return swe::str_split(s, delimiter, options);
    }
    static StringType join(const VectorType& parts, const StringType& delimiter)
    {
        return swe::str_join(parts, delimiter);
    }
    static StringType obfuscate(const StringType& s, const StringType& key)
    {
        return swe::str_obfuscate(s, key);
    }
};

template <>
struct StringAPI<std::wstring>
{
    using CharType = wchar_t;
    using StringType = std::wstring;
    using VectorType = std::vector<std::wstring>;

    static StringType to_lower(const StringType& s)
    {
        return swe::wstr_to_lower(s);
    }
    static StringType to_upper(const StringType& s)
    {
        return swe::wstr_to_upper(s);
    }
    static StringType to_title(const StringType& s)
    {
        return swe::wstr_to_title(s);
    }
    static StringType to_slug(const StringType& s)
    {
        return swe::wstr_to_slug(s);
    }
    static StringType trim(const StringType& s)
    {
        return swe::wstr_trim(s);
    }
    static StringType trim_left(const StringType& s)
    {
        return swe::wstr_trim_left(s);
    }
    static StringType trim_right(const StringType& s)
    {
        return swe::wstr_trim_right(s);
    }
    static StringType replace(const StringType& s, const StringType& old_val, const StringType& new_val)
    {
        return swe::wstr_replace(s, old_val, new_val);
    }
    static bool starts_with(const StringType& s, const StringType& prefix)
    {
        return swe::wstr_starts_with(s, prefix);
    }
    static bool ends_with(const StringType& s, const StringType& suffix)
    {
        return swe::wstr_ends_with(s, suffix);
    }
    static bool equals(const StringType& s1, const StringType& s2, swe::string_compare_type type)
    {
        return swe::wstr_equals(s1, s2, type);
    }
    static VectorType split(const StringType& s, CharType delimiter, swe::string_split_options options)
    {
        return swe::wstr_split(s, delimiter, options);
    }
    static StringType join(const VectorType& parts, const StringType& delimiter)
    {
        return swe::wstr_join(parts, delimiter);
    }
    static StringType obfuscate(const StringType& s, const StringType& key)
    {
        return swe::wstr_obfuscate(s, key);
    }
};

// Define the test fixture template
template <typename T>
class StringTest : public ::testing::Test
{
  public:
    using StringType = typename StringAPI<T>::StringType;
    using VectorType = typename StringAPI<T>::VectorType;
    using CharType = typename StringAPI<T>::CharType;

    // Helper to create string literals for wide/narrow strings
    static StringType lit(const char* narrow)
    {
        if constexpr (std::is_same_v<T, std::wstring>)
        {
            // Convert narrow string literal to wide string literal
            std::wstring ws;
            while (*narrow)
            {
                ws.push_back(static_cast<wchar_t>(*narrow++));
            }
            return ws;
        }
        else
        {
            return std::string(narrow);
        }
    }
};

using MyStringTypes = ::testing::Types<std::string, std::wstring>;
TYPED_TEST_SUITE(StringTest, MyStringTypes);

TYPED_TEST(StringTest, ToLower)
{
    auto input = TestFixture::lit("Hello World!");
    auto expected = TestFixture::lit("hello world!");
    auto result = StringAPI<TypeParam>::to_lower(input);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, ToUpper)
{
    auto input = TestFixture::lit("Hello World!");
    auto expected = TestFixture::lit("HELLO WORLD!");
    auto result = StringAPI<TypeParam>::to_upper(input);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, ToTitle)
{
    auto input = TestFixture::lit("hello world!");
    auto expected = TestFixture::lit("Hello World!");
    auto result = StringAPI<TypeParam>::to_title(input);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, ToSlug)
{
    auto input = TestFixture::lit("Hello World!");
    auto expected = TestFixture::lit("hello_world");
    auto result = StringAPI<TypeParam>::to_slug(input);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Trim)
{
    auto input = TestFixture::lit("   Hello World!   ");
    auto expected = TestFixture::lit("Hello World!");
    auto result = StringAPI<TypeParam>::trim(input);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, TrimLeft)
{
    auto input = TestFixture::lit("   Hello World!");
    auto expected = TestFixture::lit("Hello World!");
    auto result = StringAPI<TypeParam>::trim_left(input);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, TrimRight)
{
    auto input = TestFixture::lit("Hello World!   ");
    auto expected = TestFixture::lit("Hello World!");
    auto result = StringAPI<TypeParam>::trim_right(input);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Replace)
{
    auto input = TestFixture::lit("Hello World!");
    auto expected = TestFixture::lit("Hello SWE!");
    auto result = StringAPI<TypeParam>::replace(input, TestFixture::lit("World"), TestFixture::lit("SWE"));
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, StartsWith)
{
    auto input = TestFixture::lit("Hello World!");
    auto prefix = TestFixture::lit("Hello");
    EXPECT_TRUE(StringAPI<TypeParam>::starts_with(input, prefix));
}

TYPED_TEST(StringTest, EndsWith)
{
    auto input = TestFixture::lit("Hello World!");
    auto suffix = TestFixture::lit("World!");
    EXPECT_TRUE(StringAPI<TypeParam>::ends_with(input, suffix));
}

TYPED_TEST(StringTest, EqualsOrdinal)
{
    auto input1 = TestFixture::lit("Hello World!");
    auto input2 = TestFixture::lit("Hello World!");
    EXPECT_TRUE(StringAPI<TypeParam>::equals(input1, input2, swe::string_compare_type::ordinal));
}

TYPED_TEST(StringTest, EqualsOrdinalIgnoreCase)
{
    auto input1 = TestFixture::lit("Hello World!");
    auto input2 = TestFixture::lit("hello world!");
    EXPECT_TRUE(StringAPI<TypeParam>::equals(input1, input2, swe::string_compare_type::ordinal_ignore_case));
}

TYPED_TEST(StringTest, Join)
{
    typename TestFixture::VectorType input = {TestFixture::lit("Hello"), TestFixture::lit("World!")};
    auto expected = TestFixture::lit("Hello,World!");
    auto result = StringAPI<TypeParam>::join(input, TestFixture::lit(","));
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, ToLower_EmptyString)
{
    auto input = TestFixture::lit("");
    auto expected = TestFixture::lit("");
    auto result = StringAPI<TypeParam>::to_lower(input);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Trim_AllWhitespace)
{
    auto input = TestFixture::lit("     \t\n  ");
    auto expected = TestFixture::lit("");
    auto result = StringAPI<TypeParam>::trim(input);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Replace_NoMatch)
{
    auto input = TestFixture::lit("Hello World!");
    auto expected = TestFixture::lit("Hello World!");
    auto result = StringAPI<TypeParam>::replace(input, TestFixture::lit("XYZ"), TestFixture::lit("ABC"));
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, EqualsOrdinalIgnoreCase_DifferentCase)
{
    auto input1 = TestFixture::lit("HeLLo");
    auto input2 = TestFixture::lit("hello");
    EXPECT_TRUE(StringAPI<TypeParam>::equals(input1, input2, swe::string_compare_type::ordinal_ignore_case));
}

TYPED_TEST(StringTest, StartsWith_ExactMatch)
{
    auto input = TestFixture::lit("Hello");
    auto prefix = TestFixture::lit("Hello");
    EXPECT_TRUE(StringAPI<TypeParam>::starts_with(input, prefix));
}

TYPED_TEST(StringTest, EndsWith_ExactMatch)
{
    auto input = TestFixture::lit("World");
    auto suffix = TestFixture::lit("World");
    EXPECT_TRUE(StringAPI<TypeParam>::ends_with(input, suffix));
}

TYPED_TEST(StringTest, SingleCharacter)
{
    auto input = TestFixture::lit("A");
    auto expected = TestFixture::lit("a");
    auto result = StringAPI<TypeParam>::to_lower(input);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Trim_MixedWhitespace)
{
    auto input = TestFixture::lit(" \t\nHello\t\n ");
    auto expected = TestFixture::lit("Hello");
    auto result = StringAPI<TypeParam>::trim(input);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Join_EmptyVector)
{
    typename TestFixture::VectorType input = {};
    auto expected = TestFixture::lit("");
    auto result = StringAPI<TypeParam>::join(input, TestFixture::lit(","));
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Replace_WithEmpty)
{
    auto input = TestFixture::lit("Hello World!");
    auto expected = TestFixture::lit("Hello !");
    auto result = StringAPI<TypeParam>::replace(input, TestFixture::lit("World"), TestFixture::lit(""));
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, EqualsOrdinal_CaseSensitive_False)
{
    auto input1 = TestFixture::lit("Hello");
    auto input2 = TestFixture::lit("hello");
    EXPECT_FALSE(StringAPI<TypeParam>::equals(input1, input2, swe::string_compare_type::ordinal));
}

// let's write split tests for the following cases:

TYPED_TEST(StringTest, Split_Normal_None)
{
    auto input = TestFixture::lit("Hello,World!");
    auto expected = typename TestFixture::VectorType{TestFixture::lit("Hello"), TestFixture::lit("World!")};
    auto result = StringAPI<TypeParam>::split(input, ',', swe::string_split_options::none);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Split_Normal_RemoveEmptyEntries)
{
    auto input = TestFixture::lit("Hello,,World!");
    auto expected = typename TestFixture::VectorType{TestFixture::lit("Hello"), TestFixture::lit("World!")};
    auto result = StringAPI<TypeParam>::split(input, ',', swe::string_split_options::remove_empty_entries);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Split_Normal_TrimLeft)
{
    auto input = TestFixture::lit("  Hello,  World!");
    auto expected = typename TestFixture::VectorType{TestFixture::lit("Hello"), TestFixture::lit("World!")};
    auto result = StringAPI<TypeParam>::split(input, ',', swe::string_split_options::trim_left);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Split_Normal_TrimRight)
{
    auto input = TestFixture::lit("Hello,World!  ");
    auto expected = typename TestFixture::VectorType{TestFixture::lit("Hello"), TestFixture::lit("World!")};
    auto result = StringAPI<TypeParam>::split(input, ',', swe::string_split_options::trim_right);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Split_Normal_Trim)
{
    auto input = TestFixture::lit("  Hello,  World!  ");
    auto expected = typename TestFixture::VectorType{TestFixture::lit("Hello"), TestFixture::lit("World!")};
    auto result = StringAPI<TypeParam>::split(input, ',', swe::string_split_options::trim);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Split_EmptyString)
{
    auto input = TestFixture::lit("");
    auto expected = typename TestFixture::VectorType{};
    auto result = StringAPI<TypeParam>::split(input, ',', swe::string_split_options::none);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Split_DelimiterOnly_None)
{
    auto input = TestFixture::lit(",");
    auto expected = typename TestFixture::VectorType{TestFixture::lit(""), TestFixture::lit("")};
    auto result = StringAPI<TypeParam>::split(input, ',', swe::string_split_options::none);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Split_DelimiterOnly_RemoveEmptyEntries)
{
    auto input = TestFixture::lit(",");
    auto expected = typename TestFixture::VectorType{};
    auto result = StringAPI<TypeParam>::split(input, ',', swe::string_split_options::remove_empty_entries);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Split_NoDelimiter_None)
{
    auto input = TestFixture::lit("Hello World!");
    auto expected = typename TestFixture::VectorType{TestFixture::lit("Hello World!")};
    auto result = StringAPI<TypeParam>::split(input, ',', swe::string_split_options::none);
    EXPECT_EQ(result, expected);
}

// nothing else to test for No Delimiter, because the string is not split

TYPED_TEST(StringTest, Split_LeadingDelimiter_None)
{
    auto input = TestFixture::lit(",Hello World!");
    auto expected = typename TestFixture::VectorType{TestFixture::lit(""), TestFixture::lit("Hello World!")};
    auto result = StringAPI<TypeParam>::split(input, ',', swe::string_split_options::none);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Split_TrailingDelimiter_None)
{
    auto input = TestFixture::lit("Hello World!,");
    auto expected = typename TestFixture::VectorType{TestFixture::lit("Hello World!"), TestFixture::lit("")};
    auto result = StringAPI<TypeParam>::split(input, ',', swe::string_split_options::none);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Split_LeadingAndTrailingDelimiter_None)
{
    auto input = TestFixture::lit(",Hello World!,");
    auto expected = typename TestFixture::VectorType{TestFixture::lit(""), TestFixture::lit("Hello World!"), TestFixture::lit("")};
    auto result = StringAPI<TypeParam>::split(input, ',', swe::string_split_options::none);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, Split_ConsecutiveDelimiters_None)
{
    auto input = TestFixture::lit("Hello,,World!");
    auto expected = typename TestFixture::VectorType{TestFixture::lit("Hello"), TestFixture::lit(""), TestFixture::lit("World!")};
    auto result = StringAPI<TypeParam>::split(input, ',', swe::string_split_options::none);
    EXPECT_EQ(result, expected);
}

TYPED_TEST(StringTest, ObfuscateTest)
{
    auto input = TestFixture::lit("Hello World!");
    auto key = TestFixture::lit("key");
    auto obfuscated = StringAPI<TypeParam>::obfuscate(input, key);

    EXPECT_NE(obfuscated, input);

    // the 'deobfuscate' function itself is a 'conventiently named reversal function'
    // internally is just calls obfuscate with the same key
    auto deobfuscated = StringAPI<TypeParam>::obfuscate(obfuscated, key);
    EXPECT_EQ(deobfuscated, input);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}