#pragma once

#include <Core/Unit.hpp>
#include <Features/Traits/Attacks/MeleeAttack.hpp>
#include <Features/Traits/Density.hpp>
#include <Features/Traits/Health.hpp>
#include <Features/Traits/Mobility.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>

namespace sw::features::units
{
	class Swordsman : public sw::core::Unit
	{
	public:
		Swordsman(sw::core::Map& map, sw::io::SpawnSwordsman command) :
				sw::core::Unit(
					command.unitId, map, utils::Vector2i{static_cast<int>(command.x), static_cast<int>(command.y)})
		{
			constexpr int speed = 1;

			AddTrait(std::make_shared<traits::Density>(*this));
			AddTrait(std::make_shared<traits::Health>(*this, command.hp));
			AddTrait(std::make_shared<traits::MeleeAttack>(*this, command.strength));
			AddTrait(std::make_shared<traits::Mobility>(*this, speed));
		}

		std::string_view Type() const override
		{
			return "Swordsman";
		}
	};
}  // namespace sw::features::units
