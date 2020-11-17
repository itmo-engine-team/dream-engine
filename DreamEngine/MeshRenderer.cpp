#include "MeshRenderer.h"

#include "assimp/postprocess.h"
#include "ErrorLogger.h"

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
    {
        ErrorLogger::Log(Error, importer.GetErrorString());
        return false;
    }

    processNode(modelData, pScene->mRootNode, pScene);
    return true;
}

ModelData* MeshRenderer::CreateBoxModel(ModelShader* shader, Vector4 color, Vector3 boxSize)
{
    ModelData* modelData = new ModelData(shader);

    std::vector<Vertex> vertices = {
        // Front vertices
        {
            {-boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitZ, Vector2(1, 1)
        },
        {
            {-boxSize.x, +boxSize.y, -boxSize.z}, color, -Vector3::UnitZ, Vector2(1, 0)
        },
        {
            {+boxSize.x, +boxSize.y, -boxSize.z}, color, -Vector3::UnitZ, Vector2(0, 0)
        },
        {
            {+boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitZ, Vector2(0, 1)
        },

        // Back vertices
        {
            {-boxSize.x, -boxSize.y, +boxSize.z}, color, Vector3::UnitZ, Vector2(1, 1)
        },
        {
            {-boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitZ, Vector2(1, 0)
        },
        {
            {+boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitZ, Vector2(0, 0)
        },
        {
            {+boxSize.x, -boxSize.y, +boxSize.z}, color, Vector3::UnitZ, Vector2(0, 1)
        },

        // Left vertices
        {
            {+boxSize.x, -boxSize.y, -boxSize.z}, color, Vector3::UnitX, Vector2(1, 1)
        },
        {
            {+boxSize.x, +boxSize.y, -boxSize.z}, color, Vector3::UnitX, Vector2(1, 0)
        },
        {
            {+boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitX, Vector2(0, 0)
        },
        {
            {+boxSize.x, -boxSize.y, +boxSize.z}, color, Vector3::UnitX, Vector2(0, 1)
        },

        // Right vertices
        {
            {-boxSize.x, -boxSize.y, +boxSize.z}, color, -Vector3::UnitX, Vector2(1, 1)
        },
        {
            {-boxSize.x, +boxSize.y, +boxSize.z}, color, -Vector3::UnitX, Vector2(1, 0)
        },
        {
            {-boxSize.x, +boxSize.y, -boxSize.z}, color, -Vector3::UnitX, Vector2(0, 0)
        },
        {
            {-boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitX, Vector2(0, 1)
        },

        // Top vertices
        {
            {-boxSize.x, +boxSize.y, -boxSize.z}, color, Vector3::UnitY, Vector2(1, 1)
        },
        {
            {-boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitY, Vector2(1, 0)
        },
        {
            {+boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitY, Vector2(0, 0)
        },
        {
            {+boxSize.x, +boxSize.y, -boxSize.z}, color, Vector3::UnitY, Vector2(0, 1)
        },

        // Bottom vertices
        {
            {+boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitY, Vector2(1, 1)
        },
        {
            {+boxSize.x, -boxSize.y, +boxSize.z}, color, -Vector3::UnitY, Vector2(1, 0)
        },
        {
            {-boxSize.x, -boxSize.y, +boxSize.z}, color, -Vector3::UnitY, Vector2(0, 0)
        },
        {
            {-boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitY, Vector2(0, 1)
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

ModelData* MeshRenderer::CreateSquareModel(ModelShader* shader, Vector3 quardSize)
{
    ModelData* modelData = new ModelData(shader);

    std::vector<Vertex> vertices = {
        // Front vertices
        {
            {-quardSize.x, -quardSize.y, -quardSize.z}, Vector2(1, 1), -Vector3::UnitZ
        },
        {
            {-quardSize.x, +quardSize.y, -quardSize.z}, Vector2(1, 0), -Vector3::UnitZ
        },
        {
            {+quardSize.x, +quardSize.y, -quardSize.z}, Vector2(0, 0), -Vector3::UnitZ
        },
        {
            {+quardSize.x, -quardSize.y, -quardSize.z}, Vector2(0, 1), -Vector3::UnitZ
        },
    };
    std::vector<DWORD> indices = {
        // front face
        0, 1, 2,
        0, 2, 3,
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
            vertex.TexCord.x = mesh->mTextureCoords[0][i].x;
            vertex.TexCord.y = mesh->mTextureCoords[0][i].y;
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
