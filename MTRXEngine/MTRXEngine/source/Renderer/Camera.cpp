/*
	Author: Brady Jessup
	Description: Abstracts the info for camera controls in 3D space
*/

#include <PrecompiledHeader.h>
#include "Camera.h"

// TBD: Camera rotation is sometimes broken need to debug the values generated
Camera::Camera(Window* window, const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up)
	: renderWindow(window), fov(70), nearPlane(0.01f), farPlane(1000.0f), transform(position, glm::angleAxis(0.f, up)),
	axes(forward, up, glm::fastNormalize(glm::cross(forward, up)))
{}

void Camera::Pitch(float angle)
{
	glm::quat rotation = glm::angleAxis(angle, GetSide());
	transform.Rotate(rotation);
}

void Camera::Yaw(float angle)
{
	glm::quat rotation = glm::angleAxis(angle, mtrx::worldUp);
	transform.Rotate(rotation);
}

void Camera::Roll(float angle)
{
	glm::quat rotation = glm::angleAxis(angle, GetForward());
	transform.Rotate(rotation);
}
