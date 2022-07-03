#include "RNG.h"

using namespace ZE;

RNG::RNG(uint64 seed)
{
	SetSeed(seed);
}

void RNG::SetSeed(uint64 seed)
{
	m_seed[0] = seed << 3 | seed;
	m_seed[1] = seed << 7 | seed;
}

RNG& RNG::Global()
{
	static RNG GlobalRng;
	return GlobalRng;
}
