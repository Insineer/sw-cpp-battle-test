#include "Tile.hpp"

#include <Core/Map.hpp>

namespace sw::core::map
{
	Tile::Tile(utils::Vector2i position, core::Map& map) :
			_map(map),
			_position(position)
	{}

	void Tile::AddUnit(Unit& unit)
	{
		_units.push_back(&unit);
	}

	void Tile::RemoveUnit(Unit& unit)
	{
		_units.erase(std::remove(_units.begin(), _units.end(), &unit), _units.end());
	}

	const std::vector<utils::NotNull<Unit*>>& Tile::Units() const
	{
		return _units;
	}

	std::vector<utils::NotNull<Unit*>> Tile::GatherUnitsInRing(const Ring& ring) const
	{
		std::vector<utils::NotNull<Unit*>> units;
		for (int dx = -ring.toRadius; dx <= ring.toRadius; dx++)
		{
			for (int dy = -ring.toRadius; dy <= ring.toRadius; dy++)
			{
				int distance = std::max(std::abs(dx), std::abs(dy));
				if (distance < ring.fromRadius || distance > ring.toRadius)
				{
					continue;
				}
				utils::Vector2i position = _position + utils::Vector2i{dx, dy};
				const Tile* tile = _map.GetTile(position);
				if (tile)
				{
					units.insert(units.end(), tile->Units().begin(), tile->Units().end());
				}
			}
		}
		return units;
	}

	utils::Vector2i Tile::Position() const
	{
		return _position;
	}

	Map& Tile::Map()
	{
		return _map;
	}

	Arena& Tile::Arena()
	{
		return _map.Arena();
	}
}  // namespace sw::core::map
