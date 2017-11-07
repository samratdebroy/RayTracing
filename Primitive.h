#pragma once
#include "glm/glm.hpp"

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


struct Ray
{
	Ray(glm::vec3 ori, glm::vec3 dir) :
		origin(ori), direction(dir) {};

	glm::vec3 origin;
	glm::vec3 direction;
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);
};

class Primitive
{
public:
	virtual ~Primitive() = default;
	Primitive();
	virtual glm::vec3 getNormal(glm::vec3& position) =0;
	virtual bool intersect(Ray& ray, float& distance) =0;

	Material* getMaterial() { return material; }
	void setMaterial(Material* mat) { material = mat; }
protected:
	Material* material;
};

class Sphere : public Primitive
{
public:
	Sphere(glm::vec3 pos, float rad, Material* mat) :
		centerPos(pos), radius(rad) {material = mat;};
	~Sphere() {};


	glm::vec3 getNormal(glm::vec3& position) override;
	bool intersect(Ray& ray, float& distance)  override;
private:
	glm::vec3 centerPos;
	float radius;
};

class Triangle : public Primitive
{
public:
	Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, Material* mat);
	~Triangle() {};

	glm::vec3 getNormal(glm::vec3& position) override;
	bool intersect(Ray& ray, float& distance) override;
private:
	glm::vec3 v1, v2, v3;
	glm::vec3 normal;
};

class Plane : public Primitive
{
public:
	Plane(glm::vec3 pos, glm::vec3 norm, Material* mat):
	position(pos), normal(norm) {material = mat;};
	~Plane() {};

	glm::vec3 getNormal(glm::vec3& position) override;
	bool intersect(Ray& ray, float& distance) override;
private:
	glm::vec3 position;
	glm::vec3 normal;
};
