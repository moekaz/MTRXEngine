/*
	Author: Brady Jessup
	Description: Abstracts the info for camera controls in 3D space
*/

#pragma once

#include <Window.h>
#include <Defs.h>
#include <Input/InputSystem.h>

class Camera
{
public:
	Camera(Window* window, const glm::vec3& position = glm::vec3(), const glm::vec3& forward = glm::vec3(0, 0, -1.f), const glm::vec3& up = glm::vec3(0, 1.f, 0));

	inline glm::vec3 GetForward() { return glm::normalize(orientation * forward); }
	inline glm::vec3 GetSide() { return glm::normalize(orientation * side); }
	inline glm::vec3 GetUp() { return glm::normalize(orientation * up); }
	
	void UpdateCamera(float deltaTime);

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();
	void Pitch(float angle);
	void Yaw(float angle);
	void Roll(float angle);

private:
	Window* renderWindow;

	float fov;
	float nearPlane, farPlane;
	
	glm::vec3 position;
	glm::vec3 forward; // Normal vector for forward direction of the camera
	glm::vec3 up; // Normal vector up vector of the camera
	glm::vec3 side; // normal vector side vector of camera
	glm::quat orientation; // Camera orientation
};
