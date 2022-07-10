#include "zepch.h"
#include "Color.h"

ZE::Color::Color(uint8 inR, uint8 inG, uint8 inB, uint8 inA)
    : r(inR)
    , g(inG)
    , b(inB)
    , a(inA)
{
}

ZE::Color::Color(uint32 color)
    : r((color >> 24) & 0xFF)
    , g((color >> 16) & 0xFF)
    , b((color >> 8) & 0xFF)
    , a(color & 0xFF)
{
}

uint32 ZE::Color::GetColor() const
{
    uint32 value = 0x00000000;

    value |= (r << 24);
    value |= (g << 16);
    value |= (b << 8);
    value |= a;

    return value;
}
