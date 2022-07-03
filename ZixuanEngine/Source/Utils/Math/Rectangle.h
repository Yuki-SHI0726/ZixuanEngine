#pragma once

#include "Utils/Math/Math.h"
#include "Utils/TypeDefs.h"
#include "Utils/Math/Vector2.h"

namespace ZE
{
/**
 * Represents a 2d rectangle
 */
template <typename Type>
class Rect
{
    static_assert(std::is_arithmetic_v<Type>, "Rectangle template param should be arithmetic");

public:
    /** Ctors & Dtor */ 
    Rect() = default;
    Rect(Type top, Type left, Type bottom, Type right);
    Rect(const Rect&) = default;
    Rect& operator=(const Rect&) = default;
    ~Rect() = default;
    template<typename U> constexpr Rect<Type>(const Rect<U>& other);

    /** 
     * Determines if this rectangle collides with another
     * @param other     The other rectangle to compare with
     */
    bool Collide(const Rect& other) const;

    /** 
     * Determines if this rectangle contains a vector 2
     * @param point     The point to check if it's in this rectangle
     */
    bool Contains(const Vector2<Type>& point) const;

    Vector2<Type> GetTopLeft() const { return Vector2<Type>(m_left, m_top); }
    Vector2<Type> GetTopRight() const { return Vector2<Type>(m_right, m_top); }
    Vector2<Type> GetBottomLeft() const { return Vector2<Type>(m_left, m_bottom); }
    Vector2<Type> GetBottomRight() const { return Vector2<Type>(m_right, m_bottom); }

public:
    Type m_top;    
    Type m_left;     
    Type m_bottom;  
    Type m_right;   
};

using FRect = Rect<f32>;
using IRect = Rect<int32>;

template<typename Type>
inline Rect<Type>::Rect(Type top, Type left, Type bottom, Type right)
    : m_top(top)
    , m_left(left)
    , m_bottom(bottom)
    , m_right(right)
{
}

template<typename Type>
inline bool Rect<Type>::Collide(const Rect& other) const
{
    const bool collisionX = m_left < other.m_right && m_right > other.m_left;
    const bool collisionY = m_top < other.m_bottom && m_bottom > other.m_top;
    return collisionX && collisionY;
}

template<typename Type>
inline bool Rect<Type>::Contains(const Vector2<Type>& point) const
{
    const bool rightToLeft = point.x > m_left;
    const bool leftToRight = point.x < m_right;
    const bool underTop = point.y > m_top;
    const bool aboveBottom = point.y < m_bottom;
    return rightToLeft && leftToRight && underTop && aboveBottom;
}
}