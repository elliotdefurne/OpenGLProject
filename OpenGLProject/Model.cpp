#include "Model.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

void Model::draw(Shader& shader)
{
    for (unsigned int i = 0; i < m_meshes.size(); i++)
        m_meshes[i].draw();
}