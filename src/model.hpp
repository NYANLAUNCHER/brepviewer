#pragma once
#include "shader.hpp"
#include "texture.hpp"
// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;
};

class Mesh {
private:
    unsigned int VAO, VBO, EBO;
    aiMesh* mesh;
    std::vector<Vertex> verts;
    std::vector<unsigned int> indices;
public:
    Mesh(const std::string& pFile);
    ~Mesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    void draw();
};

// Defines a single vertex attribute
// NOTE: does not contain an index specifier
typedef struct vertex_attrib {
    GLint size;// component count
    GLenum type;
    GLsizei stride;// same as in glVertexAttribPointer
    const GLvoid* pointer;// same as in glVertexAttribPointer
}vertex_attrib;

class Model {
private:
    ///@brief Vertices are homogeneous, meaning the share the same size and layout
    float* m_vertices;
    uint m_attribCount;
    vertex_attrib* m_attribs;// list of vertex attributes
    bool m_textureEnabled;
    // attrib index for texture coordinates
    int m_aTexCoords;// enables m_texture for valid range in m_attribs
    Texture* m_texture;
public:
    ///@details
    /// Vertices must be homogeneous, meaning they have the same size and layout
    Model();
    ///@brief Move model in world space
    void move(glm::vec3 position);
    ///@brief Scale model from its origin point
    void scale(glm::vec3 scale);
    ///@brief Rotate model around an axis pointing through its origin
    void rotate(glm::vec3 axis, double radians);
    ///@brief Append an attribute layout to 
    ///@param size Number of components in the attribute
    ///@param offset Offset from beginning of vertex
    void addAttribLayout(uint size, uint offset);
    ///@brief Same as addAttribLayout, but manually specify attribute index
    ///@param index The per-vertex index of the attribute
    ///@param size Number of components in the attribute
    ///@param offset Offset from beginning of vertex
    void setAttribLayout(int index, uint size, uint offset);
    ///@brief Set the attribute index for texture coordinates
    void aTexCoords(uint index);
    // ERROR!!! This function has yet to be implemented.
    ///@brief Bind an existing texture for this model to use.
    ///@param texCoordIndex The attribute index for texture coordinates.
    ///@param texture Reference to existing Texture.
    void useTexture(uint texCoordIndex, Texture& texture);
    // ERROR!!! This function has yet to be implemented.
    ///@brief Creates texture internally using Texture::Texture().
    void loadTexture();
};
