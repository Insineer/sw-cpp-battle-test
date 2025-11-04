#pragma once

#include <Core/Unit.hpp>
#include <Features/Traits/Attacks/MeleeAttack.hpp>
#include <Features/Traits/Attacks/RangeAttack.hpp>
#include <Features/Traits/Density.hpp>
#include <Features/Traits/Health.hpp>
#include <Features/Traits/Mobility.hpp>
#include <IO/Commands/SpawnHunter.hpp>

namespace sw::features::units
{
	class Hunter : public sw::core::Unit
	{
	public:
		Hunter(sw::core::Map& map, sw::io::SpawnHunter command) :
				sw::core::Unit(
					command.unitId, map, utils::Vector2i{static_cast<int>(command.x), static_cast<int>(command.y)})
		{
			constexpr int speed = 1;

			AddTrait(std::make_shared<traits::Density>(*this));
			AddTrait(std::make_shared<traits::Health>(*this, command.hp));
			AddTrait(std::make_shared<traits::RangeAttack>(*this, command.range, command.agility));
			AddTrait(std::make_shared<traits::MeleeAttack>(*this, command.strength));
			AddTrait(std::make_shared<traits::Mobility>(*this, speed));
		}

		std::string_view Type() const override
		{
			return "Hunter";
		}
	};
}  // namespace sw::features::units
