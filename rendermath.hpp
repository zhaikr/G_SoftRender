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

//观察矩阵
// V = R*T
// T = [  1 , 0 , 0 , -eyex          R = [  Right , 0 
//        0 , 1 , 0 , -eyey                   UP  , 0
//        0 , 0 , 1 , -eyez               - Front , 0
//        0 , 0 , 0 ,   1   ]                 0   , 1 ]
//V =  [  Right  ,  - Right·eye
//          UP   ,  - UP·eye
//       -Front  ,   Front·eye
//         0     ,       1        ]
// 世界空间一般用右手系，靠近屏幕为+Z，从摄像机视角看过去的话+Z是朝向屏幕里的
// 为了让朝向保持不变，对Front向量取反
Matrix4D GetViewMatrix(Vector3D pos, Vector3D right, Vector3D up, Vector3D front)
{
    Matrix4D result = Matrix4D(1.0f);
    result[0][0] = right.x;
    result[1][0] = right.y;
    result[2][0] = right.z;
    result[3][0] = -glm::dot(right, pos);
    result[0][1] = up.x;
    result[1][1] = up.y;
    result[2][1] = up.z;
    result[3][1] = -glm::dot(up, pos);
    result[0][2] = -front.x;
    result[1][2] = -front.y;
    result[2][2] = -front.z;
    result[3][2] = glm::dot(front, pos);
    return result;
}

#endif // RENDERMATH_H
