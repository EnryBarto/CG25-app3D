#pragma once

#include "../../libs.h"

// Avoid circular declarations since these classes are declared as friends
class GpuBuffers;
class AbstractMesh;

class MeshGeometry {

    friend class GpuBuffers;    // Needs access to vertices and colors to copy them into GPU buffers
    friend class AbstractMesh;  // Needs access to vertices to compute the bounding box

    public:
        MeshGeometry(vector<vec3>* vertices, vector<vec4>* colors, vector<uint32_t>* indexes, vector<vec3>* normals, vector<vec2>* textureCoordinates);
        MeshGeometry(vector<vec3>* vertices, vector<vec4>* colors, vector<uint32_t>* indexes, vector<vec3>* normals, vector<vec2>* textureCoordinates, vec3 anchor, vec4 anchorColor);

        // GET
        unsigned int getNumVertices();
        unsigned int getNumIndexes();
        vec3 getAnchor();

    private:
        vector<vec3> vertices;  // Vector containing the object's vertex coordinates. Each element is a vec3 (x, y, z).
        vector<vec4> colors;    // Vector containing per-vertex colors. Each element is a vec4 (r, g, b, a).
        vector<uint32_t> indexes; // Vector containing triangle indices for use with an EBO
        vec3 anchor;
        vec4 anchorColor;

        // Optional data: normals and texture coordinates
        vector<vec3> normals;   // Per-vertex normals
        vector<vec2> textureCoordinates; // Per-vertex texture coordinates
};