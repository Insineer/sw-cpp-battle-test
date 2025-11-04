#include <Core/Arena.hpp>
#include <Core/Exceptions.hpp>
#include <fstream>
#include <iostream>

namespace
{
	std::ifstream OpenScenario(int argc, char** argv)
	{
		if (argc != 2)
		{
			throw sw::core::exceptions::InputError{"No file specified in command line argument"};
		}

		std::ifstream scenario(argv[1]);
		if (!scenario)
		{
			throw sw::core::exceptions::InputError{"File not found: '{}'", std::string(argv[1])};
		}

		return scenario;
	}
}

int main(int argc, char** argv)
try
{
	auto scenario_file = OpenScenario(argc, argv);

	sw::core::Arena arena(scenario_file);
	arena.Run();

	return 0;
}
catch (const sw::core::exceptions::InputError& e)
{
	std::cerr << "Input error: " << e.what() << std::endl;
	return 1;
}
catch (const sw::core::exceptions::BadScenarioError& e)
{
	std::cerr << "Bad scenario: " << e.what() << std::endl;
	return 1;
}
catch (const std::exception& e)
{
	std::cerr << "Unexpected application error: " << e.what() << std::endl;
	return 1;
}
