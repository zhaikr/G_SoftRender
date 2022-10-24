#include "softrendercore.h"
#include <iostream>

/********************************************************************************/
// helper functions

static inline bool JudgeOnTopLeftEdge(CoordI2D v0, CoordI2D v1)
{
  return (v0.y > v1.y) || (v0.x > v1.x && v1.y == v0.y);
}

static inline bool JudgeInsideTriangle(EdgeEquation& tri_edge, VectorI3D res)
{
  bool flag = true;
  if (res.x == 0) flag &= tri_edge.top_left_flag[0];
  if (res.y == 0) flag &= tri_edge.top_left_flag[1];
  if (res.z == 0) flag &= tri_edge.top_left_flag[2];
  return flag && ((res.x >= 0 && res.y >= 0 && res.z >= 0) || (res.x <= 0 && res.y <= 0 && res.z <= 0));
}

/********************************************************************************/
// SoftRenderCore Constructor
SoftRenderCore::SoftRenderCore(const int& w, const int& h) :shader(nullptr), _width_(w), _height_(h), framebuffer(_width_, _height_)
{
    {// set view planes
      // near
      viewPlanes_[0] = { 0, 0, 1.f, 1.f };
      // far
      viewPlanes_[1] = { 0, 0, -1.f, 1.f };
      // left
      viewPlanes_[2] = { 1.f, 0, 0, 1.f };
      // right
      viewPlanes_[3] = { -1.f, 0, 0, 1.f };
      // top
      viewPlanes_[4] = { 0, 1.f, 0, 1.f };
      // bottom
      viewPlanes_[5] = { 0, -1.f, 0, 1.f };
    }
    {// set screen border
        // left
      screenLines_[0] = { 1.f, 0, 0 };
      // right
      screenLines_[1] = { -1.f, 0, (float)w };
      // bottom
      screenLines_[2] = { 0, 1.f, 0 };
      // top
      screenLines_[3] = { 0, -1.f, (float)h };
    }
}

/********************************************************************************/
// Scanline Triangle Algorithm

void SoftRenderCore::ScanLineTriangle(const Triangle& tri)
{
    Triangle temp_tri(tri);
    //  sort tri in ascending
    if (temp_tri[0].screen_position_.y > temp_tri[1].screen_position_.y)
    {
        Vertex temp = temp_tri[0];
        temp_tri[0] = temp_tri[1];
        temp_tri[1] = temp;
    }
    if (temp_tri[1].screen_position_.y > temp_tri[2].screen_position_.y)
    {
        Vertex temp = temp_tri[1];
        temp_tri[1] = temp_tri[2];
        temp_tri[2] = temp;
    }
    if (temp_tri[0].screen_position_.y > temp_tri[1].screen_position_.y)
    {
        Vertex temp = temp_tri[0];
        temp_tri[0] = temp_tri[1];
        temp_tri[1] = temp;
    }
    // Judge is one or two triangle and uptriangle or downtriangle
    if (temp_tri[0].screen_position_.y == temp_tri[1].screen_position_.y)
    {
        ScanUpTriangle(temp_tri);
    }else if (temp_tri[1].screen_position_.y == temp_tri[2].screen_position_.y){
        ScanDownTriangle(temp_tri);
    }else{
    // pass up and bottom point use calculate interpolation to get middle point then divide one to two triangle
        float alpha = (temp_tri[2].screen_position_.y - temp_tri[1].screen_position_.y) / (temp_tri[2].screen_position_.y - temp_tri[0].screen_position_.y);
        Vertex middle_point = CalculateInterpolation(temp_tri[2], temp_tri[0], alpha);
        Triangle mid_uptri = {temp_tri[1], middle_point, temp_tri[2]};
        Triangle mid_downtri = {temp_tri[0], middle_point, temp_tri[1]};
        ScanUpTriangle(mid_uptri);
        ScanDownTriangle(mid_downtri);
    }

}

void SoftRenderCore::ScanUpTriangle(const Triangle& tri)
{
    Vertex left = tri[0].screen_position_.x < tri[1].screen_position_.x ? tri[0] : tri[1];
    Vertex right = tri[0].screen_position_.x > tri[1].screen_position_.x ? tri[0] : tri[1];
    Vertex top = tri[2];
    int dy = top.screen_position_.y - left.screen_position_.y;
    int now_y = top.screen_position_.y;
    // scan triangle from top to bottom
    for (int i = dy; i >= 0; --i)
    {
        float alpha = 0.f;  // calculate interpolation factor
        if (dy != 0)
        {
            alpha = static_cast<float>(i) / dy;
        }

        Vertex new_left = CalculateInterpolation(left, top, alpha);
        Vertex new_right = CalculateInterpolation(right, top, alpha);
        new_left.screen_position_.x = static_cast<int>(new_left.screen_position_.x);
        new_right.screen_position_.x = static_cast<int>(new_right.screen_position_.x);
        new_left.screen_position_.y = new_right.screen_position_.y = now_y;
        ScanLine(new_left, new_right);
        --now_y;
    }
}

