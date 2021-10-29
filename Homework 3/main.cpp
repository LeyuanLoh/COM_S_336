#include <iostream>
#include <memory>
#include <fstream>

#include <time.h>

#include "utils.h"
#include "artist.h"

#include "surface.h"
#include "hittable.h"
#include "hittable_list.h"
#include "vec3.h"
#include "ray.h"
#include "triangle.h"
#include "camera.h"
#include "sphere.h"
#include <time.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;

//https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
const std::string currentDateTime()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y_%m_%d_%X", &tstruct);

	return buf;
}

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	std::ofstream myfile;
	//Leyuan
	std::string fileName = currentDateTime() + ".ppm";
	std::replace(fileName.begin(), fileName.end(), ':', '_');
	myfile.open(fileName.c_str());
	printf("%s\n", fileName.c_str());
	double x, y, z;
	double resolutionX = 200;
	double resolutionY = 0.75 * resolutionX;
	double colorRange = 255;

	camera cam(vec3(0, -1, 0), vec3(0, 0, 1), vec3(0, -1, 0), 120, 0.75);

	hittable_list world;
	// // world.add(make_shared<sphere>(vec3(0, 0, 12), 4, vec3::GREEN, GLASS, 0.0, 1.2));
	world.add(make_shared<sphere>(vec3(-0.5, 0, 1), 0.5, vec3::WHITE, GLASS, 0.0, 1.5));
	world.add(make_shared<sphere>(vec3(0.5, 0, 1), 0.5, vec3::WHITE, GLASS, 0.0, 1));

	world.add(make_shared<sphere>(vec3(0, 0, 10), 0.5, vec3::BLUE, DIFFUSER));
	world.add(make_shared<sphere>(vec3(-10, 0, 10), 1, vec3::BLUE, GLASS, 0.0, 2.5));
	world.add(make_shared<sphere>(vec3(-8, 0, 10), 1, vec3::AZURE, PERFECT_MIRROR));
	world.add(make_shared<sphere>(vec3(-6, 0, 10), 1, vec3::BLACK, SPECULAR, 1));
	world.add(make_shared<sphere>(vec3(-4, 0, 10), 1, vec3::CARDINAL, DIFFUSER));
	world.add(make_shared<sphere>(vec3(-2, 0, 10), 1, vec3::CHARTREUSE, DIFFUSER));
	world.add(make_shared<sphere>(vec3(0, 0, 10), 1, vec3::CYAN, SPECULAR));
	world.add(make_shared<sphere>(vec3(2, 0, 10), 1, vec3::GOLD, GLASS, 0.0, 1.7));
	world.add(make_shared<sphere>(vec3(4, 0, 10), 1, vec3::GREEN, DIFFUSER));
	world.add(make_shared<sphere>(vec3(6, 0, 10), 1, vec3::MAGENTA, SPECULAR, 4));
	world.add(make_shared<sphere>(vec3(8, 0, 10), 1, vec3::METAL, PERFECT_MIRROR));
	world.add(make_shared<sphere>(vec3(10, 0, 10), 1, vec3::CHARTREUSE, DIFFUSER));

	world.add(make_shared<sphere>(vec3(0, 100.5, 1), 100, vec3::CYAN, SPECULAR, 0.2));

	// world.add(make_shared<sphere>(vec3(0, 0, 3), 0.3, vec3::ORANGE, SPECULAR));

	// world.add(make_shared<sphere>(vec3(-12, -4, 16), 8, vec3::AZURE, DIFFUSER));
	// world.add(make_shared<sphere>(vec3(4, 0.5, 5.7), 2.2, vec3::GOLD, SPECULAR));
	// world.add(make_shared<triangle>(vec3(0, 4, -100), vec3(-1000, 4, 500), vec3(1000, 4, 500), vec3(50.0/255, 240.0/255, 250.0/255), DIFFUSER));
	// world.add(make_shared<triangle>(vec3(0, -12, 1000), vec3(-50, -12, -2), vec3(50, -12, -2), vec3(50.0/255, 240.0/255, 250.0/255)));
	// world.add(make_shared<triangle>(vec3(0, -16, 500), vec3(-50, -16, -100), vec3(50, -16, -100), vec3(250.0/255, 240.0/255, 50.0/255), DIFFUSER));

	// world.add(make_shared<triangle>(vec3(-8, 0, 16), vec3(12, 4, 8), vec3(0, 20, 8), vec3::VIOLET));

	myfile << "P3\n"
		   << resolutionX << "\n"
		   << resolutionY << "\n"
		   << colorRange << std::endl;

	// int bounce = 128;
	// int sample_rate = 2048

	int bounce = 128;
	int sample_rate = 128;

	double pixelWidth = 1 / (resolutionX - 1);
	double pixelHeight = 1 / (resolutionY - 1);

	artist graphicRender = artist(vec3(0.76078, 0.83528, 0.85490));

	cout << endl;

	
	
	double pixelY = 0;
	double pixelX = 0;

	for (int y = 0; y < resolutionY; y++)
	{
		pixelX = 0;
		printf("\r Progress %.2f percent", (pixelY * 100.0));

		for (int x = 0; x < resolutionX; x++)
		{
			ray *array = cam.getRays(pixelX, pixelY, pixelWidth * 0.9999, pixelHeight * 0.9999, sample_rate);

			myfile << (graphicRender.getPixelColor(array, sample_rate, world, 0.00000000001, double_infinity, bounce) * colorRange).toString() << endl;

			free(array);
			pixelX += pixelWidth;
		}
		pixelY += pixelHeight;
	}
	
// 	for (double pixelY = 0; pixelY < 1; pixelY += pixelHeight)
// 	{
// 		printf("\r Progress %.2f percent", (pixelY * 100.0));

// 		for (double pixelX = 0; pixelX < 1; pixelX += pixelWidth)
// 		{
// 			ray *array = cam.getRays(pixelX, pixelY, pixelWidth * 0.9999, pixelHeight * 0.9999, sample_rate);

// 			myfile << (graphicRender.getPixelColor(array, sample_rate, world, 0.00000000001, double_infinity, bounce) * colorRange).toString() << endl;

// 			free(array);
// 		}
// 	}

	printf("\r Progress 100 percent    ");

	myfile.close();
}
