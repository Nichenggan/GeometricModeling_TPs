#pragma once

#include <stdio.h>
//#include <tchar.h>

class myVertex;
class myFace;
class myPoint3D;

class myHalfedge
{
public:
	myVertex *source; 
	myFace *adjacent_face; 
	myHalfedge *next;  
	myHalfedge *prev;  
	myHalfedge *twin;
	myPoint3D* edgePoint; //used for subdivision

	int index; //use as you wish.

	myHalfedge(void);
	void copy(myHalfedge *);
	~myHalfedge(void);
};