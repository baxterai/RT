/*******************************************************************************
 * 
 * This file is part of BAIPROJECT.
 * 
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
 * 
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 * 
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 * 
 *******************************************************************************/
 
/*******************************************************************************
 *
 * File Name: SHAREDvector.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a12a 31-July-2012
 *
 *******************************************************************************/

#include "SHAREDvector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;





/*
void calculateAreaOfQuad2D(vec * pt1, vec * pt2, vec * pt3, vec * pt4)
{
	return calculateAreaOfQuadAssumePointsAreInOrder(pt1, pt2, pt3, pt4);
}

double calculateAreaOfQuad2DAssumePointsAreInOrder(vec * pt1, vec * pt2, vec * pt3, vec * pt4)
{
	double area = (1/2)*((x1*y2 - x2*y1) + (x2*y3 - x3*y2) + (x3y4 - x4y3));
}
*/

void initialiseVector(vec * vect)
{
	vect->x = 0.0;
	vect->y = 0.0;
	vect->z = 0.0;
}

void calculateNormalOfTri(vec * pt1, vec * pt2, vec * pt3, vec * normal)
{
	vec vec1;
	vec vec2;
	subtractVectorsRT(pt2, pt1 , &vec1);
	subtractVectorsRT(pt3, pt1, &vec2);
	calculateNormal(&vec1, &vec2, normal);
}

void calculateRotationVectorFromDeformationMatrix(mat* deformationMatrix, vec * rotationVector)
{
	//http://planning.cs.uiuc.edu/node103.html
	rotationVector->x = atan2(deformationMatrix->a.y, deformationMatrix->a.x);
	rotationVector->y = atan2(deformationMatrix->a.z, sqrt(pow(deformationMatrix->b.z, 2.0) + pow(deformationMatrix->c.z, 2.0)));
	rotationVector->z = atan2(deformationMatrix->b.z, deformationMatrix->c.z);
}

/*
void calculateRotationVectorFromVector(vec* vector, vec * rotationVector)
{
	//http://planning.cs.uiuc.edu/node103.html
	rotationVector->x = atan2(vector->y, vector->z);
	rotationVector->y = atan2(vector->x * cos(rotationVector->x), vector->z);
	rotationVector->z = atan2(cos(rotationVector->x), sin(rotationVector->x)*sin(rotationVector->y));
}


//from http://www.gamedev.net/page/resources/_/technical/graphics-programming-and-theory/wwh-calculating-a-rotation-matrix-based-on-lo-r665
void generateXYZRotationMatrix(vec * vector, mat * rotationMatrix)
{
	// Get our direction vector (the Z vector component of the matrix)
	// and make sure it's normalized into a unit vector

	vec zAxis;
	zAxis.x = vector->x;
	zAxis.y = vector->y;
	zAxis.z = vector->z;
	normaliseVector(&zAxis);

	// Build the Y vector of the matrix (handle the degenerate case
	// in the way that 3DS does) -- This is not the TRUE vector, only
	// a reference vector.

	vec yAxis;
	if (!zAxis.x && !zAxis.z)
	{
		yAxis.x = -(zAxis.y);
		yAxis.y = 0.0;
		yAxis.z = 0.0;
	}
	else
	{
		yAxis.x = 0.0;
		yAxis.y = 1.0;
		yAxis.z = 0.0;
	}

	// Build the X axis vector based on the two existing vectors
	vec xAxis;
	crossProduct(&yAxis, &zAxis, &xAxis);
	normaliseVector(&xAxis);

	// Correct the Y reference vector
	crossProduct(&xAxis, &zAxis, &yAxis);
	normaliseVector(&yAxis);
	yAxis.x = -(yAxis.x);
	yAxis.y = -(yAxis.y);
	yAxis.z = -(yAxis.z);

	makeMatrix(&xAxis, &yAxis, &zAxis, rotationMatrix);

}
*/

//from; http://stackoverflow.com/questions/349050/calculating-a-lookat-matrix
void generateLookAtRotationMatrix(vec * at, vec * eye, vec * up, mat * rotationMatrix)
{
	/*
	zaxis = normal(At - Eye)
	xaxis = normal(cross(Up, zaxis))
	yaxis = cross(zaxis, xaxis)
	*/

	vec zaxis;
	subtractVectorsRT(at, eye, &zaxis);
	normaliseVector(&zaxis);

	vec xaxis;
	crossProduct(up, &zaxis, &xaxis);
	normaliseVector(&xaxis);

	vec yaxis;
	crossProduct(&zaxis, &xaxis, &yaxis);

	makeMatrix(&xaxis, &yaxis, &zaxis, rotationMatrix);

}

void transposeMatrix(mat * matx)
{
	double tmp;

	tmp = matx->a.y;
	matx->a.y = matx->b.x;
	matx->b.x = tmp;

	tmp = matx->a.z;
	matx->a.z = matx->c.x;
	matx->c.x = tmp;

	tmp = matx->b.z;
	matx->b.z = matx->c.y;
	matx->c.y = tmp;
}





