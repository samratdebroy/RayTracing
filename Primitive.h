#pragma once
#include "glm/glm.hpp"
#include "RayCaster.h"

struct Material
{
	// Constructor
	Material(glm::vec3 amb, glm::vec3 dif, glm::vec3 spec, float shin) :
		ambient(amb), diffuse(dif), specular(spec), shininess(shin) {};

	glm::vec3 ambient;	// ambient color
	glm::vec3 diffuse;	// diffuse color
	glm::vec3 specular;	// specular color
	float shininess;	// specular shininess factor
};

class Primitive
{
public:
	virtual ~Primitive() = default;
	Primitive();
	virtual glm::vec3 getNormal(glm::vec3& position) =0;
	virtual bool intersect(Ray& ray, glm::vec3& point, float& distance) =0;

	Material* getMaterial() { return material; }
	void setMaterial(Material* mat) { material = mat; }
protected:
	Material* material;
};

class Sphere : public Primitive
{
public:
	Sphere(glm::vec3 pos, float rad, Material* mat) :
		position(pos), radius(rad) {material = mat;};
	~Sphere() {};


	glm::vec3 getNormal(glm::vec3& position) override;
	bool intersect(Ray& ray, glm::vec3& point, float& distance)  override;
private:
	glm::vec3 position;
	float radius;
};

class Triangle : public Primitive
{
public:
	Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, Material* mat);
	~Triangle() {};

	glm::vec3 getNormal(glm::vec3& position) override;
	bool intersect(Ray& ray, glm::vec3& point, float& distance) override;
private:
	glm::vec3 v1, v2, v3;
	glm::vec3 normal;
};

