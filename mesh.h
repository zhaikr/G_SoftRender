#ifndef MESH_H
#define MESH_H

#include "basicdatastructure.hpp"
#include "softrendercore.h"

class Mesh
{
public:
    Mesh() = default;
    ~Mesh() = default;
    Mesh(const Mesh& mesh)
      :VBO_(mesh.VBO_), EBO_(mesh.EBO_){}

    Mesh& operator=(const Mesh& mesh);
    Mesh& operator+=(const Mesh& mesh);

    void AddMesh(const Mesh& mesh);
    void AddTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
    void DrawMesh();
    void MeshUpdata(const std::vector<unsigned int>& EBO_, const std::vector<Vertex>& VBO_);
private:
    std::vector<unsigned int> EBO_;
    std::vector<Vertex> VBO_;

};

#endif // MESH_H