double calculateInteriorAngleOfAPolygonVertex(vec * pt1centre, vec * pt2, vec * pt3)
{
	vec side1;
	vec side2;
	subtractVectorsRT(pt1centre, pt2, &side1);
	subtractVectorsRT(pt1centre, pt3, &side2);
	//subtractVectorsRT(pt3, pt1centre, &side2);
	double interiorAngle = acos(dotproduct(&side1, &side2) / (findMagnitudeOfVector(&side1) * findMagnitudeOfVector(&side2)));
	return interiorAngle;

}


double calculateAreaOfTriangle3D(vec * pt1, vec * pt2, vec * pt3)
{
	mat matrix;

	matrix.a.x = pt1->x;
	matrix.b.x = pt1->y;
	matrix.c.x = pt1->z;
	matrix.a.y = pt2->x;
	matrix.b.y = pt2->y;
	matrix.c.y = pt2->z;
	matrix.a.z = pt3->x;
	matrix.b.z = pt3->y;
	matrix.c.z = pt3->z;

	return absDouble2(0.5 * calculateDeterminant3by3(&matrix));
}


double calculateAreaOfTriangle(vec * pt1, vec * pt2, vec * pt3)
{
	mat matrix;

	matrix.a.x = pt1->x;
	matrix.b.x = pt1->y;
	matrix.c.x = 1.0;
	matrix.a.y = pt2->x;
	matrix.b.y = pt2->y;
	matrix.c.y = 1.0;
	matrix.a.z = pt3->x;
	matrix.b.z = pt3->y;
	matrix.c.z = 1.0;

	return absDouble2(0.5 * calculateDeterminant3by3(&matrix));
}


double calculateDeterminant3by3(mat* matrix)
{
	double a = matrix->a.x;
	double b = matrix->b.x;
	double c = matrix->c.x;
	double d = matrix->a.y;
	double e = matrix->b.y;
	double f = matrix->c.y;
	double g = matrix->a.z;
	double h = matrix->b.z;
	double i = matrix->c.z;

	return (a*((e*i)-(f*h)) - b*((d*i)-(f*g)) + c*((d*h)-(e*g)));
}

double absDouble2(double val)
{
	if(val < 0.0)
	{
		return (-val);
	}
	else
	{
		return val;
	}
}


void calculateNormal(vec * pt1, vec * pt2, vec * normal)
{
	crossProduct(pt1, pt2, normal);
}

void calculateMidDiffBetweenTwoPoints(vec * pt1, vec * pt2, vec * midDiff)
{
	midDiff->x = (pt2->x - pt1->x)/2.0;
	midDiff->y = (pt2->y - pt1->y)/2.0;
	midDiff->z = (pt2->z - pt1->z)/2.0;
}

void calculateMidPointBetweenTwoPoints(vec * pt1, vec * pt2, vec * midPoint)
{
	vec midDiff;
	calculateMidDiffBetweenTwoPoints(pt1, pt2, &midDiff);

	midPoint->x = pt1->x + midDiff.x;
	midPoint->y = pt1->y + midDiff.y;
	midPoint->z = pt1->z + midDiff.z;
}




void createRotationMatrix2D(mat* matrix, double rotation)
{
	matrix->a.x = cos(rotation);
	matrix->a.y = sin(rotation);
	matrix->a.z = 0.0;
	matrix->b.x = -sin(rotation);
	matrix->b.y = cos(rotation);
	matrix->b.z = 0.0;
	matrix->c.x = 0.0;
	matrix->c.y = 0.0;
	matrix->c.z = 1.0;
}

void createXAxisShearMatrix2D(mat* matrix, double shear)
{
	matrix->a.x = 1.0;
	matrix->a.y = 0.0;
	matrix->a.z = 0.0;
	matrix->b.x = shear;
	matrix->b.y = 1.0;
	matrix->b.z = 0.0;
	matrix->c.x = 0.0;
	matrix->c.y = 0.0;
	matrix->c.z = 1.0;
}

void createYAxisScaleMatrix2D(mat* matrix, double scaleFactor)
{
	matrix->a.x = 1.0;
	matrix->a.y = 0.0;
	matrix->a.z = 0.0;
	matrix->b.x = 0.0;
	matrix->b.y = scaleFactor;
	matrix->b.z = 0.0;
	matrix->c.x = 0.0;
	matrix->c.y = 0.0;
	matrix->c.z = 1.0;

}




double calculateAngleBetweenVectors2D(vec * vect1, vec * vect2)
{
	double angleBetweenVectors2D;
	//tan angleBetweenVectors2D =  (y2-y1) / (x2 - x1)

	if(compareDoubles(vect2->x, vect1->x))
	{
		angleBetweenVectors2D = 0.0;
	}
	else
	{
		angleBetweenVectors2D =  atan((vect2->y - vect1->y) / (vect2->x - vect1->x));
	}

	return angleBetweenVectors2D;

}

