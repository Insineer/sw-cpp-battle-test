#include "Map.hpp"

#include <Core/Exceptions.hpp>

namespace sw::core
{
	Map::Map(core::Arena& arena) :
			_arena(arena)
	{}

	void Map::Generate(utils::Vector2i size)
	{
		if (_generated)
		{
			throw exceptions::DoubleMapInitializationError{"Map can't be created twice"};
		}

		if (size.x <= 0 || size.y <= 0)
		{
			throw exceptions::InvalidMapSizeError{
				"Invalid map size: {}x{}, only positive values are allowed", size.x, size.y};
		}

		_size = size;
		_generated = true;

		_tiles.reserve(size.x);
		for (int x = 0; x < size.x; x++)
		{
			_tiles.push_back(std::vector<map::Tile>());
			_tiles.back().reserve(size.y);
			for (int y = 0; y < size.y; y++)
			{
				_tiles.back().push_back(map::Tile(utils::Vector2i{x, y}, *this));
			}
		}
	}

	map::Tile* Map::GetTile(utils::Vector2i position)
	{
		if (!(position >= utils::Vector2i{0, 0} && position < _size))
		{
			return nullptr;
		}
		return &_tiles[position.x][position.y];
	}

	Arena& Map::Arena()
	{
		return _arena;
	}
}  // namespace sw::core
