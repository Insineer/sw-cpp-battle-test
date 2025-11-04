#pragma once

#include <Utils/Assert.hpp>
#include <functional>
#include <type_traits>
#include <utility>

namespace sw::utils
{

	namespace details
	{
		template <typename T, typename = void>
		struct is_comparable_to_nullptr : std::false_type
		{};

		template <typename T>
		struct is_comparable_to_nullptr<
			T,
			std::enable_if_t<std::is_convertible<decltype(std::declval<T>() != nullptr), bool>::value>> : std::true_type
		{};

		// Resolves to the more efficient of `const T` or `const T&`, in the context of returning a const-qualified value
		// of type T.
		//
		// Copied from cppfront's implementation of the CppCoreGuidelines F.16 (https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-in)
		template <typename T>
		using value_or_reference_return_t = std::conditional_t<
			sizeof(T) <= 2 * sizeof(void*) && std::is_trivially_copy_constructible<T>::value,
			const T,
			const T&>;

	}  // namespace details

	template <class T>
	class NotNull
	{
	public:
		static_assert(details::is_comparable_to_nullptr<T>::value, "T cannot be compared to nullptr.");

		using element_type = T;

		template <typename U, typename = std::enable_if_t<std::is_convertible<U, T>::value>>
		constexpr NotNull(U&& u) noexcept(std::is_nothrow_move_constructible<T>::value) :
				ptr_(std::forward<U>(u))
		{
			Expects(ptr_ != nullptr);
		}

		template <typename = std::enable_if_t<!std::is_same<std::nullptr_t, T>::value>>
		constexpr NotNull(T u) noexcept(std::is_nothrow_move_constructible<T>::value) :
				ptr_(std::move(u))
		{
			Expects(ptr_ != nullptr);
		}

		template <typename U, typename = std::enable_if_t<std::is_convertible<U, T>::value>>
		constexpr NotNull(const NotNull<U>& other) noexcept(std::is_nothrow_move_constructible<T>::value) :
				NotNull(other.get())
		{}

		NotNull(const NotNull& other) = default;
		NotNull& operator=(const NotNull& other) = default;

		constexpr details::value_or_reference_return_t<T> get() const
			noexcept(noexcept(details::value_or_reference_return_t<T>(std::declval<T&>())))
		{
			return ptr_;
		}

		constexpr operator T() const
		{
			return get();
		}

		constexpr decltype(auto) operator->() const
		{
			return get();
		}

		constexpr decltype(auto) operator*() const
		{
			return *get();
		}

		// prevents compilation when someone attempts to assign a null pointer constant
		NotNull(std::nullptr_t) = delete;
		NotNull& operator=(std::nullptr_t) = delete;

		// unwanted operators...pointers only point to single objects!
		NotNull& operator++() = delete;
		NotNull& operator--() = delete;
		NotNull operator++(int) = delete;
		NotNull operator--(int) = delete;
		NotNull& operator+=(std::ptrdiff_t) = delete;
		NotNull& operator-=(std::ptrdiff_t) = delete;
		void operator[](std::ptrdiff_t) const = delete;

		void swap(NotNull<T>& other)
		{
			std::swap(ptr_, other.ptr_);
		}

	private:
		T ptr_;
	};

	template <
		typename T,
		std::enable_if_t<std::is_move_assignable<T>::value && std::is_move_constructible<T>::value, bool> = true>
	void swap(NotNull<T>& a, NotNull<T>& b)
	{
		a.swap(b);
	}

	template <class T>
	auto make_not_null(T&& t) noexcept
	{
		return NotNull<std::remove_cv_t<std::remove_reference_t<T>>>{std::forward<T>(t)};
	}

#if !defined(GSL_NO_IOSTREAMS)
	template <class T>
	std::ostream& operator<<(std::ostream& os, const NotNull<T>& val)
	{
		os << val.get();
		return os;
	}
#endif	// !defined(GSL_NO_IOSTREAMS)

	template <class T, class U>
	constexpr auto operator==(const NotNull<T>& lhs, const NotNull<U>& rhs) noexcept(noexcept(lhs.get() == rhs.get()))
		-> decltype(lhs.get() == rhs.get())
	{
		return lhs.get() == rhs.get();
	}

	template <class T, class U>
	constexpr auto operator!=(const NotNull<T>& lhs, const NotNull<U>& rhs) noexcept(noexcept(lhs.get() != rhs.get()))
		-> decltype(lhs.get() != rhs.get())
	{
		return lhs.get() != rhs.get();
	}

	template <class T, class U>
	constexpr auto operator<(const NotNull<T>& lhs, const NotNull<U>& rhs) noexcept(
		noexcept(std::less<>{}(lhs.get(), rhs.get()))) -> decltype(std::less<>{}(lhs.get(), rhs.get()))
	{
		return std::less<>{}(lhs.get(), rhs.get());
	}

	template <class T, class U>
	constexpr auto operator<=(const NotNull<T>& lhs, const NotNull<U>& rhs) noexcept(
		noexcept(std::less_equal<>{}(lhs.get(), rhs.get()))) -> decltype(std::less_equal<>{}(lhs.get(), rhs.get()))
	{
		return std::less_equal<>{}(lhs.get(), rhs.get());
	}

	template <class T, class U>
	constexpr auto operator>(const NotNull<T>& lhs, const NotNull<U>& rhs) noexcept(
		noexcept(std::greater<>{}(lhs.get(), rhs.get()))) -> decltype(std::greater<>{}(lhs.get(), rhs.get()))
	{
		return std::greater<>{}(lhs.get(), rhs.get());
	}

	template <class T, class U>
	constexpr auto operator>=(const NotNull<T>& lhs, const NotNull<U>& rhs) noexcept(noexcept(
		std::greater_equal<>{}(lhs.get(), rhs.get()))) -> decltype(std::greater_equal<>{}(lhs.get(), rhs.get()))
	{
		return std::greater_equal<>{}(lhs.get(), rhs.get());
	}

	// more unwanted operators
	template <class T, class U>
	std::ptrdiff_t operator-(const NotNull<T>&, const NotNull<U>&) = delete;
	template <class T>
	NotNull<T> operator-(const NotNull<T>&, std::ptrdiff_t) = delete;
	template <class T>
	NotNull<T> operator+(const NotNull<T>&, std::ptrdiff_t) = delete;
	template <class T>
	NotNull<T> operator+(std::ptrdiff_t, const NotNull<T>&) = delete;

	template <
		class T,
		class U = decltype(std::declval<const T&>().get()),
		bool = std::is_default_constructible<std::hash<U>>::value>
	struct NotNullHash
	{
		std::size_t operator()(const T& value) const
		{
			return std::hash<U>{}(value.get());
		}
	};

	template <class T, class U>
	struct NotNullHash<T, U, false>
	{
		NotNullHash() = delete;
		NotNullHash(const NotNullHash&) = delete;
		NotNullHash& operator=(const NotNullHash&) = delete;
	};

}  // namespace sw::utils

namespace std
{
	template <class T>
	struct hash<sw::utils::NotNull<T>> : sw::utils::NotNullHash<sw::utils::NotNull<T>>
	{};
}
