#pragma once

#include <Core/Map.hpp>
#include <Core/Unit.hpp>
#include <Core/Unit/ActionPoints.hpp>
#include <Core/Unit/UnitTrait.hpp>
#include <Features/Traits/Attacks/Attack.hpp>
#include <Utils/Random.hpp>

namespace sw::features::traits
{
	class MeleeAttack : public Attack
	{
	public:
		MeleeAttack(core::Unit& unit, int damage) :
				Attack(unit, damage, core::map::Ring{.fromRadius = 0, .toRadius = 1})
		{
			if (damage <= 0)
			{
				throw InvalidAttackDamageError("Damage must be greater than 0: {}", damage);
			}
		}
	};
}  // namespace sw::features::traits
