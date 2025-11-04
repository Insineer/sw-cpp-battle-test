#pragma once

#include "Unit/UnitTrait.hpp"

#include <Core/Unit/ActionPoints.hpp>
#include <IO/System/TypeRegistry.hpp>
#include <Utils/NotNull.hpp>
#include <Utils/Vector2.hpp>

namespace sw::core
{
	namespace map
	{
		class Tile;
	}

	class Map;

	class Unit
	{
	public:
		Unit(uint32_t id, Map& map, utils::Vector2i position);
		virtual ~Unit() = default;

		virtual unit::ActionPoints Process(uint64_t tick);

		virtual void MoveTo(map::Tile& tile);
		virtual void Destroy();

		bool IsDestroyed() const;

		template <typename TTrait>
		void AddTrait(std::shared_ptr<TTrait> trait)
		{
			static_assert(std::is_base_of_v<unit::UnitTrait, TTrait>, "Trait must derive from UnitTrait");
			_traits.push_back(trait);
			_traits_by_type.add<TTrait>(std::move(trait));
		}

		template <typename T>
		std::shared_ptr<T> Trait()
		{
			return _traits_by_type.get<T>();
		}

		uint32_t Id() const;
		map::Tile& Tile();

		virtual std::string_view Type() const = 0;

	private:
		uint32_t _id{};
		utils::NotNull<map::Tile*> _tile;
		std::vector<std::shared_ptr<unit::UnitTrait>> _traits;
		TypeRegistry _traits_by_type;

		bool _is_destroyed{};
	};
}
