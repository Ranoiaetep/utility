#include <iostream>

namespace util {
namespace os {
template<std::ios_base::fmtflags flag>
struct set_ios_flag
{
	constexpr static set_ios_flag get() { return set_ios_flag(); }
	~set_ios_flag() { pStream && pStream->flags(original_flag); }

	set_ios_flag(const set_ios_flag&) = delete;
	set_ios_flag(set_ios_flag&&) = delete;
	set_ios_flag& operator= (const set_ios_flag&) = delete;
	set_ios_flag& operator= (set_ios_flag&&) = delete;
	void* operator new(size_t) = delete;
	void* operator new[](size_t) = delete;

private:
	set_ios_flag() = default;

	void set_ios(std::ios& stream)
	{
		pStream = &stream;
		original_flag = pStream->flags();
		pStream->flags(flag);
	}

	std::ios* pStream = nullptr;
	std::ios_base::fmtflags original_flag;

	friend std::ostream& operator<< (std::ostream& os, set_ios_flag&& f)
	{
		f.set_ios(os);
		return os;
	}

	friend std::istream& operator>> (std::istream& is, set_ios_flag&& f)
	{
	f.set_ios(is);
	return is;
	}
};

constexpr auto hex = [](){ return set_ios_flag<std::ios_base::hex | std::ios_base::showbase>::get(); };
constexpr auto oct = [](){ return set_ios_flag<std::ios_base::oct | std::ios_base::showbase>::get(); };
constexpr auto dec = [](){ return set_ios_flag<std::ios_base::dec | std::ios_base::showbase>::get(); };
}
}
