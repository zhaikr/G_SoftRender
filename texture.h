#ifndef TEXTURE_H
#define TEXTURE_H
#include <QString>
#include <QImage>
#include "BasicDataStructure.hpp"


class Texture
{
    enum
    {
        DIFFUSE,
        SPECLUAR
    };
    int _width_;
    int _height_;
    QImage texture;
public:
    QString path_;
    Texture() = default;
    bool LoadFromImage(QString path);
    Color Sample2D(Coord2D coord);
};

#endif // TEXTURE_H
