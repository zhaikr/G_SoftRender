﻿#ifndef BLINNPHONGSHADER_H
#define BLINNPHONGSHADER_H

#include "shader.hpp"
#include "texture.h"

class BlinnPhongShader : public Shader
{
public:
    virtual void VertexShader(Vertex& vertex) override;
    virtual void FragmentShader(Fragment& fragment) override;
};

#endif // BLINNPHONGSHADER_H