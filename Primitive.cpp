#include "Primitive.h"



Primitive::Primitive()
{
}

glm::vec3 Sphere::getNormal(glm::vec3& position)
{
	return position;
}

bool Sphere::intersect(Ray& ray, glm::vec3& point, float& distance)
{
	return true;
}

Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, Material* mat) :v1(v1), v2(v2), v3(v3) 
{
	material = mat;

	// Compute normal
	glm::vec3 edge1 = v2 - v1;
	glm::vec3 edge2 = v3 - v1;
	glm::vec3 normalVector = glm::cross(edge1,edge2);
	normal = glm::normalize(normalVector);
}

glm::vec3 Triangle::getNormal(glm::vec3& position)
{
	return position;
}

bool Triangle::intersect(Ray& ray, glm::vec3& point, float& distance)
{
	return true;
}

