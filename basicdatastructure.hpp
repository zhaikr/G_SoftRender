#ifndef BASICDATASTRUCTURE_HPP
#define BASICDATASTRUCTURE_HPP

#include <array>
#include <vector>
#include "glm/glm.hpp"

using Color = glm::vec4;
using Vector3D = glm::vec3;
using VectotI3D = glm::ivec3;
using Vector4D = glm::vec4;
using VectorI4D = glm::ivec4;
using Coord2D = glm::vec2;
using Coord4D = glm::vec4;
using Matrix4D = glm::mat4;



struct Vertex
{
    Coord4D world_position_;
    Coord2D screen_position_;
    Coord2D texture_position_;
    Vector3D normal_;
    Color color_;
    float screen_depth;
};

using Triangle = std::array<Vertex, 3>;

struct Fragment
{
    Coord4D world_position_;
    Coord2D screen_position_;
    Coord2D texture_position_;
    Vector3D normal_;
    Color color_;
    float screen_depth;
};

#endif // BASICDATASTRUCTURE_HPP
