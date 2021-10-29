#ifndef RAY_H
#define RAY_H

#include <cmath>
#include <iostream>
#include "vec3.h"

class ray {
	private:
		//origin of the ray
		vec3 origin;
		//unit direction vector
        vec3 direction;
		//Color of the ray
		vec3 color;
		//Ray color is multiplied with the color of the objects to get the color value of the ray. Ex: (1, 1, 1) * (1, 0.5, 0) = (1, 0.5, 0)
		double intensity;
		//Refractive index of the environment the ray is in right now (Only rays generators: camera, light sources, and surface objs have refractiveIndex attribute)
		double refractiveIndex;

	public:
		//Initialize the origin, the direction using the parameters, ray's color = white (1,1,1).
		ray(const vec3 &o, const vec3 &dir, const double rIndex = 1.0){
			this->origin = o;
            this->direction = dir.unit();
			this->color = vec3(1,1,1);
			this->refractiveIndex = rIndex;
		}

		
        vec3 getOrigin();
        vec3 getDirection();
		void setColor(const vec3 &color);
		vec3 getColor();
		double getRefractiveIndex();
		void setRefractiveIndex(double newRefractiveIndex);
        vec3 eval(double t);

};

#endif