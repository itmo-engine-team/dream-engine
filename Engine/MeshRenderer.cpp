#include "MeshRenderer.h"
#include "assimp/postprocess.h"

MeshRenderer::MeshRenderer()
{

}

bool MeshRenderer::ProcessModel(ModelData* modelData, const std::string& filePath)
{
    Importer importer;

    const aiScene* pScene = importer.ReadFile(filePath,
        aiProcess_Triangulate |
        aiProcess_ConvertToLeftHanded);

    if (pScene == nullptr)
        return false;

    processNode(modelData, pScene->mRootNode, pScene);
    return true;
}

ModelData* MeshRenderer::CreateBoxModel(Shader* shader, Vector4 color, Vector3 boxSize)
{
    ModelData* modelData = new ModelData(shader);

    std::vector<Vertex> vertices = {
        // Front vertices
        {
            {-boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitZ
        },
        {
            {-boxSize.x, +boxSize.y, -boxSize.z}, color, -Vector3::UnitZ
        },
        {
            {+boxSize.x, +boxSize.y, -boxSize.z}, color, -Vector3::UnitZ
        },
        {
            {+boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitZ
        },

        // Back vertices
        {
            {-boxSize.x, -boxSize.y, +boxSize.z}, color, Vector3::UnitZ
        },
        {
            {-boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitZ
        },
        {
            {+boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitZ
        },
        {
            {+boxSize.x, -boxSize.y, +boxSize.z}, color, Vector3::UnitZ
        },

        // Left vertices
        {
            {+boxSize.x, -boxSize.y, -boxSize.z}, color, Vector3::UnitX
        },
        {
            {+boxSize.x, +boxSize.y, -boxSize.z}, color, Vector3::UnitX
        },
        {
            {+boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitX
        },
        {
            {+boxSize.x, -boxSize.y, +boxSize.z}, color, Vector3::UnitX
        },

        // Right vertices
        {
            {-boxSize.x, -boxSize.y, +boxSize.z}, color, -Vector3::UnitX
        },
        {
            {-boxSize.x, +boxSize.y, +boxSize.z}, color, -Vector3::UnitX
        },
        {
            {-boxSize.x, +boxSize.y, -boxSize.z}, color, -Vector3::UnitX
        },
        {
            {-boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitX
        },

        // Top vertices
        {
            {-boxSize.x, +boxSize.y, -boxSize.z}, color, Vector3::UnitY
        },
        {
            {-boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitY
        },
        {
            {+boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitY
        },
        {
            {+boxSize.x, +boxSize.y, -boxSize.z}, color, Vector3::UnitY
        },

        // Bottom vertices
        {
            {+boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitY
        },
        {
            {+boxSize.x, -boxSize.y, +boxSize.z}, color, -Vector3::UnitY
        },
        {
            {-boxSize.x, -boxSize.y, +boxSize.z}, color, -Vector3::UnitY
        },
        {
            {-boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitY
        },
    };
    std::vector<DWORD> indices = {
        // front face
        0, 1, 2,
        0, 2, 3,

        // back face
        4, 6, 5,
        4, 7, 6,

        // left face
        8, 9, 10,
        8, 10, 11,

        // right face
        12, 13, 14,
        12, 14, 15,

        // top face
        16, 17, 18,
        16, 18, 19,

        // bottom face
        20, 21, 22,
        20, 22, 23,
    };

    auto meshData = new MeshData(vertices, indices);
    modelData->AddMeshData(meshData);

    return modelData;
}

void MeshRenderer::processNode(ModelData* modelData, aiNode* node, const aiScene* scene)
{
    for (UINT i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        modelData->AddMeshData(processMesh(mesh, scene));
    }

    for (UINT i = 0; i < node->mNumChildren; i++)
    {
        processNode(modelData, node->mChildren[i], scene);
    }
}

MeshData* MeshRenderer::processMesh(aiMesh* mesh, const aiScene* scene)
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

    return new MeshData(vertices, indices);
}
