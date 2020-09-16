#include "ModelObject.h"
#include "MeshRenderer.h"
#include "Shader.h"
#include "assimp/postprocess.h"

MeshRenderer::MeshRenderer(Game* game) : m_game(game)
{
}

bool MeshRenderer::addModel(ModelObject* model, const std::string& filePath, Shader* shader)
{
    Importer importer;

    const aiScene* pScene = importer.ReadFile(filePath,
        aiProcess_Triangulate |
        aiProcess_ConvertToLeftHanded);

    if (pScene == nullptr)
        return false;

	processNode(model, pScene->mRootNode, pScene, shader);
    return true;
}

void MeshRenderer::processNode(ModelObject* model, aiNode* node, const aiScene* scene, Shader* shader)
{
    for (UINT i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        model->addMesh(processMesh(mesh, scene, shader));
    }

    for (UINT i = 0; i < node->mNumChildren; i++)
    {
        processNode(model, node->mChildren[i], scene, shader);
    }
}

MeshObject* MeshRenderer::processMesh(aiMesh* mesh, const aiScene* scene, Shader* shader)
{
    std::vector<Vertex> vertices;
    std::vector<DWORD> indices;

    // Get vertices
    for (UINT i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex{
        	Vector3{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z},
        	Vector4{0, 1, 0, 1},
        	Vector3{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z}
        };

        if (mesh->mTextureCoords[0])
        {
            vertex.texCord.x = mesh->mTextureCoords[0][i].x;
            vertex.texCord.y = mesh->mTextureCoords[0][i].y;
        }

        vertices.push_back(vertex);
    }

    // Get indices
    for (UINT i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (UINT j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return new MeshObject(m_game, vertices, indices, shader);
}
