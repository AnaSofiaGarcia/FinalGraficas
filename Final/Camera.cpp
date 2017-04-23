#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::SetOrthographic(float size, float aspectRatio) {
	float xSize = aspectRatio * size;
	_projectionMatrix = glm::ortho(-xSize, xSize, -size, size, -size, size);
}
