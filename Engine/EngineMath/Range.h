#pragma once

namespace SHMath
{
	/*bool InRange(const int _low, const int _high, const int _x)
	{
		return ((_x - _high) * (_x - _low) <= 0);
	}*/

	template<typename T>
	bool InRange(const T _low, const T _high, const T _x)
	{
		static_assert(std::is_arithmetic_v<T>, "Value should be a numerical type"); // Ensure T is a numerical value
		return ((_x - _high) * (_x - _low) <= 0);
	}

	// use std::clamp instead
	//template<typename T>
	//void ConstrainInRange(const T _low, const T _high, const T _x)
	//{
	//	static_assert(std::is_arithmetic_v<T>, "Value should be a numerical type"); // Ensure T is a numerical value
	//	_x = _x < _low ? _low : _x;
	//	_x = _x > _high ? _high : _x;
	//}
}
