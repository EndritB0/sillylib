#include "pch.h"
#include "sillylib/assert.h"

namespace silly {

	void ReportAssertFailure(const char* expression, const char* message, const char* file, int line) noexcept
	{
		std::fprintf(stderr, "SILLY_ASSERT failed: %s\n  message: %s\n  at %s(%d)\n", expression, message, file, line);
		std::fflush(stderr);
		std::abort();
	}

}