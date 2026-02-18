#include "MeshGeometryFactory.h"

MeshGeometry* MeshGeometryFactory::getCube() {
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

MeshGeometry* MeshGeometryFactory::getPyramid() {
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

    // texture coordinates per vertex
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

	for (int i = 0; i < vertices.size(); i++)
		normals.push_back(vec3(0.0));

	return new MeshGeometry(&vertices, &colors, &indices, &normals, &texCoords);
}

MeshGeometry* MeshGeometryFactory::getPlane(vec4 color) {
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

MeshGeometry* MeshGeometryFactory::getSphere(vec4 color) {
	vector<vec3> vertices;
	vector<vec4> colors;
	vector<GLuint> indices;
	vector<vec3> normals;
	vector<vec2> texCoords;

    float s, t;
    vec3 center = vec3(0.0, 0.0, 0.0);
    vec3 radius = vec3(1.0, 1.0, 1.0);

    int stacks = 20;  // number of subdivisions along the Y axis
    int slices = 20;  // number of subdivisions along the X axis

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
