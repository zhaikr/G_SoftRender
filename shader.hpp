#ifndef SHADER_H
#define SHADER_H

#include "BasicDataStructure.hpp"
#include "rendermath.hpp"

class Shader
{
public:
    Matrix4D Model = Matrix4D(1.0f);
    Matrix4D View = Matrix4D(1.0f);
    Matrix4D Projection = Matrix4D(1.0f);
    std::vector<Light> lightList;
    Material material;
    Coord4D eyePos;
    virtual void VertexShader(Vertex &vertex);
    virtual void FragmentShader(Fragment &fragment);
};

inline void Shader::VertexShader(Vertex &vertex)
{
    vertex.world_position_ = Coord3D(Model * Coord4D(vertex.world_position_, 1.f));
    vertex.ndc_space_position_ = Projection * View * Coord4D(vertex.world_position_, 1.f);

}

inline void Shader::FragmentShader(Fragment &fragment)
{
    fragment.fragment_color_ = fragment.fragment_color_;
}
#endif // SHADER_H
