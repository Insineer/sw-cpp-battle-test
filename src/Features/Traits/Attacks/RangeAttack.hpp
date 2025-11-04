#pragma once

#include <Core/Map.hpp>
#include <Core/Unit.hpp>
#include <Core/Unit/ActionPoints.hpp>
#include <Core/Unit/UnitTrait.hpp>
#include <Features/Traits/Attacks/Attack.hpp>
#include <Utils/Random.hpp>

namespace sw::features::traits
{
	class RangeAttack : public Attack
	{
	public:
		RangeAttack(core::Unit& unit, int toRadius, int damage) :
				Attack(unit, damage, core::map::Ring{.fromRadius = 2, .toRadius = toRadius})
		{
			if (damage <= 0)
			{
				throw InvalidAttackDamageError("Damage must be greater than 0: {}", damage);
			}
			if (toRadius < 2)
			{
				throw InvalidAttackRadiusError("RangeAttack radius must be greater than 2: {}", toRadius);
			}
		}

		core::unit::ActionPoints Process(uint64_t tick) override
		{
			if (!IsAbleToShoot())
			{
				return core::unit::action_points::Zero;
			}

			return Attack::Process(tick);
		}

	private:
		bool IsAbleToShoot()
		{
			return _unit.Tile().GatherUnitsInRing(core::map::Ring{.fromRadius = 0, .toRadius = 1}).size() == 1;
		}
	};
}  // namespace sw::features::traits
