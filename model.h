#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "basicdatastructure.hpp"
#include "mesh.h"

class Model
{
public:
    Model();
    void DrawModel();
    void ProcessNode(const std::vector<Vertex>& vertex_list);
private:
    std::vector<Mesh> meshes_;  //storing all meshes of a model
    Mesh ProcessMesh(const std::vector<Vertex>& vertex_lsit);

    int vertex_count = 0;
    int triangle_count = 0;

};

#endif // MODEL_H
