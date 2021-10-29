#include "utils.h"


double random_double(){
    return  ((double)rand() / ((double)RAND_MAX + 1.0));
}

double random_double(double min, double max){
    return min + (max - min) * random_double();
}

//Leyuan
vec3 clamp(vec3 vec, double min, double max)
{
    double x = vec.x();
    double y = vec.y();
    double z = vec.z();
    if (vec.x() < min)
    {
        x = min;
    }
    else if (vec.x() > max)
    {
        x = max;
    }
    if (vec.y() < min)
    {
        y = min;
    }
    else if (vec.y() > max)
    {
        y = max;
    }
    if (vec.z() < min)
    {
        z = min;
    }
    else if (vec.z() > max)
    {
        z = max;
    }
    return vec3(x, y, z);
}