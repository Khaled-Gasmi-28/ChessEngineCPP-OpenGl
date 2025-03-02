#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "ShaderClass.h"

using namespace glm;

class Camera
{
public:
	vec3 Position;
	vec3 Orientation = vec3(0.0f, 0.0f, -1.0f);
	vec3 Up = vec3(0.0f, 1.0f, 0.0f);

	int width;
	int height;

	bool firstClick = true;

	float speed = 0.01f;
	float sensitivity = 80.0f;

	// Frustum planes
	vec4 frustumPlanes[6];
	float maxRenderDistance = 50.0f; // Max render distance (adjust as needed)

	Camera(int width, int height, vec3 position);

	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);
	bool IsBlockInFrustum(const vec3& blockPosition, float size);
	void ExtractFrustumPlanes(const mat4& VP);

};

#endif