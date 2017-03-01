/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	The Mesh contains the info about how to render a mesh and also how to parse it from a file.
*/

#ifndef MESH_H
#define MESH_H

#include <vector>
#include "framework.h"
#include <map>
#include "Entity.h"

class Shader;

class Mesh
{
public:
	std::vector< Vector3 > vertices; //here we store the vertices
	std::vector< Vector3 > normals;	 //here we store the normals
	std::vector< Vector2 > uvs;	 //here we store the texture coordinates
	std::vector< Vector4 > colors;	 //here we store colors by vertex
	Vector3 center;
	Vector3 halfsize;

	/*Struct para almacenar en los archivos binarios*/
	struct meshValues {
		char info[4];
		int num_vertex;
		int num_normals;
		int num_uvs;
		Vector3 center;
		Vector3 halfsize;
		
	};

	unsigned int vertices_vbo_id;
	unsigned int normals_vbo_id;
	unsigned int uvs_vbo_id;
	unsigned int colors_vbo_id;

	Mesh();
	Mesh( const Mesh& m );
	~Mesh();

	void clear();
	void render(int primitive);
	void render(int primitive, Shader* sh);
	
	bool writeBinMESH(const char * filename);
	bool readBinMESH(const char * filename);

	void uploadToVRAM(); //store the mesh info in the GPU RAM so it renders faster

	void createPlane( float size );
	void createQuad(float center_x, float center_y, float w, float h, bool flip_uvs = false);
	bool createASEmesh(const char *);
	void shoot();

};

class MeshManager{

public:
	MeshManager() {};
	~MeshManager();

	static MeshManager * getInstance() {
		if (instance == NULL) instance = new MeshManager();
		return instance;
	};
	Mesh * getMesh(const char * meshName);
private:
	static MeshManager * instance;
	std::map<std::string, Mesh*> projectMeshes;
};
#endif