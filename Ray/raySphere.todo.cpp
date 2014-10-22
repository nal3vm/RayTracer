#include <math.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include "rayScene.h"
#include "raySphere.h"
#include <iostream>


////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RaySphere::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	Point3D L = center-ray.position;
	double tca = L.dot(ray.direction);
	double d2 = L.dot(L) - pow(tca,2);
	if (d2 > pow(radius, 2)) {
		return -1;
	}

	double thc = sqrt(pow(radius,2)-d2);
	double t = tca - thc;
	double distance = (ray(t)-ray.position).length();

	if (mx > 0 && distance > mx) {
		return -1;
	}

	Point3D PminusO = ray(t)-center;
	Point3D normal = PminusO.unit();

	iInfo.normal = normal;
	iInfo.iCoordinate = ray(t);
	iInfo.material = material;

	return distance;

}

BoundingBox3D RaySphere::setBoundingBox(void){
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RaySphere::drawOpenGL(int materialIndex){
	return -1;
}
