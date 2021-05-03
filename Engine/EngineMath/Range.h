#pragma once

namespace SHMath
{
	bool InRange(const int _low, const int _high, const int _x)
	{
		return ((_x - _high) * (_x - _low) <= 0);
	}
}
