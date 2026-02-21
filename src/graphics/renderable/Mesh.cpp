#include "Mesh.h"

Mesh::Mesh(MeshGeometry* geometry, Shader* basicShader, vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector) {
    this->geometry = geometry;
	this->gpuObject = new RenderableObject();
	this->gpuObject->initVao(geometry);
	this->gpuObject->setShader(basicShader);
	this->translation = translation;
	this->rotationAxis = rotationAxis;
	this->angle = angle;
	this->scaleVector = scaleVector;
	this->computeModelMatrix();
}

Mesh::~Mesh() {
    delete this->gpuObject;
    delete this->geometry;
}

void Mesh::computeModelMatrix() {
	this->modelMatrix = translate(mat4(1.0), this->translation);
	if (this->angle != 0 && this->rotationAxis != vec3(0)) this->modelMatrix = rotate(this->modelMatrix, radians(this->angle), this->rotationAxis);
	this->modelMatrix = scale(this->modelMatrix, this->scaleVector);
}

void Mesh::render(const mat4& globalModelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos, bool showAnchor) {
	mat4 modelMatrix = globalModelMatrix * this->modelMatrix; // Apply first the local transform, next the global
	this->gpuObject->render(modelMatrix, viewMatrix, projectionMatrix, camPos, showAnchor);
}

float Mesh::distanceFromAnchor(vec3 point, vec3 direction, mat4 worldModelMatrix) {

    float intersectionDistance;
    direction = normalize(direction);

    // Compute the vector from the anchor (sphere center) to the ray origin
    vec3 anchorToPoint = point - vec3(worldModelMatrix * this->modelMatrix * vec4(this->geometry->getAnchor(), 1));
    float anchorToPointProjectionOnDirection = dot(anchorToPoint, direction);
    float cc = dot(anchorToPoint, anchorToPoint) - ANCHOR_SPERE_RADIUS * ANCHOR_SPERE_RADIUS;

    float delta = anchorToPointProjectionOnDirection * anchorToPointProjectionOnDirection - cc;

    if (delta < 0) return -1; // The ray does not intersect the sphere
    
    // Compute t values for which the ray intersects the sphere and return
    // the intersection closest to the observer (the smaller t)
    if (delta > 0.0f) {
        // Compute the two intersections
        float intersectionA = -anchorToPointProjectionOnDirection + sqrt(delta);
        float intersectionB = -anchorToPointProjectionOnDirection - sqrt(delta);
        intersectionDistance = intersectionB;

        // Case where intersections are behind the observer
        if (intersectionA < 0 && intersectionB < 0) return -1;

        return intersectionDistance;
    }

    // Case where the ray is tangent to the sphere: a double (degenerate) intersection.
    if (delta == 0) {
        float intersectionAB = -anchorToPointProjectionOnDirection + sqrt(delta);
        if (intersectionAB < 0) return -1;
        intersectionDistance = intersectionAB;
        return intersectionDistance;
    }

    return -1;
}