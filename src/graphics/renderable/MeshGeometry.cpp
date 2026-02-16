#include "MeshGeometry.h"

MeshGeometry::MeshGeometry(vector<vec3>* vertices, vector<vec4>* colors, vector<uint32_t>* indexes) : MeshGeometry(vertices, colors, indexes, NULL, NULL) {
}

MeshGeometry::MeshGeometry(vector<vec3>* vertices, vector<vec4>* colors, vector<uint32_t>* indexes, vector<vec3>* normals) : MeshGeometry(vertices, colors, indexes, normals, NULL) {
}

MeshGeometry::MeshGeometry(vector<vec3>* vertices, vector<vec4>* colors, vector<uint32_t>* indexes, vector<vec2>* textureCoordinates) : MeshGeometry(vertices, colors, indexes, NULL, textureCoordinates) {
}

MeshGeometry::MeshGeometry(vector<vec3>* vertices, vector<vec4>* colors, vector<uint32_t>* indexes, vector<vec3>* normals, vector<vec2>* textureCoordinates) {
	if (vertices->size() <= 0 || vertices->size() != colors->size() ||
		(normals->size() != NULL && normals->size() != vertices->size()) ||
		(textureCoordinates->size() != NULL && textureCoordinates->size() != vertices->size())
	) {
		throw exception();
	}

	for (int i = 0; i < vertices->size(); i++) {
		this->vertices.push_back(vertices->at(i));
		this->colors.push_back(colors->at(i));
	}

	for (int i = 0; i < indexes->size(); i++) {
		this->indexes.push_back(indexes->at(i));
	}

	if (normals != NULL) {
		for (int i = 0; i < normals->size(); i++) {
			this->normals.push_back(normals->at(i));
		}
	}

	if (textureCoordinates != NULL) {
		for (int i = 0; i < textureCoordinates->size(); i++) {
			this->textureCoordinates.push_back(textureCoordinates->at(i));
		}
	}
}

unsigned int MeshGeometry::getNumVertices() {
	return (unsigned int)this->vertices.size();
}

unsigned int MeshGeometry::getNumIndexes() {
	return (unsigned int)this->indexes.size();
}