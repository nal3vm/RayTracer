#include "rayScene.h"
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include <math.h>
#include <iostream>


///////////////////////
// Ray-tracing stuff //
///////////////////////

Point3D RayScene::Reflect(Point3D v,Point3D n){
	return Point3D();
}

int RayScene::Refract(Point3D v,Point3D n,double ir,Point3D& refract){
	return 0;
}

Ray3D RayScene::GetRay(RayCamera* camera,int i,int j,int width,int height){
	double angle = camera->heightAngle;
	double pi = 3.1415926535897;
	Point3D p0 = camera->position;

	// Calculate the Z position of the coordinate relative to the XY plane.
	Point3D pBottom = p0 + camera->direction - camera->up*tan((angle/2));
	Point3D pTop = p0 + camera->direction + camera->up*tan((angle/2));
	double planeHeight = 2*tan(angle/2);

	// Calculate the Y position of the coordinate relative to the XZ plane.
	Point3D pLeft = p0 + camera->direction - camera->right*tan((angle/2));
	Point3D pRight = p0 + camera->direction + camera->right*tan((angle/2));
	double planeWidth = 2*tan(angle/2);

	Point3D pCorner = p0+camera->direction - camera->right*(planeWidth/2) - camera->up*(planeHeight/2);

	Point3D pixel = pCorner + camera->up*(j*planeHeight/height) + camera->right*(i*planeWidth/width);
	Point3D ray = pixel - p0;
	// Normalize 

	Point3D vectUnit = ray.unit();

	Ray3D ret;
	ret.direction = vectUnit;
	ret.position = p0;

/*	std::cout << "<";
	std::cout << ray[0];
	std::cout << ",";
	std::cout << ray[1];
	std::cout << ",";
	std::cout << ray[2];
	std::cout << ">";
	std::cout << "\n";*/
	return ret;
}

Point3D RayScene::GetColor(Ray3D ray,int rDepth,Point3D cLimit){

	RayIntersectionInfo iInfo;
	double resp = group->intersect(ray, iInfo);
	if (resp > 0) {
		return Point3D(1,1,1);
	}
	return Point3D();
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void){
}
void RayTexture::setUpOpenGL(void){
}
