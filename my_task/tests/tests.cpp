// my_sin.cpp: определяет точку входа для приложения.
//

#include <gtest/gtest.h>
#include "task.h"
using namespace testspace;
TEST(task_lib_test, Hamming1)
{
    Hamming74 D;
    std::vector<uint8_t> in = { 1, 2, 3, 4};
    std::vector<uint8_t> En = D.Encode(in);
    std::vector<uint8_t> De = D.Decode(En);
    ASSERT_EQ(De, in);
}
TEST(task_lib_test, Hamming2)
{
    Hamming74 D;
    std::vector<uint8_t> in = { 240, 127, 255, 0, 90};
    std::vector<uint8_t> En = D.Encode(in);
    std::vector<uint8_t> De = D.Decode(En);
    ASSERT_EQ(De, in);
}
TEST(task_lib_test, Hamming_with_errors)
{
    Hamming74 D;
    std::vector<uint8_t> in = { 1, 2, 3, 4 };
    std::vector<uint8_t> En = D.Encode(in);
    En[0] += 32;
    En[0] += 128;
    En[2] += 2;
    En[2] += 64;
    En[4] -= 1;
    std::vector<uint8_t> De = D.Decode(En);
    ASSERT_EQ(De, in);
}
TEST(task_lib_test, Diff1)
{
    DiffCode D;
    std::vector<uint8_t> in = { 1, 2, 3, 4 };
    std::vector<uint8_t> En = D.Encode(in);
    std::vector<uint8_t> De = D.Decode(En);
    ASSERT_EQ(De, in);
}
TEST(task_lib_test, Diff2)
{
    DiffCode D;
    std::vector<uint8_t> in = { 244, 43, 2, 54 ,99};
    std::vector<uint8_t> En = D.Encode(in);
    std::vector<uint8_t> De = D.Decode(En);
    ASSERT_EQ(De, in);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}