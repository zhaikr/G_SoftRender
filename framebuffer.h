#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <QImage>
#include <QColor>
#include <QString>
#include "basicdatastructure.hpp"

//storage row-major order
class FrameBuffer
{
public:
    FrameBuffer();
    FrameBuffer(const int& w, const int& h);
    //~FrameBuffer();

    bool CompareDepth(const int& x, const int& y, const float& depth);

    void SetPixelColor(const int& x, const int& y, const Color& color);

    void ClearBuffer(const Color& color);

    bool SaveImage(const QString& file_path);

    QImage& GetImage(){return _color_buffer_;}

private:
    int _width_;  //screen resolution
    int _height_;
    std::vector<float> _depth_buffer_; //declare depthbuffer and colorbuffer
    QImage _color_buffer_;
};

#endif // FRAMEBUFFER_H
