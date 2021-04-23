#pragma once

namespace SHMath
{
	bool InRange(const int low, const int high, const int x)
	{
		return ((x - high) * (x - low) <= 0);
	}
}
