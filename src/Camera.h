#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera
{
public:
	Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget);
	~Camera();
	glm::mat4 getLookAt();
	void setPosX(float x);
	void setPosY(float y);
	void setPosZ(float z);

private:
	glm::vec3 position;
	glm::vec3 target;


};

