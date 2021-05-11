#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/**
 * Handles the camera that views the "scene", a view matrix in actuality
 */
class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 front);
	~Camera();

	glm::mat4 getLookAt() const;
	glm::vec3 getPosition() const;
	glm::vec3 getFront() const;

	void moveAlongX(float speed);
	void moveAlongY(float speed);
	void moveAlongZ(float speed);
	void rotate(float pitch, float yaw, float roll);

	void setPosition(glm::vec3 newPosition);
	void setFront(glm::vec3 newFront);

private:
	glm::vec3 m_position;
	glm::vec3 m_front;


};

