#ifndef RENDERMATH_H
#define RENDERMATH_H

#include "basicdatastructure.hpp"

template<typename T>
T CalculateInterpolation(const T& a, const T&b, const float& alpha)
{
    return (1-alpha)*a + alpha*b;
}

inline Vertex CalculateInterpolation(const Vertex& a, const Vertex& b, float& alpha)
{
    Vertex temp_vertex;
    temp_vertex.world_position_ = CalculateInterpolation(a.world_position_, b.world_position_, alpha);
    temp_vertex.screen_position_ = CalculateInterpolation(a.screen_position_, b.screen_position_, alpha);
    temp_vertex.texture_position_ = CalculateInterpolation(a.texture_position_, b.texture_position_, alpha);
    temp_vertex.normal_ = CalculateInterpolation(a.normal_, b.normal_, alpha);
    temp_vertex.color_ = CalculateInterpolation(a.color_, b.color_, alpha);
    temp_vertex.screen_depth = CalculateInterpolation(a.screen_depth, b.screen_depth, alpha);
    return temp_vertex;
}

#endif // RENDERMATH_H
