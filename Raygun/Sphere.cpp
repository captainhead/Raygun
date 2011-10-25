#include "Sphere.h"

const float eps = 0.0001f;

Sphere::Sphere(Vector &c, float r)
{
	_c = c;
	_r = r;
}
Sphere::~Sphere()
{

}


const float pi = 3.14159;

bool Sphere::intersect(const Ray &r, float &t, Vector &p, Vector &n, float &u, float &v)
{
	Vector e_c = r.e() - _c;
	float A = r.d().dot(r.d());
	float B = r.d().dot(e_c);
	float C = e_c.dot(e_c) - _r*_r;

	// If discriminant is negative, no intersection!
	float discrim = B*B - A*C;
	if(discrim < eps)
		return false;

	// Determine nearest (lowest) intersection distance that occurs in front of the ray origin
	float sqrtDiscrim = sqrt(discrim);
	float near_t = (-B - sqrtDiscrim) / A;
	if(near_t > eps)
		t = near_t;
	else
	{
		float far_t = (-B + sqrtDiscrim) / A;
		if(far_t > eps)
		{
			t = far_t;
		}
		else
			return false;
	}
	
	p = r.e() + r.d()*t;
	n = (p-_c).normalized();

	float ph = acos(-(p.y() - _c.y()) / _r);
	float th = atan2(-(p.z() - _c.z()), p.x() - _c.x());

	u = 0.5*(th/pi) + 0.5;
	v = ph/pi;

	return true;
}