#pragma once
#include "glm/glm.hpp"
#include "Scene.h"

class RayCaster
{
public:
	RayCaster(Scene* scene);
	~RayCaster();

	Scene* scene;
	glm::vec3 castRay(glm::vec3 dir) const;
	bool rayIntersection(Ray& ray, float& minDist, int & closestPrimitiveIndex) const;
	bool rayIntersection(Ray& ray, float& minDist) const;
};

