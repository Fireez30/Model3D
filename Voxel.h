#ifndef VOXEL_H
#define VOXEL_H

#include <math.h>
#include <stdio.h>      
#include <stdlib.h>  
#include <vector> 
#include "Point.h"
#include <GL/glut.h>


class Voxel {

private:

    Point* ct;
    double l;
    std::vector<Point>* cornerPoints;
    std::vector<Point>* subCenterPoints;

public:

	Voxel();
	~Voxel();
	Voxel(Point* c, double length);

	Point* getCenter();
	double getLength();
	std::vector<Point>* getCornerPoints();
	std::vector<Point>* getSubCenterPoints();

	void tracePoint(Point *A,Vector color);
	void traceQuad(Point* A, Point* B,Point* C,Point* D, Vector color);

	void displayV();
	void computeDivision();	
	void computeCornerPoints();
	void displayDivision();	
	int isInsideSphere(Point* cts, double ray);
};

#endif