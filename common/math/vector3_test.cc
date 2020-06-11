#include "gtest/gtest.h"
#include "vector3.hh"

TEST(Vector3Test, MultiplyFloat) {
    Common::Math::Vector3 test(3, 4, 5);
    Common::Math::Vector3 foo = test * 5.0f;
    EXPECT_EQ(foo.x, 15);
    EXPECT_EQ(foo.y, 20);
    EXPECT_EQ(foo.z, 25);
}