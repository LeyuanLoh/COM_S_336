#include "surface.h"
#include <iostream>

vec3 surface::getColor()
{
    return this->color;
}

void surface::setColor(const vec3 color)
{
    this->color = color;
}

double surface::getRefractiveIndex()
{
    return this->refractiveIndex;
}

void surface::setRefractiveIndex(double newRefractiveIndex)
{
    this->refractiveIndex = newRefractiveIndex;
}

ray surface::getReflectedRay(ray &r, hit_record &rec)
{
    if (this->type == SPECULAR)
        return this->getReflectedRaySpecular(r, rec);
    else if (this->type == PERFECT_MIRROR)
        return this->getReflectedRayPerfectMirror(r, rec);
    else if (this->type == GLASS)
        return this->getReflectedRayGlass(r, rec);
    else
        return this->getReflectedRayDiffuser(r, rec);
}

ray surface::getReflectedRaySpecular(ray &r, hit_record &rec)
{

    //Find the perfectly reflected direction
    vec3 i = r.getDirection();
    vec3 n = rec.normal;

    vec3 perfectlyReflected_Dir = i - 2 * n * i.dot(n);
    //making sure its reflecsted dir not refracted lol
    if (!perfectlyReflected_Dir.sameSide(rec.normal))
        perfectlyReflected_Dir = -1 * perfectlyReflected_Dir;

    //Finding the not perfectly reflected direction
    vec3 notPerfectlyReflected_Dir;

    //Create a bounding box, randomly pic one point until you get one in the sphere
    vec3 random_Dir = vec3(random_double(-1, 1), random_double(-1, 1), random_double(-1, 1));
    while (random_Dir.magnitude() > 1)
        random_Dir = vec3(random_double(-1, 1), random_double(-1, 1), random_double(-1, 1));

    //Making sure the ray is not reflecting into the intersecting plan, and also the randomness is inside the unit sphere
    //Also I multiply perfectlyReflected_Dir by 3 to make the reflection more clear, less fuzzy
    notPerfectlyReflected_Dir = perfectlyReflected_Dir + random_Dir * this->fuzziness;
    while (!notPerfectlyReflected_Dir.sameSide(rec.normal) || random_Dir.magnitude() > 1)
    {
        random_Dir = vec3(random_double(-1, 1), random_double(-1, 1), random_double(-1, 1));
        notPerfectlyReflected_Dir = perfectlyReflected_Dir + random_Dir * this->fuzziness;
    }

    return ray(rec.p, notPerfectlyReflected_Dir.to_unit());
}

ray surface::getReflectedRayPerfectMirror(ray &r, hit_record &rec)
{
    //Calculating the reflected array: https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    vec3 i = r.getDirection();
    vec3 n = rec.normal;

    vec3 reflectedDir = i - 2 * n * i.dot(n);
    //making sure its reflecsted dir not refracted lol
    if (!reflectedDir.sameSide(rec.normal))
        reflectedDir = -1 * reflectedDir;

    return ray(rec.p, reflectedDir);
}

ray surface::getReflectedRayDiffuser(ray &r, hit_record &rec)
{

    //Create a bounding box, randomly pic one point until you get one in the sphere
    vec3 randomDirection = vec3(random_double(-1, 1), random_double(-1, 1), random_double(-1, 1));
    while (randomDirection.magnitude() > 1)
        randomDirection = vec3(random_double(-1, 1), random_double(-1, 1), random_double(-1, 1));

    //Calculate that randomly reflected ray
    return ray(rec.p, (rec.normal + randomDirection).unit());
}

double schlick(double cos_incoming_angle, double refractiveIndexRatio)
{
    float t = (1 - refractiveIndexRatio) / (1 + refractiveIndexRatio);
    t = t * t;
    return t + (1 - t) * pow(1 - cos_incoming_angle, 5);
}

ray surface::getReflectedRayGlass(ray &r, hit_record &rec)
{

    //Calculating the reflected ray using Snell's law
    vec3 i = r.getDirection();
    i.to_unit();
    vec3 n = rec.normal;
    // n = i.sameSide(n) ? -n : n;
    double refractiveIndexRatio = !rec.outside ? (1.0 / rec.hitObj->getRefractiveIndex()) : rec.hitObj->getRefractiveIndex();
    // double refractiveIndexRatio = 1.0 / rec.hitObj->getRefractiveIndex();
    

    double cos_incoming_angle = (-i).dot(n);
    double sin_incoming_angle = sqrt(1 - cos_incoming_angle * cos_incoming_angle);
    //If the ray doesn't refract but reflect
    double s = schlick(cos_incoming_angle, refractiveIndexRatio);
    double random = random_double(0, 0.999999);

    if ((refractiveIndexRatio * sin_incoming_angle > 1) || random < s)
    {
        return this->getReflectedRayPerfectMirror(r, rec);
    }

    // vec3 a = refractiveIndex * (i + cos_incoming_angle * n);
    // vec3 b = -1 * sqrt(1 - a.squared_length()) * n;

    // return ray(rec.p, (a + b).unit());

    auto r_t = refractiveIndexRatio * (i + cos_incoming_angle * n);
    auto r_tt = - sqrt(abs(1.0 - r_t.squared_length())) * n;
    return ray(rec.p, (r_t + r_tt),refractiveIndex);
}