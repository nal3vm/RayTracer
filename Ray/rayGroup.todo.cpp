#include <stdlib.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include "rayGroup.h"
#include <iostream>
#include <algorithm>

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

	int hitCount = 0;
	for (int i = 0; i < sNum; i++) {

		double resp = shapes[i]->bBox.intersect(transformedRay);
		if (resp < 0){continue;}
		else {
			RayShapeHit hit;
			hit.t = resp;
			hit.shape = shapes[i];
			hits[hitCount] = hit;
			hitCount++;
		}
	}

	for (int i = 1; i < hitCount; i++) {
		int j = i;
		while (j > 0 && hits[j-1].t > hits[j].t) {
			std::swap(hits[j-1],hits[j]);
		}
	}

	for (int i = 0; i < hitCount; i++) {
		if (hits[i].shape->bBox.intersect(transformedRay) < 0){continue;}
		double respTime = hits[i].shape->intersect(transformedRay, iInfo, retTime);
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
	for (int i = 0; i < sNum; i++) {
		shapes[i]->setBoundingBox();
	}
	bBox.p[0] = shapes[0]->bBox.p[0];
	bBox.p[1] = shapes[0]->bBox.p[1];
	for (int i = 0; i < sNum; i++) {
		BoundingBox3D shapeBox = shapes[i]->bBox.transform(getMatrix());
		if(shapeBox.p[0][0] < bBox.p[0][0]){bBox.p[0][0]=shapeBox.p[0][0];}
		if(shapeBox.p[0][1] < bBox.p[0][1]){bBox.p[0][1]=shapeBox.p[0][1];}
		if(shapeBox.p[0][2] < bBox.p[0][2]){bBox.p[0][2]=shapeBox.p[0][2];}
		if(shapeBox.p[1][0] > bBox.p[1][0]){bBox.p[1][0]=shapeBox.p[1][0];}
		if(shapeBox.p[1][1] > bBox.p[1][1]){bBox.p[1][1]=shapeBox.p[1][1];}
		if(shapeBox.p[1][2] > bBox.p[1][2]){bBox.p[1][2]=shapeBox.p[1][2];}
	}

/*	std::cout << "<";
	std::cout << bBox.p[0][0];
	std::cout << ",";
	std::cout << bBox.p[0][1];
	std::cout << ",";
	std::cout << bBox.p[0][2];
	std::cout << ">";
	std::cout << "  --  ";

	std::cout << "<";
	std::cout << bBox.p[1][0];
	std::cout << ",";
	std::cout << bBox.p[1][1];
	std::cout << ",";
	std::cout << bBox.p[1][2];
	std::cout << ">";
	std::cout << "\n";*/

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
	glPushMatrix();
	Matrix4D mat = getMatrix();
	GLdouble input[16] = {GLdouble(mat(0,0)), GLdouble(mat(0,1)), GLdouble(mat(0,2)), GLdouble(mat(0,3)), GLdouble(mat(1,0)), GLdouble(mat(1,1)), GLdouble(mat(1,2)), GLdouble(mat(1,3)), GLdouble(mat(2,0)), GLdouble(mat(2,1)), GLdouble(mat(2,2)), GLdouble(mat(2,3)), GLdouble(mat(3,0)), GLdouble(mat(3,1)), GLdouble(mat(3,2)), GLdouble(mat(3,3))};
	glMultMatrixd(input);
	for (int i = 0; i < sNum; i++) {
		shapes[i]->drawOpenGL(-1);
	}
	glPopMatrix();
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
