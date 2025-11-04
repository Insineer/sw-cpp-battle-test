#pragma once

#include <Core/Unit/ActionPoints.hpp>
#include <cstdint>

namespace sw::core::unit
{
	class UnitTrait
	{
	public:
		virtual ~UnitTrait() = default;

		virtual ActionPoints Process(uint64_t tick)
		{
			return action_points::Zero;
		}
	};
}  // namespace sw::core::unit
