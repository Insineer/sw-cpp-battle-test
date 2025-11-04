#include "RegisterCommands.hpp"

#include <Core/Exceptions.hpp>
#include <Features/Units/Hunter.hpp>
#include <Features/Units/Swordsman.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/System/PrintDebug.hpp>

namespace sw::features
{

	namespace
	{

		void CreateMap(core::Arena& arena, io::CreateMap command)
		{
			arena.CreateMap(utils::Vector2i{static_cast<int>(command.width), static_cast<int>(command.height)});
		}

		void SpawnSwordsman(core::Arena& arena, io::SpawnSwordsman command)
		{
			arena.AddUnit(std::make_shared<units::Swordsman>(arena.Map(), command));
		}

		void SpawnHunter(core::Arena& arena, io::SpawnHunter command)
		{
			arena.AddUnit(std::make_shared<units::Hunter>(arena.Map(), command));
		}

		void March(core::Arena& arena, io::March command)
		{
			auto unit = arena.GetUnitById(command.unitId);
			if (!unit)
			{
				throw core::exceptions::UnknownUnitError("Unit with id {} not found", command.unitId);
			}
			auto target_position
				= utils::Vector2i{static_cast<int>(command.targetX), static_cast<int>(command.targetY)};
			auto target_tile = arena.Map().GetTile(target_position);
			if (!target_tile)
			{
				throw core::exceptions::BadPositionError("Bad position: {}x{}", command.targetX, command.targetY);
			}
			unit->Trait<traits::Mobility>()->SetTarget(target_tile);
			arena.LogEvent(
				io::MarchStarted{
					unit->Id(),
					static_cast<uint32_t>(unit->Tile().Position().x),
					static_cast<uint32_t>(unit->Tile().Position().y),
					command.targetX,
					command.targetY});
		}
	}

	io::CommandParser RegisterCommands(core::Arena& arena)
	{
		io::CommandParser parser;
		parser.add<io::CreateMap>([&arena](auto command) { CreateMap(arena, command); })
			.add<io::SpawnSwordsman>([&arena](auto command) { SpawnSwordsman(arena, command); })
			.add<io::SpawnHunter>([&arena](auto command) { SpawnHunter(arena, command); })
			.add<io::March>([&arena](auto command) { March(arena, command); });
		return parser;
	}
}  // namespace sw::features
