#pragma once

#include "Primitive.h"
#include <vector>
#include<fstream>
#include<sstream>
#include <memory>
#include "objloader.h"

using namespace std;

struct Camera
{
	Camera() :position(glm::vec3(0, 0, 0)), fov(45), focalLength(1000), aspectRatio(1.33f) {};
	Camera(glm::vec3 pos, float fView, float fLength, float aspect) :
		position(pos), fov(fView), focalLength(fLength), aspectRatio(aspect) {};

	glm::vec3 position;
	float fov;			// field of view angle
	float focalLength;
	float aspectRatio;
};

struct Light
{
	Light(glm::vec3 pos, glm::vec3 col) :
		position(pos), color(col) {};

	glm::vec3 position;
	glm::vec3 color;	// normalized
};


class Scene
{
public:
	Scene(string path);

	const Camera& getCamera() const { return camera; }
	const vector<shared_ptr<Primitive> >&  getPrimitives() const { return primitives; }
	const vector<Light>&  getLights() const { return lights; }

	static float getFarPlaneDist() { return 9999.0f; }
	static glm::vec3 getBackgroundColor() { return glm::vec3(0.0f,0.0f,0.0f); }

private:
	Camera camera;
	vector<Light> lights;
	vector<shared_ptr<Primitive> > primitives;
	vector<Material> materials;

	bool parseScene(string path);
	void parseCamera(ifstream& textFile);
	void parseLight(ifstream& textFile);
	void parseSphere(ifstream& textFile);
	void parseTriangle(ifstream& textFile);
	void parseModel(ifstream& textFile);
	Material* parseMaterial(ifstream& textFile, glm::vec3& amb, glm::vec3& dif, glm::vec3& spe, float& shi);

	string const PATH_HOME = "scene_files/scene_files/";
};

