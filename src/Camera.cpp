#include "Camera.h"



constexpr glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // A basic up vector


/**
 * Constructs the object
 */
Camera::Camera(glm::vec3 position, glm::vec3 front) :
m_position(position),
m_front(front) {}

/**
 * Deconstructs the object
 */
Camera::~Camera()
{

}

/**
 * Calculates and returns lookAt matrix based on stored values
 * @return the 4x4 lookAt matrix
 */
glm::mat4 Camera::getLookAt() const
{
	return glm::lookAt(m_position, m_position + m_front, glm::vec3(0.0f, 1.0f, 0.0f));
}

/**
 * @return The camera position 
 */
glm::vec3 Camera::getPosition() const
{
	return m_position;
}

/**
 * @return The camera front
 */
glm::vec3 Camera::getFront() const
{
	return m_front;
}

/**
 * Moves the camera along the x axis
 * @param The speed of which the camera moves
 */
void Camera::moveAlongX(float speed)
{
	m_position += glm::normalize(glm::cross(m_front, up)) * speed;
}

/**
 * Moves the camera along the y axis
 * @param The speed of which the camera moves
 */
void Camera::moveAlongY(float speed)
{
	m_position += glm::normalize(up) * speed;
}

/**
 * Moves the camera along the z axis
 * @param The speed of which the camera moves
 */
void Camera::moveAlongZ(float speed)
{
	m_position += glm::normalize(m_front) * speed;
}

/**
 * Rotates the camera 
 * @param pitch The pitch rotation
 * @param yaw The yaw rotation
 * @param roll The roll rotation
 */
void Camera::rotate(float pitch, float yaw, float roll)
{
	m_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_front.y = sin(glm::radians(pitch));
	m_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_front = glm::normalize(m_front);
}


/**
 * @param position The new position of the camera
 */
void Camera::setPosition(glm::vec3 position)
{
	m_position = position;
}

/**
 * @param front The new front of the camera
 */
void Camera::setFront(glm::vec3 front)
{
	m_front = front;
}