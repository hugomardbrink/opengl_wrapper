#include "Camera.h"



constexpr glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);


Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraFront) :
position(cameraPosition),
front(cameraFront) {}

Camera::~Camera()
{

}

glm::mat4 Camera::getLookAt() const
{
	return glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 Camera::getPosition() const
{
	return position;
}

glm::vec3 Camera::getFront() const
{
	return front;
}

void Camera::moveAlongX(float speed)
{
	position += glm::normalize(glm::cross(front, up)) * speed;
}

void Camera::moveAlongY(float speed)
{
	position += glm::normalize(up) * speed;
}

void Camera::moveAlongZ(float speed)
{
	position += glm::normalize(front) * speed;
}

void Camera::rotateYaw(float angle)
{

}

void Camera::rotatePitch(float angle)
{

}

void Camera::rotateRoll(float angle)
{

}

void Camera::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Camera::setFront(glm::vec3 newFront)
{
	front = newFront;
}