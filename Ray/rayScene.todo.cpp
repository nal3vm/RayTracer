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

	Point3D pBottom = p0 + camera->direction - camera->up*tan(angle);
	Point3D pTop = p0 + camera->direction + camera->up*tan(angle);
	Point3D pI = pBottom + (pTop-pBottom)*((double(i)+0.5)/double(height));


	Point3D pRight = p0 + camera->direction - camera->right*tan(angle);
	Point3D pLeft = p0 + camera->direction + camera->right*tan(angle);
	Point3D pJ = pRight + (pLeft-pRight)*((double(i)+0.5)/double(height));

	Point3D pFinal(1, pJ[1], pI[2]);

	Point3D vect = (camera->position-pFinal).unit();

	std::cout << "<";
	std::cout << vect[0];
	std::cout << ",";
	std::cout << vect[1];
	std::cout << ",";
	std::cout << vect[2];
	std::cout << ">";
	std::cout << "\n";
	return vect;
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
