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
		if (!originof) return;
		myHalfedge *h = originof;
		myHalfedge *step = h;
		normal->clear();
		int counter = 0;

		do {
			if (step->adjacent_face && step->adjacent_face->normal) {
				normal->dX += step->adjacent_face->normal->dX;
				normal->dY += step->adjacent_face->normal->dY;
				normal->dZ += step->adjacent_face->normal->dZ;
				counter++;
			}
			if (!step->twin) break;  // to fix some obj issues
			step = step->twin->next;
			if (!step) break;
		} while (step != h);

		if (counter == 0) return;
		normal->dX /= counter;
		normal->dY /= counter;
		normal->dZ /= counter;
		normal->normalize();
}


