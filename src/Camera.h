#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera
{
public:
	Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget);
	~Camera();

	glm::mat4 getLookAt() const;
	glm::vec3 getPosition() const;
	glm::vec3 getFront() const;

	void moveAlongX(float speed);
	void moveAlongY(float speed);
	void moveAlongZ(float speed);
	void rotateYaw(float angle);
	void rotatePitch(float angle);
	void rotateRoll(float angle);


	void setPosition(glm::vec3 newPosition);
	void setFront(glm::vec3 newFront);

private:
	glm::vec3 position;
	glm::vec3 front;


};