double calculateAngleOfVector3D(vec * vect1, int axis)
{
	double angle;

	if(axis == AXIS_X)
	{
		if(compareDoubles(vect1->z, 0.0))
		{
			angle = 0.0;
		}
		else
		{
			angle = atan(vect1->x / vect1->z);
		}
	}
	else if(axis == AXIS_Y)
	{
		if(compareDoubles(vect1->z, 0.0))
		{
			angle = 0.0;
		}
		else
		{
			angle =  atan(vect1->y / vect1->z);
		}
	}
	else if(axis == AXIS_Z)
	{
		if(compareDoubles(vect1->x, 0.0))
		{
			angle = 0.0;
		}
		else
		{
			angle = atan(vect1->z / vect1->x);
		}
	}
	else
	{
		exit(0);
	}

	return angle;

}




void createScaleMatrix2D(mat* matrix, double scaleFactor)
{
	matrix->a.x = scaleFactor;
	matrix->a.y = 0.0;
	matrix->a.z = 0.0;
	matrix->b.x = 0.0;
	matrix->b.y = scaleFactor;
	matrix->b.z = 0.0;
	matrix->c.x = 0.0;
	matrix->c.y = 0.0;
	matrix->c.z = 1.0;

}

void multiplyVectorByMatrix(vec * vecNew, vec * vecToMultiply, mat * matrix)
{
	vecNew->x = matrix->a.x*vecToMultiply->x + matrix->b.x*vecToMultiply->y +  matrix->c.x*vecToMultiply->z;
	vecNew->y = matrix->a.y*vecToMultiply->x + matrix->b.y*vecToMultiply->y +  matrix->c.y*vecToMultiply->z;
	vecNew->z = matrix->a.z*vecToMultiply->x + matrix->b.z*vecToMultiply->y +  matrix->c.z*vecToMultiply->z;

}






double findMagnitudeOfVector(vec * vect1)
{
	return sqrt(pow(vect1->x, 2) + pow(vect1->y,2) + pow(vect1->z,2));
}



void normaliseVector(vec *vect1)
{
	double magnitude = findMagnitudeOfVector(vect1);
#ifdef OR_DO_NOT_CHECK_FOR_ZERO_DIVISION_DURING_POINT_NORMAL_CALC
	vect1->x = (vect1->x)/magnitude;
	vect1->y = (vect1->y)/magnitude;
	vect1->z = (vect1->z)/magnitude;
#else
	if(magnitude > DOUBLE_MIN_PRECISION)
	{
		vect1->x = (vect1->x)/magnitude;
		vect1->y = (vect1->y)/magnitude;
		vect1->z = (vect1->z)/magnitude;
	}
	else
	{
		vect1->x = 0.0;
		vect1->y = 0.0;
		vect1->z = 0.0;
	}
#endif
	return;
}

void normaliseVectorRT(vec *vect1, vec *vect)
{
	double magnitude = findMagnitudeOfVector(vect1);
	vect->x = (vect1->x)/magnitude;
	vect->y = (vect1->y)/magnitude;
	vect->z = (vect1->z)/magnitude;
	return;
}


void addVectorsRT(vec *vect1, vec *vect2, vec* vect)
{
	vect->x = vect1->x + vect2->x;
	vect->y = vect1->y + vect2->y;
	vect->z = vect1->z + vect2->z;
}

void subtractVectorsRT(vec *vect1, vec *vect2, vec *vect)
{
	vect->x = vect1->x - vect2->x;
	vect->y = vect1->y - vect2->y;
	vect->z = vect1->z - vect2->z;
}

void negativeVector(vec *vect1, vec* vect)
{
	vect->x = -(vect1->x);
	vect->y = -(vect1->y);
	vect->z = -(vect1->z);
}

double dotproduct(vec *vect1, vec *vect2)
{
	double scalar = vect1->x*vect2->x + vect1->y*vect2->y + vect1->z*vect2->z;
	return scalar;
}

void multiplyVectorByScalarRT(vec* vect1, double multiplyer, vec* vect)
{
	vect->x = vect1->x*multiplyer;
	vect->y = vect1->y*multiplyer;
	vect->z = vect1->z*multiplyer;
}

void divideVectorByScalarRT(vec* vect1, double divisor, vec* vect)
{
	vect->x = vect1->x/divisor;
	vect->y = vect1->y/divisor;
	vect->z = vect1->z/divisor;
}





void makeMatrix(vec* vect1, vec* vect2, vec* vect3, mat* matx)
{
	matx->a = *(vect1);
	matx->b = *(vect2);
	matx->c = *(vect3);
}

void multMatrixByVector(mat* matx, vec* vect1, vec* vect)
{
	vect->x = matx->a.x * vect1->x + matx->b.x * vect1->y + matx->c.x * vect1->z;
	vect->y = matx->a.y * vect1->x + matx->b.y * vect1->y + matx->c.y * vect1->z;
	vect->z = matx->a.z * vect1->x + matx->b.z * vect1->y + matx->c.z * vect1->z;
}

void crossProduct(vec* vect1, vec* vect2, vec* vect)
{
	vect->x = (vect1->y)*(vect2->z) - (vect2->y)*(vect1->z);
	vect->y = -((vect1->x)*(vect2->z) - (vect2->x)*(vect1->z));
	vect->z = (vect1->x)*(vect2->y) - (vect2->x)*(vect1->y);
}

