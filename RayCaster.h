#pragma once
#include "glm/glm.hpp"


struct Ray
{
	Ray(glm::vec3 ori, glm::vec3 dir) :
	origin(ori), direction(dir){};

	glm::vec3 origin;
	glm::vec3 direction;
	glm::vec3 color = glm::vec3(0.0f,0.0f,0.0f);
};

class RayCaster
{
public:
	RayCaster();
	~RayCaster();
};

