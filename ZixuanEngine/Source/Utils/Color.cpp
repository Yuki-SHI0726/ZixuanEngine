#include "Color.h"

ZE::Color::Color(uint8 inR, uint8 inG, uint8 inB, uint8 inA)
    : r(inR)
    , g(inG)
    , b(inB)
    , a(inA)
{
}

ZE::Color::Color(uint32 color)
{
    //TODO
}

uint32 ZE::Color::GetColor() const
{
    //TODO
    uint32 value = 0x00;
    return value;
}