void createVector(vec* vec)
{
	vec->x = 0;
	vec->y = 0;
	vec->z = 0;
}

	/*method is not used*/
void createIdentityMatrixRT(mat* matx)
{
	matx->a.x = ONE;
	matx->b.x = ZERO;
	matx->c.x = ZERO;
	matx->a.y = ZERO;
	matx->b.y = ONE;
	matx->c.y = ZERO;
	matx->a.z = ZERO;
	matx->b.z = ZERO;
	matx->c.z = ONE;
}

void copyVectorRT(vec * vecNew, vec * vecbToCopy)
{

	vecNew->x = vecbToCopy->x;
	vecNew->y = vecbToCopy->y;
	vecNew->z = vecbToCopy->z;
}




bool compareVectorsArbitraryError(vec * veca, vec * vecb, double error)
{
	bool result = true;
	if(!compareDoublesArbitraryError(veca->x, vecb->x, error))
	{
		result = false;
	}
	if(!compareDoublesArbitraryError(veca->y, vecb->y, error))
	{
		result = false;
	}
	if(!compareDoublesArbitraryError(veca->z, vecb->z, error))
	{
		result = false;
	}
	return result;
}




bool compareVectors(vec * veca, vec * vecb)
{
	bool result = true;
	if(!compareDoubles(veca->x, vecb->x))
	{
		result = false;
	}
	if(!compareDoubles(veca->y, vecb->y))
	{
		result = false;
	}
	if(!compareDoubles(veca->z, vecb->z))
	{
		result = false;
	}
	return result;
}

bool compareMatricies(mat * mata, mat * matb)
{
	bool result = true;
	if(!compareVectors(&(mata->a), &(matb->a)))
	{
		result = false;
	}
	if(!compareVectors(&(mata->b), &(matb->b)))
	{
		result = false;
	}
	if(!compareVectors(&(mata->c), &(matb->c)))
	{
		result = false;
	}
	return result;
}

void copyVectors(vec * vecNew, vec * vecbToCopy)
{

	vecNew->x = vecbToCopy->x;
	vecNew->y = vecbToCopy->y;
	vecNew->z = vecbToCopy->z;
}

void copyMatricies(mat * matNew, mat * matToCopy)
{
	copyVectors(&(matNew->a), &(matToCopy->a));
	copyVectors(&(matNew->b), &(matToCopy->b));
	copyVectors(&(matNew->c), &(matToCopy->c));
}

/*
void multiplyMatricies(mat * matNew, mat * mat1, mat * mat2)
{
	matNew->a.x = (mat1->a.x * mat2->a.x) + (mat1->b.x * mat2->a.y) + (mat1->c.x * mat2->a.z);
	matNew->a.y = (mat1->a.y * mat2->a.x) + (mat1->b.y * mat2->a.y) + (mat1->c.y * mat2->a.z);
	matNew->a.z = (mat1->a.z * mat2->a.x) + (mat1->b.z * mat2->a.y) + (mat1->c.z * mat2->a.z);

	matNew->b.x = (mat1->a.x * mat2->b.x) + (mat1->b.x * mat2->b.y) + (mat1->c.x * mat2->b.z);
	matNew->b.y = (mat1->a.y * mat2->b.x) + (mat1->b.y * mat2->b.y) + (mat1->c.y * mat2->b.z);
	matNew->b.z = (mat1->a.z * mat2->b.x) + (mat1->b.z * mat2->b.y) + (mat1->c.z * mat2->b.z);

	matNew->c.x = (mat1->a.x * mat2->c.x) + (mat1->b.x * mat2->c.y) + (mat1->c.x * mat2->c.z);
	matNew->c.y = (mat1->a.y * mat2->c.x) + (mat1->b.y * mat2->c.y) + (mat1->c.y * mat2->c.z);
	matNew->c.z = (mat1->a.z * mat2->c.x) + (mat1->b.z * mat2->c.y) + (mat1->c.z * mat2->c.z);

}*/

