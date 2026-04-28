#pragma once
#include "myFace.h"
#include "myHalfedge.h"
#include "myVertex.h"
#include <vector>
#include <string>
#include <map>
#include <set>

// the struct to store edge record for edge collapse
struct EdgeRecord {
	myHalfedge* he;
	double length;
	std::multiset<EdgeRecord>::iterator set_it;

	// must implement this operator to use EdgeRecord in a multiset
	bool operator<(const EdgeRecord& other) const {
		return length < other.length;
	}
};

class myMesh
{
public:
	std::vector<myVertex *> vertices;
	std::vector<myHalfedge *> halfedges;
	std::vector<myFace *> faces;
	std::string name;

	void checkMesh();
	bool readFile(std::string filename);
	void computeNormals();
	void normalize();

	void subdivisionCatmullClark();
	void Revolution();

	void splitFaceTRIS(myFace *, myPoint3D *);

	void splitEdge(myHalfedge *, myPoint3D *);
	void splitFaceQUADS(myFace *, myPoint3D *);

	void triangulate();
	bool triangulate(myFace *);
	void simplify();
	void simplify(myVertex *);
	void clear();

	myHalfedge* RevolutionMakeHE(int src_i, int dst_i, std::map<std::pair<int,int>, myHalfedge*> &twin_map);
	void RevolutionMakeFace(myHalfedge *ea, myHalfedge *eb, myHalfedge *ec);

	myMesh(void);
	~myMesh(void);
};

