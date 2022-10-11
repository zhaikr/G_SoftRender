#include "mesh.h"

Mesh& Mesh::operator=(const Mesh& mesh)
{
    if (&mesh == this)
    {
        return *this;
    }
    VBO_ = mesh.VBO_;
    EBO_ = mesh.EBO_;
    return *this;
}
Mesh& Mesh::operator+=(const Mesh& mesh)
{
    AddMesh(mesh);
    return *this;
}

void Mesh::AddMesh(const Mesh& mesh)
{
    int offset = VBO_.size();
    VBO_.insert(VBO_.end(), mesh.VBO_.begin(), mesh.VBO_.end());
    EBO_.reserve(EBO_.size() + mesh.EBO_.size());
    for (int i = 0; i < mesh.EBO_.size(); i++) {
        EBO_.emplace_back(mesh.EBO_[i] + offset);
    }
}

void Mesh::AddTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
    int offset = VBO_.size();
    VBO_.emplace_back(v1);
    VBO_.emplace_back(v2);
    VBO_.emplace_back(v3);
    EBO_.emplace_back(offset);
    EBO_.emplace_back(offset+1);
    EBO_.emplace_back(offset+2);

}

void Mesh::DrawMesh()
{
    SoftRenderCore::GetInstance().VBO_ = VBO_;
    SoftRenderCore::GetInstance().EBO_ = EBO_;
    SoftRenderCore::GetInstance().Render();
}

void Mesh::MeshUpdata(const std::vector<unsigned int>& EBO_, const std::vector<Vertex>& VBO_)
{
    this->EBO_ = EBO_;
    this->VBO_ = VBO_;
}
