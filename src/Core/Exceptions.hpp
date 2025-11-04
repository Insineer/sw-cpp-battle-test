#pragma once

#include <format>
#include <stdexcept>
#include <string_view>

namespace sw::core::exceptions
{
	struct Error : public std::runtime_error
	{
		template <typename... Args>
		Error(std::string_view message, Args&&... args) :
				std::runtime_error(std::vformat(message, std::make_format_args(args...)))
		{}
	};

	struct InputError : public Error
	{
		using Error::Error;
	};

	struct BadScenarioError : public Error
	{
		using Error::Error;
	};

	struct DoubleMapInitializationError : public BadScenarioError
	{
		using BadScenarioError::BadScenarioError;
	};

	struct InvalidMapSizeError : public BadScenarioError
	{
		using BadScenarioError::BadScenarioError;
	};

	struct BadPositionError : public BadScenarioError
	{
		using BadScenarioError::BadScenarioError;
	};

	struct UnknownUnitError : public BadScenarioError
	{
		using BadScenarioError::BadScenarioError;
	};

	struct UnitIdIsUsedError : public BadScenarioError
	{
		using BadScenarioError::BadScenarioError;
	};

	struct InvariantViolationError : public Error
	{
		using Error::Error;
	};
}  // namespace sw::core::exceptions
