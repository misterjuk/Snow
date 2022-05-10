/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#ifndef MESH_H
#define MESH_H

#include <gl/glew.h>

class Mesh
{
public:
    Mesh(/* args */);
    virtual ~Mesh();
    void generateMesh(int width, int height);

    GLuint vertexbuffer() { return _vertexbuffer;}
    GLuint uvbuffer() { return _uvbuffer;}
private:
    GLuint _vertexbuffer;
    GLuint _uvbuffer;
};

#endif /* MESH_H */