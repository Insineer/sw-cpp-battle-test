#include <Core/Arena.hpp>
#include <Core/Exceptions.hpp>
#include <Core/Map.hpp>
#include <Core/Map/Tile.hpp>
#include <Core/Unit.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>

namespace sw::core
{

	namespace
	{

		map::Tile* GetTile(Map& map, utils::Vector2i position)
		{
			auto tile = map.GetTile(position);
			if (!tile)
			{
				throw exceptions::BadPositionError(
					"Failed to create Unit: bad position ({}x{})", position.x, position.y);
			}
			return tile;
		}
	}

	Unit::Unit(uint32_t id, Map& map, utils::Vector2i position) :
			_id(id),
			_tile(GetTile(map, position))
	{
		_tile->AddUnit(*this);
	}

	unit::ActionPoints Unit::Process(uint64_t tick)
	{
		unit::ActionPoints actionPoints = unit::action_points::Zero;
		for (auto& trait : _traits)
		{
			actionPoints = trait->Process(tick);
			if (actionPoints != unit::action_points::Zero)
			{
				return actionPoints;
			}
		}
		return actionPoints;
	}

	void Unit::MoveTo(map::Tile& tile)
	{
		_tile->RemoveUnit(*this);
		_tile = &tile;
		_tile->AddUnit(*this);
		_tile->Map().Arena().LogEvent(
			io::UnitMoved{Id(), static_cast<uint32_t>(tile.Position().x), static_cast<uint32_t>(tile.Position().y)});
	}

	void Unit::Destroy()
	{
		_is_destroyed = true;
	}

	bool Unit::IsDestroyed() const
	{
		return _is_destroyed;
	}

	uint32_t Unit::Id() const
	{
		return _id;
	}

	map::Tile& Unit::Tile()
	{
		return *_tile;
	}
}  // namespace sw::core
