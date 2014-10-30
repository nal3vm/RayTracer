#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <SVD/SVDFit.h>
#include <SVD/MatrixMNTC.h>

#include "geometry.h"


///////////////////////
// Ray-tracing stuff //
///////////////////////
double BoundingBox3D::intersect(const Ray3D& ray) const {
	Ray3D tempRay = ray;
	BoundingBox3D tempBox = *this;

	//Calculate X values
	double tXmin = (tempBox.p[0][0]-tempRay.position[0])/tempRay.direction[0];
	double tXmax = (tempBox.p[1][0]-tempRay.position[0])/tempRay.direction[0];
	if(tXmin > tXmax) std::swap(tXmin, tXmax);

	//Calculate Y values.
	double tYmin = (tempBox.p[0][1]-tempRay.position[1])/tempRay.direction[1];
	double tYmax = (tempBox.p[1][1]-tempRay.position[1])/tempRay.direction[1];
	if(tYmin > tYmax) std::swap(tYmin, tYmax);

	//Check for miss.
	if ((tXmin > tYmax) || (tYmin > tXmax)) return -1;

	//Checks for.... something.
	if (tYmin > tXmin) tXmin = tYmin;
	if (tYmax < tXmax) tXmax = tYmax;

	//Calculating Z values.
	double tZmin = (tempBox.p[0][2]-tempRay.position[2])/tempRay.direction[2];
	double tZmax = (tempBox.p[1][2]-tempRay.position[2])/tempRay.direction[2];
	if(tZmin > tZmax) std::swap(tZmin, tZmax);

	//Check for miss.
	if ((tXmin > tZmax) || (tZmin > tXmax)) return -1;

	//Checks for... something else.
	if (tZmin > tXmin) tXmin = tZmin;
	if (tZmax < tXmax) tXmax = tZmax;

	return (tXmin < 0) ? 0 : tXmin;
}

/////////////////////
// Animation stuff //
/////////////////////
Matrix3D::Matrix3D(const Point3D& e){
	(*this)=Matrix3D();
}

Matrix3D::Matrix3D(const Quaternion& q){
	(*this)=Matrix3D();
}
Matrix3D Matrix3D::closestRotation(void) const {
	return (*this);
}
/* While these Exp and Log implementations are the direct implementations of the Taylor series, the Log
 * function tends to run into convergence issues so we use the other ones:*/
Matrix3D Matrix3D::Exp(const Matrix3D& m,int iter){
	return m;
}
