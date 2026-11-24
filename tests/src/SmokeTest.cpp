#include "pch.h"

static_assert(_MSVC_LANG >= 202002L, "sillylib tests must be compiled as C++20 or later");

TEST(Smoke, GoogleTestRuns)
{
	EXPECT_EQ(1 + 1, 2);
}
