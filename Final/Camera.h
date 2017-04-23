#pragma once
#include <glm/glm.hpp>
class Camera
{
public:
	Camera();
	~Camera();
	void SetOrthographic(float size, float aspectRatio);

private:
	glm::mat4 _projectionMatrix;
};