void SoftRenderCore::ScanDownTriangle(const Triangle& tri)
{
    Vertex left = tri[1].screen_position_.x < tri[2].screen_position_.x ? tri[1] : tri[2];
    Vertex right = tri[1].screen_position_.x > tri[2].screen_position_.x ? tri[1] : tri[2];
    Vertex bottom = tri[0];
    int dy = left.screen_position_.y - bottom.screen_position_.y;
    int now_y = bottom.screen_position_.y;
    // scan triangle from bottom to top
    for (int i = dy; i >= 0; --i)
    {
        float alpha = 0.f;  // calculate interpolation factor
        if (dy != 0)
        {
            alpha = static_cast<float>(i) / dy;
        }

        Vertex new_left = CalculateInterpolation(left, bottom, alpha);
        Vertex new_right = CalculateInterpolation(right, bottom, alpha);
        new_left.screen_position_.x = static_cast<int>(new_left.screen_position_.x);
        new_right.screen_position_.x = static_cast<int>(new_right.screen_position_.x);
        new_left.screen_position_.y = new_right.screen_position_.y = now_y;
        ScanLine(new_left, new_right);
        --now_y;
    }

}

void SoftRenderCore::ScanLine(const Vertex& left, const Vertex& right)
{
    int length = right.screen_position_.x - left.screen_position_.x;
    if (length == 0)
    {
        int x = static_cast<float>(right.screen_position_.x) ;
        int y = static_cast<float>(right.screen_position_.y);
        framebuffer.SetPixelColor(x, y, right.color_);
    }

    for (int i = 0; i < length; ++i)
    {
        float alpha = static_cast<float>(i) / length;
        Vertex temp_vertex = CalculateInterpolation(left, right, alpha);
        int x = static_cast<float>(left.screen_position_.x) + i;
        int y = static_cast<float>(left.screen_position_.y);
        framebuffer.SetPixelColor(x, y, temp_vertex.color_);
    }
}

/********************************************************************************/
// struct EdgeEquation implementation

CoordI4D SoftRenderCore::GetBoundingBox(const Triangle& tri)
{
  int xMin = _width_ - 1;
  int yMin = _height_ - 1;
  int xMax = 0;
  int yMax = 0;
  for (auto& v : tri)
  {
    xMin = std::min(xMin, static_cast<int>(v.screen_position_.x));
    yMin = std::min(yMin, static_cast<int>(v.screen_position_.y));
    xMax = std::max(xMax, static_cast<int>(v.screen_position_.x));
    yMax = std::max(yMax, static_cast<int>(v.screen_position_.y));
  }
  return {
      xMin > 0 ? xMin : 0,
      yMin > 0 ? yMin : 0,
      xMax < _width_ - 1 ? xMax : _width_ - 1,
      yMax < _height_ - 1 ? yMax : _height_ - 1 };
}

/********************************************************************************/
// struct EdgeEquation implementation
// see in https://zhuanlan.zhihu.com/p/140926917
EdgeEquation::EdgeEquation(const Triangle& tri)
{
    I = {
        tri[0].screen_position_.y - tri[1].screen_position_.y,
        tri[1].screen_position_.y - tri[2].screen_position_.y,
        tri[2].screen_position_.y - tri[0].screen_position_.y };
    J = {
        tri[1].screen_position_.x - tri[0].screen_position_.x,
        tri[2].screen_position_.x - tri[1].screen_position_.x,
        tri[0].screen_position_.x - tri[2].screen_position_.x };
    K = {
        tri[0].screen_position_.x * tri[1].screen_position_.y - tri[0].screen_position_.y * tri[1].screen_position_.x,
        tri[1].screen_position_.x * tri[2].screen_position_.y - tri[1].screen_position_.y * tri[2].screen_position_.x,
        tri[2].screen_position_.x * tri[0].screen_position_.y - tri[2].screen_position_.y * tri[0].screen_position_.x };
    top_left_flag[0] = JudgeOnTopLeftEdge(tri[0].screen_position_, tri[1].screen_position_);
    top_left_flag[1] = JudgeOnTopLeftEdge(tri[1].screen_position_, tri[2].screen_position_);
    top_left_flag[2] = JudgeOnTopLeftEdge(tri[2].screen_position_, tri[0].screen_position_);
    two_area = K[0] + K[1] + K[2];
    delta = 1.f / two_area;
}

VectorI3D EdgeEquation::GetResult(const int& x, const int& y)
{
   VectorI3D res = I * x + J * y + K;
   return res;
}

void EdgeEquation::UpX(VectorI3D& res)
{
    res += I;
}

void EdgeEquation::UpY(VectorI3D& res)
{
    res += J;
}

Vector3D EdgeEquation::GetBarycentric(VectorI3D& val)
{
    return { val.y * delta, val.z * delta, val.x * delta };
}

void SoftRenderCore::RasterizationTriangle(Triangle &tri)
{
    for(auto& v : tri)
    {
        //shader->FragmentShader(v);
    }
    ScanLineTriangle(tri);
}

void SoftRenderCore::ProcessTriangle(Triangle &tri)
{
    for(auto& v : tri)
    {
        //shader->VertexShader(v);
    }
    ConvertToScreen(tri, _width_, _height_);
    RasterizationTriangle(tri);
}

/********************************************************************************/
// main render function

void SoftRenderCore::Render()
{
    std::vector<Triangle> triangle_list;
    for (int i = 0; i < EBO_.size(); i += 3)
    {
        try
        {
            if (i + 1 < EBO_.size() && i + 2 < EBO_.size())
            {
                triangle_list.push_back({VBO_.at(EBO_.at(i)), VBO_.at(EBO_.at(i+1)), VBO_.at(EBO_.at(i+2))});
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    for (int i = 0; i < triangle_list.size(); i++)
    {
        //ScanLineTriangle(triangle_list[i]);
        ProcessTriangle(triangle_list[i]);
    }
}
