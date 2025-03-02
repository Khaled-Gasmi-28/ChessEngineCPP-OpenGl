#include "Camera.h"

Camera::Camera(int width, int height, vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);

	view = lookAt(Position, Position + Orientation, Up);
	projection = perspective(radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	mat4 viewProjection = projection * view;

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, value_ptr(projection * view));

	ExtractFrustumPlanes(viewProjection); // Extract frustum planes every frame
}

// **Extract six frustum planes from the view-projection matrix**
void Camera::ExtractFrustumPlanes(const glm::mat4& VP) {
	frustumPlanes[0] = vec4(VP[0][3] + VP[0][0], VP[1][3] + VP[1][0], VP[2][3] + VP[2][0], VP[3][3] + VP[3][0]); // Left
	frustumPlanes[1] = vec4(VP[0][3] - VP[0][0], VP[1][3] - VP[1][0], VP[2][3] - VP[2][0], VP[3][3] - VP[3][0]); // Right
	frustumPlanes[2] = vec4(VP[0][3] + VP[0][1], VP[1][3] + VP[1][1], VP[2][3] + VP[2][1], VP[3][3] + VP[3][1]); // Bottom
	frustumPlanes[3] = vec4(VP[0][3] - VP[0][1], VP[1][3] - VP[1][1], VP[2][3] - VP[2][1], VP[3][3] - VP[3][1]); // Top
	frustumPlanes[4] = vec4(VP[0][3] + VP[0][2], VP[1][3] + VP[1][2], VP[2][3] + VP[2][2], VP[3][3] + VP[3][2]); // Near
	frustumPlanes[5] = vec4(VP[0][3] - VP[0][2], VP[1][3] - VP[1][2], VP[2][3] - VP[2][2], VP[3][3] - VP[3][2]); // Far

	// Normalize the planes
	for (int i = 0; i < 6; i++) {
		float length = glm::length(glm::vec3(frustumPlanes[i])) + 1.0f;
		frustumPlanes[i] /= length;
	}
}

// **Check if a block is inside the frustum**
bool Camera::IsBlockInFrustum(const vec3& blockPosition, float size) {

	// **Check if the block is within the render distance**
	if (glm::distance(Position, blockPosition) > maxRenderDistance) {
		return false; // Skip rendering if it's too far
	}

	for (int i = 0; i < 6; i++) {
		float distance = frustumPlanes[i].x * blockPosition.x +
			frustumPlanes[i].y * blockPosition.y +
			frustumPlanes[i].z * blockPosition.z +
			frustumPlanes[i].w;

		if (distance < -size) return false; // Block is outside this plane
	}
	return true;
}

void Camera::Inputs(GLFWwindow* window) {
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += speed * Orientation;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += speed * -Orientation;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += speed * -normalize(cross(Orientation,Up));
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += speed * normalize(cross(Orientation, Up));
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Position += speed * Up;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		Position += speed * -Up;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 0.01f;
	}
	else if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){
		speed = 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		maxRenderDistance += 1.0f; // Increase render distance
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		maxRenderDistance -= 1.0f; // Decrease render distance
		if (maxRenderDistance < 10.0f) maxRenderDistance = 10.0f; // Prevent extreme close-up
	}

	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick) {
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		double MouseX;
		double MouseY;
		glfwGetCursorPos(window, &MouseX, &MouseY);

		float rotX = sensitivity * (float)(MouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(MouseX - (height / 2)) / height;

		vec3 newOrientation = rotate(Orientation, radians(-rotX), normalize(cross(Orientation, Up)));

		if (!((angle(newOrientation, Up) <= radians(5.0f)) or (angle(newOrientation,-Up) <= radians(5.0f)))){
			Orientation = newOrientation;
		}

		Orientation = rotate(Orientation, radians(-rotY), Up);

		glfwSetCursorPos(window, (width / 2), (height / 2));

	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
	
}