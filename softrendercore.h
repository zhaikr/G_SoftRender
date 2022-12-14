#ifndef SOFTRENDERCORE_H
#define SOFTRENDERCORE_H

#include "framebuffer.h"
#include "rendermath.hpp"

class SoftRenderCore
{
public:
    SoftRenderCore();
    SoftRenderCore(const int& w, const int& h);
    //~SoftRenderCore();
    std::vector<Vertex> VBO_;
    std::vector<unsigned> EBO_;  //array of vertex indices

    void ClearBuffer(){framebuffer.ClearBuffer(clearcolor);}
    QImage& GetBuffer(){return framebuffer.GetImage();}

    static SoftRenderCore& GetInstance(const int& w = 0 ,const int& h = 0)
    {
        static SoftRenderCore Instance(w, h);
        return Instance;
    }

    static void Init(const int& w,const int& h)
    {
        GetInstance(w, h);
    }

    // Render triangle , this is interface of out function to run the core render class 
    void Render();



private:
    int _width_;
    int _height_;
    Color clearcolor;
    FrameBuffer framebuffer;
    //Scan line Triangle function
    void ScanLineTriangle(const Triangle& tri);
    void ScanLine(const Vertex& left, const Vertex& right);
    void ScanUpTriangle(const Triangle& tri);
    void ScanDownTriangle(const Triangle& tri);

    void RasterizationTriangle(const Triangle& tri);

};

#endif // SOFTRENDERCORE_H
