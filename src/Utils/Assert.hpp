#pragma once

namespace sw::utils
{

#if defined(__clang__) || defined(__GNUC__)
	#define GSL_LIKELY(x) __builtin_expect(!!(x), 1)
	#define GSL_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
	#define GSL_LIKELY(x) (!!(x))
	#define GSL_UNLIKELY(x) (!!(x))
#endif	// defined(__clang__) || defined(__GNUC__)

#define CONTRACT_CHECK(type, cond) (GSL_LIKELY(cond) ? static_cast<void>(0) : std::terminate())

#define Expects(cond) CONTRACT_CHECK("Precondition", cond)
#define Ensures(cond) CONTRACT_CHECK("Postcondition", cond)

}  // namespace sw::utils
