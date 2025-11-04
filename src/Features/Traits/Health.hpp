#pragma once

#include <Core/Arena.hpp>
#include <Core/Exceptions.hpp>
#include <Core/Map/Tile.hpp>
#include <Core/Unit.hpp>
#include <Core/Unit/UnitTrait.hpp>
#include <IO/Events/UnitAttacked.hpp>

namespace sw::features::traits
{
	struct InvalidHealthValueError : public core::exceptions::BadScenarioError
	{
		using core::exceptions::BadScenarioError::BadScenarioError;
	};

	class Health : public sw::core::unit::UnitTrait
	{
	public:
		Health(sw::core::Unit& unit, int maxHealth) :
				_unit(unit),
				_maxHealth(maxHealth),
				_currentHealth(maxHealth)
		{
			if (maxHealth <= 0)
			{
				throw InvalidHealthValueError("Max health must be greater than 0: {}", maxHealth);
			}
		}

		void ApplyChange(core::Unit& actor, int change)
		{
			_currentHealth += change;
			if (_currentHealth <= 0)
			{
				_currentHealth = 0;
				_unit.Destroy();
			}
			else if (_currentHealth > _maxHealth)
			{
				_currentHealth = _maxHealth;
			}

			if (change < 0)
			{
				_unit.Tile().Arena().LogEvent(
					io::UnitAttacked{
						actor.Id(),
						_unit.Id(),
						static_cast<uint32_t>(std::abs(change)),
						static_cast<uint32_t>(_currentHealth)});
			}
		}

	private:
		sw::core::Unit& _unit;
		int _maxHealth{};
		int _currentHealth{};
	};
}  // namespace sw::features::traits
