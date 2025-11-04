#pragma once

#include <Core/Unit.hpp>
#include <Core/Unit/UnitTrait.hpp>

namespace sw::features::traits
{
	class Density : public core::unit::UnitTrait
	{
	public:
		Density(core::Unit& unit) :
				_unit(unit)
		{}

		bool CheckCollision([[maybe_unused]] core::Unit& unit)
		{
			if (unit.Trait<Density>())
			{
				return true;
			}

			return false;
		}

	private:
		core::Unit& _unit;
	};
}  // namespace sw::features::traits
