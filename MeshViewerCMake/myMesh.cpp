#include "myMesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <utility>
#include <GL/glew.h>
#include "myVector3D.h"
#include <set>

using namespace std;

myMesh::myMesh(void)
{
	/**** TODO ****/
}


myMesh::~myMesh(void)
{
	/**** TODO ****/
	clear();
}

void myMesh::clear()
{
	for (unsigned int i = 0; i < vertices.size(); i++) if (vertices[i]) delete vertices[i];
	for (unsigned int i = 0; i < halfedges.size(); i++) if (halfedges[i]) delete halfedges[i];
	for (unsigned int i = 0; i < faces.size(); i++) if (faces[i]) delete faces[i];

	vector<myVertex *> empty_vertices;    vertices.swap(empty_vertices);
	vector<myHalfedge *> empty_halfedges; halfedges.swap(empty_halfedges);
	vector<myFace *> empty_faces;         faces.swap(empty_faces);
}

void myMesh::checkMesh()
{
	vector<myHalfedge *>::iterator it;
	for (it = halfedges.begin(); it != halfedges.end(); it++)
	{
		if ((*it)->twin == NULL)
			break;
	}
	if (it != halfedges.end())
		cout << "Error! Not all edges have their twins!\n";
	else cout << "Each edge has a twin!\n";
}


bool myMesh::readFile(std::string filename)
{
	string s, t, u;
	vector<int> faceids;
	myHalfedge **hedges;

	ifstream fin(filename);
	if (!fin.is_open()) {
		cout << "Unable to open file!\n";
		return false;
	}
	name = filename;

	map<pair<int, int>, myHalfedge *> twin_map;
	map<pair<int, int>, myHalfedge *>::iterator it;

	while (getline(fin, s))
	{
		stringstream myline(s);
		t = "";
		myline >> t;
		if (t == "g") {}
		else if (t == "v")
		{
			float x, y, z;
			myline >> x >> y >> z;
			myPoint3D *p = new myPoint3D(x, y, z);
			myVertex *v = new myVertex();
			v->point = p;
			vertices.push_back(v);
		}
		else if (t == "mtllib") {}
		else if (t == "usemtl") {}
		else if (t == "s") {}
		else if (t == "f")
		{
			myFace *f = new myFace();
			faceids.clear();
			while (myline >> u) {
				int v_idx = atoi((u.substr(0, u.find("/"))).c_str());
					faceids.push_back(v_idx - 1);
			}
			hedges = new myHalfedge*[faceids.size()];
			for (unsigned int i = 0; i < faceids.size(); i++) {
				int v_start = faceids[i];
				int v_end = faceids[(i + 1) % faceids.size()];

				myHalfedge *e = new myHalfedge();
				hedges[i] = e;
				e->source = vertices[faceids[i]];
				vertices[faceids[i]]->originof = e;
				e->adjacent_face = f;
				halfedges.push_back(e);

				it = twin_map.find(make_pair(v_end, v_start));
				if (it != twin_map.end()) {
					myHalfedge *twin_e = it->second;
					e->twin = twin_e;
					twin_e->twin = e;
				}else {
					pair<int, int> my_key(v_start, v_end);
					twin_map[my_key] = e;
				} //used AI on this part to know how to use map to find twin edge, and it works!
			}
			for (unsigned int i = 0; i < faceids.size(); i++) {
				hedges[i]->next = hedges[(i + 1) % faceids.size()];
				hedges[(i + 1) % faceids.size()]->prev = hedges[i];
			}
			f->adjacent_halfedge = hedges[0];//Reminder:do not use faceid[0] to access vertex
			faces.push_back(f);
			delete[] hedges;
		}
	}

	checkMesh();
	normalize();

	return true;
}


void myMesh::computeNormals()
{
	for (unsigned int i = 0; i < faces.size(); ++i) {
		myFace *f = faces[i];
		if (f && f->adjacent_halfedge) f->computeNormal();
	}

	for (unsigned int i = 0; i < vertices.size(); ++i) {
		myVertex *v = vertices[i];
		if (v && v->originof) v->computeNormal();
	}
}

