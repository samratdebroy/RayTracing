
#include <iostream>
#include "glm/glm.hpp"
#include "Scene.h"
#include "RayCaster.h"
#include "CImg/CImg.h"
#include <valarray>


using namespace std;

int main()
{
	Scene scene("scene2.txt");
	RayCaster rayCaster(&scene);

	Camera cam = scene.getCamera();
	int width = cam.focalLength * cam.aspectRatio * tan(glm::radians(cam.fov)/ 2) *2 +1;
	int height = cam.focalLength * tan(glm::radians(cam.fov) / 2) *2 +1;

	// Create Image with 3 channels to write to
	cimg_library::CImg<float> image(width, height, 1, 3, 0);

	// World Position of bottom left corner of screen
	glm::vec3 screenOrigin = glm::vec3(
		-cam.focalLength * cam.aspectRatio * tan(glm::radians(cam.fov) / 2) + cam.position.x,
		-cam.focalLength * tan(glm::radians(cam.fov) / 2) + cam.position.y,
		-cam.focalLength + cam.position.z
	);

	// Raycast through every pixel
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
		{
			// Create Ray from camera to pixel
			glm::vec3 pixelPos(screenOrigin.x + i, screenOrigin.y + j, screenOrigin.z);
			glm::vec3 dir = glm::normalize( pixelPos - cam.position);
			glm::vec3 rayColor = rayCaster.castRay(dir);

			float pixelColor[3] = { rayColor.x *255.0f,rayColor.y*255.0f, rayColor.z *255.0f };
			image.draw_point(i,height - j, pixelColor);
		}

	// Save image
	image.save("render.bmp");

	//Display the rendered image on screen
	cimg_library::CImgDisplay main_disp(image, "Render");
	while (!main_disp.is_closed())
		main_disp.wait();
};