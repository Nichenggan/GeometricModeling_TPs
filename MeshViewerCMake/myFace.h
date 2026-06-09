#pragma once

class myHalfedge;
class myVector3D;
class myPoint3D;

class myFace
{
public:
	myHalfedge *adjacent_halfedge;

	myVector3D *normal;

	int index; //use this variable as you wish.
	myPoint3D* facePoint;
	void computeNormal();
	myFace(void);
	~myFace(void);
};