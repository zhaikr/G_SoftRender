#ifndef BASICDATASTRUCTURE_HPP
#define BASICDATASTRUCTURE_HPP

#include <array>
#include <vector>
#include "glm/glm.hpp"

using Color = glm::vec3;
using Vector3D = glm::vec3;
using VectotI3D = glm::ivec3;
using Vector4D = glm::vec4;
using VectorI4D = glm::ivec4;
using Coord2D = glm::vec2;
using Coord3D = glm::vec3;
using Coord4D = glm::vec4;
using Matrix4D = glm::mat4;



struct Vertex
{
    Coord3D world_position_;
    union
    {
        Coord4D clip_space_positon_;
        Coord4D ndc_space_position_;
    };
    Coord2D screen_position_;
    Coord2D texture_position_;
    Vector3D normal_;
    Color color_;
    float screen_depth;
};

using Triangle = std::array<Vertex, 3>;

struct Fragment
{
    Coord3D world_position_;
    Coord2D screen_position_;
    Coord2D texture_position_;
    Vector3D normal_;
    Color fragment_color_;
    float screen_depth;
};

struct Light
{
    union{
    Coord4D pos;
    Vector4D dir;
    };
    Color ambient;
    Color diffuse;
    Color specular;
};

struct Material
{
    int diffuse;
    int specular;
    float shininess;
};

#endif // BASICDATASTRUCTURE_HPP
