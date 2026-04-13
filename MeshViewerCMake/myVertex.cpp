#include "myVertex.h"
#include "myVector3D.h"
#include "myHalfedge.h"
#include "myFace.h"

myVertex::myVertex(void)
{
	point = NULL;
	originof = NULL;
	normal = new myVector3D(1.0,1.0,1.0);
}

myVertex::~myVertex(void)
{
	if (normal) delete normal;
}


void myVertex::computeNormal()
{
	myHalfedge *h = originof;
	myHalfedge *step = h;
	normal->clear();
	int counter = 0;
	do {
		myVector3D* fn = step -> adjacent_face -> normal;
		normal -> dX += fn -> dX;
		normal -> dY += fn -> dY;
		normal -> dZ += fn -> dZ;
		counter++;
		step = step -> twin -> next;
	} while (h != step);
	normal->dX /= counter;
	normal->dY /= counter;
	normal->dZ /= counter;
	normal->normalize();
}
