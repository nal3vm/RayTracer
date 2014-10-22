#include <math.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include "rayDirectionalLight.h"
#include "rayScene.h"
#include <iostream>

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayDirectionalLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	Point3D L = -direction.unit();
	Point3D Kd = iInfo.material->diffuse;
	Point3D Il = color;
	Point3D N = iInfo.normal;
	Point3D Id = Kd*(N.dot(L))*Il;
	return Id;
}
Point3D RayDirectionalLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	double n = iInfo.material->specularFallOff;
	Point3D L = direction.unit();
	Point3D Ks = iInfo.material->specular;
	Point3D N = iInfo.normal;
	Point3D V = (cameraPosition - iInfo.iCoordinate).unit();
	Point3D R = N*2*(N.dot(L)) - L;
	Point3D Il = color;
	Point3D Is = Ks*Il*(pow(V.dot(R), n));
	return Is;
}
int RayDirectionalLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	return 0;
}
Point3D RayDirectionalLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RayDirectionalLight::drawOpenGL(int index){
}
