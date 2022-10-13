#ifndef SHADER_H
#define SHADER_H

#include "basicdatastructure.hpp"

class Shader
{
public:
    Shader();
    ~Shader() = default;
    virtual void VertexShader(Vertex &vertex) = 0;
    virtual void FragmentShader(Fragment &fragment) = 0;
private:
    Matrix4D ModelMatrix;
    Matrix4D ViewMatrix;
    Matrix4D ProjectMatrix;
};

#endif // SHADER_H