void myMesh::normalize()
{
	if (vertices.size() < 1) return;

	int tmpxmin = 0, tmpymin = 0, tmpzmin = 0, tmpxmax = 0, tmpymax = 0, tmpzmax = 0;

	for (unsigned int i = 0; i < vertices.size(); i++) {
		if (vertices[i]->point->X < vertices[tmpxmin]->point->X) tmpxmin = i;
		if (vertices[i]->point->X > vertices[tmpxmax]->point->X) tmpxmax = i;

		if (vertices[i]->point->Y < vertices[tmpymin]->point->Y) tmpymin = i;
		if (vertices[i]->point->Y > vertices[tmpymax]->point->Y) tmpymax = i;

		if (vertices[i]->point->Z < vertices[tmpzmin]->point->Z) tmpzmin = i;
		if (vertices[i]->point->Z > vertices[tmpzmax]->point->Z) tmpzmax = i;
	}

	double xmin = vertices[tmpxmin]->point->X, xmax = vertices[tmpxmax]->point->X,
		ymin = vertices[tmpymin]->point->Y, ymax = vertices[tmpymax]->point->Y,
		zmin = vertices[tmpzmin]->point->Z, zmax = vertices[tmpzmax]->point->Z;

	double scale = (xmax - xmin) > (ymax - ymin) ? (xmax - xmin) : (ymax - ymin);
	scale = scale > (zmax - zmin) ? scale : (zmax - zmin);

	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i]->point->X -= (xmax + xmin) / 2;
		vertices[i]->point->Y -= (ymax + ymin) / 2;
		vertices[i]->point->Z -= (zmax + zmin) / 2;

		vertices[i]->point->X /= scale;
		vertices[i]->point->Y /= scale;
		vertices[i]->point->Z /= scale;
	}
}


void myMesh::splitFaceTRIS(myFace *f, myPoint3D *p)
{
	/**** TODO ****/
}

void myMesh::splitEdge(myHalfedge *e1, myPoint3D *p)
{

	/**** TODO ****/
}

void myMesh::splitFaceQUADS(myFace *f, myPoint3D *p)
{
	/**** TODO ****/
}


void myMesh::subdivisionCatmullClark()
{
	/**** TODO ****/
}

void myMesh::simplify()
{
	/**** TODO ****/
}

void myMesh::simplify(myVertex *)
{
	/**** TODO ****/
}

void myMesh::triangulate()
{
	size_t originalFaceCount = faces.size();
	for (size_t i = 0; i < originalFaceCount; ++i) {
		triangulate(faces[i]);
	}
	computeNormals();
}

bool ifPointContainTriangle(myPoint3D* p1, myPoint3D* p2, myPoint3D* p3, myPoint3D* p) {
	if (!p1 || !p2 || !p3 || !p) return false;

	// Build edge vectors and point vectors
	myVector3D vAB = (*p2) - (*p1);
	myVector3D vAP = (*p) - (*p1);

	myVector3D vBC = (*p3) - (*p2);
	myVector3D vBP = (*p) - (*p2);

	myVector3D vCA = (*p1) - (*p3);
	myVector3D vCP = (*p) - (*p3);

	// Cross products for each edge with the vector to point
	myVector3D c1 = vAB.crossproduct(vAP);
	myVector3D c2 = vBC.crossproduct(vBP);
	myVector3D c3 = vCA.crossproduct(vCP);


	// Check that all cross products point to the same general direction:
	// dot products between them should be non-negative.
	double d12 = c1 * c2;
	double d13 = c1 * c3;
	double d23 = c2 * c3;

	return (d12 >= 0) && (d13 >= 0) && (d23 >= 0);
}

bool ifContainTriangle(myPoint3D* p1, myPoint3D* p2, myPoint3D* p3, const std::set<myVertex*>& vertices) {
	for (const myVertex* v : vertices) {
		if (!v || !v->point) continue;
		// skip the triangle's own vertices
		if (v->point == p1 || v->point == p2 || v->point == p3) continue;

		if (ifPointContainTriangle(p1, p2, p3, v->point)) {
			return true;
		}
	}
	return false;
}

