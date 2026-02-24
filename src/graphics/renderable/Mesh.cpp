#include "Mesh.h"

Mesh::Mesh(MeshGeometry* geometry, Shader* basicShader, Material* defaultMaterial, vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector, Shader* boundingBoxShader) {
    this->geometry = geometry;
	this->gpuObject = new RenderableObject();
	this->gpuObject->initVao(geometry);
	this->gpuObject->setShader(basicShader);
	this->updateModelMatrix(translation, rotationAxis, angle, scaleVector);
    this->material = defaultMaterial;
    this->customMaterial = new Material("Custom", vec3(0.1f), vec3(1.0f, 0.2f, 0.1f), vec3(0.5f), 50);
    this->boundingBox = new BoundingBox(geometry, boundingBoxShader, vec4(0, 1, 0, 1));
}

Mesh::~Mesh() {
    delete this->gpuObject;
    delete this->geometry;
    delete this->boundingBox;
}

void Mesh::updateModelMatrix(vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector) {
    this->translation = translation;
    this->rotationAxis = rotationAxis;
    this->angle = angle;
    this->scaleVector = scaleVector;
	this->modelMatrix = translate(mat4(1.0), this->translation);
	if (this->angle != 0 && this->rotationAxis != vec3(0)) this->modelMatrix = rotate(this->modelMatrix, radians(this->angle), normalize(this->rotationAxis));
	this->modelMatrix = scale(this->modelMatrix, this->scaleVector);
}

void Mesh::render(const mat4& globalModelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos, bool showAnchor, const vector<PointLight*>* lights, bool showBoundingBox) {
	mat4 modelMatrix = globalModelMatrix * this->modelMatrix; // Apply first the local transform, next the global
	this->gpuObject->render(modelMatrix, viewMatrix, projectionMatrix, camPos, showAnchor, this->material, lights);
    if (showBoundingBox) this->boundingBox->render(modelMatrix, viewMatrix, projectionMatrix, camPos);
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

vec3 Mesh::getTranslationVector() {
    return this->translation;
}

vec3 Mesh::getRotationAxis() {
    return this->rotationAxis;
}

float Mesh::getRotationAngle() {
    return this->angle;
}

vec3 Mesh::getScaleVector() {
    return this->scaleVector;
}

void Mesh::setShader(Shader* shader) {
    this->gpuObject->setShader(shader);
}

Shader* Mesh::getCurrentShader() {
    return this->gpuObject->getCurrentShader();
}

Material* Mesh::getCurrentMaterial() {
    return this->material;
}

Texture* Mesh::getCurrentTexture() {
    return this->gpuObject->getCurrentTexture();
}

void Mesh::setTexture(Texture* texture) {
    this->gpuObject->setTexture(texture);
}

pair<vec3, vec3> Mesh::getBoundingBox() {
    vec3 localMin = this->boundingBox->getMin();
    vec3 localMax = this->boundingBox->getMax();
    
    const vector<vec3>& corners = this->boundingBox->getCorners();

    vec3 globalMin(std::numeric_limits<float>::max());
    vec3 globalMax(-std::numeric_limits<float>::max());

    // Because the mesh can be scaled and rotated we have to consider all the vertices to find the corners
    for (auto c : corners) {
        vec3 worldPos = vec3(this->modelMatrix * vec4(c, 1.0f));
        globalMin = glm::min(globalMin, worldPos);
        globalMax = glm::max(globalMax, worldPos);
    }

    return { globalMin, globalMax };
}

bool Mesh::isColliding(vec3 position, const mat4& objectModelMatrix, const mat4& objectInvertedModelMatrix) {
    // Composition of the object model matrix and the mesh model matrix
    mat4 totalModelMatrix = objectModelMatrix * this->modelMatrix;

    // WCS -> OCS positioning
    vec3 localPos = vec3(glm::inverse(this->modelMatrix) * objectInvertedModelMatrix * vec4(position, 1));

    // In the OCS the bounding box is Axis-Aligned: find the nearest point with clamping
    vec3 boundingMin = this->boundingBox->getMin();
    vec3 boundingMax = this->boundingBox->getMax();
    vec3 nearestPointLocal = glm::max(boundingMin, glm::min(localPos, boundingMax));

    // Take back the nearest point to WCS
    vec3 nearestPointWorld = vec3(totalModelMatrix * vec4(nearestPointLocal, 1));

    vec3 difference = nearestPointWorld - position;
    return glm::dot(difference, difference) <= (CAMERA_COLLISION_RADIUS * CAMERA_COLLISION_RADIUS);
}

void Mesh::setMaterial(Material* material) {
    this->material = material;
}

void Mesh::setFileLoadedMaterial(Material* material) {
    this->fileLoadedMaterial = material;
}

Material* Mesh::getFileLoadedMaterial() {
    return this->fileLoadedMaterial;
}

Material* Mesh::getCustomMaterial() {
    return this->customMaterial;
}

