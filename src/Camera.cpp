#include "Camera.h"

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget) :
position(cameraPosition),
target(cameraTarget) {}

Camera::~Camera()
{

}

glm::mat4 Camera::getLookAt()
{
	return glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::setPosX(float x)
{
	position.x = x;
}

void Camera::setPosY(float y)
{
	position.y = y;
}

void Camera::setPosZ(float z)
{
	position.z = z;
}
