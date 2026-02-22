#pragma once
#include "MeshGeometry.h"
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

class MeshGeometryFactory {

	public:
		static MeshGeometry* createCube();
		static MeshGeometry* createPyramid();
		static MeshGeometry* createPlane(vec4 color);
		static MeshGeometry* createSphere(vec4 color);
		static MeshGeometry* createTorus(vec4 color);
		static MeshGeometry* createCone(vec4 color);
		static MeshGeometry* createCylinder(vec4 color);
		static MeshGeometry* createFromAssimpMesh(const aiMesh* mesh);
};