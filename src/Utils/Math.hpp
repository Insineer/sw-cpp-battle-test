#pragma once

namespace sw::utils
{
	template <typename T>
	T Sign(T value)
	{
		return value > 0 ? 1 : value < 0 ? -1 : 0;
	}
}  // namespace sw::utils
