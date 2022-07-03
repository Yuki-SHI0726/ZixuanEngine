#pragma once

#include "Vector2.h"
#include "Rectangle.h"
#include <array>

namespace ZE
{
//---------------------------------------------------------------------------------------
// Describes a 3x3 Matrix. Used as 2D transformation Matrix.
//---------------------------------------------------------------------------------------
class Matrix
{
private:
    std::array<float, 9> m_matrix;

public:
    Matrix();
    Matrix(float a00, float a01, float a02,
        float a10, float a11, float a12,
        float a20, float a21, float a22);

    Matrix& Scale(FVec2 factors);
    Matrix& Scale(FVec2 factors, FVec2 center);
    Matrix& Rotate(float angle);
    Matrix& Rotate(float angle, FVec2 center);
    Matrix& Translate(FVec2 offset);
    Matrix& Combine(const Matrix& other);
    FVec2 TransformPoint(FVec2 point) const;
    FRect TransformAARect(FRect rect) const;
};
}