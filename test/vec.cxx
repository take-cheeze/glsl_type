#include <vec.hxx>

#include <gtest/gtest.h>


TEST(vec, plus) {
  cheeze::vec4 const v(1.0f, 2.0f, 0.5f, 1.0f);
  cheeze::vec4 v1 = v + 1.2f;
}
TEST(vec, multiply) {
  cheeze::vec4 m;
  m *= m;
}
TEST(vec, other_type) {
  cheeze::vec4 m;
  cheeze::dvec4 n;
  n += m;
}
