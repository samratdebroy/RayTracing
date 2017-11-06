#include "Primitive.h"



Primitive::Primitive()
{
}

glm::vec3 Sphere::getNormal(glm::vec3& position)
{
	// where position is a point on the surface of the sphere
	return glm::normalize(position - centerPos);
}

bool Sphere::intersect(Ray& ray, float& distance)
{

	glm::vec3 OC = ray.origin - centerPos; // vector from center of the sphere to origin of ray

	// Get parameters of equation f(x) = at^2 + bt + c
	float a = 1; // because the directional vector of the ray should be unit length
	float b = 2 * glm::dot(ray.direction, OC);	// 2*D.OC
	float c = glm::dot(OC, OC) - radius*radius;	// OC^2 - r^2 

	// Two step values at which there may be an intersection
	float t0, t1;

	// Solve the quadratic
	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) t0 = t1 = -0.5 * b / a;
	else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		t0 = q / a;
		t1 = c / q;
	}

	// Distance is equal to the closest positive value
	distance = -1;
	if (t0 > 0 && t1 > 0)
		distance = (t0 > t1) ? t1 : t0;
	else if (t0 > 0 && t1 < 0)
		distance = t0;
	else if (t0 < 0 && t1 > 0)
		distance = t1;
	else
		return false;	// false if both solutions were negative


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

bool Triangle::intersect(Ray& ray, float& distance)
{
	return true;
}

