#pragma once

#include <Core/Arena.hpp>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/System/CommandParser.hpp>

namespace sw::features
{

	io::CommandParser RegisterCommands(core::Arena& arena);

}  // namespace sw::features
