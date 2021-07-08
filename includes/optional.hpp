#include <optional>
#include <type_traits>

namespace util {
template<typename... Args, typename T = std::remove_reference_t<decltype(std::make_optional((std::declval<Args>(), ...)).value())>>
constexpr std::optional<T> optional(bool condition, Args&& ...args)
{
	return condition ? std::make_optional<T>(((std::forward<Args>(args)), ...)) : std::nullopt;
}

template<typename T>
constexpr std::optional<T> optional(bool condition)
{
	return condition ? std::make_optional<T>() : std::nullopt;
}
}
