#include <math.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include "rayPointLight.h"
#include "rayScene.h"
#include <iostream>

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayPointLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	double distance = (iInfo.iCoordinate - location).length();
	Point3D L = (iInfo.iCoordinate - location).unit();
	Point3D Kd = iInfo.material->diffuse;
	Point3D Il = color/((constAtten)+(linearAtten*distance)+(quadAtten*pow(distance,2)));
	Point3D N = iInfo.normal;
	Point3D Id = Kd*(N.dot(L))*Il;
	return Id;
}
Point3D RayPointLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	double distance = (iInfo.iCoordinate - location).length();
	double n = iInfo.material->specularFallOff;
	Point3D L = (iInfo.iCoordinate - location).unit();
	Point3D Ks = iInfo.material->specular;
	Point3D N = iInfo.normal;
	Point3D V = (cameraPosition - iInfo.iCoordinate).unit();
	Point3D R = L - N*L.dot(N)*2;
	Point3D Il = color/((constAtten)+(linearAtten*distance)+(quadAtten*pow(distance,2)));
	Point3D Is = Ks*Il*(pow(V.dot(R), n));
	return Is;
}
int RayPointLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	Point3D p0 = iInfo.iCoordinate;
	Point3D dir = location.unit().negate();
	Point3D epsilon(0.00001, 0.00001, 0.00001);
	epsilon = dir*epsilon;
	p0 = p0+epsilon;
	Ray3D ray(p0, dir);
	double dist = shape->intersect(ray, iInfo, -1);
	if (dist > 0) {
		return 0;
	}
	return 1;
}
Point3D RayPointLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}


//////////////////
// OpenGL stuff //
//////////////////
void RayPointLight::drawOpenGL(int index){
}
