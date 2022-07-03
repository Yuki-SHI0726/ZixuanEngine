#pragma once
#include "Typedefs.h"

#include <type_traits>
#include <time.h>

namespace ZE
{

/**
 * Random number generator using XorShift128+
 */
class RNG
{
public:
	/**
	 * Constructor
	 * @seed		Default to time seed. Can be anything to keep RNG stable
	 */
	RNG(uint64 seed = unsigned(time(nullptr)));

	/**
	 * @return		a random integral value
	 */
	template<typename Type = int32>
	Type Rand();

	/**
	 * Specialized template Rand() for floating points version
	 * @return		A random floating point from 0 to 1 inclusive
	 */
	template<>
	f32 Rand();

	/**
	 * @return		A random floating point from min to max inclusive
	 */
	template<>
	bool Rand();

	/**
	 * @param max	Largest possible value (inclusive)
	 * @return		a random integral value within max range
	 */
	template<typename Type = int32>
	Type RandInMax(Type max);

	/**
	 * @param min	Smallest possible value (inclusive)
	 * @param max	Largest possible value (inclusive)
	 * @return		A random integral value within min and max range
	 */
	template<typename Type = int32> 
	Type RandInRange(Type min, Type max);

	/** 
	 * @param min	Smallest possible floating value (inclusive)
	 * @param max	Largest possible floating value (inclusive)
	 * @return		A random floating point from min to max inclusive
	 */
	template<>
	f32 RandInRange(f32 min, f32 max);

	/** Update two seeds */
	void SetSeed(uint64 seed);

	/** Singleton to get a static global RNG instance */
	static RNG& Global();

private:
	uint64 m_seed[2];
};

template<typename Type>
inline Type RNG::Rand()
{
	// https://en.wikipedia.org/wiki/Xorshift
	static_assert(std::is_integral_v<Type>, "Type must be integral");

	uint64 t = m_seed[0];
	const uint64 s = m_seed[1];

	m_seed[0] = s;

	t ^= t << 23;		// a
	t ^= t >> 17;		// b -- Again, the shifts and the multipliers are tunable
	t ^= s ^ (s >> 26);	// c

	m_seed[1] = t;
	return Type(t + s);
}

template<>
inline f32 RNG::Rand()
{
	f32 result = 0.0f;

	// mangling...
	uint64 temp1 = m_seed[1];
	m_seed[0] ^= m_seed[0] << 23;
	uint64 temp2 = m_seed[0] ^ m_seed[1] ^ (m_seed[0] >> 17) ^ (m_seed[1] >> 26);
	uint64 temp3 = temp2 + m_seed[1];

	result = 1.0f / ((f32)INT_MAX + 1.0f) * (0x7FFFFFFF & temp3);

	// reassign seed
	m_seed[0] = temp1;
	m_seed[1] = temp2;

	return result;
}

template<>
inline bool RNG::Rand()
{
	return static_cast<bool>(RandInRange(0, 1));
}

template<typename Type>
inline Type RNG::RandInMax(Type max)
{
	return RandInRange<Type>(0, max);
}

template<typename Type>
inline Type RNG::RandInRange(Type min, Type max)
{
	uint64 mod = (uint64)max - (uint64)min + 1;
	return Rand<Type>() % mod + min;
}

template<>
inline f32 RNG::RandInRange(f32 min, f32 max)
{
	f32 randomFloat = Rand<f32>();
	f32 range = max - min;
	return randomFloat * range + min;
}
}
