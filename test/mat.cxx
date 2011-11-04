#include <mat.hxx>

#include <gtest/gtest.h>


using namespace cheeze;

mat2 const A(vec2(5, 6), vec2(7, 8));
mat2 const B(vec2(1, 2), vec2(3, 4));

TEST(mat, plus) {
    ASSERT_EQ(A + B, mat2(vec2(6, 8), vec2(10, 12)));
}
TEST(mat, minus) {
    ASSERT_EQ(A - B, mat2(vec2(4, 4), vec2(4, 4)));
}
TEST(mat, multiply) {
    ASSERT_EQ(mat2(vec2(23, 34), vec2(31, 46)), A * B);
    ASSERT_EQ(mat2(vec2(19, 22), vec2(43, 50)), B * A);
}
