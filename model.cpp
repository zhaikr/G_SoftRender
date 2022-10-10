#include "model.h"

Model::Model()
{

}

void Model::DrawModel()
{
    for (int i = 0; i < meshes_.size(); ++i)
    {
        meshes_[i].DrawMesh();
    }
}

void Model::ProcessNode(const std::vector<Vertex>& vertex_list)
{
    //std::vector<Vertex> vertex_list;
    meshes_.push_back(ProcessMesh(vertex_list));
}

//process node, generating VBO and EBO,
Mesh Model::ProcessMesh(const std::vector<Vertex>& vertex_list)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Mesh mesh;
    for (int i = 0; i < vertex_list.size(); ++i)
    {
        vertices.emplace_back(vertex_list[i]);
        indices.emplace_back(i);
    }
    mesh.MeshUpdata(indices, vertices);
    return mesh;
}


