#pragma once

#include <Core/Unit.hpp>
#include <Utils/NotNull.hpp>
#include <Utils/Vector2.hpp>
#include <vector>

namespace sw::core
{
	class Arena;
	class Map;
}

namespace sw::core::map
{
	struct Ring
	{
		int fromRadius{};
		int toRadius{};

		bool IsValid() const
		{
			return fromRadius >= 0 && toRadius >= 0 && fromRadius <= toRadius;
		}

		std::string ToString() const
		{
			return std::format("Ring(fromRadius={}, toRadius={})", fromRadius, toRadius);
		}
	};

	class Tile
	{
	public:
		Tile(utils::Vector2i position, Map& map);

		void AddUnit(Unit& unit);
		void RemoveUnit(Unit& unit);

		const std::vector<utils::NotNull<Unit*>>& Units() const;
		std::vector<utils::NotNull<Unit*>> GatherUnitsInRing(const Ring& ring) const;

		utils::Vector2i Position() const;

		Map& Map();
		Arena& Arena();

	private:
		const utils::Vector2i _position;
		std::vector<utils::NotNull<Unit*>> _units;
		core::Map& _map;
	};
}  // namespace sw::core::map
