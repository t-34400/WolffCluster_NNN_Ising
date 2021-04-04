#pragma once
#include <cassert>

namespace isingConstant
{
	constexpr int timeSize{ 16 };
	constexpr int spaceSize{ 32 };

	constexpr int latticeSize{ timeSize * spaceSize };

	static_assert(timeSize > 0 && spaceSize > 0 && "timeSize and spaceSize must have non-negative value");
}