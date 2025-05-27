#include <gtest/gtest.h>

#include "Vector/Vector.hpp"
#include "Utilities/Utilities.hpp"

TEST(VectorTests, ScalarProductTest1) {
    const lab::Vector a(std::vector{1.0, 2.0, 3.0});
    const lab::Vector b(std::vector{4.0, 6.0, 1.0});

    const double result = a.Dot(b);

    EXPECT_EQ(19, result);
}


TEST(VectorTests, CalcLengthTest1) {
    const lab::Vector vec(std::vector{6.0, 8.0});
    const double result = vec.CalculateLength();

    EXPECT_EQ(result, 10.0);
}

TEST(VectorTests, CalcLengthTest2) {
    const lab::Vector vec(std::vector{ 2.0, 5.0 });
    const double result = vec.CalculateLength();

    EXPECT_EQ(result, 5.0);
}


TEST(VectorTests, ConstrDataTest1) {
    const lab::Vector vec({ 1.0, 2.0, 3.0 });
    EXPECT_EQ(vec.GetDimentionsCount(), 3);

    EXPECT_DOUBLE_EQ(vec[0], 1.0);
    EXPECT_DOUBLE_EQ(vec[1], 2.0);
    EXPECT_DOUBLE_EQ(vec[2], 3.0);
}

TEST(VectorTests, ConstrDataTest2) {
    const lab::Vector vec({ 8.0, 2.0, 4.0 });
    EXPECT_EQ(vec.GetDimentionsCount(), 3);

    EXPECT_DOUBLE_EQ(vec[0], 8.0);
    EXPECT_DOUBLE_EQ(vec[1], 2.0);
    EXPECT_DOUBLE_EQ(vec[2], 3.0);
}


TEST(VectorTests, ConstrSizeTest1) {
    const lab:: Vector vec(4);

    EXPECT_EQ(vec.GetDimentionsCount(), 4);
    for (size_t i = 0; i < 4; ++i)
        EXPECT_DOUBLE_EQ(vec[i], 0.0);
}

TEST(VectorTests, LengthTest1) {
    const lab:: Vector vec({ 3.0, 4.0 });

    EXPECT_DOUBLE_EQ(vec.CalculateLength(), 5.0);
}

TEST(VectorTests, DotProduct1) {
    const lab::Vector a({ 1.0, 2.0, 3.0 });
    const lab::Vector b({ 4.0, -5.0, 6.0 });

    EXPECT_DOUBLE_EQ(a.Dot(b), 12.0);
}

TEST(VectorTests, SumTest1) {
    const lab::Vector a(std::vector{1.0, 2.0, 3.0});
    const lab::Vector b(std::vector{4.0, 5.0, 6.0});

    const lab::Vector result = a.Sum(b);

    EXPECT_EQ(result, std::vector({5.0, 7.0, 9.0}));
}

TEST(VectorTests, DiffTest1) {
    const lab::Vector a(std::vector{1.0, 2.0, 3.0});
    const lab::Vector b(std::vector{4.0, 5.0, 6.0});

    const lab::Vector result = a.Diff(b);

    EXPECT_EQ(result, std::vector({ -3.0, -3.0, -3.0}));
}

TEST(VectorTests, ScalarMultTest1) {
    const lab::Vector a(std::vector{1.0, 2.0, 3.0});

    const lab::Vector result = a * 2.0;

    EXPECT_EQ(result, std::vector({2.0, 4.0, 6.0}));
}

TEST(VectorTests, CrossTest1) {
    const lab::Vector a(std::vector{1.0, 0.0, 0.0});
    const lab::Vector b(std::vector{0.0, 1.0, 0.0});

    const lab::Vector result = a.Cross(b);

    EXPECT_EQ(result, std::vector({0.0, 0.0, 1.0}));
}

TEST(VectorTests, CrossTest2) {
    const lab::Vector a(std::vector{1.0, 2.0, 3.0, 4.0});
    const lab::Vector b(std::vector{4.0, 3.0, 2.0, 1.0});

    EXPECT_THROW(a.Cross(b), std::runtime_error);
}

TEST(VectorTests, NegateTest1) {
    const lab::Vector vec(std::vector{1.0, -2.0, 3.0});

    EXPECT_EQ(-vec, std::vector({-1.0, 2.0, -3.0}));
}

TEST(VectorTests, ColinearTest1) {
    const lab::Vector a(std::vector{1.0, 2.0});
    const lab::Vector b(std::vector{2.0, 4.0});

    EXPECT_TRUE(a.IsColinear(b));
}

TEST(VectorTests, OrthoTest1) {
    const lab::Vector a(std::vector{1.0, 0.0});
    const lab::Vector b(std::vector{0.0, 1.0});

    EXPECT_TRUE(a.IsOrtho(b));
}
