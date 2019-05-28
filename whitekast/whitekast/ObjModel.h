#pragma once

#include <string>
#include <vector>
#include <list>

#include <windows.h>
#include <gl/GL.h>
#include "Vec.h"
#include "Texture.h"


class ObjModel
{
private:

	class Vertex
	{
	public:
		int position;
		int normal;
		int texcoord;
	};

	class Face
	{
	public:
		std::list<Vertex> vertices;
	};

	class MaterialInfo
	{
	public:
		MaterialInfo();
		std::string name;
		Texture* texture;

		::Vec3f diffuse;
		::Vec3f ambient;
		::Vec3f specular;
	};

	class ObjGroup
	{
	public:
		std::string name;
		int materialIndex;
		std::list<Face> faces;
	};


	std::vector<::Vec3f>	vertices;
	std::vector<::Vec3f>	normals;
	std::vector<::Vec2f>	texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;

	void loadMaterialFile(const std::string &fileName, const std::string &dirName);

public:
	float radius;

	ObjModel();
	~ObjModel(void);

	void load(const std::string &filename);
	void draw();
};
