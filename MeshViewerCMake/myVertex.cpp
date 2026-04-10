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
	if (point) delete point;
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
	// myHalfedge *h = originof;
	// myVector3D v1, v2;
	// v1.dX = h->source->point->X - h->next->source->point->X;
	// v1.dY = h->source->point->Y - h->next->source->point->Y;
	// v1.dZ = h->source->point->Z - h->next->source->point->Z;
	//
	// h = h->next;
	// v2.dX = h->source->point->X - h->next->source->point->X;
	// v2.dY = h->source->point->Y - h->next->source->point->Y;
	// v2.dZ = h->source->point->Z - h->next->source->point->Z;
	//
	// normal->crossproduct(v1, v2);
	// normal->normalize();
}
