#include "mesh.h"

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
