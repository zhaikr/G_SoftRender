#ifndef RENDERMATH_H
#define RENDERMATH_H

#include "basicdatastructure.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
    temp_vertex.screen_depth_ = CalculateInterpolation(a.screen_depth_, b.screen_depth_, alpha);
    return temp_vertex;
}
// glm 的矩阵是行矩阵，而一般我们用的都是列矩阵，所以存放的时候要转置
// 行矩阵做变换是  v * M  ，列矩阵是 M * v
// ox oy 是原点的坐标
// x坐标乘以w/2 ，y坐标乘以h/2，整体向左下平移
// Vp = [  w/2 ,   0  ,  0  , ox+w/2 ,
//	    0  ,  h/2 ,  0  , oy+h/2 ,
//          0  ,   0  ,  1  ,   0    ,
//          0  ,   0  ,  0  ,   1   ]
inline Matrix4D GetViewPortMatrix(int ox, int oy, int width, int height) {

    Matrix4D result = Matrix4D(1.0f);
    result[0][0] = width / 2.0f;
    result[3][0] = ox + (width / 2.0f);
    result[1][1] = height / 2.0f;
    result[3][1] = oy + (height / 2.0f);
    return result;
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
inline Matrix4D GetViewMatrix(Vector3D pos, Vector3D right, Vector3D up, Vector3D front)
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

//glm::lookAt(eye, center, up)
//lookAt函数有三个参数，分别代表观察点的位置，要看向的中心点，以及摄像机的up向量
inline Matrix4D GetViewMatrix(Vector3D position, Vector3D center)
{
    return glm::lookAt(position,center,{0.0f,1.0f,0.0f});
}

//透视投影 参数 fov(弧度) aspect near far
//M = [   1/aspect*tan(fov/2),       0      ,         0      ,       0
//               0  ,         1/tan(fov/2)  ,         0      ,       0
//               0  ,                0      ,  - (f+n)/(f-n) ,  -2fn/(f-n)
//               0  ,                0      ,         -1     ,       0     ]
// 投影之后从右手系变成了左手系，Z靠近屏幕的是负
inline Matrix4D GetPerspectiveMatrix(const float & fovy, const float & aspect, const float & n, const float & f)
{
    Matrix4D result = Matrix4D(0.0f);
    const float tanHalfFov = tan(fovy*0.5f);
    result[0][0] = 1.0f / (aspect*tanHalfFov);
    result[1][1] = 1.0f / (tanHalfFov);
    result[2][2] = -(f + n) / (f - n);
    result[2][3] = -1.0f;
    result[3][2] = (-2.0f*n*f) / (f - n);
    return result;
}

//glm::perspective 参数fov表示 field of view ，aspect 表示屏幕宽高比, z_near和z_far定义了frustum的近平面和远平面的距离
inline Matrix4D GetProjectionMatrix(const float& fov, const float& aspect, const float& z_near, const float& z_far)
{
    return glm::perspective(glm::radians(fov), aspect, z_near, z_far);
}


//Convert NDC To Screen
inline void ConvertToScreen(Triangle& tri, const int& w, const int& h)
{
    for (auto& v : tri)
    {
        v.screen_position_.x = static_cast<int>(0.5f * w * (v.ndc_space_position_.x + 1.0f) + 0.5f);
        v.screen_position_.y = static_cast<int>(0.5f * h * (v.ndc_space_position_.y + 1.0f) + 0.5f);
        v.screen_depth_ = v.ndc_space_position_.z;
    }
}

//Coordinate x, y, z dividing w, 
inline void ExecutePerspectiveDivision(Triangle& tri)
{
  for (auto& v : tri)
  {
    v.ndc_space_position_.x /= v.clip_space_positon_.w;
    v.ndc_space_position_.y /= v.clip_space_positon_.w;
    v.ndc_space_position_.z /= v.clip_space_positon_.w;
  }
}


#endif // RENDERMATH_H
