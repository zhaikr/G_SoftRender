#include "Texture.h"
#include <QDebug>

bool Texture::LoadFromImage(QString path)
{
    this->path_ = path;
    if(texture.load(path))
    {
        //texture.mirror();
        _width_ = texture.width();
        _height_ = texture.height();
        return true;
    }
    return false;
}

Color Texture::Sample2D(Coord2D coord)
{
    int x = static_cast<int>(coord.x * _width_ - 0.5f) % _width_;
    int y = static_cast<int>(coord.y * _height_ - 0.5f) % _height_;
    x = x < 0 ? _width_ + x : x;
    y = y < 0 ? _height_ + y : y;
    return Color(texture.pixelColor(x, y).red() / 255.f, texture.pixelColor(x, y).green() / 255.f, texture.pixelColor(x, y).blue() / 255.f);
}
