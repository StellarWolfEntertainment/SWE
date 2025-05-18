#include "../include/swe/ci_map.hpp"
#include <gtest/gtest.h>

TEST(CIHashTest, HashesCaseInsensitive)
{
    swe::ci_hash hash_fn;
    std::string a = "Hello";
    std::string b = "hello";
    EXPECT_EQ(hash_fn(a), hash_fn(b));
}

TEST(CIWHashTest, WHashesCaseInsensitive)
{
    swe::wci_hash hash_fn;
    std::wstring a = L"Hello";
    std::wstring b = L"hello";
    EXPECT_EQ(hash_fn(a), hash_fn(b));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}