void multiplyMatricies(mat * matNew, mat * mat1, mat * mat2)
{
	/*
	cout << "mat1: " << endl;
	cout << mat1->a.x << endl;
	cout << mat1->b.x << endl;
	cout << mat1->c.x << endl;
	cout << mat1->a.y << endl;
	cout << mat1->b.y << endl;
	cout << mat1->c.y << endl;
	cout << mat1->a.z << endl;
	cout << mat1->b.z << endl;
	cout << mat1->c.z << endl;

	cout << "mat2: " << endl;
	cout << mat2->a.x << endl;
	cout << mat2->b.x << endl;
	cout << mat2->c.x << endl;
	cout << mat2->a.y << endl;
	cout << mat2->b.y << endl;
	cout << mat2->c.y << endl;
	cout << mat2->a.z << endl;
	cout << mat2->b.z << endl;
	cout << mat2->c.z << endl;
	*/

	matNew->a.x = mat1->a.x*mat2->a.x + mat1->b.x*mat2->a.y +  mat1->c.x*mat2->a.z;
	matNew->b.x = mat1->a.x*mat2->b.x + mat1->b.x*mat2->b.y +  mat1->c.x*mat2->b.z;
	matNew->c.x = mat1->a.x*mat2->c.x + mat1->b.x*mat2->c.y +  mat1->c.x*mat2->c.z;

	matNew->a.y = mat1->a.y*mat2->a.x + mat1->b.y*mat2->a.y +  mat1->c.y*mat2->a.z;
	matNew->b.y = mat1->a.y*mat2->b.x + mat1->b.y*mat2->b.y +  mat1->c.y*mat2->b.z;
	matNew->c.y = mat1->a.y*mat2->c.x + mat1->b.y*mat2->c.y +  mat1->c.y*mat2->c.z;

	matNew->a.z = mat1->a.z*mat2->a.x + mat1->b.z*mat2->a.y +  mat1->c.z*mat2->a.z;
	matNew->b.z = mat1->a.z*mat2->b.x + mat1->b.z*mat2->b.y +  mat1->c.z*mat2->b.z;
	matNew->c.z = mat1->a.z*mat2->c.x + mat1->b.z*mat2->c.y +  mat1->c.z*mat2->c.z;
}


void subtractVectors(vec * vecNew, vec * a, vec * b)
{

	vecNew->x = a->x - b->x;
	vecNew->y = a->y - b->y;
	vecNew->z = a->z - b->z;
}

void addVectors(vec * vecNew, vec * a, vec * b)
{

	vecNew->x = a->x + b->x;
	vecNew->y = a->y + b->y;
	vecNew->z = a->z + b->z;
}


void multiplyVectorByScalar(vec * vec, double scalar)
{
	vec->x = vec->x * scalar;
	vec->y = vec->y * scalar;
	vec->z = vec->z * scalar;
}


double calculateTheDistanceBetweenTwoPoints(vec * positionOfUnit1, vec * positionOfUnit2)
{
	return calculateTheDistanceBetweenTwoPoints(positionOfUnit1->x, positionOfUnit2->x, positionOfUnit1->y, positionOfUnit2->y, positionOfUnit1->z, positionOfUnit2->z);
}

double calculateTheDistanceBetweenTwoPointsXYOnly(vec * positionOfUnit1, vec * positionOfUnit2)
{
	return calculateTheDistanceBetweenTwoPoints(positionOfUnit1->x, positionOfUnit2->x, positionOfUnit1->y, positionOfUnit2->y, 0, 0);
}

double calculateTheDistanceBetweenTwoPoints(double positionXOfUnit1, double positionXOfUnit2, double positionYOfUnit1, double positionYOfUnit2, double positionZOfUnit1, double positionZOfUnit2)
{
	double xDistanceBetweenTheTwoUnits = positionXOfUnit1 - positionXOfUnit2; //fabs((positionXOfUnit1) - (positionXOfUnit2));
	double yDistanceBetweenTheTwoUnits = positionYOfUnit1 - positionYOfUnit2; //fabs((positionYOfUnit1) - (positionYOfUnit2));
	double zDistanceBetweenTheTwoUnits = positionZOfUnit1 - positionZOfUnit2; //fabs((positionZOfUnit1) - (positionZOfUnit2));
	double distanceBetweenTheTwoUnits = sqrt(pow(xDistanceBetweenTheTwoUnits, 2) + pow(yDistanceBetweenTheTwoUnits, 2) + pow(zDistanceBetweenTheTwoUnits, 2));

	return distanceBetweenTheTwoUnits;
}

double calculateTheDistanceBetweenTwoPoints2D(double positionXOfUnit1, double positionXOfUnit2, double positionYOfUnit1, double positionYOfUnit2)
{
	double xDistanceBetweenTheTwoUnits = positionXOfUnit1 - positionXOfUnit2; //fabs((positionXOfUnit1) - (positionXOfUnit2));
	double yDistanceBetweenTheTwoUnits = positionYOfUnit1 - positionYOfUnit2; //fabs((positionYOfUnit1) - (positionYOfUnit2));
	double distanceBetweenTheTwoUnits = sqrt(pow(xDistanceBetweenTheTwoUnits, 2) + pow(yDistanceBetweenTheTwoUnits, 2));

	return distanceBetweenTheTwoUnits;
}









void createRotationxMatrix(mat* matrix, double rotation)
{
	matrix->b.y = cos(rotation);
	matrix->b.z = -sin(rotation);
	matrix->c.y = sin(rotation);
	matrix->c.z = cos(rotation);
}

void createRotationyMatrix(mat* matrix, double rotation)
{
	matrix->a.x = cos(rotation);
	matrix->a.z = sin(rotation);
	matrix->c.x = -sin(rotation);
	matrix->c.z = cos(rotation);
}

void createRotationzMatrix(mat* matrix, double rotation)
{
	matrix->a.x = cos(rotation);
	matrix->a.y = -sin(rotation);
	matrix->b.x = sin(rotation);
	matrix->b.y = cos(rotation);
}

double convertDegreesToRadian(double degrees)
{
	return (degrees/180*PI);
}

