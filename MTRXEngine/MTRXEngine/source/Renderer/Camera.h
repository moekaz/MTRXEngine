#pragma once

#include <Window.h>
#include <Defs.h>
#include <Input/InputSystem.h>
#include <math/Transform.h>

class Camera
{
public:
	Camera(Window* window, const glm::vec3& position = glm::vec3(), const glm::vec3& forward = mtrx::worldForward, const glm::vec3& up = mtrx::worldUp);

	inline glm::vec3 GetForward() 
	{
		axes[0] = glm::fastNormalize(transform.GetOrientation() * mtrx::worldForward); 
		return axes[0];
	}
	
	inline glm::vec3 GetSide() 
	{
		axes[1] = glm::fastNormalize(transform.GetOrientation() * mtrx::worldSide); 
		return axes[1];
	}
	
	inline glm::vec3 GetUp() 
	{
		axes[2] = glm::fastNormalize(transform.GetOrientation() * mtrx::worldUp);
		return axes[2];
	}

	inline mtrx::Transform& GetTransform() { return transform; }

	// Camera matrix calculations
	inline glm::mat4 GetProjectionMatrix() { return glm::perspective(fov, renderWindow->GetAspectRatio(), nearPlane, farPlane); }
	inline glm::mat4 GetViewMatrix() { return glm::lookAt(transform.GetPosition(), transform.GetPosition() + GetForward() * 10.f, GetUp()); }

	void Pitch(float angle);
	void Yaw(float angle);
	void Roll(float angle);

private:
	Window* renderWindow;
	float fov;
	float nearPlane, farPlane;
	mtrx::Transform transform;
	mtrx::ObjectAxes axes;
};
