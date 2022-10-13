#include "shader.h"

Shader::Shader()
{
    ModelMatrix = Matrix4D(1.0f);
    ViewMatrix = Matrix4D(1.0f);
    ProjectMatrix = Matrix4D(1.0f);
}
