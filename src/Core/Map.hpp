#pragma once

#include "Map/Tile.hpp"

#include <Utils/Vector2.hpp>
#include <vector>

namespace sw::core
{
	class Map
	{
	public:
		Map(core::Arena& arena);

		void Generate(utils::Vector2i size);

		map::Tile* GetTile(utils::Vector2i position);

		Arena& Arena();

	private:
		bool _generated = false;

		std::vector<std::vector<map::Tile>> _tiles;
		utils::Vector2i _size;
		core::Arena& _arena;
	};
}  // namespace sw::core
