#include "myFace.h"
#include "myVector3D.h"
#include "myHalfedge.h"
#include "myVertex.h"
#include <GL/glew.h>

myFace::myFace(void)
{
	adjacent_halfedge = NULL;
	normal = new myVector3D(1.0, 1.0, 1.0);
}

myFace::~myFace(void)
{
	if (normal) delete normal;
}

void myFace::computeNormal()
{
	// myPoint3D* p1;
	// myPoint3D* p2;
	// myPoint3D* p3;
	// p1 = adjacent_halfedge->source->point;
	// p2 = adjacent_halfedge->next->source->point;
	// p3 = adjacent_halfedge->next->next->source->point;
	// normal->setNormal(p1, p2, p3);

	// I changed the normal computation method to Newell's Method, asked AI for help
	//because the original method will not show correct normal for gear

	double nx = 0.0;
	double ny = 0.0;
	double nz = 0.0;

	myHalfedge *curr = adjacent_halfedge;

	do {
		myPoint3D* currP = curr->source->point;
		myPoint3D* nextP = curr->next->source->point;

		nx += (currP->Y - nextP->Y) * (currP->Z + nextP->Z);
		ny += (currP->Z - nextP->Z) * (currP->X + nextP->X);
		nz += (currP->X - nextP->X) * (currP->Y + nextP->Y);

		curr = curr->next;
	} while (curr != adjacent_halfedge);

	normal->dX = nx;
	normal->dY = ny;
	normal->dZ = nz;
	normal->normalize();
}
