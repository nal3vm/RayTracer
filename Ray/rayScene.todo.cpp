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
	Point3D R = n*2*(n.dot(v.negate().unit()))-v.negate().unit();
	return R;
}

int RayScene::Refract(Point3D v,Point3D n,double ir,Point3D& refract){
	refract = v;
	return 1;
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
	if (rDepth == 0) {
		return Point3D();			
	}
	RayIntersectionInfo iInfo;
	double resp = group->intersect(ray, iInfo, -1);
	if (resp > 0) {
		Point3D reflectedDirection = Reflect(ray.direction, iInfo.normal);
		Ray3D reflectedRay(iInfo.iCoordinate+(reflectedDirection.unit()*0.0001), reflectedDirection.unit());

		Point3D refractedDirection;
		int refract = Refract(ray.direction, iInfo.normal, 0, refractedDirection);
		Ray3D refractedRay(iInfo.iCoordinate+(refractedDirection.unit()*0.0001), refractedDirection.unit());
		Point3D refractedTransparency = iInfo.material->transparent;

		Point3D diffuse = Point3D(0,0,0);
		Point3D specular = Point3D(0,0,0);
		for (int i=0; i<lightNum; i++) {
			RayIntersectionInfo iInfo2 = iInfo;
			int iSectCount = 0;
			Point3D diffuseResp = lights[i]->getDiffuse(camera->position, iInfo2);
			Point3D specularResp = lights[i]->getSpecular(camera->position, iInfo2);
			Point3D transparency = lights[i]->transparency(iInfo2, group, cLimit);
			diffuse = diffuse+diffuseResp*transparency;
			specular = specular+specularResp*transparency;
		}
		Point3D response = iInfo.material->ambient*ambient+iInfo.material->emissive + diffuse + specular + GetColor(reflectedRay, rDepth-1, cLimit) +GetColor(refractedRay, rDepth-1, cLimit)*refractedTransparency;
		for (int i = 0; i <3; i++) {
			if (response[i] < 0) {
				response[i] = 0;
			}
			if (response[i] > 1) {
				response[i] = 1;
			}
		}
		return response;
	}
	else return Point3D();
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void){
}
void RayTexture::setUpOpenGL(void){
}
