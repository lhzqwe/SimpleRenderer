#pragma once
#include "CommonLib.h"

class Vertex;

class Model
{	
public:
	Model();
	~Model();

public:
	void Load(string file_name);

private:
	vector<Vertex> m_VertexList;
};

