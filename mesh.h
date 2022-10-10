#ifndef MESH_H
#define MESH_H

#include "basicdatastructure.hpp"
#include "softrendercore.h"

class Mesh
{
public:
    Mesh() = default;
    void DrawMesh();
    void MeshUpdata(const std::vector<unsigned int>& EBO_, const std::vector<Vertex>& VBO_);
private:
    std::vector<unsigned int> EBO_;
    std::vector<Vertex> VBO_;

};

#endif // MESH_H
