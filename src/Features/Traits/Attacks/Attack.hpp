#pragma once

#include <Core/Map.hpp>
#include <Core/Unit.hpp>
#include <Core/Unit/ActionPoints.hpp>
#include <Core/Unit/UnitTrait.hpp>
#include <Features/Traits/Health.hpp>
#include <Utils/Random.hpp>

namespace sw::features::traits
{
	struct InvalidAttackDamageError : public core::exceptions::BadScenarioError
	{
		using core::exceptions::BadScenarioError::BadScenarioError;
	};

	struct InvalidAttackRadiusError : public core::exceptions::BadScenarioError
	{
		using core::exceptions::BadScenarioError::BadScenarioError;
	};

	class Attack : public core::unit::UnitTrait
	{
	public:
		Attack(core::Unit& unit, int damage, core::map::Ring attackRing) :
				_unit(unit),
				_damage(damage),
				_attackRing(attackRing)
		{}

		core::unit::ActionPoints Process(uint64_t tick) override
		{
			std::vector<utils::NotNull<core::Unit*>> units = _unit.Tile().GatherUnitsInRing(_attackRing);
			units.erase(std::remove(units.begin(), units.end(), &_unit), units.end());
			auto iter = utils::PickRandom(units);
			if (iter != units.end())
			{
				(*iter)->Trait<traits::Health>()->ApplyChange(_unit, -_damage);
				return core::unit::action_points::One;
			}
			return core::unit::action_points::Zero;
		}

	protected:
		core::Unit& _unit;

	private:
		int _damage{};
		const core::map::Ring _attackRing;
	};
}  // namespace sw::features::traits
