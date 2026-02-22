#include "MeshGeometryFactory.h"

MeshGeometry* MeshGeometryFactory::createCube() {
	vector<vec3> vertices;
	vector<vec4> colors;
	vector<GLuint> indices;
	vector<vec3> normals;
	vector<vec2> texCoords;

	vertices.push_back(vec3(-1.0, -1.0, 1.0));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	colors.push_back(vec4(1.0, 0.0, 0.0, 0.5));
	vertices.push_back(vec3(1.0, -1.0, 1.0));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	colors.push_back(vec4(0.0, 1.0, 0.0, 0.5));
	vertices.push_back(vec3(1.0, 1.0, 1.0));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	colors.push_back(vec4(0.0, 0.0, 1.0, 0.5));
	vertices.push_back(vec3(-1.0, 1.0, 1.0));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	colors.push_back(vec4(1.0, 0.0, 1.0, 0.5));

	vertices.push_back(vec3(-1.0, -1.0, -1.0));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	colors.push_back(vec4(1.0, 1.0, 1.0, 0.5));
	vertices.push_back(vec3(1.0, -1.0, -1.0));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	colors.push_back(vec4(1.0, 1.0, 1.0, 0.5));
	vertices.push_back(vec3(1.0, 1.0, -1.0));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	colors.push_back(vec4(1.0, 1.0, 1.0, 0.5));
	vertices.push_back(vec3(-1.0, 1.0, -1.0));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	colors.push_back(vec4(1.0, 1.0, 1.0, 0.5));

	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(2); indices.push_back(3); indices.push_back(0);
	indices.push_back(1); indices.push_back(5); indices.push_back(6);
	indices.push_back(6); indices.push_back(2); indices.push_back(1);
	indices.push_back(7); indices.push_back(6); indices.push_back(5);
	indices.push_back(5); indices.push_back(4); indices.push_back(7);
	indices.push_back(4); indices.push_back(0); indices.push_back(3);
	indices.push_back(3); indices.push_back(7); indices.push_back(4);
	indices.push_back(4); indices.push_back(5); indices.push_back(1);
	indices.push_back(1); indices.push_back(0); indices.push_back(4);
	indices.push_back(3); indices.push_back(2); indices.push_back(6);
	indices.push_back(6); indices.push_back(7); indices.push_back(3);

	normals.push_back(normalize(vec3(0, 0, 1)));
	normals.push_back(normalize(vec3(0, 0, 1)));
	normals.push_back(normalize(vec3(0, 0, 1)));
	normals.push_back(normalize(vec3(0, 0, 1)));
	normals.push_back(normalize(vec3(0, 0, -1)));
	normals.push_back(normalize(vec3(0, 0, -1)));
	normals.push_back(normalize(vec3(0, 0, -1)));
	normals.push_back(normalize(vec3(0, 0, -1)));

	return new MeshGeometry(&vertices, &colors, &indices, &normals, &texCoords);
}

MeshGeometry* MeshGeometryFactory::createPyramid() {
	vector<vec3> vertices;
	vector<vec4> colors;
	vector<GLuint> indices;
	vector<vec3> normals;
	vector<vec2> texCoords;

	vertices.push_back(vec3(-1.0, 0.0, 1.0));
	colors.push_back(vec4(1.0, 0.0, 0.0, 0.5));
	vertices.push_back(vec3(1.0, 0.0, 1.0));
	colors.push_back(vec4(0.0, 1.0, 0.0, 0.5));
	vertices.push_back(vec3(1.0, 0.0, -1.0));
	colors.push_back(vec4(0.0, 0.0, 1.0, 0.5));
	vertices.push_back(vec3(-1.0, 0.0, -1.0));
	colors.push_back(vec4(1.0, 1.0, 0.0, 0.5));
	vertices.push_back(vec3(0.0, 1.0, 0.0));
	colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));

    // Texture coordinates per vertex
    texCoords.push_back(vec2(0.0f, 0.0f)); // base - bottom-left
    texCoords.push_back(vec2(1.0f, 0.0f)); // base - bottom-right
    texCoords.push_back(vec2(1.0f, 1.0f)); // base - top-right
    texCoords.push_back(vec2(0.0f, 1.0f)); // base - top-left
    texCoords.push_back(vec2(0.5f, 0.5f)); // apex

	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(0); indices.push_back(2); indices.push_back(3);

	indices.push_back(0); indices.push_back(4); indices.push_back(3);
	indices.push_back(0); indices.push_back(1); indices.push_back(4);

	indices.push_back(3); indices.push_back(2); indices.push_back(4);
	indices.push_back(1); indices.push_back(2); indices.push_back(4);

	for (int i = 0; i < vertices.size(); i++) normals.push_back(vec3(0.0));

	return new MeshGeometry(&vertices, &colors, &indices, &normals, &texCoords, vec3(0, 1, 0), vec4(1));
}

