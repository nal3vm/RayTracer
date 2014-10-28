#include <stdlib.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include "rayGroup.h"
#include <iostream>

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	RayIntersectionInfo temp;
	double retTime = -1;
	double retDistance = -1;

	Matrix4D mat = getInverseMatrix();
	Ray3D transformedRay;
	transformedRay.position = mat.multPosition(ray.position);
	transformedRay.direction = mat.multDirection(ray.direction).unit();

	for (int i = 0; i < sNum; i++) {
		double respTime = shapes[i]->intersect(transformedRay, iInfo, retTime);
		if (respTime < 0) {
			continue;
		}
		iInfo.iCoordinate = getMatrix().multPosition(iInfo.iCoordinate);
		iInfo.normal = (getMatrix().multNormal(iInfo.normal)).unit();

		double distance = (iInfo.iCoordinate - ray.position).length();
		if (distance < retDistance || retDistance < 0) {
			retDistance = distance;
			retTime = respTime;
			temp = iInfo;
		}
	}

	iInfo = temp;
	return retTime;
}

BoundingBox3D RayGroup::setBoundingBox(void){
	return bBox;
}

int StaticRayGroup::set(void){
	inverseTransform = localTransform.invert();
	Matrix4D transposeTransform = localTransform.transpose();
	normalTransform = transposeTransform.invert();
	return 1;
}
//////////////////
// OpenGL stuff //
//////////////////
int RayGroup::getOpenGLCallList(void){
	return 0;
}

int RayGroup::drawOpenGL(int materialIndex){
	return -1;
}

/////////////////////
// Animation Stuff //
/////////////////////
Matrix4D ParametrizedEulerAnglesAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedClosestRotationAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedRotationLogarithmAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedQuaternionAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
