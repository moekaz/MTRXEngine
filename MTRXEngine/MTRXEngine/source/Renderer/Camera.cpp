/*
	Author: Brady Jessup
	Description: Abstracts the info for camera controls in 3D space
*/

#include <PrecompiledHeader.h>
#include "Camera.h"

Camera::Camera(Window* window, const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up)
	: renderWindow(window), fov(90), nearPlane(0.01f), farPlane(1000.0f), position(position), forward(forward), up(up),
	side(glm::normalize(glm::cross(forward, up))), orientation(glm::angleAxis(0.f, up))
{}

void Camera::UpdateCamera(float deltaTime)
{
	// Camera movement
	if (mtrx::InputSystem::GetKey(GLFW_KEY_W))
		position += GetForward() * deltaTime * 2.f;
	if (mtrx::InputSystem::GetKey(GLFW_KEY_A))
		position += -GetSide() * deltaTime * 2.f;
	if (mtrx::InputSystem::GetKey(GLFW_KEY_S))
		position += -GetForward() * deltaTime * 2.f;
	if (mtrx::InputSystem::GetKey(GLFW_KEY_D))
		position += GetSide() * deltaTime * 2.f;

	// Camera rotation
	if (mtrx::InputSystem::yOffset != 0.000001)
		Pitch((float)mtrx::InputSystem::yOffset * deltaTime);
	if (mtrx::InputSystem::xOffset != 0.000001)
		Yaw(-(float)mtrx::InputSystem::xOffset * deltaTime);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(fov, renderWindow->GetAspectRatio(), nearPlane, farPlane);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + GetForward(), GetUp());
}

void Camera::Pitch(float angle)
{
	glm::quat rotation = glm::angleAxis(angle, GetSide());
	orientation = rotation * orientation;
}

void Camera::Yaw(float angle)
{
	glm::quat rotation = glm::angleAxis(angle, mtrx::worldUp);
	orientation = rotation * orientation;
}

void Camera::Roll(float angle)
{
	glm::quat rotation = glm::angleAxis(angle, GetForward());
	orientation = rotation * orientation;
}
