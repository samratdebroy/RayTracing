#include "RayCaster.h"


RayCaster::RayCaster(Scene* scene)
{
	this->scene = scene;
}

RayCaster::~RayCaster()
{
}

glm::vec3 RayCaster::castRay(glm::vec3 dir) const
{
	Ray ray(scene->getCamera().position, dir);

	float minDist = Scene::getFarPlaneDist();
	int closestPrimitiveIndex = -1;

	// if the ray did not intersect with anything, then return background color
	if (!rayIntersection(ray,minDist,closestPrimitiveIndex))
		return Scene::getBackgroundColor();

	// evaluate the color at the point of intersection
	auto prim = scene->getPrimitives()[closestPrimitiveIndex];
	glm::vec3 intersectionPt = ray.origin + ray.direction*minDist;
	ray.color += prim->getMaterial()->ambient; // Add material's ambient light

	// Add color contribution from every light source
	for (const auto& light : scene->getLights())
	{
		// Create new ray from intersection point to light source
		glm::vec3 vecToLight = light.position - intersectionPt;
		glm::vec3 lightDir = glm::normalize(vecToLight);
		Ray rayToLight(intersectionPt, lightDir); // TODO check if maybe ray needs to be offset from the intersection point before being cast again
		float distClosestObj;

		// If any object lies between the surface point and the light source, don't add light contribution
		if(rayIntersection(rayToLight,distClosestObj))
			if (distClosestObj < glm::length(vecToLight))
				continue;
		
		glm::vec3 normalDir = prim->getNormal(intersectionPt);
		glm::vec3 reflectionDir = glm::reflect(-lightDir, normalDir);

		float LN = glm::clamp(glm::dot(lightDir, normalDir), 0.0f, 1.0f);
		float RV = pow(glm::clamp(glm::dot(reflectionDir, -ray.direction), 0.0f, 1.0f),prim->getMaterial()->shininess);

		glm::vec3 intensity = prim->getMaterial()->diffuse * LN + prim->getMaterial()->specular * RV;
		ray.color.x += light.color.x * intensity.x;
		ray.color.y += light.color.y * intensity.y;
		ray.color.z += light.color.z * intensity.z;
	}

	return glm::clamp(ray.color,0.0f,1.0f);

}

bool RayCaster::rayIntersection(Ray& ray, float& minDist, int& closestPrimitiveIndex) const
{
	float dist;

	// Find closest intersection
	for (int i = 0; i < scene->getPrimitives().size(); i++)
	{
		if (scene->getPrimitives()[i]->intersect(ray, dist))
		{
			if (dist < minDist)
			{
				minDist = dist;
				closestPrimitiveIndex = i;
			}
		}
	}
	
	if (closestPrimitiveIndex < 0)
		return false;
	else
		return true;

}

bool RayCaster::rayIntersection(Ray& ray, float& minDist) const
{
	int closestPrimitiveIndex = -1;
	return rayIntersection(ray, minDist, closestPrimitiveIndex);
}
