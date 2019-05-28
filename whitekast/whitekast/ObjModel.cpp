#define STB_IMAGE_IMPLEMENTATION

#include "ObjModel.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "stbi.h"


static std::string replace(std::string str, const std::string &toReplace, const std::string &replacement)
{
	size_t index = 0;
	while (true)
	{
		index = str.find(toReplace, index);
		if (index == std::string::npos)
			break;
		str.replace(index, toReplace.length(), replacement);
		++index;
	}
	return str;
}

static std::vector<std::string> split(std::string str, const std::string &seperator)
{
	std::vector<std::string> ret;
	size_t index;
	while (true)
	{
		index = str.find(seperator);
		if (index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index + 1);
	}
	ret.push_back(str);
	return ret;
}

static inline std::string toLower(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}

static inline std::string cleanLine(std::string line)
{
	line = replace(line, "\t", " ");
	while (line.find("  ") != std::string::npos)
		line = replace(line, "  ", " ");
	if (line == "")
		return "";
	if (line[0] == ' ')
		line = line.substr(1);
	if (line == "")
		return "";
	if (line[line.length() - 1] == ' ')
		line = line.substr(0, line.length() - 1);
	return line;
}


ObjModel::ObjModel()
{
	
}

ObjModel::~ObjModel(void)
{
}

void ObjModel::load(const std::string& fileName)
{
	Vec2f currentVec;
	Vec2f highestVec;
	Vec2f lowestVec;

	std::cout << "Loading " << fileName << std::endl;
	std::string dirName = fileName;
	if (dirName.rfind("/") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("/"));
	if (dirName.rfind("\\") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("\\"));
	if (fileName == dirName)
		dirName = "";


	std::ifstream pFile(fileName.c_str());

	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << fileName << std::endl;
		return;
	}


	ObjGroup* currentGroup = new ObjGroup();
	currentGroup->materialIndex = -1;


	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		line = cleanLine(line);
		if (line == "" || line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "v")
		{
			vertices.push_back(::Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));

			currentVec = Vec2f(static_cast<float>(atof(params[1].c_str())), static_cast<float>(atof(params[2].c_str())));
			if (currentVec.x > highestVec.x)
				highestVec = currentVec;
			if (currentVec.x < lowestVec.x)
				lowestVec = currentVec;

			printf("Highest %f:%f and Lowest %f:%f \n", highestVec.x, highestVec.y, lowestVec.x, lowestVec.y);
		}
		else if (params[0] == "vn")
			normals.push_back(::Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if (params[0] == "vt")
			texcoords.push_back(::Vec2f((float)atof(params[1].c_str()), (float)atof(params[2].c_str())));
		else if (params[0] == "f")
		{
			for (size_t ii = 4; ii <= params.size(); ii++)
			{
				Face face;

				for (size_t i = ii - 3; i < ii; i++)
				{
					Vertex vertex;
					std::vector<std::string> indices = split(params[i == (ii - 3) ? 1 : i], "/");
					if (indices.size() >= 1)
						vertex.position = atoi(indices[0].c_str()) - 1;
					if (indices.size() == 2)
						vertex.texcoord = atoi(indices[1].c_str()) - 1;
					if (indices.size() == 3)
					{
						if (indices[1] != "")
							vertex.texcoord = atoi(indices[1].c_str()) - 1;
						vertex.normal = atoi(indices[2].c_str()) - 1;
					}
					face.vertices.push_back(vertex);
				}
				currentGroup->faces.push_back(face);
			}
		}
		else if (params[0] == "s") {}
		else if (params[0] == "mtllib")
		{
			loadMaterialFile(dirName + "/" + params[1], dirName);
		}
		else if (params[0] == "usemtl")
		{
			if (currentGroup->faces.size() != 0)
				groups.push_back(currentGroup);
			currentGroup = new ObjGroup();
			currentGroup->materialIndex = -1;

			for (size_t i = 0; i < materials.size(); i++)
			{
				MaterialInfo* info = materials[i];
				if (info->name == params[1])
				{
					currentGroup->materialIndex = i;
					break;
				}
			}
			if (currentGroup->materialIndex == -1)
				std::cout << "Could not find material name " << params[1] << std::endl;
		}
	}
	radius = (highestVec.x - lowestVec.x);
	groups.push_back(currentGroup);
}


void ObjModel::draw()
{
	for (auto group : groups)
	{
		auto& material = materials[group->materialIndex];
		if (material->texture)
		{
			material->texture->bind();
			glEnable(GL_TEXTURE_2D);
			glColor3f(1, 1, 1);
		}
		else
		{
			glColor3fv(material->diffuse.v);
			glDisable(GL_TEXTURE_2D);
		}

		glBegin(GL_TRIANGLES);
		for (auto& face : group->faces)
		{
			for (auto& vertex : face.vertices)
			{
				::Vec3f& vec = vertices[vertex.position];
				::Vec2f& tex = texcoords[vertex.texcoord];
				glTexCoord2fv(tex.v); glVertex3fv(vec.v);
			}
		}
		glEnd();
	}
}

void ObjModel::loadMaterialFile(const std::string &fileName, const std::string &dirName)
{
	std::cout << "Loading " << fileName << std::endl;
	std::ifstream pFile(fileName.c_str());
	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << fileName << std::endl;
		return;
	}

	MaterialInfo* currentMaterial = NULL;

	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		line = cleanLine(line);
		if (line == "" || line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (
			params[0] == "illum" ||
			params[0] == "map_bump" ||
			params[0] == "map_ke" ||
			params[0] == "map_ka" ||
			params[0] == "map_d" ||
			params[0] == "d" ||
			params[0] == "ke" ||
			params[0] == "ns" ||
			params[0] == "ni" ||
			params[0] == "td" ||
			params[0] == "tf" ||
			params[0] == "tr" ||
			false) {	}
		else if (params[0] == "newmtl")
		{
			if (currentMaterial != NULL)
			{
				materials.push_back(currentMaterial);
			}
			currentMaterial = new MaterialInfo();
			currentMaterial->name = params[1];
		}
		else if (params[0] == "map_kd")
		{
			std::string tex = params[1];
			if (tex.find("/"))
				tex = tex.substr(tex.rfind("/") + 1);
			if (tex.find("\\"))
				tex = tex.substr(tex.rfind("\\") + 1);

			currentMaterial->texture = new Texture(dirName + "/" + tex);
		}
		else if (params[0] == "kd")
		{
			currentMaterial->diffuse.x = (float)atof(params[1].c_str());
			currentMaterial->diffuse.y = (float)atof(params[2].c_str());
			currentMaterial->diffuse.z = (float)atof(params[3].c_str());
		}
		else if (params[0] == "ka")
		{
			currentMaterial->ambient.x = (float)atof(params[1].c_str());
			currentMaterial->ambient.y = (float)atof(params[2].c_str());
			currentMaterial->ambient.z = (float)atof(params[3].c_str());
		}
		else if (params[0] == "ks")
		{
			currentMaterial->specular.x = (float)atof(params[1].c_str());
			currentMaterial->specular.y = (float)atof(params[2].c_str());
			currentMaterial->specular.z = (float)atof(params[3].c_str());
		}
		else
			std::cout << "Didn't parse " << params[0] << " in material file" << std::endl;
	}
	if (currentMaterial != NULL)
		materials.push_back(currentMaterial);

}

ObjModel::MaterialInfo::MaterialInfo()
{
	texture = NULL;
}
