#include <math.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include "rayScene.h"
#include "raySpotLight.h"


////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RaySpotLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	Point3D L = (iInfo.iCoordinate - location).unit();
	double DdotL = direction.dot(L);
	if (DdotL < cos(cutOffAngle)) {
		double distance = (iInfo.iCoordinate - location).length();
		Point3D Kd = iInfo.material->diffuse;
		Point3D Il = (color*pow(DdotL, dropOffRate))/((constAtten)+(linearAtten*distance)+(quadAtten*pow(distance,2)));
		Point3D N = iInfo.normal;
		Point3D Id = Kd*(N.dot(L))*Il;
		return Id;
	} else return Point3D(0,0,0);
}
Point3D RaySpotLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	Point3D L = (iInfo.iCoordinate - location).unit();
	double DdotL = direction.dot(L);
	if (DdotL < cos(cutOffAngle)) {
		double distance = (iInfo.iCoordinate - location).length();
		double n = iInfo.material->specularFallOff;
		Point3D Ks = iInfo.material->specular;
		Point3D N = iInfo.normal;
		Point3D V = (cameraPosition - iInfo.iCoordinate).unit();
		Point3D R = N*2*(N.dot(L)) - L;
		Point3D Il = (color*pow(DdotL, dropOffRate))/((constAtten)+(linearAtten*distance)+(quadAtten*pow(distance,2)));
		Point3D Is = Ks*Il*(pow(V.dot(R), n));
		return Is;
	} else return Point3D(0,0,0);
}
int RaySpotLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	return 0;
}
Point3D RaySpotLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RaySpotLight::drawOpenGL(int index){
}
