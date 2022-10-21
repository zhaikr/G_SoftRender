// Copyright 2022 JackRay
// Author: JackRay
// Time: 2022-08-17
// Licence: LGPL
#include "framebuffer.h"

FrameBuffer::FrameBuffer(const int& w, const int& h)
    : _width_(w),
      _height_(h),
      _depth_buffer_(_width_ * _height_),
      _color_buffer_(_width_, _height_, QImage::Format_RGBA8888)
{
    _color_buffer_.fill(QColor(0.0f, 0.0f, 0.0f));
    std::fill(_depth_buffer_.begin(), _depth_buffer_.end(), -1.0f);
}

bool FrameBuffer::CompareDepth(const int& x, const int& y, const float& depth)
{
    if (depth > _depth_buffer_[y * _width_ + x])
    {
        _depth_buffer_[y * _width_ + x] = depth;
        return true;
    }
    return false;
}

void FrameBuffer::SetPixelColor(const int& x, const int& y, const Color& color)
{
    _color_buffer_.setPixelColor(x, _height_ - 1 - y,
                                 QColor(color.r * 255.f, color.g * 255.f, color.b * 255.f));
}

void FrameBuffer::ClearBuffer(const Color& color)
{
    std::fill(_depth_buffer_.begin(), _depth_buffer_.end(), -1.f);
    _color_buffer_.fill(QColor(color.r * 255.f, color.g * 255.f, color.b * 255.f));
}

bool FrameBuffer::SaveImage(const QString& file_path)
{
    return _color_buffer_.save(file_path);
}
