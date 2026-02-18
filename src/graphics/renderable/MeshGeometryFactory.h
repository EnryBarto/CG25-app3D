#pragma once
#include "MeshGeometry.h"

class MeshGeometryFactory {

	public:
		static MeshGeometry* getCube();
		static MeshGeometry* getPyramid();
		static MeshGeometry* getPlane(vec4 color);
		static MeshGeometry* getSphere(vec4 color);
};