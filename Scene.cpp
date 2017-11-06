#include "Scene.h"

Scene::Scene(string path)
{
	parseScene(path);
}


bool Scene::parseScene(string path)
{
	//// Get lines from text file ////
	string nextLine;
	string completePath = PATH_HOME + path;
	ifstream textFile(completePath.c_str());
	if (textFile.is_open())
	{
		// Get the number of objects in the scene from the first line
		if(getline(textFile, nextLine))
		{
			// Get number of materials that will be used in scene
			int numMaterials = stoi(nextLine);
			materials.reserve(numMaterials);
		};

		// Get every line from the text file
		while (getline(textFile, nextLine))
		{
			if (nextLine == "camera")
				parseCamera(textFile);
			else if (nextLine == "light")
				parseLight(textFile);
			else if (nextLine == "sphere")
				parseSphere(textFile);
			else if (nextLine == "model")
				parseModel(textFile);
			else if (nextLine == "triangle")
				parseTriangle(textFile);
		}
		textFile.close();
		return true;
	}
	return false;
}

void Scene::parseCamera(ifstream& textFile)
{
	string nextLine;

	// Set up camera parameters
	glm::vec3 pos;
	float fov, focalLength, aspectRatio;

	// position
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "pos: %f %f %f", &pos.x, &pos.y, &pos.z);

	// field of view
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "fov: %f", &fov);

	// focal Length
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "f: %f", &focalLength);

	// Aspect Ratio
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "a: %f", &aspectRatio);

	// Create Camera Object
	Camera tempCam(pos, fov, focalLength, aspectRatio);
	camera = tempCam;
}

void Scene::parseLight(ifstream& textFile)
{
	string nextLine;

	// Set up Light parameters
	glm::vec3 pos, col;

	// position
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "pos: %f %f %f", &pos.x, &pos.y, &pos.z);

	// color
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "col: %f %f %f", &col.x, &col.y, &col.z);
	
	// Create Light Object and push it to vector
	Light tempLight(pos, col);
	lights.push_back(tempLight);
}

void Scene::parseSphere(ifstream& textFile)
{
	string nextLine;

	// Set up Sphere parameters
	glm::vec3 pos, amb, dif, spe;
	float radius, shi;

	// position
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "pos: %f %f %f", &pos.x, &pos.y, &pos.z);

	// radius
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "rad: %f", &radius);

	// Material
	Material* tempMat = parseMaterial(textFile, amb, dif, spe, shi);

	// Create Sphere and push to primitives vector
	primitives.push_back(make_shared<Sphere>(pos, radius, tempMat));
}

void Scene::parseTriangle(ifstream& textFile)
{
	string nextLine;

	// Set up Sphere parameters
	glm::vec3 amb, dif, spe, v1, v2, v3;
	float shi;

	// vertexes
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "v1: %f %f %f", &v1.x, &v1.y, &v1.z);
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "v2: %f %f %f", &v2.x, &v2.y, &v2.z);
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "v3: %f %f %f", &v3.x, &v3.y, &v3.z);

	// Material
	Material* tempMat = parseMaterial(textFile, amb, dif, spe, shi);

	// Create Sphere and push to primitives vector
	primitives.push_back(make_shared<Triangle>(v1,v2,v3, tempMat));
}

void Scene::parseModel(ifstream& textFile)
{
	string nextLine;

	// Set up Model parameters
	glm::vec3 amb, dif, spe;
	float shi;
	string modelPath;

	// FilePath of .obj file
	getline(textFile, nextLine);
	modelPath = PATH_HOME + nextLine;

	// Material to be shared by all the primitives in the model
	Material* tempMat = parseMaterial(textFile, amb, dif, spe, shi);

	// Create all the triangle primitives
	ObjLoader::loadOBJ(modelPath.c_str(), primitives, tempMat);
}

Material* Scene::parseMaterial(ifstream& textFile, glm::vec3& amb, glm::vec3& dif, glm::vec3& spe, float& shi)
{
	string nextLine;

	// Ambient
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "amb: %f %f %f", &amb.x, &amb.y, &amb.z);

	// Diffuse
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "dif: %f %f %f", &dif.x, &dif.y, &dif.z);

	// Specular
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "spe: %f %f %f", &spe.x, &spe.y, &spe.z);

	// Shininess
	getline(textFile, nextLine);
	sscanf_s(nextLine.c_str(), "shi: %f", &shi);

	// Create Material
	Material tempMat(amb, dif, spe, shi);
	materials.push_back(tempMat);
	return &materials.back();
}
