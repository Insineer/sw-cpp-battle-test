#include "Arena.hpp"

#include <Core/Exceptions.hpp>
#include <Features/RegisterCommands.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>

namespace sw::core
{
	Arena::Arena(std::istream& scenario) :
			_map(*this)
	{
		auto commandParser = features::RegisterCommands(*this);
		commandParser.parse(scenario);
	}

	void Arena::Run()
	{
		unit::ActionPoints actionPoints{};
		do
		{
			_tick++;
			actionPoints = unit::action_points::Zero;
			for (auto& unit : _units)
			{
				actionPoints += unit->Process(_tick);
			}

			for (auto iter = _units.begin(); iter != _units.end();)
			{
				if ((*iter)->IsDestroyed())
				{
					LogEvent(io::UnitDied{(*iter)->Id()});
					iter = _units.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}
		while (actionPoints != unit::action_points::Zero && _units.size() > 1);
	}

	void Arena::CreateMap(utils::Vector2i size)
	{
		_map.Generate(size);
		_eventLog.log(_tick, io::MapCreated{static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y)});
	}

	void Arena::AddUnit(std::shared_ptr<Unit> unit)
	{
		if (_unitsById.find(unit->Id()) != _unitsById.end())
		{
			throw exceptions::UnitIdIsUsedError("Unit's ID is already used: {}", unit->Id());
		}

		auto event = io::UnitSpawned{
			unit->Id(),
			std::string(unit->Type()),
			static_cast<uint32_t>(unit->Tile().Position().x),
			static_cast<uint32_t>(unit->Tile().Position().y)};
		_units.push_back(unit);
		_unitsById[unit->Id()] = std::move(unit);
		LogEvent(std::move(event));
	}

	Unit* Arena::GetUnitById(uint32_t id)
	{
		auto iter = _unitsById.find(id);
		if (iter == _unitsById.end())
		{
			return nullptr;
		}
		return iter->second.get();
	}

	Map& Arena::Map()
	{
		return _map;
	}

}  // namespace sw::core