double convertRadianToDegrees(double radian)
{
	return (radian*180/PI);
}


void createIdentityMatrix(mat* matrix)
{
	matrix->a.x = 1;
	matrix->b.x = 0;
	matrix->c.x = 0;
	matrix->a.y = 0;
	matrix->b.y = 1;
	matrix->c.y = 0;
	matrix->a.z = 0;
	matrix->b.z = 0;
	matrix->c.z = 1;
}

void copyMatrix2IntoMatrix1(mat* mat1, mat* mat2)
{
	mat1->a.x = mat2->a.x;
	mat1->b.x = mat2->b.x;
	mat1->c.x = mat2->c.x;
	mat1->a.y = mat2->a.y;
	mat1->b.y = mat2->b.y;
	mat1->c.y = mat2->c.y;
	mat1->a.z = mat2->a.z;
	mat1->b.z = mat2->b.z;
	mat1->c.z = mat2->c.z;
}


void scaleMatrix(mat * matrix, double scaleFactor)
{
	matrix->a.x = matrix->a.x * scaleFactor;
	matrix->b.y = matrix->b.y * scaleFactor;
	matrix->c.z = matrix->c.z * scaleFactor;
}


void createRotatationMatrix(mat * matrix, int rotationAxis, double rotationRadians)
{
	if(rotationAxis == AXIS_X)
	{
		createRotationxMatrix(matrix, rotationRadians);
	}
	else if(rotationAxis == AXIS_Y)
	{
		createRotationyMatrix(matrix, rotationRadians);
	}
	else if(rotationAxis == AXIS_Z)
	{
		createRotationzMatrix(matrix, rotationRadians);
	}
}




























//void find2DIntersectionPoint(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, double * intersectionX, double * intersectionY, bool * interceptionFound, bool * xinterceptionPointFound, bool * yinterceptionPointFound)	//NB an interception may be a line and not a point

