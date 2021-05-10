#include "Camera.h"



constexpr glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);


Camera::Camera(glm::vec3 position, glm::vec3 front) :
m_position(position),
m_front(front) {}

Camera::~Camera()
{

}

glm::mat4 Camera::getLookAt() const
{
	return glm::lookAt(m_position, m_position + m_front, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 Camera::getPosition() const
{
	return m_position;
}

glm::vec3 Camera::getFront() const
{
	return m_front;
}

void Camera::moveAlongX(float speed)
{
	m_position += glm::normalize(glm::cross(m_front, up)) * speed;
}

void Camera::moveAlongY(float speed)
{
	m_position += glm::normalize(up) * speed;
}

void Camera::moveAlongZ(float speed)
{
	m_position += glm::normalize(m_front) * speed;
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
	m_position = newPosition;
}

void Camera::setFront(glm::vec3 newFront)
{
	m_front = newFront;
}