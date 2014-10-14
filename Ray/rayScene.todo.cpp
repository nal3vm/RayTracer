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
	Point3D p0 = camera->position;

	// Calculate the Z position of the coordinate relative to the XY plane.
	Point3D pBottom = p0 + camera->direction - camera->up*tan(angle);
	Point3D pTop = p0 + camera->direction + camera->up*tan(angle);
	Point3D pI = pBottom + (pTop-pBottom)*((double(i)+0.5)/double(height));

	// Calculate the Y position of the coordinate relative to the XZ plane.
	Point3D pRight = p0 + camera->direction - camera->right*tan(angle);
	Point3D pLeft = p0 + camera->direction + camera->right*tan(angle);
	Point3D pJ = pRight + (pLeft-pRight)*((double(j)+0.5)/double(height));

	// Map the pixel location on a plane 1 unit away.
	Point3D pFinal(1, pJ[1], pI[2]);

	// Normalize 
	Point3D vect = pFinal - camera->position;
	vect = vect.unit();

	Ray3D ret;
	ret.direction = vect;
	ret.position = p0;

	std::cout << "<";
	std::cout << ret.direction[0];
	std::cout << ",";
	std::cout << ret.direction[1];
	std::cout << ",";
	std::cout << ret.direction[2];
	std::cout << ">";
	std::cout << "\n";
	return Ray3D();
}

Point3D RayScene::GetColor(Ray3D ray,int rDepth,Point3D cLimit){
	return Point3D();
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void){
}
void RayTexture::setUpOpenGL(void){
}
