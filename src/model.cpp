#include "model.hpp"
#include "util.hpp"
#include <iostream>
#include <string>
// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model::Model() {
    m_attribCount=0;
    m_aTexCoords=-1;
}

void Mesh::draw() {
    // Bind & Configure VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER, verts.size()*sizeof(Vertex), verts.data(), GL_STATIC_DRAW
    );
    // Bind & Configure EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint), indices.data(), GL_STATIC_DRAW
    );
    // Bind & Configure VAO
    glBindVertexArray(VAO);
    // POSITION (location = 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, position)
    );
    // TEXCOORD (location = 1)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, texCoords)
    );

    // NORMAL (location = 2)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        2,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, normal)
    );
    // Draw the Mesh
    glDrawArrays(GL_TRIANGLES, 0, verts.size());
}

Mesh::Mesh(const std::string& pFile) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    std::cout << GREEN("Assimp Errors and stuff:") << std::endl;
    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(pFile,
        aiProcess_Triangulate           |
        aiProcess_GenNormals            |
        aiProcess_JoinIdenticalVertices// |
        //aiProcess_CalcTangentSpace      |
        //aiProcess_SortByPType
    );
    if (nullptr == scene) {
      std::cout << RED("ERROR: ") << importer.GetErrorString() << std::endl;
    }
    if (!scene || !scene->HasMeshes()) {
      std::cout << RED("ERROR: ") << (std::string)importer.GetErrorString() << std::endl;
    }
    std::cout << GREEN("INFO: ") << scene->mNumMeshes << std::endl;
    mesh = scene->mMeshes[0];
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        // positions
        vertex.position = {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        };

        // normals
        if (mesh->HasNormals()) {
            vertex.normal = {
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z
            };
        } else {
            vertex.normal = {0.0f, 0.0f, 0.0f};
        }

        // texture coords (if any)
        if (mesh->HasTextureCoords(0)) {
            vertex.texCoords = {
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            };
        } else {
            vertex.texCoords = {0.0f, 0.0f};
        }

        verts.push_back(vertex);
    }
    
    // walk through faces (triangles assumed) to get indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        if (face.mNumIndices < 3) continue;
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
}
