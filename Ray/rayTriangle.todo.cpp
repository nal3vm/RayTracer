#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayTriangle.h"
#include <iostream>

////////////////////////
//  Ray-tracing stuff //
////////////////////////
void RayTriangle::initialize(void){
	plane = Plane3D(v[0]->position, v[1]->position, v[2]->position);

}
double RayTriangle::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){

	plane = Plane3D(v[0]->position, v[1]->position, v[2]->position);
	double t = (ray.position.dot(plane.normal.unit())+plane.distance)*-1/(ray.direction.dot(plane.normal));
	if (t < 0) {
		return -1;
	}
	double distance = (ray.direction*t-ray.position).length();

	if (mx > 0 && t > mx) {
		return -1;
	}

	v1 = v[0]->position - ray.position;
	v2 = v[1]->position - ray.position;
	Point3D norm = v2.crossProduct(v1).unit();
	Point3D p = ray.position + ray.direction*t;

	if ((p-ray.position).dot(norm) < 0) {
		return -1;
	}

	v1 = v[1]->position - ray.position;
	v2 = v[2]->position - ray.position;
	norm = v2.crossProduct(v1).unit();
	if ((p-ray.position).dot(norm) < 0) {
		return -1;
	}

	v1 = v[2]->position - ray.position;
	v2 = v[0]->position - ray.position;
	norm = v2.crossProduct(v1).unit();
	if ((p-ray.position).dot(norm) < 0) {
		return -1;
	}

	iInfo.iCoordinate = p;
	iInfo.material = material;
	iInfo.normal = plane.normal;

	return t;
}
BoundingBox3D RayTriangle::setBoundingBox(void){
	BoundingBox3D box;
	box.p[0] = v[0]->position;
	box.p[1] = v[1]->position;
	for (int i = 0; i < 3; i++) {
		if(v[i]->position[0] < box.p[0][0]){box.p[0][0]=v[i]->position[0];}
		if(v[i]->position[1] < box.p[0][1]){box.p[0][1]=v[i]->position[1];}
		if(v[i]->position[2] < box.p[0][2]){box.p[0][2]=v[i]->position[2];}
		if(v[i]->position[0] > box.p[1][0]){box.p[1][0]=v[i]->position[0];}
		if(v[i]->position[1] > box.p[1][1]){box.p[1][1]=v[i]->position[1];}
		if(v[i]->position[2] > box.p[1][2]){box.p[1][2]=v[i]->position[2];}
	}

	bBox = box;
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayTriangle::drawOpenGL(int materialIndex){
	material->drawOpenGL();
	glBegin(GL_TRIANGLES);
		glNormal3f(GLfloat(plane.normal[0]),GLfloat(plane.normal[1]),GLfloat(plane.normal[2]));
		glVertex3f(GLfloat(v[0]->position[0]),GLfloat(v[0]->position[1]),GLfloat(v[0]->position[2]));
		glNormal3f(GLfloat(plane.normal[0]),GLfloat(plane.normal[1]),GLfloat(plane.normal[2]));
		glVertex3f(GLfloat(v[1]->position[0]),GLfloat(v[1]->position[1]),GLfloat(v[1]->position[2]));
		glNormal3f(GLfloat(plane.normal[0]),GLfloat(plane.normal[1]),GLfloat(plane.normal[2]));
		glVertex3f(GLfloat(v[2]->position[0]),GLfloat(v[2]->position[1]),GLfloat(v[2]->position[2]));
	glEnd();
	glFlush();
	return -1;
}
