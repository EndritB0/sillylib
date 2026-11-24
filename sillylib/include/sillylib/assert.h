#pragma once 

namespace silly {

	[[noreturn]] void ReportAssertFailure(const char* expression, const char* message, const char* file, int line) noexcept;

}

#ifdef NDEBUG

#define SILLY_ASSERT(expr, msg) ((void)0)

#else 

#define SILLY_ASSERT(expr, msg) ((expr) ? ((void)0) : ::silly::ReportAssertFailure(#expr, msg, __FILE__, __LINE__))

#endif