MeshGeometry* MeshGeometryFactory::createPlane(vec4 color) {
	vector<vec3> vertices;
	vector<vec4> colors;
	vector<GLuint> indices;
	vector<vec3> normals;
	vector<vec2> texCoords;

	vertices.push_back(vec3(-0.5, 0.0, 0.5));
	colors.push_back(color);
	vertices.push_back(vec3(0.5, 0.0, 0.5));
	colors.push_back(color);
	vertices.push_back(vec3(0.5, 0.0, -0.5));
	colors.push_back(color);
	vertices.push_back(vec3(-0.5, 0.0, -0.5));
	colors.push_back(color);

	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(0); indices.push_back(2); indices.push_back(3);

	texCoords.push_back(vec2(0.0, 1.0));
	texCoords.push_back(vec2(1.0, 1.0));
	texCoords.push_back(vec2(1.0, 0.0));
	texCoords.push_back(vec2(0.0, 0.0));

	normals.push_back(vec3(0.0, 1.0, 0.0));
	normals.push_back(vec3(0.0, 1.0, 0.0));
	normals.push_back(vec3(0.0, 1.0, 0.0));
	normals.push_back(vec3(0.0, 1.0, 0.0));

	return new MeshGeometry(&vertices, &colors, &indices, &normals, &texCoords);
}

