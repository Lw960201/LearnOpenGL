#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include <gl/glew.h>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string paht;
};

class Mesh
{
public:
	Mesh(float vertices[]);
	Mesh(std::vector<Vertex> vertices,std::vector<unsigned int> indices,	std::vector<Texture> textures);
	~Mesh();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	void Draw(Shader* shader);

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

