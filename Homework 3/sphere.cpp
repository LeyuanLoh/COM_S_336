#include <iostream>
#include <math.h>
#include "sphere.h"

bool sphere::hit(ray &r, double t_min, double t_max, hit_record &rec) const
{

    vec3 oc = r.getOrigin() - this->center;
    vec3 d = r.getDirection();

    double a = d.dot(d);
    double b = d.dot(oc);
    double c = oc.dot(oc) - (this->radius * this->radius);

    double discriminant = b * b - a * c;
    double root;
    double sqrt_d;

    if (discriminant < 0)
    {
        return false;
    }
    if (discriminant == 0)
    {
        root = -b/a;
    }
    else
    {
        sqrt_d = sqrt(discriminant);
        root = (-b - sqrt_d) / a;
        if (root < t_min)
        {
            root = (-b + sqrt_d) / a;

            if (root < t_min || root > t_max)
            {
                return false;
            }
        }
        else if (root > t_max)
        {
            //Because the other t value > this t value => other t value is also > t_max
            return false;
        }
    }

    rec.t = root;
    rec.p = r.eval(root);
    rec.normal = ((rec.p - this->center) / radius); //Already unit vector doesnt have to call unit()

    //If normal is poiting to the same direction as the incoming ray then flip the normal
    if (rec.normal.dot(r.getDirection()) > 0.0)
    {
        rec.normal = -1 * rec.normal;
        rec.outside = true;
    }

    rec.hitObj = (hittable *)this;

    return true;
}