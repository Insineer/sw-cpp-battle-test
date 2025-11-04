#pragma once

#include <Core/Map.hpp>
#include <Core/Unit.hpp>
#include <IO/System/EventLog.hpp>
#include <istream>
#include <vector>

namespace sw::core
{
	class Arena
	{
	public:
		Arena(std::istream& stream);

		void Run();

		void CreateMap(utils::Vector2i size);
		void AddUnit(std::shared_ptr<Unit> unit);

		Unit* GetUnitById(uint32_t id);

		Map& Map();

		template <typename TEvent>
		void LogEvent(TEvent&& event)
		{
			_eventLog.log(_tick, std::move(event));
		}

	private:
		uint64_t _tick = 1;
		core::Map _map;
		sw::EventLog _eventLog;
		std::vector<std::shared_ptr<Unit>> _units;
		std::unordered_map<uint32_t, std::shared_ptr<Unit>> _unitsById;
	};

}  // namespace sw::core
