#include "softrendercore.h"
#include <iostream>

SoftRenderCore::SoftRenderCore(const int& w, const int& h) : _width_(w), _height_(h), framebuffer(_width_, _height_)
{

}

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
    for (int i = 0; i <= length; ++i)
    {
        float alpha = static_cast<float>(i) / length;
        Vertex temp_vertex = CalculateInterpolation(left, right, alpha);
        framebuffer.SetPixelColor(temp_vertex.screen_position_.x, temp_vertex.screen_position_.y, temp_vertex.color_);
    }
}

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
        ScanLineTriangle(triangle_list[i]);
    }
}