//NB uses 0 is the centre of the quad drawn by the 4 points. a, b, c, d.
void find2DIntersectionPoint(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, double * intersectionX, double * intersectionY, bool * interceptionFound, bool * interceptionPointFound)	//NB an interception may be a line and not a point
{
	/*
	double distanceab;
	double distancebc;
	double distancecd;
	double distanceda;

	double distanceac;
	double distancebd;

	//cout << "DEBUG: here1" << endl;

	distanceab = calcDistanceBetweenTwoPoints2D(ax, ay, bx, by);
	distancebc = calcDistanceBetweenTwoPoints2D(bx, by, cx, cy);
	distancecd = calcDistanceBetweenTwoPoints2D(cx, cy, dx, dy);
	distanceda = calcDistanceBetweenTwoPoints2D(dx, dy, ax, ay);


	distanceac = calcDistanceBetweenTwoPoints2D(ax, ay, cx, cy);
	distancebd = calcDistanceBetweenTwoPoints2D(bx, by, dx, dy);

	bool interceptionPointCannotBeFound = false;
	*/

	//safe guard **

	//try for analytical solution

	double mEdge;
	double iEdge;
	double mOptionalLine;
	double iOptionalLine;
	bool edgeGradientInfinityDetected = false;
	bool optionalLineGradientInfinityDetected = false;
	bool edgeNoLineDetected = false;
	bool optionalLineNoLineDetected = false;

	if(!twoPointsAreTheSame2D(ax, ay, cx, cy))
	{
		if(solve2DLineEquationWithTwoPoints(ax, ay, cx, cy, &mEdge, &iEdge))
		{//m != infinity

		}
		else
		{//m = infinity detected, y=iEdge
			edgeGradientInfinityDetected = true;
		}
	}
	else
	{
		edgeNoLineDetected = true;
	}

	if(!twoPointsAreTheSame2D(bx, by, dx, dy))
	{
		if(solve2DLineEquationWithTwoPoints(bx, by, dx, dy, &mOptionalLine, &iOptionalLine))
		{//m != infinity

		}
		else
		{//m = infinity detected, y=iOptionalLine
			optionalLineGradientInfinityDetected = true;
		}
	}
	else
	{
		optionalLineNoLineDetected = true;
	}

	if(!edgeGradientInfinityDetected && !optionalLineGradientInfinityDetected && !edgeNoLineDetected && !optionalLineNoLineDetected)
	{
		if(find2DIntersectionPointOfTwoLines(mEdge, iEdge, mOptionalLine, iOptionalLine, intersectionX, intersectionY))
		{
			*interceptionPointFound = true;

			/*
			if(totalNumOptionalLines == 12)
			{
				cout << "\nDEBUG: "<< endl;
				cout << "totalNumOptionalLines = " << totalNumOptionalLines << endl;
				cout << "\t ax = " << ax << endl;
				cout << "\t ay = " << ay << endl;
				cout << "\t bx = " << bx << endl;
				cout << "\t by = " << by << endl;
				cout << "\t cx = " << cx << endl;
				cout << "\t cy = " << cy << endl;
				cout << "\t dx = " << dx << endl;
				cout << "\t dy = " << dy << endl;
				cout << "\t mEdge = " << mEdge << endl;
				cout << "\t iEdge = " << iEdge << endl;
				cout << "\t mOptionalLine = " << mOptionalLine << endl;
				cout << "\t iOptionalLine = " << iOptionalLine << endl;
				cout << "\t intersectionX = " << *intersectionX << endl;
				cout << "\t intersectionY = " << *intersectionY << endl;
			}
			*/
		}
		else
		{//edge and optional lines are parallel as their gradients are equal, therefore no intersection occurs unless their y intercepts are equal also
			//cout << " here " << endl;

		#ifdef USE_RT
			if(compareDoublesRelaxed(iEdge, iOptionalLine))
		#else
			if(compareDoubles(iEdge, iOptionalLine))
		#endif
			{
				//return from function that there is no precise interception point on this plane (Eg xy plane).
				*interceptionFound = true;

				/*
				#ifdef USE_RT
					*interceptionFound = false;
				#else
					*interceptionFound = true;
				#endif
				*/
			}
		}
	}
	else if(!edgeNoLineDetected && !optionalLineNoLineDetected)
	{

		if(edgeGradientInfinityDetected && !optionalLineGradientInfinityDetected)
		{
			*interceptionPointFound = true;

			*intersectionX  = ax;
			*intersectionY = mOptionalLine*ax + iOptionalLine;	//y = mx + i
		}
		else if(!edgeGradientInfinityDetected && optionalLineGradientInfinityDetected)
		{
			*interceptionPointFound = true;

			*intersectionX = bx;
			*intersectionY = mEdge*bx + iEdge;	//y = mx + i
		}
		else if(edgeGradientInfinityDetected && optionalLineGradientInfinityDetected)
		{//edge and optional lines are parallel as their gradients are equal, therefore no intersection occurs unless their x intercepts are equal also
		#ifdef USE_RT
			if(compareDoublesRelaxed(ax, bx))
		#else
			if(compareDoubles(ax, bx))
		#endif
			{
				//return from function that there is no precise interception point on this plane (Eg xy plane).
				*interceptionFound = true;

				/*removed by RBB oct 08*/
			#ifdef USE_ORIGINAL_OLC_CODE
				*intersectionX = ax;
				*intersectionY = ay;
			#endif
			}
		}

	}
	else
	{
		if((edgeNoLineDetected) && (optionalLineNoLineDetected))
		{
			//in this case all 4 points must be the same for an intersection to occur a, b, c, d
		#ifdef USE_RT
			if(twoPointsAreTheSame2DRelaxed(ax, ay, bx, by))
		#else
			if(twoPointsAreTheSame2D(ax, ay, bx, by))
		#endif
			{
				*interceptionPointFound = true;
				*intersectionX = ax;
				*intersectionY = ay;
			}
		}
		else if(edgeNoLineDetected)
		{
			if(!optionalLineGradientInfinityDetected)
			{
			#ifdef USE_RT
				if(determineIfPointLiesOnAKnownLine2DRelaxed(mOptionalLine, iOptionalLine, ax, ay))
			#else
				if(determineIfPointLiesOnAKnownLine2D(mOptionalLine, iOptionalLine, ax, ay))
			#endif
				{
					*interceptionPointFound = true;
					*intersectionX = ax;
					*intersectionY = ay;
				}
			}
			else
			{
			#ifdef USE_RT
				if(compareDoublesRelaxed(ax, bx))
			#else
				if(compareDoubles(ax, bx))
			#endif
				{
					*interceptionPointFound = true;
					*intersectionX = ax;
					*intersectionY = ay;
				}
			}
		}
		else if(optionalLineNoLineDetected)
		{
			if(!edgeGradientInfinityDetected)
			{
			#ifdef USE_RT
				if(determineIfPointLiesOnAKnownLine2DRelaxed(mEdge, iEdge, bx, by))
			#else
				if(determineIfPointLiesOnAKnownLine2D(mEdge, iEdge, bx, by))
			#endif
				{
					*interceptionPointFound = true;
					*intersectionX = bx;
					*intersectionY = by;
				}
			}
			else
			{
			#ifdef USE_RT
				if(compareDoublesRelaxed(bx, ax))
			#else
				if(compareDoubles(bx, ax))
			#endif
				{
					*interceptionPointFound = true;
					*intersectionX = bx;
					*intersectionY = by;
				}
			}
		}
	}

	if(*interceptionPointFound)
	{
		*interceptionFound = true;
	}
}




bool find2DIntersectionPointOfTwoLines(double m1, double i1, double m2, double i2, double * xIntersection, double * yIntersection)
{
	bool result;

	/*
	/*theory
	m1, m2, i1, i2 are known, find x, and y, in y = m1x + i1, and y = m2x + i2

	y = m1x + i1
	y = m2x + i2
	---

	0 = (m1 - m2)x + (i1 - i2)
	x = -(i1 - i2)/(m1-m2)
	y = m1*x + i1
	*/

	double mNumerator = - (i1-i2);
	double mDenomenator = (m1-m2);

	if(mDenomenator == 0)
	{
		*xIntersection = 0;	//no intersection found
		result = false;
	}
	else
	{
		*xIntersection = mNumerator/mDenomenator;
		result = true;
	}

	*yIntersection = m1*(*xIntersection) + i1;

	return result;
}


