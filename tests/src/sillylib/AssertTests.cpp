#include "pch.h"

#include <sillylib/Assert.h>

TEST(Assert, PassingAssertDoesNotAbort)
{
	int value = 42;
	SILLY_ASSERT(value == 42, "value should be 42");
	EXPECT_EQ(value, 42);
}

#ifndef NDEBUG

TEST(Assert, EvaluatesExpressionExactlyOnceInDebug)
{
	int evaluations = 0;
	SILLY_ASSERT(++evaluations == 1, "the expression is evaluated once");
	EXPECT_EQ(evaluations, 1);
}

TEST(Assert, FailingAssertCallsAbortInDebug)
{
	int answer = 42;
	EXPECT_EXIT(SILLY_ASSERT(answer == 41, "the answer should be 41"), ::testing::ExitedWithCode(3), "");
}

TEST(Assert, FailureReportContainsMessage)
{
	int answer = 42;
	EXPECT_DEATH(SILLY_ASSERT(answer == 41, "the answer should be 41"), "the answer should be 41");
}

TEST(Assert, FailureReportContainsExpressionText)
{
	int answer = 42;
	EXPECT_DEATH(SILLY_ASSERT(answer == 41, "wrong answer"), "answer == 41");
}

TEST(Assert, FailureReportContainsFileAndLine)
{
	int answer = 42;
	const std::string fileAndLine = "AssertTests\\.cpp\\(" + std::to_string(__LINE__ + 1) + "\\)";
	EXPECT_DEATH(SILLY_ASSERT(answer == 41, "wrong answer"), fileAndLine);
}

#endif // !NDEBUG

namespace {
	class PositiveNumber {
	public:
		explicit PositiveNumber(int value)
			: m_value((SILLY_ASSERT(value > 0, "PositiveNumber needs a positive value"), value))
		{
		}

		int Get() const { return m_value; }

	private:
		int m_value;
	};

	constexpr int HalfOfEven(int value)
	{
		SILLY_ASSERT(value % 2 == 0, "HalfOfEven needs an even value");
		return value / 2;
	}
}

TEST(Assert, IsAVoidExpression)
{
	static_assert(std::is_void_v<decltype(SILLY_ASSERT(true, "an expression of type void"))>);
}

TEST(Assert, IsNoexcept)
{
	static_assert(noexcept(SILLY_ASSERT(true, "never throws")));
}

TEST(Assert, WorksAsTheBodyOfAnUnbracedIf)
{
	bool takeIfBranch = false;
	bool elseBranchRan = false;
	if (takeIfBranch)
		SILLY_ASSERT(takeIfBranch, "only reached when the if branch is taken");
	else
		elseBranchRan = true;
	EXPECT_TRUE(elseBranchRan);
}

TEST(Assert, WorksInAMemberInitializerList)
{
	PositiveNumber number(5);
	EXPECT_EQ(number.Get(), 5);
}

TEST(Assert, WorksInAConstexprFunction)
{
	static_assert(HalfOfEven(8) == 4);
	EXPECT_EQ(HalfOfEven(6), 3);
}

#ifndef NDEBUG

TEST(Assert, FailingAssertInAMemberInitializerListDiesInDebug)
{
	EXPECT_DEATH(PositiveNumber(-1).Get(), "PositiveNumber needs a positive value");
}

TEST(Assert, FailingAssertInAConstexprFunctionDiesAtRunTimeInDebug)
{
	int odd = 7;
	EXPECT_DEATH(HalfOfEven(odd), "HalfOfEven needs an even value");
}

TEST(Assert, ChecksLowPrecedenceExpressionsAsAWhole)
{
	int value = 2;
	SILLY_ASSERT(value == 1 || value == 2, "value is 1 or 2");

	bool useFirst = false;
	int first = -1;
	int second = 1;
	SILLY_ASSERT(useFirst ? first > 0 : second > 0, "the chosen value is positive");

	SUCCEED();
}

TEST(Assert, FailingLowPrecedenceExpressionDiesInDebug)
{
	int value = 2;
	EXPECT_DEATH(SILLY_ASSERT(value == 3 || value == 4, "value is 3 or 4"), "value is 3 or 4");
}

#endif // !NDEBUG

#ifdef NDEBUG

TEST(Assert, DoesNotEvaluateExpressionInRelease)
{
	int evaluations = 0;
	SILLY_ASSERT(++evaluations == 1, "never evaluated in Release");
	EXPECT_EQ(evaluations, 0);
}

TEST(Assert, FailingAssertDoesNothingInRelease)
{
	EXPECT_EXIT({ SILLY_ASSERT(false, "ignored in Release"); std::exit(0); }, ::testing::ExitedWithCode(0), "");
}

#endif // NDEBUG
