/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * - OpenGL documentory is used
 */
#include "common/mesh.h"
Mesh::Mesh()
{
	_vertexbuffer = 0;
	_uvbuffer = 0;
}
Mesh::~Mesh()
{
    glDeleteBuffers(1, &_vertexbuffer);
	glDeleteBuffers(1, &_uvbuffer);
}
void Mesh::generateMesh(int width, int height)
{
	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A sprite has 1 face (quad) with 2 triangles each, so this makes 1*2=2 triangles, and 2*3 vertices
    GLfloat vertex_data[18] = {
		 0.5f * width, -0.5f * height, 0.0f,
		-0.5f * width, -0.5f * height, 0.0f,
		-0.5f * width,  0.5f * height, 0.0f,

		-0.5f * width,  0.5f * height, 0.0f,
		 0.5f * width,  0.5f * height, 0.0f,
		 0.5f * width, -0.5f * height, 0.0f
	};

	// Two UV coordinates for each vertex.
	GLfloat uv_data[12] = {
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

    glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	// Send UV's to GPU
	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv_data), uv_data, GL_STATIC_DRAW);
	
}