double calcDistanceBetweenTwoPoints2D(double x1, double y1, double x2, double y2)
{
	double xDistanceBetweenTheTwoPoints = x1 -  x2;
	double yDistanceBetweenTheTwoPoints = y1 -  y2;
	return sqrt(pow(xDistanceBetweenTheTwoPoints, 2) + pow(yDistanceBetweenTheTwoPoints, 2));
}


bool solve2DLineEquationWithTwoPoints(double x1, double y1, double x2, double y2, double * m, double * i)
{
	bool result;

	/*theory
	find m and i, in y = mx + i

	y1 = mx1 + i
	y2 = mx2 + i
	--
	y1 - y2 = mx1 - mx2
	m = (y1-y2)/(x1-x2)
	---
	i = y1 - ((y1-y2)/(m1-x2) * x1)

	*/

	double mNumerator = (y1-y2);
	double mDenomenator = (x1-x2);
	if(mDenomenator == 0)
	{
		#define VERY_LARGE_DOUBLE 999999999999.0;
		*m = VERY_LARGE_DOUBLE;
		result = false;
	}
	else
	{
		*m = mNumerator/mDenomenator;
		result = true;
	}
	*i = y1 - ((*m) * x1);
	return result;
}

bool determineIfPointLiesOnLine2D(double x1, double y1, double x2, double y2, double x3, double y3)
{
	bool result = false;

	double m, i;
	if(solve2DLineEquationWithTwoPoints(x1, y1, x2, y2, &m, &i))
	{//m != infinity
		double RHS = m*(x3) + i;
		if(compareDoubles(y3, RHS))
		{
			result = true;
		}
	}
	else
	{//m = infinity detected
		if(compareDoubles(x1, x3))
		{
			result = true;
		}
	}

	return result;
}


bool determineIfPointLiesOnAKnownLine2D(double m1, double i1, double x3, double y3)
{//preconditions: m != infinity
	bool result = false;


	double RHS = m1*(x3) + i1;

	if(compareDoubles(y3, RHS))
	{
		result = true;
	}

	return result;
}



bool twoPointsAreTheSame2D(double x1, double y1, double x2, double y2)
{
	bool result;

	if(compareDoubles(calcDistanceBetweenTwoPoints2D(x1, y1, x2, y2), 0.0))
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}

/*
#ifndef	USE_LRRC

#define DOUBLE_MIN_PRECISION 0.00001

bool compareDoubles(double a, double b)
{
	bool result;
	if((a < (b+DOUBLE_MIN_PRECISION)) && (a > (b-DOUBLE_MIN_PRECISION)))
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}
#endif
*/

#ifdef USE_RT


bool compareDoublesRelaxed(double a, double b)	//required for raytracing operations
{
	bool result;
	if((a < (b+RELAXED_DOUBLE_MIN_PRECISION)) && (a > (b-RELAXED_DOUBLE_MIN_PRECISION)))
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}


bool determineIfPointLiesOnAKnownLine2DRelaxed(double m1, double i1, double x3, double y3)
{//preconditions: m != infinity
	bool result = false;


	double RHS = m1*(x3) + i1;

	if(compareDoublesRelaxed(y3, RHS))
	{
		result = true;
	}

	return result;
}

bool twoPointsAreTheSame2DRelaxed(double x1, double y1, double x2, double y2)
{
	bool result;

	if(compareDoublesRelaxed(calcDistanceBetweenTwoPoints2D(x1, y1, x2, y2), 0.0))
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}

#endif







/*
double getMatrixValue(mat* matx, int matrixCellABC, int vectorCellXYZ)
{
	if(matrixCellABC == MATRIX_VEC_A)
	{
		if(vectorCellXYZ == VECTOR_VAL_X)
		{
			return matx->a.x;
		}
		else if(vectorCellXYZ == VECTOR_VAL_Y)
		{
			return matx->a.y;
		}
		else if(vectorCellXYZ == VECTOR_VAL_Z)
		{
			return matx->a.z;
		}
	}
	else if(matrixCellABC == MATRIX_VEC_B)
	{
		if(vectorCellXYZ == VECTOR_VAL_X)
		{
			return matx->b.x;
		}
		else if(vectorCellXYZ == VECTOR_VAL_Y)
		{
			return matx->b.y;
		}
		else if(vectorCellXYZ == VECTOR_VAL_Z)
		{
			return matx->b.z;
		}
	}
	else if(matrixCellABC == MATRIX_VEC_C)
	{
		if(vectorCellXYZ == VECTOR_VAL_X)
		{
			return matx->c.x;
		}
		else if(vectorCellXYZ == VECTOR_VAL_Y)
		{
			return matx->c.y;
		}
		else if(vectorCellXYZ == VECTOR_VAL_Z)
		{
			return matx->c.z;
		}
	}
	return 0;
}
*/



