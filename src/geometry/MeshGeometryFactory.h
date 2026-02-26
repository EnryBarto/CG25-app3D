#pragma once

#include <glm/glm.hpp>
#include <assimp/mesh.h>

#include "MeshGeometry.h"

using namespace glm;

class MeshGeometryFactory {

	public:
		static MeshGeometry* createCube(vec4 color);
		static MeshGeometry* createPyramid(vec4 color);
		static MeshGeometry* createPlane(vec4 color);
		static MeshGeometry* createTriangulatedPlane(int n, vec4 color);
		static MeshGeometry* createSphere(vec4 color);
		static MeshGeometry* createTorus(vec4 color);
		static MeshGeometry* createCone(vec4 color);
		static MeshGeometry* createCylinder(vec4 color);
		static MeshGeometry* createFromAssimpMesh(const aiMesh* mesh);
		static MeshGeometry* createBoundingBox(vec3 min, vec3 max, vec4 color);
};