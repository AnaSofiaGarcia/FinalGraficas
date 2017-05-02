#pragma once

#include "Ray.h"
#include "Transform.h"
#include<glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
#include <string>

class Camera : public Transform{
private:
	Ray _camPos;
	Ray _camDir;
	Ray _camRight;
	Ray _camDown;

	Transform _transform;
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;

public:
	Camera();
	Camera(Ray, Ray, Ray, Ray);

	Ray getCameraPosition();
	Ray getCameraDirection();
	Ray getCameraRight();
	Ray getCameraDown();


	void SetOrthographic(float size, float aspectRatio);

	glm::vec3 GetPosition();
	glm::mat4 GetViewProjection();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	void SetPosition(float x, float y, float z);
	void SetPosition(glm::vec3 position);
	void SetRotation(float x, float y, float z);
	void SetRotation(glm::vec3 rotation);

	void MoveForward(float delta, bool world = false);
	void MoveUp(float delta, bool world = false);
	void MoveRight(float delta, bool world = false);


	void Yaw(float degrees);
	void Pitch(float degrees);
	void Roll(float degrees);

	void Rotate(float x, float y, float z, bool world);

	void SetPerspective(float nearPlane, float farPlane, float fieldOfView, float aspectRatio);
};

