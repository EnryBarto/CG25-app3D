#pragma once
#include "MeshGeometry.h"

class MeshGeometryFactory {

	public:
		static MeshGeometry* createCube();
		static MeshGeometry* createPyramid();
		static MeshGeometry* createPlane(vec4 color);
		static MeshGeometry* createSphere(vec4 color);
};