bool ifPointsConvex(myPoint3D* p1, myPoint3D* p2, myPoint3D* p3, myVector3D* normal) {

	myVector3D v12 = (*p2) - (*p1);
	myVector3D v23 = (*p3) - (*p2);

	myVector3D cross = v12.crossproduct(v23);
	double product = cross * *normal;
	return product > 0;
}


//return false if already triangle, true othewise.
bool myMesh::triangulate(myFace *f)
{
	/**** keep existing triangulation logic ****/

	// Compute face normal BEFORE triangulating (needed for convexity check)
	f->computeNormal();

	// Set the Vertex set
	bool isCut = false;
	std::set<myVertex*> vertexSet;
	myHalfedge *curr = f->adjacent_halfedge;
	do {
		vertexSet.insert(curr->source);
		curr = curr->next;
	} while(curr != f->adjacent_halfedge);
	if (vertexSet.size() == 3) return false;


	myHalfedge *e1 = f->adjacent_halfedge;
	myHalfedge *e2 = e1->next;
	myHalfedge *e3 = e2->next;
	int totalIter = 0;
	int maxTotalIter = (int)vertexSet.size() * (int)vertexSet.size() * 4;
	while (vertexSet.size() >= 3) {
		// reset cut flag for this iteration
		isCut = false;
		if (!ifContainTriangle(e1->source->point, e2->source->point, e3->source->point, vertexSet) && vertexSet.find(e2->source) != vertexSet.end()) {
			// Split the face into two faces by edge e1->e3
			if (ifPointsConvex(e1->source->point, e2->source->point, e3->source->point, f->normal)) {
				if (vertexSet.size() == 3) {
				    //last triangle, just close the loop and assign face
				    e1->next = e2;
				    e2->prev = e1;
				    e2->next = e3;
				    e3->prev = e2;
				    e3->next = e1;
				    e1->prev = e3;

				    e1->adjacent_face = f;
				    e2->adjacent_face = f;
				    e3->adjacent_face = f;

				    f->adjacent_halfedge = e1;

				    vertexSet.clear();
				}
				else {
				    myHalfedge *e_prev = e1->prev;

				    myFace *newFace = new myFace();
				    myHalfedge *newEdge = new myHalfedge();
				    myHalfedge *newEdgeTwin = new myHalfedge();


				    newEdge->source = e3->source;
				    newEdgeTwin->source = e1->source;
				    newEdge->twin = newEdgeTwin;
				    newEdgeTwin->twin = newEdge;

				    newEdge->adjacent_face = newFace;
				    e1->adjacent_face = newFace;
				    e2->adjacent_face = newFace;

				    e1->next = e2;
				    e2->prev = e1;
				    e2->next = newEdge;
				    newEdge->prev = e2;
				    newEdge->next = e1;
				    e1->prev = newEdge;

				    newFace->adjacent_halfedge = e1;
				    newEdgeTwin->adjacent_face = f;

				    e_prev->next = newEdgeTwin;
				    newEdgeTwin->prev = e_prev;

				    newEdgeTwin->next = e3;
				    e3->prev = newEdgeTwin;

				    f->adjacent_halfedge = newEdgeTwin;


				    faces.push_back(newFace);
				    halfedges.push_back(newEdge);
				    halfedges.push_back(newEdgeTwin);

				    vertexSet.erase(e2->source);


				    e1 = newEdgeTwin;
				    e2 = e1->next;
				    e3 = e2->next;
					isCut = true;
				}
			}
		}
		if(!isCut) {
			e1 = e1->next;
			e2 = e2->next;
			e3 = e3->next;
			totalIter++;
			if (totalIter > maxTotalIter) {
				cout << "Warning: triangulation gave up on a face (likely non-planar or degenerate)." << endl;
				break;
			}
		}

	}
	// If we reached here the face has been (or attempted to be) triangulated
	return true;
}

