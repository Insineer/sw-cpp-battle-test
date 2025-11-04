#pragma once

#include "Core/Unit/ActionPoints.hpp"
#include "Features/Traits/Density.hpp"

#include <Core/Arena.hpp>
#include <Core/Exceptions.hpp>
#include <Core/Map.hpp>
#include <Core/Map/Tile.hpp>
#include <Core/Unit.hpp>
#include <Core/Unit/UnitTrait.hpp>
#include <IO/Events/MarchEnded.hpp>

namespace sw::features::traits
{
	struct InvalidSpeedValueError : public core::exceptions::BadScenarioError
	{
		using core::exceptions::BadScenarioError::BadScenarioError;
	};

	class Mobility : public core::unit::UnitTrait
	{
	public:
		Mobility(core::Unit& unit, int speed) :
				_unit(unit),
				_speed(speed)
		{
			if (speed <= 0)
			{
				throw InvalidSpeedValueError("Speed must be greater than 0: {}", speed);
			}
		}

		void SetTarget(core::map::Tile* target)
		{
			_target = target;
		}

		core::unit::ActionPoints Process(uint64_t tick) override
		{
			if (!_target)
			{
				return core::unit::action_points::Zero;
			}

			int steps = _speed;
			while (steps > 0)
			{
				if (&_unit.Tile() == _target)
				{
					break;
				}

				utils::Vector2i direction = (_target->Position() - _unit.Tile().Position()).Sign();
				auto stepTargetTile = _unit.Tile().Map().GetTile(_unit.Tile().Position() + direction);

				for (auto unit : stepTargetTile->Units())
				{
					auto density = unit->Trait<Density>();
					if (density && density->CheckCollision(_unit))
					{
						return core::unit::action_points::Zero;
					}
				}

				_unit.MoveTo(*stepTargetTile);
				if (&_unit.Tile() == _target)
				{
					_target = nullptr;
					_unit.Tile().Arena().LogEvent(
						io::MarchEnded{
							_unit.Id(),
							static_cast<uint32_t>(_unit.Tile().Position().x),
							static_cast<uint32_t>(_unit.Tile().Position().y)});
				}
				steps--;
			}

			return steps != _speed ? core::unit::action_points::One : core::unit::action_points::Zero;
		}

	private:
		core::Unit& _unit;
		int _speed;
		core::map::Tile* _target{};
	};
}  // namespace sw::features::traits