MeshGeometry* MeshGeometryFactory::createSphere(vec4 color) {
	vector<vec3> vertices;
	vector<vec4> colors;
	vector<GLuint> indices;
	vector<vec3> normals;
	vector<vec2> texCoords;

    float s, t;
    vec3 center = vec3(0.0, 0.0, 0.0);
    vec3 radius = vec3(1.0, 1.0, 1.0);

    int stacks = 20;  // Number of subdivisions along the Y axis
    int slices = 20;  // Number of subdivisions along the X axis

    // Calc The Vertices
    for (int i = 0; i <= stacks; ++i) {
        float V = i / (float)stacks;
        float phi = V * glm::pi<float>();

        for (int j = 0; j <= slices; ++j) {
            float U = j / (float)slices;
            float theta = U * (2.0f * glm::pi<float>());

            // Spherical coordinates
            float x = center.x + radius.x * (cosf(theta) * sinf(phi));
            float y = center.y + radius.y * cosf(phi);
            float z = center.z + radius.z * (sinf(theta) * sinf(phi));

            vertices.push_back(vec3(x, y, z));
            colors.push_back(color);

            // Normal (for unit sphere normal == position) normalized for safety
            normals.push_back(normalize(vec3(x, y, z)));

            // Texture coordinates
            s = U;
            t = V;
            texCoords.push_back(vec2(s, t));
        }
    }

    // Calc The Index Positions (two triangles per quad)
    for (int i = 0; i < stacks; ++i) {
        for (int j = 0; j < slices; ++j) {
            int first = (i * (slices + 1)) + j;
            int second = first + slices + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    return new MeshGeometry(&vertices, &colors, &indices, &normals, &texCoords);
}

MeshGeometry* MeshGeometryFactory::createTorus(vec4 color) {
	vector<vec3> vertices;
	vector<vec4> colors;
	vector<GLuint> indices;
	vector<vec3> normals;
	vector<vec2> texCoords;

	int stacks = 30;
	int slices = 30;
	float R = 1, r = 0.5;
	float s, t;

	//Calc The Vertices
	for (int i = 0; i <= stacks; ++i) {

		float V = i / (float)stacks;
		float phi = V * glm::pi <float>() * 2;

		// Loop Through Slices
		for (int j = 0; j <= slices; ++j) {

			float U = j / (float)slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = (R + r * cosf(phi)) * cosf(theta);
			float y = r * sinf(phi);
			float z = (R + r * cosf(phi)) * sinf(theta);

			// Push Back Vertex Data
			vertices.push_back(vec3(x, y, z));
			colors.push_back(color);
			// Vertex normal
			normals.push_back(vec3(normalize(vec3(sin(phi) * cos(theta), cos(phi), sin(theta) * sin(phi)))));

			// Texture coordinate
			s = U;
			t = V;
			texCoords.push_back(vec2(s, t));
		}

	}

	// Calc The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {
		indices.push_back(i);
		indices.push_back(i + slices + 1);
		indices.push_back(i + slices);

		indices.push_back(i + slices + 1);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	return new MeshGeometry(&vertices, &colors, &indices, &normals, &texCoords);
}

MeshGeometry* MeshGeometryFactory::createCone(vec4 color) {
	vector<vec3> vertices;
	vector<vec4> colors;
	vector<GLuint> indices;
	vector<vec3> normals;
	vector<vec2> texCoords;

	int stacks = 30;
	int slices = 30;
	float s, t;

	//Calc The Vertices
	for (int i = 0; i <= stacks; ++i) {

		float V = i / (float)stacks;
		float h = V;

		// Loop Through Slices
		for (int j = 0; j <= slices; ++j) {

			float U = j / (float)slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = h * cosf(theta);
			float y = h;
			float z = h * sinf(theta);

			// Push Back Vertex Data
			vertices.push_back(vec3(x, y, z));
			colors.push_back(color);
			normals.push_back(normalize(vec3(cos(theta) / sqrt(2.0f), -1 / sqrt(2.0f), sin(theta) / sqrt(2.0f))));

			// Texture coord
			s = U;
			t = V;
			texCoords.push_back(vec2(s, t));
		}
	}

	// Compute The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {

		indices.push_back(i);
		indices.push_back(i + slices + 1);
		indices.push_back(i + slices);

		indices.push_back(i + slices + 1);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	return new MeshGeometry(&vertices, &colors, &indices, &normals, &texCoords);
}

MeshGeometry* MeshGeometryFactory::createCylinder(vec4 color) {
	vector<vec3> vertices;
	vector<vec4> colors;
	vector<GLuint> indices;
	vector<vec3> normals;
	vector<vec2> texCoords;
	
    int stacks = 30;  // Number of subdivisions along the Y axis
    int slices = 30;  // Number of subdivisions along the X axis

	float s, t;
	//Calc The Vertices
	for (int i = 0; i <= stacks; ++i) {

		float V = i / (float)stacks;
		float h = V;

		// Loop Through Slices
		for (int j = 0; j <= slices; ++j) {

			float U = j / (float)slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = cosf(theta);
			float y = h;
			float z = sinf(theta);


			// Push Back Vertex Data
			vertices.push_back(vec3(x, y, z));
			colors.push_back(color);
			normals.push_back(vec3(normalize(vec3(cos(theta), 0, sin(theta)))));
			
			// Texture coord
			s = U;
			t = V;
			texCoords.push_back(vec2(s, t));
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {
		indices.push_back(i);
		indices.push_back(i + slices + 1);
		indices.push_back(i + slices);

		indices.push_back(i + slices + 1);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	return new MeshGeometry(&vertices, &colors, &indices, &normals, &texCoords);
}

MeshGeometry* MeshGeometryFactory::createFromAssimpMesh(const aiMesh* mesh) {
	vector<vec3> vertices;
	vector<vec4> colors;
	vector<GLuint> indices;
	vector<vec3> normals;
	vector<vec2> texCoords;

	// Fill vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(vec3(pos.x, pos.y, pos.z));
	}

	// Fill texture coordinates
	if (mesh->HasTextureCoords(0)) {
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D uv = mesh->mTextureCoords[0][i];
			texCoords.push_back(vec2(uv.x, uv.y));
		}
	} else {
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			texCoords.push_back(vec2(0));
		}
	}
	
	// Fill Colors
	if (mesh->HasVertexColors(0)) {
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiColor4D c = mesh->mColors[0][i];
			colors.push_back(vec4(c.r, c.g, c.b, c.a));
		}
	} else {
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			colors.push_back(vec4(0.1f, 0.5f, 1.0f, 1.0f));
		}
	}
	
	// Fill vertices normal
	if (mesh->HasNormals()) {
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D n = mesh->mNormals[i];
			normals.push_back(vec3(n.x, n.y, n.z));
		}
	} else {
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			normals.push_back(vec3(0));
		}
	}

	// Fill face indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		// Assume the model has only triangles, so 3 indices per vertex
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}

	return new MeshGeometry(&vertices, &colors, &indices, &normals, &texCoords, vertices.back(), vec4(1));
}