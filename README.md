# Mesh Viewer Project
===================

This is my mesh viewer project using a half-edge data structure.
The main work is in `myMesh`, may modify other files.
Wroted this Readme with the help of ChatGPT.

## Implemented goals
-----------------

### 1. readFile

I completed OBJ file reading in `myMesh::readFile`.

- It reads vertex lines and face lines from `.obj` files.
- It creates vertices, faces, and half-edges.
- It connects `next`, `prev`, `twin`, `source`, and `adjacent_face` pointers.
- It also normalizes the mesh after loading when the mesh has faces.

### 2. Compute normals

I completed normal computation for faces and vertices.

- Face normals are computed with Newell's method, so it works better for polygon faces.
- Vertex normals are computed by averaging the normals of adjacent faces.
- These normals are used for smooth shading and for drawing normal lines.

### 3. Silhouette

I completed silhouette drawing.

- The program checks each edge and compares the two adjacent face normals with the camera direction.
- If one face is front-facing and the other is back-facing, the edge is drawn as a silhouette edge.
- The silhouette is drawn in red and thicker than the normal wireframe.

### 4. Triangulation

I completed triangulation using the ear clipping algorithm.

- Basic case: convex polygon faces are triangulated.
- Advanced case: concave polygon faces are triangulated.
- Expert case: polygons with holes were also tested and completed.
- The method cuts one ear at a time and updates the half-edge structure after each cut.

### 5. Half-edge data structure tests

I completed tests for the half-edge structure in `checkMesh`.

The tests check:

- every half-edge has a twin when expected;
- twin links are symmetric;
- `next` and `prev` links are consistent;
- every half-edge has a face;
- every half-edge has a source vertex;
- twin directions are correct;
- face loops are closed.

These tests helped me find problems after reading files, triangulation, revolution, and simplification.

### 6. Surface of revolution

I completed surface of revolution.

- It starts from a profile mesh with vertices and no faces.
- The profile is rotated around the Y axis.
- I used 10 rotation steps.
- The side surface is made with triangles.
- The top and bottom caps are added and triangulated.
- The result is stored again as a half-edge mesh.

### 7. Mesh simplification

I completed mesh simplification using shortest edge collapse.

- The mesh is triangulated first.
- All edges are sorted by length.
- The shortest valid edge is collapsed first.
- The new vertex position is the midpoint of the collapsed edge.
- The method removes vertices, faces, and half-edges and then updates the structure.
- The target is to remove 20% of the vertices.

### 8. Catmull-Clark mesh subdivision

I completed the Catmull-Clark subdivision part as a simplified version.

- A face point is computed as the average of all vertices of the face.
- An edge point is computed as the it's the average of the two vertices and the two adjacent face points
- New vertex positions are created using the surrounding face points and edge information.
- The final step is to rebuild the mesh into quad faces after subdivision.


## Tested files
------------

I tested the project with several OBJ files in the folder, for example:

- `cube.obj`
- `c_gear.obj`
- `hand.obj`
- `octogon.obj`
- `truncated_cuboctahedron.obj`



