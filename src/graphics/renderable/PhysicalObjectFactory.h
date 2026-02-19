#pragma once

#include "../shader/Shader.h"
#include "PhysicalObject.h"
#include "MeshGeometryFactory.h"

class PhysicalObjectFactory {
		
	public:
		PhysicalObjectFactory(Shader* defaultShader);
		PhysicalObject* createSimpleCube();
		PhysicalObject* createBase();

	private:
		Shader* defaultShader;
};