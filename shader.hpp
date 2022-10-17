#ifndef SHADER_H
#define SHADER_H
#include "BasicDataStructure.hpp"

class Shader
{
public:
    Matrix4D Model;
    Matrix4D View;
    Matrix4D Projection;
    //std::vector<Light> lightList;
    //Material material;
    Coord4D eyePos;
    virtual void VertexShader(Vertex &vertex) = 0;
    virtual void FragmentShader(Fragment &fragment) = 0;
};

#endif // SHADER_H
