#pragma once

#include <random>

namespace sw::utils
{
	template <class T>
	std::vector<T>::iterator PickRandom(std::vector<T>& container)
	{
		if (container.empty())
		{
			return container.end();
		}
		thread_local std::mt19937_64 rng{std::random_device{}()};
		std::uniform_int_distribution<std::size_t> dist(0, container.size() - 1);
		return container.begin() + dist(rng);
	}
}  // namespace sw::utils
