#pragma once
#include "Utils/Typedefs.h"

namespace ZE
{
/**
 * Describes a color in four RGBA unsigned 8 bits integers from [0 - 255]
 */
class ZE_API Color
{
public:
    uint8 r = 0; 
    uint8 g = 0; 
    uint8 b = 0; 
    uint8 a = 255; 

    Color() = default;
    Color(uint8 inR, uint8 inG, uint8 inB, uint8 inA);

    /**
     * Color's constructor with a unsigned 32 bits integer parameter. Should be in RGBA order
     * @param color     Should be in RGBA order's 32 bits integer
     */
    Color(uint32 color);

    /*
     * @return An unsigned 32 bits integer with RGBA info of this color
     */
    uint32 GetColor() const;
};
}